/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_wkt.h $
 * Project: NXP LPC8xx software example
 *
 * Description:
 * This file contains definition and prototype for alarm/wake timer 
 * configuration.
 */
#ifndef __WKT_H 
#define __WKT_H

/* Control register bit definition. */
#define WKT_CLKSEL					(0x1<<0)
#define WKT_FLAG						(0x1<<1)
#define WKT_CLR							(0x1<<2)

void WKT_IRQHandler(void);
void init_wkt(uint32_t clkSrc, uint32_t timerInterval);
void halt_wkt(void);

#endif /* end __WKT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
