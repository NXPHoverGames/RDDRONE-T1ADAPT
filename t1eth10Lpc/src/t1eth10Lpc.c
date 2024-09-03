/*
 * Copyright 2020, 2024 NXP 
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
===============================================================================
 Author      : Han Raaijmakers
 Description : main definition
===============================================================================
*/

#include "LPC8xx.h"
#include "lpc8xx_uart.h"
#include "lpc8xx_gpio.h"
#include "stdio.h"
#include "string.h"
#include "connection.h"
#include "ethernetControl.h"

// #define UARTLOG
#define AUTOCONFIG

#define WELCOM_MESS       "Automotive media converter\r\n"
#define UNKNOWN_TJA       "ERROR: Did not recognize TJA1101\r\n"
#define UNKNOWN_LAN       "ERROR: Did not recognize BCM5241\r\n"
#define TJA_RESET_ERR     "ERROR: TJA1101 not reset correctly\r\n"
#define TJA_NOT_STBY      "ERROR: TJA1101 not in standby mode\r\n"
#define TJA_MASTER_MODE   "TJA1101 Master mode\r\n"
#define TJA_SLAVE_MODE    "TJA1101 Slave mode\r\n"
#define REINIT_LAN        "BCM5241 re-init\r\n"
#define REINIT_TJA        "TJA1101 re-init\r\n"
#define OK_LAN            "BCM5241 con OK\r\n"
#define OK_TJA            "TJA1101 con OK\r\n"
#define FAIL_LAN          "BCM5241 con FAIL\r\n"
#define FAIL_TJA          "TJA1101 con FAIL\r\n"
#define INIT_DONE_OK      "Initialization done OK\r\n"

void SwitchMatrix_Init();
void IOCON_Init();
extern int master_switch;

void init_tja(void)
{
	uint16_t val;

	mdio_write(TJA, TJA1101_PHY, SMI_CNTRL, SMI_0_RESET);       // send reset to TJA1101
	val = mdio_read(TJA, TJA1101_PHY, SMI_CNTRL);
	if (!(((val & SMI_0_SPD_MASK) == SMI_0_SPD_100) && (val & SMI_0_DUPLEX))) {
		UARTSend(LPC_USART0, (uint8_t *) TJA_RESET_ERR, strlen(TJA_RESET_ERR));
	}
	val = mdio_read(TJA, TJA1101_PHY, SMI_INT_SRC_TJA); // read interrupt source
	val = mdio_read(TJA, TJA1101_PHY, SMI_INT_SRC_TJA); // read interrupt source
	val = mdio_read(TJA, TJA1101_PHY, SMI_INT_SRC_TJA); // read interrupt source

	mdio_write(TJA, TJA1101_PHY, SMI_EXT_CNTRL, SMI_17_CONFIG_EN);  // select mode TJA1101

	// configure
	if (master_switch) {
		// slave mode
		   mdio_write(TJA, TJA1101_PHY, SMI_CONFIG1, (SMI_18_REV_MII | (1 << 7)));
		   UARTSend(LPC_USART0, (uint8_t *) TJA_SLAVE_MODE, strlen(TJA_SLAVE_MODE));
	} else {
		// master mode
		   mdio_write(TJA, TJA1101_PHY, SMI_CONFIG1, (SMI_18_MASTER | SMI_18_REV_MII | (1 << 7)));
		   UARTSend(LPC_USART0, (uint8_t *) TJA_MASTER_MODE, strlen(TJA_MASTER_MODE));
	}
	val = mdio_read(TJA, TJA1101_PHY, SMI_CONFIG1);

	mdio_write(TJA, TJA1101_PHY, SMI_COM_CONF, (1 << 15));  // fix TJA1101
	mdio_write(TJA, TJA1101_PHY, SMI_LINK_FAIL, (1 << 15));  // fix TJA1101

	delay(80);  // delay about 10 ms

	mdio_write(TJA, TJA1101_PHY, SMI_EXT_CNTRL, (SMI_17_LINK_CNTRL | SMI_17_NORMAL));  // select normal mode TJA1101
	val = mdio_read(TJA, TJA1101_PHY, SMI_EXT_CNTRL);
}

