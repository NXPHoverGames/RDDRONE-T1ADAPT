/*
 * Copyright 2013-2014, 2024 NXP 
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clauseconnection.h
 */

#ifndef ETHERNETCONTROL_H_
#define ETHERNETCONTROL_H_


typedef enum phySel {
	 TJA,
	 BCM
} PHYSEL;

// SMI registers
#define SMI_CNTRL         0
#define SMI_STATUS        1
#define SMI_PHY_ID1       2
#define SMI_PHY_ID2       3
#define SMI_AUTO_NEG_ADV  4
#define SMI_AUTO_NEG_LNK  5
#define SMI_AUTO_NEG_EXP  6
#define SMI_AUTO_NEG_PNR  7
#define SMI_REG8          8
#define SMI_REG9          9
#define SMI_REG10        10
#define SMI_REG11        11
#define SMI_REG12        12
#define SMI_REG13        13
#define SMI_REG14        14
#define SMI_EXT_STAT     15   // TJA1100
#define SMI_AUTO_MDIX    16   // BCM5241
#define SMI_MODE_CNTRL   17   // BCM5241
#define SMI_SPEC_MODE    18   // LAN8700
#define SMI_REG19        19
#define SMI_REG24        24
#define SMI_REG25        25
#define SMI_INTREG       26
#define SMI_AUXMODE4     26   // BCM5241  (shadow)
#define SMI_STAT_IND     27   // LAN8700
#define SMI_REG28        28   // LAN8700
#define SMI_INT_SRC_LN   29   // LAN8700
#define SMI_INT_MSK      30   // LAN8700
#define SMI_PHY_CNTRL    31   // BCM5241, shadow select

#define SMI_EXT_CNTRL    17   // 0x11 TJA1100
#define SMI_CONFIG1      18   // 0x12 TJA1100
#define SMI_CONFIG2      19   // 0x13 TJA1100
#define SMI_SYM_ERR      20   // 0x14 TJA1100
#define SMI_INT_SRC_TJA  21   // 0x15 TJA1100
#define SMI_INT_ENA_TJA  22   // 0x16 TJA1100
#define SMI_COMM_STAT    23   // 0x17 TJA1100
#define SMI_GEN_STAT     24   // 0x18 TJA1100
#define SMI_EXTERN_STAT  25   // 0x19 TJA1100
#define SMI_LINK_FAIL    26   // 0x1A TJA1100
#define SMI_COM_CONF     27   // 0x1B TJA1101

// basic control register 0
#define SMI_0_RESET      (1 << 15)
#define SMI_0_LOOPBACK   (1 << 14)
#define SMI_0_SPD_10     ((0 << 13) | (0 << 6))
#define SMI_0_SPD_100    ((1 << 13) | (0 << 6))
#define SMI_0_SPD_1000   ((0 << 13) | (1 << 6))
#define SMI_0_SPD_MASK   ((1 << 13) | (1 << 6))
#define SMI_0_AUTONEG_EN (1 << 12)             // Not supported by TJA1100
#define SMI_0_POWER_DOWN (1 << 11)             // ISOLATE should be zero
#define SMI_0_ISOLATE    (1 << 10)             // should be off for normal operation
#define SMI_0_RE_AUTO    (1 << 9)              // Not supported by TJA1100
#define SMI_0_DUPLEX     (1 << 8)              // Only supported by TJA1100
#define SMI_0_COLL_TST   (1 << 7)              // Not supported by TJA1100
#define SMI_0_UNIDIR     (1 << 5)

// basic status register 1
#define SMI_1_100BASE_T4    (1 << 15)
#define SMI_1_100BASE_X_FD  (1 << 14)
#define SMI_1_100BASE_X_HD  (1 << 13)
#define SMI_1_10MBPS_FD     (1 << 12)
#define SMI_1_10MBPS_HD     (1 << 11)
#define SMI_1_100BASE_T2_FD (1 << 10)
#define SMI_1_100BASE_T2_HD (1 <<  9)
#define SMI_1_EXT_STAT      (1 <<  8)
#define SMI_1_UNI_ABLE      (1 <<  7)
#define SMI_1_MF_PRE_SUP    (1 <<  6)
#define SMI_1_AUTONEG_CMP   (1 <<  5)
#define SMI_1_REM_FAULT     (1 <<  4)
#define SMI_1_AUTONEG_ABLE  (1 <<  3)
#define SMI_1_LINK_STAT     (1 <<  2)
#define SMI_1_JAB_DET       (1 <<  1)
#define SMI_1_EXT_CAP       (1 <<  0)

// PHY identifier register 1
#define SMI_2_TJA1101    0x0180
#define SMI_2_BCM5241    0x0143

