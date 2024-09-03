/*
 * @brief 
 * This file is used to config SwitchMatrix module.
 *
 * @note
 * Copyright 2020, 2024 NXP 
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
    
#include "LPC8xx.h"    /* LPC8xx Peripheral Registers */
#include "type.h"

void SwitchMatrix_Init() 
{ 
    /* Enable SWM clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);

    /* Pin Assign 8 bit Configuration */
    /* U0_TXD */
    LPC_SWM->PINASSIGN0 = 0xffffff04UL; 

    /* Pin Assign 1 bit Configuration */
    /* SWCLK */
    /* SWDIO */
    /* RESET */
    LPC_SWM->PINENABLE0 = 0xffffffb3UL; 
}

 /**********************************************************************
 **                            End Of File
 **********************************************************************/
