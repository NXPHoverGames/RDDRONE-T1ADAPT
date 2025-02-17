/*
 * Copyright 2014, 2024 NXP 
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_wdt.c $
 * Project: NXP LPC8xx WDT(Watchdog timer) example
 *
 * Description:
 * This file contains WDT code example which include WDT 
 * initialization, WDT interrupt handler, and APIs for WDT
 * reading.
 */
#include "lpc8xx.h"			/* LPC8xx Peripheral Registers */
#include "lpc8xx_nmi.h"
#include "lpc8xx_wdt.h"

volatile uint32_t wdt_counter;

/*****************************************************************************
** Function name:		WDTHandler
**
** Descriptions:		Watchdog timer interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void WDT_IRQHandler(void)
{
  uint32_t i;

#if PROTECT_MODE
  /* For WDPROTECT test */
  /* Make sure counter is below WDWARNINT */
  wdt_counter = LPC_WWDT->TV;
  while (wdt_counter >= 0x3FF)
  {
    wdt_counter = LPC_WWDT->TV;
  }

  LPC_WWDT->FEED = 0xAA;		/* Feeding sequence */
  LPC_WWDT->FEED = 0x55;    
  /* Make sure feed sequence executed properly */
  for (i = 0; i < 0x80; i++);

  /* Make sure counter is reloaded with WDTC */
  wdt_counter = LPC_WWDT->TV;
  while (wdt_counter < 0x400)
  {
    wdt_counter = LPC_WWDT->TV;
  }
#endif

  LPC_WWDT->MOD |= (WDINT | WDTOF);		/* clear the interrupt flag */
  LPC_WWDT->MOD &= ~(WDINT | WDTOF);	/* clear the time-out flag  */
}

/*****************************************************************************
** Function name:		WDTInit
**
** Descriptions:		Initialize watchdog timer, install the
**						watchdog timer interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void WDTInit( void )
{
  uint32_t i, regVal;

  wdt_counter = 0;

  /* Enable the WDT Interrupt */
#if NMI_ENABLED
	NVIC_DisableIRQ( WDT_IRQn );
	NMI_Init( WDT_IRQn );
#else
  NVIC_EnableIRQ(WDT_IRQn);
#endif
	
  LPC_WWDT->TC = WDT_FEED_VALUE;	/* once WDEN is set, the WDT will start after feeding */
#if PROTECT_MODE
  LPC_WWDT->TC = 0x3FFF;
#endif
#if WINDOW_MODE
  LPC_WWDT->TC = 0x3FFF;
#endif

#if WATCHDOG_RESET
  regVal = WDEN | WDRESET;
  LPC_WWDT->MOD = regVal;
#else
  regVal = WDEN;
  LPC_WWDT->MOD = regVal;
#endif

#if LOCKCLK_MODE
  regVal |= WDLOCKCLK;
  LPC_WWDT->MOD = regVal;
#endif

  LPC_WWDT->FEED = 0xAA;		/* Feeding sequence */
  LPC_WWDT->FEED = 0x55;    
  /* Make sure feed sequence executed properly */
  for (i = 0; i < 0x80; i++);

  /* For WDWARNINT test */
  LPC_WWDT->WARNINT = 0x3FF;

#if PROTECT_MODE
  /* For WDPROTECT test */
  regVal |= WDPROTECT;
  LPC_WWDT->MOD = regVal;

  LPC_WWDT->WINDOW = 0x2FFF;
#endif

#if WINDOW_MODE
  /* For WDWINDOW test */
  LPC_WWDT->WINDOW = 0x2FFF;
#endif

#if WINDOW_MODE
  /* For WDWINDOW test */
  while (1)
  {
    wdt_counter = LPC_WWDT->TV;
    while (wdt_counter >= 0x00001FFF)
    {
      wdt_counter = LPC_WWDT->TV;
    }

    LPC_WWDT->FEED = 0xAA;		/* Feeding sequence */
    LPC_WWDT->FEED = 0x55;    
    /* Make sure feed sequence executed properly */
    for (i = 0; i < 0x80; i++);
  }
#endif

  return;
}

/*****************************************************************************
** Function name:		WDTFeed
**
** Descriptions:		Feed watchdog timer to prevent it from timeout
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void WDTFeed( void )
{
  LPC_WWDT->FEED = 0xAA;		/* Feeding sequence */
  LPC_WWDT->FEED = 0x55;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
