/*
 * Copyright 2014, 2024 NXP 
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause 
 *
 * $Id: lpc8xx_wkt.c $
 * Project: NXP LPC8xx alarm/wake timer example
 *
 * Description:
 * This file contains alarm/wake timer code example which include timer 
 * initialization, timer interrupt handler, and related APIs for 
 * timer setup.
 */
#include "lpc8xx.h"
#include "lpc8xx_nmi.h"
#include "lpc8xx_wkt.h"

/******************************************************************************
** Function name:		WKT_IRQHandler
**
** Descriptions:		alarm/wake timer interrupt handler
**
** parameters:			None
** Returned value:	None
** 
******************************************************************************/
void WKT_IRQHandler(void)
{
  if ( LPC_WKT->CTRL & WKT_FLAG )
  {
		LPC_WKT->CTRL |= WKT_FLAG;			/* clear interrupt flag */
  }
  return;
}

/******************************************************************************
** Function name:		init_wkt
**
** Descriptions:		Initialize timer, select clock source, set timer interval,
**									install timer interrupt handler
**
** parameters:			clock source and timer interval
** Returned value:	None
** 
******************************************************************************/
void init_wkt(uint32_t clkSrc, uint32_t timerInterval) 
{
  LPC_SYSCON->SYSAHBCLKCTRL |= (0x1 << 9);
	LPC_SYSCON->PRESETCTRL &= ~(0x1 << 9);
	LPC_SYSCON->PRESETCTRL |= (0x1 << 9);

	if ( clkSrc & WKT_CLKSEL )
	{
		LPC_WKT->CTRL |= WKT_CLKSEL;
	}
	else
	{
		LPC_WKT->CTRL &= ~WKT_CLKSEL;
	}
  LPC_WKT->COUNT = timerInterval;
	
  /* Enable the WKT Interrupt */
#if NMI_ENABLED
	NVIC_DisableIRQ( WKT_IRQn );
	NMI_Init( WKT_IRQn );
#else
  NVIC_EnableIRQ(WKT_IRQn);
#endif
  return;
}

/******************************************************************************
** Function name:		halt_wkt
**
** Descriptions:		Halt timer
**
** parameters:			None
** Returned value:	None
** 
******************************************************************************/
void halt_wkt(void) 
{
	LPC_WKT->CTRL |= WKT_CLR;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
