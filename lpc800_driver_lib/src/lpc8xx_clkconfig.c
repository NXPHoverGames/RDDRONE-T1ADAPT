/*
 * Copyright 2014 , 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * $Id: lpc8xx_clkconfig.c $
 * 
 * Project: NXP LPC8xx Clock Configuration example
 *
 * Description:
 * This file contains clock configuration code example which include 
 * watchdog setup and debug clock out setup.
 */
#include "lpc8xx.h"
#include "lpc8xx_clkconfig.h"


/*****************************************************************************
** Function name:		WDT_CLK_Setup
**
** Descriptions:		Configure WDT clock.
** parameters:			None
** 						
** Returned value:		None
** 
*****************************************************************************/
void WDT_CLK_Setup ( void )
{
  /* Freq = 0.5Mhz, div_sel is 0x1F, divided by 64. WDT_OSC should be 7.8125khz */
  LPC_SYSCON->WDTOSCCTRL = (0x1<<5)|0x1F;
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    /* Let WDT clock run */

  /* Enables clock for WDT */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<17);
  return;
}

/*****************************************************************************
** Function name:		CLKOUT_Setup
**
** Descriptions:		Configure CLKOUT for reference clock check.
** parameters:			clock source: irc_osc(0), sys_osc(1), wdt_osc(2),
**						main_clk(3).			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void CLKOUT_Setup ( uint32_t clksrc )
{
  /* debug PLL after configuration. */
  LPC_SYSCON->CLKOUTSEL = clksrc;	/* Select Main clock */
  LPC_SYSCON->CLKOUTUEN = 0x01;		/* Update clock */
  while ( !(LPC_SYSCON->CLKOUTUEN & 0x01) );		/* Wait until updated */
  LPC_SYSCON->CLKOUTDIV = 1;			/* Divided by 1 */
  return;
}

