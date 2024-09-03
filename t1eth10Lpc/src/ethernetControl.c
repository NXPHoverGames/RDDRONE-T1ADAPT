/*
 * Copyright 2013-2014, 2024 NXP 
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clauseconnection.h
 */
#include "LPC8xx.h"
#include "lpc8xx_gpio.h"
#include "connection.h"
#include "ethernetControl.h"

int master_switch = 1;

void delay(int len)
{
	volatile int i;
	int          j;

	for (j=0; j<len; j++) {
	  for (i=0; i<100; i++);
	}
}

void mdelay(int32_t len)
{
	volatile int32_t j;

	for (j=0; j<len; j++) {
	}
}

static void output_MDIO(PHYSEL phy, uint32_t val, uint32_t n)
{
	 for (val <<= (32 -n); n; val <<= 1, n--) {
		 if (phy == TJA) {
			   if (val & 0x80000000) {
				 // set MDIO
				 GPIOSetBitValue( PORTNUM, MDIO_TJA_POS, 1);
			   } else {
				 // clear MDIO
				 GPIOSetBitValue( PORTNUM, MDIO_TJA_POS, 0);
			   }
		 } else {
			   if (val & 0x80000000) {
				 // set MDIO
				 GPIOSetBitValue( PORTNUM, MDIO_BCM_POS, 1);
			   } else {
				 // clear MDIO
				 GPIOSetBitValue( PORTNUM, MDIO_BCM_POS, 0);
			   }
		 }
		 // set MDC
		 GPIOSetBitValue( PORTNUM, MDC_POS, 1);
		 mdelay(1);
		 // clear MDC
	     GPIOSetBitValue( PORTNUM, MDC_POS, 0);
	 }
}

static uint32_t input_MDIO(PHYSEL phy)
{
	// input value from MII PHY management interface
	uint32_t i, val = 0;

	 for (i = 0; i < 16; i++) {
		 val <<= 1;
		 // set MDC
		 GPIOSetBitValue( PORTNUM, MDC_POS, 1);
		 mdelay(1);
		 // clear MDC
		 GPIOSetBitValue( PORTNUM, MDC_POS, 0);
		 if (GPIOGetPinValue( PORTNUM, (phy == TJA) ? MDIO_TJA_POS : MDIO_BCM_POS)) {
				 val |= 1;
		 }
	 }
     return val;
}

static void turnaround_MDIO(PHYSEL phy)
{
	GPIOSetDir( PORTNUM, (phy == TJA) ? MDIO_TJA_POS : MDIO_BCM_POS,  PORT_IN );
	// set MDC
	GPIOSetBitValue( PORTNUM, MDC_POS, 1);
	mdelay(1);
	// clear MDC
	GPIOSetBitValue( PORTNUM, MDC_POS, 0);
	mdelay(1);
}

void reset_phy(void)
{
	// send reset to both PHYs
	GPIOSetBitValue( PORTNUM, nRST_PHY_TJA_POS, 0);
	GPIOSetBitValue( PORTNUM, nRST_PHY_BCM_POS, 0);
	delay(1800);  // TODO should be 100ms...
	GPIOSetBitValue( PORTNUM, nRST_PHY_TJA_POS, 1);
	GPIOSetBitValue( PORTNUM, nRST_PHY_BCM_POS, 1);
	delay(1800);  // TODO should be 100ms...

}

void reset_tja_phy(void)
{
	GPIOSetBitValue( PORTNUM, nRST_PHY_TJA_POS, 0);
	delay(1800);  // TODO should be 100ms...
	GPIOSetBitValue( PORTNUM, nRST_PHY_TJA_POS, 1);
	delay(1800);  // TODO should be 100ms...

}

void reset_bmc_phy(void)
{
	GPIOSetBitValue( PORTNUM, nRST_PHY_BCM_POS, 0);
	delay(1800);  // TODO should be 100ms...
	GPIOSetBitValue( PORTNUM, nRST_PHY_BCM_POS, 1);
	delay(1800);  // TODO should be 100ms...

}

uint16_t mdio_read(PHYSEL phy, int phyadr, int phyreg)
{
	uint16_t val;

	// configure to make MDIO output
	GPIOSetBitValue(PORTNUM, (phy == TJA) ? MDIO_TJA_POS : MDIO_BCM_POS, 1);  // make sure we don't get a glitch
	GPIOSetDir( PORTNUM, (phy == TJA) ? MDIO_TJA_POS : MDIO_BCM_POS, PORT_OUT );

	/* 32 consecutive ones on MDO to establish sync */
	output_MDIO(phy, 0xFFFFFFFF, 32);

	/* start code (01), read command (10) */
	output_MDIO(phy, 0x06, 4);

	/* write PHY adddress */
	output_MDIO(phy, phyadr, 5);

	/* write PHY register */
	output_MDIO(phy, phyreg, 5);

	/* turnaround MDIO is tri-stated (we want to read) */
	turnaround_MDIO(phy);

	/* read the value */
	val = input_MDIO(phy);

	/* turnaround MDIO is tri-stated */
	turnaround_MDIO(phy);

	return (uint16_t) val;
}


void mdio_write(PHYSEL phy, int phyadr, int phyreg, uint16_t value)
{
	uint32_t val;

	/* configure MDC on P0_17, MDIO on P0_13 */
	// configure to make MDIO output
	GPIOSetDir( PORTNUM, (phy == TJA) ? MDIO_TJA_POS : MDIO_BCM_POS, PORT_OUT );

	/* 32 consecutive ones on MDO to establish sync */
	output_MDIO(phy, 0xFFFFFFFF, 32);

	/* start code (01), read command (01) */
	output_MDIO(phy, 0x05, 4);

	/* write PHY adddress */
	output_MDIO(phy, phyadr, 5);

	/* write PHY register */
	output_MDIO(phy, phyreg, 5);

	/* turnaround MDIO write (10) */
	output_MDIO(phy, 0x02, 2);

	/* write the value */
	val = value;
	output_MDIO(phy, val, 16);

	/* turnaround MDIO is tri-stated */
	turnaround_MDIO(phy);
}
