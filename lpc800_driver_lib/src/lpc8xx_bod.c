/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_bod.c $
 * Project: NXP LPC8xx BOD(Brown-OUt Detect) example
 *
 * Description:
 * This file contains BOD code example which include BOD 
 * initialization, BOD interrupt handler, and APIs.
 */
#include "lpc8xx.h"			/* LPC8xx Peripheral Registers */
#include "lpc8xx_gpio.h"
#include "lpc8xx_bod.h"

volatile uint32_t bod_counter;

/*****************************************************************************
** Function name:		BOD_IRQHandler
**
** Descriptions:		BOD interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void BOD_IRQHandler(void)
{
  if ( LPC_SYSCON->SYSRSTSTAT & BOD_RESET )
  {
		/* If the BOD RESET has occured, disable the BOD interrupt,
		or we will stuck here serving BOD interrupt instead of
		LED blinking showing BOD RESET. */ 
		NVIC_DisableIRQ(BOD_IRQn);
		return;
  }

  bod_counter++;

  /* Turn on BOD RST LED only, turn off the rest. */
  GPIOSetBitValue( 0, BOD_INTERRUPT_LED, 1 );
  GPIOSetBitValue( 0, BOD_RESET_LED, 0 );
  GPIOSetBitValue( 0, POR_RESET_LED, 0 );
  return;
}

/*****************************************************************************
** Function name:		BOD_Init
**
** Descriptions:		Initialize BOD control register
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void BOD_Init( void )
{
  /* Set BOD control register. interrupt level assertion is 1.65V, 
  de-assertion is 1.80V. */
  LPC_SYSCON->BODCTRL = BOD_INT_LVL3|BOD_RST_LVL2|BOD_RST_ENABLE;
  /* Enable the BOD Interrupt */
  NVIC_EnableIRQ(BOD_IRQn);
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
