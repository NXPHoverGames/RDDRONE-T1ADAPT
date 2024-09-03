/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_bod.h $
 * Project: NXP LPC8xx BOD(Brown-OUt Detect) example
 *
 * Description:
 * This file contains headers for BOD related modules and definition.
 */
#ifndef __BOD_H 
#define __BOD_H

#define DEEPSLEEP_BOD_WAKEUP	0
#define BOD_DEBUG				0

#define BOD_RESET_LED					7
#define POR_RESET_LED					8
#define BOD_INTERRUPT_LED			9
#define PWR_DOWN_BUTTON				15

#define BOD_INT_LVL0	(0<<2)		/* 1.65~1.80 */
#define BOD_INT_LVL1	(1<<2)		/* 2.22~2.35 */
#define BOD_INT_LVL2	(2<<2)		/* 2.52~2.66 */
#define BOD_INT_LVL3	(3<<2)		/* 2.80~2.90 */

#define BOD_RST_LVL0	0			/* 1.46~1.63 */
#define BOD_RST_LVL1	1			/* 2.06~2.15 */
#define BOD_RST_LVL2	2			/* 2.35~2.43 */
#define BOD_RST_LVL3	3			/* 2.63~2.71 */

#define BOD_RST_ENABLE	(0x1<<4)

/* For System Reset Source Identification or "SYSRSTSTAT" */
#define POR_RESET		(0x1<<0)
#define EXT_RESET		(0x1<<1)
#define WDT_RESET		(0x1<<2)
#define BOD_RESET		(0x1<<3)
#define SYS_RESET		(0x1<<4)
		
extern void BOD_IRQHandler(void);
extern void BOD_Init( void );

#endif /* end __BOD_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
