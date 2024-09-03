/*
 * Copyright 2011, 2014, 2024 NXP
 * All rights reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * $Id: lpc8xx_mrt.c $
 * Project: NXP LPC8xx multi-rate timer(MRT) example
 *
 * Description:
 * This file contains MRT timer code example which include timer 
 * initialization, timer interrupt handler, and related APIs for 
 * timer setup.
*/
#include "lpc8xx.h"
#include "lpc8xx_nmi.h"
#include "lpc8xx_mrt.h"

volatile uint32_t mrt_counter = 0;

/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:	None
** 
*****************************************************************************/
void delayMs(uint32_t delayInMs)
{
  /* wait until delay time has elapsed */
	LPC_MRT->Channel[0].INTVAL = delayInMs;
  LPC_MRT->Channel[0].INTVAL |= 0x1UL<<31;
  while (LPC_MRT->Channel[0].TIMER);
  return;
}

/******************************************************************************
** Function name:		MRT_IRQHandler
**
** Descriptions:		MRT interrupt handler
**
** parameters:			None
** Returned value:	None
** 
******************************************************************************/
void MRT_IRQHandler(void)
{  
  if ( LPC_MRT->Channel[0].STAT & MRT_STAT_IRQ_FLAG )
  {
		LPC_MRT->Channel[0].STAT = MRT_STAT_IRQ_FLAG;			/* clear interrupt flag */
		mrt_counter++;
  }
  return;
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**									install timer interrupt handler
**
** parameters:			timer interval
** Returned value:	None
** 
******************************************************************************/
void init_mrt(uint32_t TimerInterval) 
{
  /* Enable clock to MRT and reset the MRT peripheral */
  LPC_SYSCON->SYSAHBCLKCTRL |= (0x1<<10);
	LPC_SYSCON->PRESETCTRL &= ~(0x1<<7);
	LPC_SYSCON->PRESETCTRL |= (0x1<<7);

	mrt_counter = 0;
  LPC_MRT->Channel[0].INTVAL = TimerInterval;
  LPC_MRT->Channel[0].INTVAL |= 0x1UL<<31;
	
	LPC_MRT->Channel[0].CTRL = MRT_REPEATED_MODE|MRT_INT_ENA;
	
  /* Enable the MRT Interrupt */
#if NMI_ENABLED
	NVIC_DisableIRQ( MRT_IRQn );
	NMI_Init( MRT_IRQn );
#else
  NVIC_EnableIRQ(MRT_IRQn);
#endif
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
