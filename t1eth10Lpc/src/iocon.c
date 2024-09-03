/*
 * @brief 
 * This file is used to config IOCON module.
 *
 * @note
 * Copyright 2020, 2024 NXP 
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
    
#include "LPC8xx.h"    /* LPC8xx Peripheral Registers */
#include "type.h"

void IOCON_Init() {
    
    /* Enable UART clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<18);

    /* Pin I/O Configuration */
    /* LPC_IOCON->PIO0_0 = 0x90; */
    /* LPC_IOCON->PIO0_1 = 0x90; */
    /* LPC_IOCON->PIO0_2 = 0x90; */
    /* LPC_IOCON->PIO0_3 = 0x90; */
    /* LPC_IOCON->PIO0_4 = 0x90; */
    /* LPC_IOCON->PIO0_5 = 0x90; */
    /* LPC_IOCON->PIO0_6 = 0x90; */
    /* LPC_IOCON->PIO0_7 = 0x90; */
    /* LPC_IOCON->PIO0_8 = 0x90; */
    /* LPC_IOCON->PIO0_9 = 0x90; */
    /* LPC_IOCON->PIO0_10 = 0x80; */
    /* LPC_IOCON->PIO0_11 = 0x80; */
    /* LPC_IOCON->PIO0_12 = 0x90; */
    /* LPC_IOCON->PIO0_13 = 0x90; */
}
 /**********************************************************************
 **                            End Of File
 **********************************************************************/