void init_bcm(void)
{
	uint16_t val, bcmBase;

	mdio_write(BCM, BCM5241_PHY, SMI_CNTRL, SMI_L0_RESET);   // send reset to BCM5241
	delay(8000);  // delay about 1000 ms

	val = mdio_read(BCM, BCM5241_PHY, SMI_INTREG);                        // read interrupts
    mdio_write(BCM, BCM5241_PHY, SMI_INTREG, 0xF00);                      // mask interrupts

	bcmBase = mdio_read(BCM, BCM5241_PHY, SMI_PHY_CNTRL);                             // read shadow
    mdio_write(BCM, BCM5241_PHY, SMI_PHY_CNTRL, (bcmBase | SMI_L31_BCM_ENSHA));       // enable shadow

    val = mdio_read(BCM, BCM5241_PHY, SMI_AUTO_MDIX);
    mdio_write(BCM, BCM5241_PHY, SMI_AUTO_MDIX, (val | SMI_L16_AUTOMDIX));        // select auto MDIX

    val = mdio_read(BCM, BCM5241_PHY, SMI_MODE_CNTRL);
    mdio_write(BCM, BCM5241_PHY, SMI_MODE_CNTRL, (val | SMI_L17_APDE));           // select auto power down

    mdio_write(BCM, BCM5241_PHY, SMI_PHY_CNTRL, bcmBase);                       // disable shadow

	val = mdio_read(BCM, BCM5241_PHY, SMI_CNTRL);
    mdio_write(BCM, BCM5241_PHY, SMI_CNTRL, (val | SMI_L0_AUTONEG));  // select auto negotiation

    val = mdio_read(BCM, BCM5241_PHY, SMI_CNTRL);
}

int smi_init(void)
{
	uint16_t name;
	int      okCnt = 0; //, i;

	// initialise both PHYs
	GPIOSetBitValue( PORTNUM, TJA_EN_POS,    1);        // VBAT OFF
	delay(8000);                                      // delay about 100 ms
	reset_phy();
	delay(800);                                       // delay about 100 ms

	name = mdio_read(TJA, TJA1101_PHY, SMI_PHY_ID1);
	if (name == 0xFFFF) {
		// retry once
		name = mdio_read(TJA, TJA1101_PHY, SMI_PHY_ID1);
	}
	if (name != SMI_2_TJA1101) {
		UARTSend(LPC_USART0, (uint8_t *) UNKNOWN_TJA, strlen(UNKNOWN_TJA));
	} else {
		okCnt++;
		name = mdio_read(TJA, TJA1101_PHY, SMI_PHY_ID2);  // 0xDC40 for RMA1, 0xDC60 for RMA2, 0xDC41 for RMA4 -> we don't care here!
	}
	name = mdio_read(BCM, BCM5241_PHY, SMI_PHY_ID1);
	if (name == 0xFFFF) {
		// retry once
		name = mdio_read(BCM, BCM5241_PHY, SMI_PHY_ID1);
	}
	if (name != SMI_2_BCM5241) {
		UARTSend(LPC_USART0, (uint8_t *) UNKNOWN_LAN, strlen(UNKNOWN_LAN));
	} else {
		okCnt++;
		name = mdio_read(BCM, BCM5241_PHY, SMI_PHY_ID2);  // 0xC0C4
		init_bcm();
	}
	// if okCnt == 2 we know both PHYs are there

	init_tja();

	return okCnt;
}

int main(void)
{
	int okCnt, retry, lretry, msearch;
	uint16_t val, valext;
	char line[80];

	GPIOInit();             // driver init

	IOCON_Init();           // defined by switch matrix tool

	SwitchMatrix_Init();    // defined by switch matrix tool

	GPIOSetDir( PORTNUM,      MDC_POS, PORT_OUT );
	GPIOSetDir( PORTNUM,     MDIO_TJA_POS,  PORT_IN ); // changed by driver routines
	GPIOSetDir( PORTNUM,     MDIO_BCM_POS,  PORT_IN ); // changed by driver routines
	GPIOSetDir( PORTNUM, nRST_PHY_TJA_POS, PORT_OUT );
	GPIOSetDir( PORTNUM, nRST_PHY_BCM_POS, PORT_OUT );

	GPIOSetDir( PORTNUM,  LED_BLUE_POS, PORT_OUT );
	GPIOSetDir( PORTNUM,   LED_RED_POS, PORT_OUT );
	GPIOSetDir( PORTNUM,    TJA_EN_POS, PORT_OUT );
	GPIOSetBitValue( PORTNUM, TJA_EN_POS,       0);

	// both LEDs on to start with (LED test)
	GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 0);     // signal BLUE LED
	GPIOSetBitValue( PORTNUM, LED_RED_POS, 0);      // signal RED LED

	// Uart Init
	UARTInit(LPC_USART0, 115200);
	UARTSend(LPC_USART0, (uint8_t *) WELCOM_MESS, strlen(WELCOM_MESS));

	// both LEDs on to start with (LED test)
	GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 1);     // signal BLUE LED
	GPIOSetBitValue( PORTNUM,  LED_RED_POS, 1);      // signal RED LED

	msearch = 0;
	retry   = 4;
	okCnt   = smi_init();
	while (retry-- && (okCnt != 2)) {
	  okCnt = smi_init();
	  delay(3000);  // delay about 100 ms
	}
	if (okCnt == 2) {
		UARTSend(LPC_USART0, (uint8_t *) INIT_DONE_OK, strlen(INIT_DONE_OK));
		// OK condition
		GPIOSetBitValue( PORTNUM, LED_RED_POS, 1);      // signal RED LED OFF
		GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 0);     // signal BLUE LED
	} else {
		// FALSE condition
		GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 1);     // signal BLUE LED OFF
		GPIOSetBitValue( PORTNUM, LED_RED_POS, 0);      // signal RED LED
	}
	retry  = 20; // TJA retry
	lretry = 20; // BCM retry
	while (1) {
#ifdef UARTLOG
      val = mdio_read(BCM, BCM5241_PHY, SMI_CNTRL);         // reg  0: 0x1100
	  sprintf(line, "BCM5241.0  = 0x%04X\r\n", val);
	  UARTSend(LPC_USART0, (uint8_t *) line, strlen(line));
#endif
	  val = mdio_read(BCM, BCM5241_PHY, SMI_STATUS);        // reg  1: 0x782D
#ifdef UARTLOG
	  sprintf(line, "BCM5241.1  = 0x%04X\r\n", val);
	  UARTSend(LPC_USART0, (uint8_t *) line, strlen(line));
#endif
	  if ((val & SMI_1_LINK_STAT) == SMI_1_LINK_STAT) {
		  // link up
		  UARTSend(LPC_USART0, (uint8_t *) OK_LAN, strlen(OK_LAN));
		  GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 0);    // signal BLUE LED
		  lretry = 20;
	  } else {
		  lretry--;
		  if (lretry <= 0) {
			  lretry = 20;
		  UARTSend(LPC_USART0, (uint8_t *) REINIT_LAN, strlen(REINIT_LAN));
		  init_bcm();
		  }
		  UARTSend(LPC_USART0, (uint8_t *) FAIL_LAN, strlen(FAIL_LAN));
		  GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 1);    // signal BLUE LED OFF
	  }
	  val = mdio_read(TJA, TJA1101_PHY, SMI_STATUS);
