/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_mrt.h $
 * Project: NXP LPC8xx software example
 *
 * Description:
 * This file contains definition and prototype for multi-rate timer 
 * configuration.
 */
#ifndef __MRT_H 
#define __MRT_H

/* Control register bit definition. */
#define MRT_INT_ENA					(0x1<<0)
#define MRT_REPEATED_MODE		(0x00<<1)
#define MRT_ONE_SHOT_INT		(0x01<<1)
#define MRT_ONE_SHOT_STALL	(0x02<<1)

/* Status register bit definition */
#define MRT_STAT_IRQ_FLAG		(0x1<<0)
#define MRT_STAT_RUN				(0x1<<1)


void delayMs(uint32_t delayInMs);
void MRT_IRQHandler(void);
void init_mrt(uint32_t timerInterval);

#endif /* end __MRT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
