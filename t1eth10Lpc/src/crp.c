/*
 * crp.c
 * Source file to create CRP word expected by LPCXpresso IDE linker
 ******************************************************************************
 *
 * Copyright 2013, 2024 NXP 
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if defined (__CODE_RED)
#include <NXP/crp.h>
// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;
#endif