#ifdef UARTLOG
	  sprintf(line, "TJA1101.1  = 0x%04X %s\r\n", val, (val & 4) ? "UP" : "DOWN");
	  UARTSend(LPC_USART0, (uint8_t *) line, strlen(line));
#endif
	  GPIOSetBitValue( PORTNUM, LED_RED_POS, 0);      // signal RED LED
      delay(1000);
	  GPIOSetBitValue( PORTNUM, LED_RED_POS, 1);      // signal RED LED OFF
	  delay(4000);
	  valext = mdio_read(TJA, TJA1101_PHY, SMI_COMM_STAT);
#ifdef UARTLOG
	  sprintf(line, "TJA1101.23 = 0x%04X\r\n", valext);
	  UARTSend(LPC_USART0, (uint8_t *) line, strlen(line));

	  val2 = mdio_read(TJA, TJA1101_PHY, SMI_GEN_STAT);
	  sprintf(line, "TJA1101.24 = 0x%04X\r\n", val2);
	  UARTSend(LPC_USART0, (uint8_t *) line, strlen(line));
	  if (val2 & 0x8000) {
		  // interrupt pending
		  val2 = mdio_read(TJA, TJA1101_PHY, SMI_INT_SRC_TJA); // read interrupt source
		  sprintf(line, "TJA1101.21 = 0x%04X\r\n", val2);
		  UARTSend(LPC_USART0, (uint8_t *) line, strlen(line));
	  }
#endif
	  if ((valext & 0xBCC0) != 0xBCC0) {
//	  if ((val & SMI_1_LINK_STAT) != SMI_1_LINK_STAT) {
		  // link down
		    UARTSend(LPC_USART0, (uint8_t *) FAIL_TJA, strlen(FAIL_TJA));
			snprintf(line, 79, "TJA1101.23 = 0x%04X\r\n", valext);
			UARTSend(LPC_USART0, (uint8_t *) line, strlen(line));
			GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 1);    // signal BLUE LED OFF
			retry--;
			if (retry <= 0) {
				msearch++;
				if (msearch > 10) {
					msearch = 0;
				}
				retry = 20 + msearch; // make sure we don't lockup with equal delay
			    UARTSend(LPC_USART0, (uint8_t *) REINIT_TJA, strlen(REINIT_TJA));
			    if (master_switch) {
			    	// check as master now
			    	master_switch = 0;
			    } else {
			    	// check as slave now
			    	master_switch = 1;
			    }
			    // TODO switch master/slave
				init_tja();
			}
	  } else {
		  retry = 20;
		  UARTSend(LPC_USART0, (uint8_t *) OK_TJA, strlen(OK_TJA));
		  if (master_switch) {
			  UARTSend(LPC_USART0, (uint8_t *) TJA_SLAVE_MODE, strlen(TJA_SLAVE_MODE));
		  } else {
			  UARTSend(LPC_USART0, (uint8_t *) TJA_MASTER_MODE, strlen(TJA_MASTER_MODE));
		  }
		  GPIOSetBitValue( PORTNUM, LED_BLUE_POS, 0);    // signal BLUE LED
	  }
	  delay(5000);
	  // TODO check interrupt pin and act on it
	}

	return 0 ;
}
