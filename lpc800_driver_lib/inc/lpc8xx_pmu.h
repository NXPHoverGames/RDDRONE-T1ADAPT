/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause 
 *
 * $Id: lpc8xx_pmu.h $
 * Project: NXP LPC8xx PMU example
 *
 * Description:
 * This file contains PMU code header definition.
 */
#ifndef __LPC8XX_PMU_H 
#define __LPC8XX_PMU_H

#define TEST_DEEPPOWERDOWN  0

#define MCU_SLEEP           0
#define MCU_DEEP_SLEEP      1
#define MCU_POWER_DOWN      2

/* System Low Power ----------------------------------------------------------*/
#define NVIC_LP_SEVONPEND   (0x10)
#define NVIC_LP_SLEEPDEEP   (0x04)
#define NVIC_LP_SLEEPONEXIT (0x02)

#define IRC_OUT_PD          (0x1<<0)
#define IRC_PD              (0x1<<1)
#define FLASH_PD            (0x1<<2)
#define BOD_PD              (0x1<<3)
// #define ADC_PD              (0x1<<4)
#define SYS_OSC_PD          (0x1<<5)
#define WDT_OSC_PD          (0x1<<6)
#define SYS_PLL_PD          (0x1<<7)

void PMU_Init( void );
void PMU_Sleep( uint32_t SleepMode, uint32_t SleepCtrl );
void PMU_DeepPowerDown( void );

#endif /* end __LPC8XX_PMU_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
