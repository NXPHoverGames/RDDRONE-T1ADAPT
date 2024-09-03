/*
 * comp.h:  Header file for NXP LPC8xx Family Microprocessors
 *
 * Copyright 2012, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __COMP_H__
#define __COMP_H__


#define COMP_VP	0
#define COMP_VM	1

#define COMPSA			(0x1 << 6)
#define EDGECLR			(0x1 << 20)
#define COMPSTAT		(0x1 << 21)
#define COMPEDGE		(0x1 << 23)

extern void CMP_IRQHandler (void);
extern void COMP_IOConfig( void );
extern void COMP_Init( void );
extern void COMP_SelectInput( uint32_t comp_channel, uint32_t input );
extern void COMP_SetOutput( uint32_t sync );
extern void COMP_SetInterrupt( uint32_t single, uint32_t event );
extern void COMP_SetHysteresis( uint32_t level );
extern uint32_t COMP_GetOutputStatus( void );

#endif  /* __COMP_H__ */
/*****************************************************************************
**                            End Of File
******************************************************************************/

