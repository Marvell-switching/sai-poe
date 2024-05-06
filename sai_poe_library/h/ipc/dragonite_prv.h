/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */


/*#include <cpssDriver/pp/hardware/cpssDriverPpHw.h>*/
/***************************************************************************/
#define EXTHWG_POE_DRG_IRQ_MASK_REG_ADDR_CNS	0x68
#define EXTHWG_POE_DRG_MASK_VAL_CNS				0

#define EXTHWG_POE_DRG_DEBUG_MAX_LEN			0x500

#define EXTHWG_POE_DRG_FW_LOAD_ADDR		0



#define INIT_VAL					0xFF

/****************/
/*  RX / TX     */
/****************/
#define TX_MO_ADDR					0x50
#define TX_MO_HOST_OWNERSHIP		0xA0
#define TX_MO_POE_OWNERSHIP			0x0A

#define RX_MO_ADDR					0x100
#define RX_MO_HOST_OWNERSHIP		0xB0
#define RX_MO_POE_OWNERSHIP			0x0B

#define TX_BUF_ADDR					0x54
#define RX_BUF_ADDR					0x104

/****************/
/*  D E B U G   */
/****************/
#define TX_DEBUG_MO_ADDR			0x150
#define TX_DEBUG_MO_HOST_OWNERSHIP	0xC0
#define TX_DEBUG_MO_POE_OWNERSHIP	0x0C

#define RX_DEBUG_MO_ADDR			0x650
#define RX_DEBUG_MO_HOST_OWNERSHIP	0xD0
#define RX_DEBUG_MO_POE_OWNERSHIP	0x0D

#define TX_DEBUG_BUF_ADDR			0x154
#define RX_DEBUG_BUF_ADDR			0x654


/****************/
/*  Management  */
/****************/
#define HOST_PROTOCOL_VERSION_REGISTER	0x0 

#define HOST_PROTOCOL_VERSION_NUMBER_CNS 0x01/* Protocol version � 2: 
											 * Additional support for sniffer, secondary interface and Dragonite interrupt mask register (Control Dragonite IRQ to Host output).
											 * may change in new versions */
#define HOST_INPUT_FROM_POE_REG_ADDR	0x10
#define HOST_RST_CAUSE_REG_ADDR			0x34

#define POE_PROT_VER_REG_ADDR			0x4