// PHY identifier register 2
#define SMI_3_TJA1101    0xDD01
#define SMI_3_BCM5241    0xBC31

// PHY SMI_EXT_CNTRL TJA1100
#define SMI_17_LINK_CNTRL  (1   << 15)
#define SMI_17_NOCHANGE    (0x0 << 11)
#define SMI_17_NORMAL      (0x3 << 11)
#define SMI_17_STBY        (0xC << 11)
#define SMI_17_SLEEP_REQ   (0xB << 11)
#define SMI_17_PWR_MASK    (0xF << 11)
#define SMI_17_TRAIN       (1   <<  9)
#define SMI_17_TEST1       (1   <<  6)
#define SMI_17_TEST2       (2   <<  6)
#define SMI_17_TEST3       (3   <<  6)
#define SMI_17_TEST4       (4   <<  6)
#define SMI_17_TEST5       (5   <<  6)
#define SMI_17_TEST6       (6   <<  6)
#define SMI_17_TEST7       (7   <<  6)
#define SMI_17_CABLE_TST   (1   <<  5)
#define SMI_17_INT_LPB     (0   <<  3)
#define SMI_17_EXT1_LPB    (1   <<  3)
#define SMI_17_EXT2_LPB    (2   <<  3)
#define SMI_17_REM_LPB     (3   <<  3)
#define SMI_17_CONFIG_EN   (1   <<  2)
#define SMI_17_CONFIG_INH  (1   <<  1)
#define SMI_17_WAKE_REQ    (1   <<  0)    // transmit idle symbols as bus wake-up request

// PHY SMI_CONFIG1  TJA1100
#define SMI_18_MASTER      (1   << 15)
#define SMI_18_AUTO_OP     (1   << 14)
#define SMI_18_LINK_15M    (1   << 13)    // cable length > 15 m
#define SMI_18_TX_500MV    (0   << 10)
#define SMI_18_TX_750MV    (1   << 10)
#define SMI_18_TX_1000MV   (2   << 10)
#define SMI_18_TX_1250MV   (3   << 10)
#define SMI_18_MII_MODE    (0   <<  8)
#define SMI_18_RMII_50MHZ  (1   <<  8)
#define SMI_18_RMII_25MHZ  (2   <<  8)
#define SMI_18_REV_MII     (3   <<  8)
#define SMI_18_MII_DRV_RED (1   <<  7)  // reduced strength MII output driver
#define SMI_18_LEDLINK     (0   <<  4)
#define SMI_18_LEDFRAME    (1   <<  4)
#define SMI_18_LEDSYMERR   (2   <<  4)
#define SMI_18_LEDCRS      (3   <<  4)
#define SMI_18_LED_EN      (1   <<  3)
#define SMI_18_CNFG_WAKE   (1   <<  2)  // ratiometric input threshold, absolute if zero
#define SMI_18_AUTO_PWD    (1   <<  1)  // autonomous power-down enabled

// PHY SMI CONFIG2 TJA1100
#define SMI_19_PHYAD_MASK  (0x1F << 11)  // readback of scrambler key
#define SMI_19_SNR_AV32    (0    <<  9)  // signal to noise ratio averaging over  32 symbols
#define SMI_19_SNR_AV64    (1    <<  9)  // signal to noise ratio averaging over  64 symbols
#define SMI_19_SNR_AV128   (2    <<  9)  // signal to noise ratio averaging over 128 symbols
#define SMI_19_SNR_AV256   (3    <<  9)  // signal to noise ratio averaging over 256 symbols
#define SMI_19_WLIM_NO     (0    <<  6)  // no warning
#define SMI_19_WLIM_A      (1    <<  6)  // Class A SNR warning limit
#define SMI_19_WLIM_B      (2    <<  6)  // Class B SNR warning limit
#define SMI_19_WLIM_C      (3    <<  6)  // Class C SNR warning limit
#define SMI_19_WLIM_D      (4    <<  6)  // Class D SNR warning limit
#define SMI_19_WLIM_E      (5    <<  6)  // Class E SNR warning limit
#define SMI_19_WLIM_F      (6    <<  6)  // Class F SNR warning limit
#define SMI_19_WLIM_G      (7    <<  6)  // Class G SNR warning limit
#define SMI_19_SNR_F_NL    (0    <<  3)  // signal to noise ratio fail limit - no limit
#define SMI_19_SNR_F_CLA   (1    <<  3)  // signal to noise ratio fail limit - Class A
#define SMI_19_SNR_F_CLB   (2    <<  3)  // signal to noise ratio fail limit - Class B
#define SMI_19_SNR_F_CLC   (3    <<  3)  // signal to noise ratio fail limit - Class C
#define SMI_19_SNR_F_CLD   (4    <<  3)  // signal to noise ratio fail limit - Class D
#define SMI_19_SNR_F_CLE   (5    <<  3)  // signal to noise ratio fail limit - Class E
#define SMI_19_SNR_F_CLF   (6    <<  3)  // signal to noise ratio fail limit - Class F
#define SMI_19_SNR_F_CLG   (7    <<  3)  // signal to noise ratio fail limit - Class G
#define SMI_19_JUMBO_EN    (1    <<  2)  // enable packets up to 16 kB instead of 4 kB
#define SMI_19_SLP_T_04    (0    <<  0)  // sleep request timeout 0.4 ms
#define SMI_19_SLP_T_1     (1    <<  0)  // sleep request timeout 1 ms
#define SMI_19_SLP_T_4     (2    <<  0)  // sleep request timeout 4 ms
#define SMI_19_SLP_T_16    (3    <<  0)  // sleep request timeout 16 ms

