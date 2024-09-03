/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_wdt.h $
 * Project: NXP LPC8xx WDT example
 *
 * Description:
 * This file contains WDT code header definition.
 */
#ifndef __WDT_H 
#define __WDT_H

#define WDEN              (0x1<<0)
#define WDRESET           (0x1<<1)
#define WDTOF             (0x1<<2)
#define WDINT             (0x1<<3)
#define WDPROTECT         (0x1<<4)
#define WDLOCKCLK         (0x1<<5)

#define WDT_FEED_VALUE    0x003FFFFF

#define WINDOW_MODE       0
#define PROTECT_MODE      1
#define WATCHDOG_RESET    0
#define LOCKCLK_MODE      0

extern void WDT_IRQHandler(void);
extern void WDTInit( void );
extern void WDTFeed( void );

#endif /* end __WDT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
