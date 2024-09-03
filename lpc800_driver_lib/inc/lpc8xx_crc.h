/*
 * Copyright 2014, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * $Id: lpc8xx_crc.h $
 * Project: NXP LPC8xx CRC example
 *
 * Description:
 * This file contains CRC code header definition.
 */
#ifndef __CRC_H__
#define __CRC_H__

#define CRC_32_POLYNOMIAL		0
#define CRC_16_POLYNOMIAL		1
#define CRC_CCITT_POLYNOMIAL	2

extern void CRC_SetMode( uint32_t crc_poly, uint32_t bit_rvs_wr,
						 uint32_t cmpl_wr, uint32_t bit_rvs_sum, uint32_t cmpl_sum );
extern void CRC_WriteData( uint8_t * data, uint8_t length );
extern uint32_t CRC_GetSum( void );

#endif  /* __CRC_H__ */
/*****************************************************************************
**                            End Of File
******************************************************************************/