// PHY SMI COM STAT TJA1100
#define SMI_23_LINK_STAT    (1 << 15)     // Link OK
#define SMI_23_TX_MODE_MASK (3 << 13)     // TX mode mask
#define SMI_23_TX_MODE_DIS  (0 << 13)     // transmitter disabled
#define SMI_23_TX_MODE_N    (1 << 13)     // transmitter in SEND_N mode
#define SMI_23_TX_MODE_I    (2 << 13)     // transmitter in SEND_I mode
#define SMI_23_TX_MODE_Z    (3 << 13)     // transmitter in SEND_Z mode
#define SMI_23_LOC_RCVR_ST  (1 << 12)     // local receiver OK
#define SMI_23_REM_RCVR_ST  (1 << 11)     // remote receiver OK
#define SMI_23_SCR_LOCKED   (1 << 10)     // descrambler locked
#define SMI_23_SSD_ERR      (1 <<  9)     // SSD error detected
#define SMI_23_ESD_ERR      (1 <<  8)     // ESD error detected
#define SMI_23_SNR_MASK     (7 <<  5)     // Signal to noise mask
#define SMI_23_SNR_F_WRS    (0 <<  5)     // worse than Class A
#define SMI_23_SNR_F_CLA    (1 <<  5)     // Class A
#define SMI_23_SNR_F_CLB    (2 <<  5)     // Class B
#define SMI_23_SNR_F_CLC    (3 <<  5)     // Class C
#define SMI_23_SNR_F_CLD    (4 <<  5)     // Class D
#define SMI_23_SNR_F_CLE    (5 <<  5)     // Class E
#define SMI_23_SNR_F_CLF    (6 <<  5)     // Class F
#define SMI_23_SNR_F_CLG    (7 <<  5)     // Class G
#define SMI_23_REC_NO_ERR   (1 <<  4)     // no receive error detected
#define SMI_23_TRAN_NO_ERR  (1 <<  3)     // no transmitt error detected
#define SMI_23_PHY_STAT_MSK (7 <<  0)     // phy state mask
#define SMI_23_PHY_IDLE     (0 <<  0)     // idle
#define SMI_23_PHY_INIT     (1 <<  0)     // initialized
#define SMI_23_PHY_CONFIG   (2 <<  0)     // configured
#define SMI_23_PHY_OFFLINE  (3 <<  0)     // Offline
#define SMI_23_PHY_ACTIVE   (4 <<  0)     // Active
#define SMI_23_PHY_ISOLATE  (5 <<  0)     // isolate
#define SMI_23_PHY_CABLE    (6 <<  0)     // cable test
#define SMI_23_PHY_TEST     (7 <<  0)     // test mode

// SPEC_MODE  BCM5241
#define SMI_L31_BCM_ENSHA    (1 <<  7)    // select shadow registers interface
#define SMI_L26_LEDMODE1     (1 <<  0)    // LED mode 1
#define SMI_L17_APDE         (1 <<  5)    // Auto power down enable
#define SMI_L16_AUTOMDIX     (1 << 14)    // select auto MDIX
#define SMI_L0_AUTONEG       (1 << 12)    // select auto negotiation
#define SMI_L0_RESET         (1 << 15)    // reset

void reset_phy(void);
void reset_tja_phy(void);
void reset_bmc_phy(void);

uint16_t mdio_read(PHYSEL phy, int phyadr, int phyreg);
void mdio_write(PHYSEL phy, int phyadr, int phyreg, uint16_t value);
void delay(int len);

#endif /* ETHERNETCONTROL_H_ */
