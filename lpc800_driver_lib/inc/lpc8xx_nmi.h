/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_nmi.h $
 * Project: NXP LPC8xx NMI software example
 *
 * Description:
 * This file contains definition and prototype for NMI interrupt.
 */
#ifndef __NMI_H 
#define __NMI_H

#define NMI_ENABLED          0

#define MAX_NMI_NUM          32

void NMI_Init( uint32_t NMI_num );
void NMI_Handler(void);
#endif /* end __NMI_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
