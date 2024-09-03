/*
 * Copyright 2013-2014, 2024 NXP 
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clauseconnection.h
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

	/* MDC      on P0_17
	 * MDIO     on P0_13
	 * nRST_PHY on P0_12
	 * masterSw on P0_14
	 * INTn     on P0_6
	 * LAN_INTn on P0_7
	 * LED_GR   on P0_10
	 * LED_RD   on P0_16 */

// POS values to be used for gpio driver
#define MDC_POS            12 // ok
#define MDIO_BCM_POS       13 // ok
#define MDIO_TJA_POS       7 // 0  // TODO: currently mapped here
#define nRST_PHY_TJA_POS   1 //11
#define nRST_PHY_BCM_POS   9 // 1
#define LED_BLUE_POS       10  //9
#define LED_RED_POS        11 //8
#define TJA_EN_POS         6 //10

#define PORTNUM   0  // no different port on LPC812

#define PORT_OUT  1
#define PORT_IN   0

// direct values to be used for port control
#define MDC       (1 << MDC_POS)
#define MDIO_BCM  (1 << MDIO_BCM_POS)
#define MDIO_TJA  (1 << MDIO_TJA_POS)
#define nRST_PHY  (1 << nRST_PHY_POS)
#define LED_BLUE  (1 << LED_BLUE_POS)
#define LED_RED   (1 << LED_RED_POS)

// MDC address info
#define TJA1101_PHY  0
#define BCM5241_PHY  0

#endif /* CONNECTION_H_ */
