/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_clkconfig.h $
 * Project: NXP LPC8xx software example
 *
 * Description:
 * This file contains definition and prototype for clock configuration.
 */
#ifndef __CLKCONFIG_H 
#define __CLKCONFIG_H

#define CLKOUTCLK_SRC_IRC_OSC       0
#define CLKOUTCLK_SRC_SYS_OSC       1
#define CLKOUTCLK_SRC_WDT_OSC       2
#define CLKOUTCLK_SRC_MAIN_CLK      3

void WDT_CLK_Setup(void);
void CLKOUT_Setup(uint32_t timer_num);
#endif /* end __CLKCONFIG_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
