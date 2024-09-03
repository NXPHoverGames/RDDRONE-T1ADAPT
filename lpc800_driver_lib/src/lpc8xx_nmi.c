/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_nmi.c $
 * Project: NXP LPC8xx NMI interrupt example
 *
 * Description:
 * This file contains NMI interrupt handler code example.
 */
#include "lpc8xx.h"
#include "lpc8xx_mrt.h"
#include "lpc8xx_uart.h"
#include "lpc8xx_spi.h"
#include "lpc8xx_i2c.h"
#include "lpc8xx_bod.h"
#include "lpc8xx_wdt.h"
#include "lpc8xx_gpio.h"
#include "lpc8xx_wkt.h"
#include "lpc8xx_comp.h"
#include "lpc8xx_nmi.h"

#if NMI_ENABLED
volatile uint32_t NMI_Counter[MAX_NMI_NUM];

/*****************************************************************************
** Function name:		NMI_Handler
**
** Descriptions:		NMI interrupt handler
** parameters:		None			 
** 						
** Returned value:	None
** 
*****************************************************************************/
void NMI_Handler( void )
{
  uint32_t regVal;

  regVal = LPC_SYSCON->NMISRC;
  regVal &=	~0x80000000;
  if ( regVal < MAX_NMI_NUM )
  {
		if ( regVal == MRT_IRQn )
		{
			MRT_IRQHandler();
		}
		if ( regVal == UART0_IRQn )
		{
			UART0_IRQHandler();
			//UART_Handler(LPC_USART0);
		}
		if ( regVal == UART1_IRQn )
		{
			UART1_IRQHandler();
			//UART_Handler(LPC_USART1);
		}
		if ( regVal == UART2_IRQn )
		{
			UART2_IRQHandler();
			//UART_Handler(LPC_USART2);
		}
		if ( regVal == SPI0_IRQn )
		{
			SPI0_IRQHandler();
			//SPI_Handler(LPC_SPI0);
		}
		if ( regVal == SPI1_IRQn )
		{
			SPI1_IRQHandler();
			//SPI_Handler(LPC_SPI1);
		}
		if ( regVal == I2C_IRQn )
		{
			I2C_IRQHandler();
		}
		if ( regVal == SCT_IRQn )
		{
			SCT_IRQHandler();
		}
		if ( regVal == BOD_IRQn )
		{
			BOD_IRQHandler();
		}
		if ( regVal == WDT_IRQn )
		{
			WDT_IRQHandler();
		}
		if ( (regVal >= PININT0_IRQn) && (regVal <= PININT7_IRQn) )
		{
			PININT_Handler ( regVal - PININT0_IRQn );
		}
		if ( regVal == WKT_IRQn )
		{
			WKT_IRQHandler();
		}
		if ( regVal == CMP_IRQn )
		{
			CMP_IRQHandler();
		}
		NMI_Counter[regVal]++; 
  }
  return;
}

/*****************************************************************************
** Function name:		NMI_Init
**
** Descriptions:		NMI initialization
** parameters:			NMI number			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void NMI_Init( uint32_t NMI_num )
{
  uint32_t i;

  for ( i = 0; i < MAX_NMI_NUM; i++ )
  {
    NMI_Counter[i] = 0x0;
  }
  LPC_SYSCON->NMISRC = 0x80000000|NMI_num;
  return;
}

#endif
