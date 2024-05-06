/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE IS A REFERENCE CODE FOR MARVELL SWITCH PRODUCTS.  IT IS PROVIDED   *
* "AS IS" WITH NO WARRANTIES, EXPRESSED, IMPLIED OR OTHERWISE, REGARDING ITS   *
* ACCURACY, COMPLETENESS OR PERFORMANCE.                                       *
* CUSTOMERS ARE FREE TO MODIFY IT AND USE IT ONLY IN THEIR PRODUCTION          *
* SOFTWARE RELEASES WITH MARVELL SWITCH CHIPSETS.                              *
*******************************************************************************/
/**
********************************************************************************
* @file gtDragoniteDrv.h
*
* @brief Includes Dragonite managment routines.
*
* @version   3
********************************************************************************
*/
#ifndef __gtDragoniteDrvh
#define __gtDragoniteDrvh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*#include <gtExtDrv/os/extDrvOs.h>*/
#include <h/ipc/cpssHwInfo.h>
#include <h/ipc/mvShmIpc.h>

#define DRAGONITE_FW_LOAD_ADDR_CNS      0
#define ITCM_DIR                        0
#define DTCM_DIR                        1

#define DRAGONITE_DATA_MSG_LEN          15

/****************/
/*  RX / TX     */
/****************/
#define TX_MO_ADDR                      0x50
#define TX_MO_HOST_OWNERSHIP_CODE       0xA0
#define TX_MO_POE_OWNERSHIP_CODE        0x0A

#define RX_MO_ADDR                      0x100
#define RX_MO_HOST_OWNERSHIP_CODE       0xB0
#define RX_MO_POE_OWNERSHIP_CODE        0x0B

#define TX_BUF_ADDR                     0x54
#define RX_BUF_ADDR                     0x104

/****************/
/*  D E B U G   */
/****************/
#define TX_DEBUG_MO_ADDR                0x150
#define TX_DEBUG_MO_HOST_OWNERSHIP      0xC0
#define TX_DEBUG_MO_POE_OWNERSHIP       0x0C

#define RX_DEBUG_MO_ADDR                0x650
#define RX_DEBUG_MO_HOST_OWNERSHIP      0xD0
#define RX_DEBUG_MO_POE_OWNERSHIP       0x0D

#define TX_DEBUG_BUF_ADDR               0x154
#define RX_DEBUG_BUF_ADDR               0x654

/****************/
/*  Management  */
/****************/
#define HOST_PROT_VER_REG_ADDR          0x0
#define PROT_VER_REG_ADDR               0x4
#define MEM_INIT_VAL                    0xFF
#define HOST_INPUT_FROM_POE_REG_ADDR    0x10
#define HOST_OUTPUT_TO_POE_REG_ADDR     0x30
#define HOST_RST_CAUSE_REG_ADDR         0x34

/****************/
/*  MCU IPC     */
/****************/
#define EXTDRVIPC_TX_HEADER_SIZE       (sizeof(GT_32)*2)
#define EXTDRVIPC_RX_HEADER_SIZE   (sizeof(GT_32)*3)
#define EXTDRVIPC_MAX_MSG_SIZE     256
#define EXTDRVIPC_MAX_INTERNAL_TX_DATA_MSG_SIZE    (EXTDRVIPC_MAX_MSG_SIZE - EXTDRVIPC_TX_HEADER_SIZE)
#define EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE    (EXTDRVIPC_MAX_MSG_SIZE - EXTDRVIPC_RX_HEADER_SIZE)

/****************/
/*  Conbtroller     */
/****************/
typedef int8_t EXTHWG_POE_ret_TYP;
#define EXTHWG_POE_ret_ok_CNS			0
#define EXTHWG_POE_ret_not_init_CNS		(-1)
#define EXTHWG_POE_ret_failed_CNS		(-2)
#define EXTHWG_POE_ret_not_owned_CNS	(-3)
#define EXTHWG_POE_ret_timeout_CNS		(-4)

typedef enum {
    EXTHWG_POE_ret_ok_E        = EXTHWG_POE_ret_ok_CNS,
    EXTHWG_POE_ret_not_init_E  = EXTHWG_POE_ret_not_init_CNS,  
    EXTHWG_POE_ret_failed_E    = EXTHWG_POE_ret_failed_CNS,
    EXTHWG_POE_ret_not_owned_E = EXTHWG_POE_ret_not_owned_CNS,
    EXTHWG_POE_ret_timeout_E   = EXTHWG_POE_ret_timeout_CNS,
    EXTHWG_POE_ret_last_E,
} EXTHWG_POE_ret_ENT;
/********************************************************************************
*        These variables can be customized by the user
*********************************************************************************/
extern GT_U32 EXTDRVIPC_WAIT_FOR_RESPONSE_TIMEOUT_uSec;
extern GT_U32 EXTDRVIPC_WAIT_FOR_RESPONSE_NUM_OF_RETRIES;

/*******************************************************************************
* DRAGONITE_HW_WRITE_MASKED_FUNC
*
* DESCRIPTION:
*       Write data to register with mask applied
*
* INPUTS:
*       hwData      - a custom data. This data is passed to
*                     extDrvDragoniteDriverInit
*       as          - Address space
*                     as==0  - Switching core registers
*                     as==1  - Control And Management (PCI) registers
*                     as==2  - Reset And Init Controller (DFX) registers
*       regAddr     - the register address within given address space
*       data        - data word to write
*       mask        - Data mask. Only bits which is set in mask will be changed
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - otherwise.
*
*******************************************************************************/
typedef GT_STATUS (*DRAGONITE_HW_WRITE_MASKED_FUNC)
(
    IN  void*       hwData,
    IN  GT_U32      as,
    IN  GT_U32      regAddr,
    IN  GT_U32      data,
    IN  GT_U32      mask
);

/**
* @internal extDrvDragoniteDriverInit function
* @endinternal
*
* @brief   Initialize dragonite driver - addresses of ITCM/DTCM, method
*         to access POE configuration registers
*         (in Packet Processor address space)
* @param[in] hwInfoPtr                - hardware info srtuctute of selected PP
* @param[in] hwData                   - custom data, will be first parameter of hwWriteMaskedFunc
* @param[in] hwWriteMaskedFunc        - function to write PP registers
*                                       GT_OK if successful
*
* @note Available only in NOKM
*
*/
GT_STATUS extDrvDragoniteDriverInit(
    IN CPSS_HW_INFO_STC   *hwInfoPtr,
    IN void*              hwData,
    IN DRAGONITE_HW_WRITE_MASKED_FUNC hwWriteMaskedFunc
);

/*
 * typedef: enum extDrvDrgReg_ENT
 *
 * Description: Enumeration For Dragonite control registers (registers located outside the drg, i.e in MG or DFX)
 *
* COMMENTS:
*       Available only in NOKM
*/
typedef enum
{
    extDrvDrgReg_ctrl,
    extDrvDrgReg_maskIrq,
    extDrvDrgReg_reset,
    extDrvDrgReg_jtag
} extDrvDrgReg_ENT;

/**
* @internal extDrvDragoniteCtrlRegWrite function
* @endinternal
*
* @brief   Sets a Dragonite ctrl register (a register which is not found in the DTCM area)
*
* @retval GT_NOT_INITIALIZED       - when driver fields were not init by NOKM
* @retval GT_BAD_PARAM             - when reg is out of enum range.
*
* @note Available only in NOKM
*
*/
GT_STATUS extDrvDragoniteCtrlRegWrite (
    IN extDrvDrgReg_ENT reg,
    IN GT_U32 mask,
    IN GT_U32 value
);


/**
* @internal extDrvDragoniteSharedMemWrite function
* @endinternal
*
* @brief   Write a given buffer to the given address in shared memory of Dragonite
*         microcontroller.
* @param[in] offset                   - Offset from beginning of shared memory
* @param[in] buffer                   - The  to be written.
* @param[in] length                   - Length of buffer in bytes.
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - otherwise.
*/
GT_STATUS extDrvDragoniteSharedMemWrite
(
    IN  GT_U32  offset,
    IN  GT_VOID *buffer,
    IN  GT_U32  length
);

/**
* @internal extDrvDragoniteSharedMemRead function
* @endinternal
*
* @brief   Read a data from the given address in shared memory of Dragonite microcontroller
*
* @param[in] offset                   - Offset from beginning of shared memory
* @param[in] length                   - Length of the memory block to read (in
*                                      bytes).
*
* @param[out] buffer                   - The read data.
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - otherwise.
*/
GT_STATUS extDrvDragoniteSharedMemRead
(
    IN  GT_U32  offset,
    IN  GT_U32  length,
    OUT GT_VOID *buffer
);

/**
* @internal extDrvDragoniteShMemBaseAddrGet function
* @endinternal
*
* @brief   Get start address of communication structure in DTCM
*
* @param[out] dtcmPtr                  - Pointer to beginning of DTCM, where
*                                      communication structures must be placed
*                                       GT_OK if successful, or
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteShMemBaseAddrGet
(
    OUT  GT_U32  *dtcmPtr
);


/**
* @internal extDrvDragoniteFwCrcCheck function
* @endinternal
*
* @brief   This routine executes Dragonite firmware checksum test
*
* @note Mostly for debug purposes, when FW download executed by CPSS CRC check
*       engaged automatically
*
*/
GT_STATUS extDrvDragoniteFwCrcCheck
(
    GT_VOID
);

/**
* @internal extDrvDragoniteDevInit function
* @endinternal
*
* @brief   Config and enable dragonite sub-system. CPU still in reset
*/
GT_STATUS extDrvDragoniteDevInit
(
    GT_VOID
);

/**
* @internal extDrvDragoniteUnresetSet function
* @endinternal
*
* @brief   Reset/Unreset Dragonite.
*
* @param[in] unresetEnable            - GT_TRUE - set to un-reset state
*                                      GT_FALSE - set to reset state
*                                       GT_OK if successful, or
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteUnresetSet
(
    GT_BOOL unresetEnable
);


/**
* @internal extDrvDragoniteMemoryTypeSet function
* @endinternal
*
* @brief   Reset/Unreset Dragonite.
*
* @param[in] memType                  - 0 - ITCM
*                                      1 - DTCM
*                                       GT_OK if successful, or
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteMemoryTypeSet
(
    GT_U32 memType
);


/**
* @internal extDrvDragoniteFwDownload function
* @endinternal
*
* @brief   Download FW to instruction shared memory
*/
GT_STATUS extDrvDragoniteFwDownload
(
    IN GT_VOID  *buf,
    GT_U32      size
);

/**
* @internal extDrvDragoniteRegisterRead function
* @endinternal
*
* @brief   Dragonite register read.
*
* @param[in] addr                     - register address to read from.
*
* @param[out] valuePtr                 - (pointer to) returned value
*                                       GT_OK if successful, or
*
* @retval GT_BAD_PTR               - on NULL pointer
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteRegisterRead
(
    IN  GT_U32 addr,
    OUT GT_U32 *valuePtr
);

/**
* @internal extDrvDragoniteRegisterWrite function
* @endinternal
*
* @brief   Dragonite register write.
*
* @param[in] addr                     - register address to write.
*                                      value - register value to write.
*                                       GT_OK if successful, or
*
* @retval GT_BAD_PTR               - on NULL pointer
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteRegisterWrite
(
    IN  GT_U32 addr,
    IN  GT_U32 regValue
);

/**
* @internal extDrvDragoniteMsgWrite function
* @endinternal
*
* @brief   Dragonite message write.
*
* @param[in] msg[DRAGONITE_DATA_MSG_LEN] - buffer to write.
*                                       GT_OK if successful, or
*
* @retval GT_BAD_PTR               - on NULL pointer
* @retval GT_NOT_READY             - ownership problem
* @retval GT_NOT_INITIALIZED       - driver not initialized
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteMsgWrite
(
    IN GT_U8 msg[DRAGONITE_DATA_MSG_LEN]
);

/**
* @internal extDrvDragoniteMsgRead function
* @endinternal
*
* @brief   Dragonite message write.
*
* @param[in] msg[DRAGONITE_DATA_MSG_LEN] - buffer to write.
*                                       GT_OK if successful, or
*
* @retval GT_BAD_PTR               - on NULL pointer
* @retval GT_NOT_READY             - ownership problem
* @retval GT_NOT_INITIALIZED       - driver not initialized
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteMsgRead
(
    OUT GT_U8 msg[DRAGONITE_DATA_MSG_LEN]
);

/**
* @internal extDrvDragoniteProtect function
* @endinternal
*
* @brief   Protect the Dragonite ITCM area
*
* @param[in] protect                  - true = protect
*                                      flase = unprotect
*                                       GT_OK if successful, or
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvDragoniteProtect
(
    IN GT_BOOL protect
);


/**
* @internal extDrvIpcDrgInit function
* @endinternal
*
* @brief   Initialize the IPC messaging driver that communicates with the
*          Dragonite
*
* @param[in] hwInfoPtr            - pointer to a structure contains HW addresses
*
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - othersise.
*/
GT_STATUS extDrvIpcDrgInit(
    IN CPSS_HW_INFO_STC   *hwInfoPtr
);

/**
* @internal extDrvIpcPoeMsgRead function
* @endinternal
*
* @brief   Marvell PoE protocol compliant for IPC Rx messages
*
* @param[in] msg_opcode               - Opcode of requested msg
* @param[in] msg_request_len          -
* @param[in] msg_request_PTR          - Buffer of max length
*       DRAGONITE_DTCM_IPC_MAX_INTERNAL_TX_DATA_MSG_SIZE
*
* @param[out] msg_response_len_PTR    - actual msg len read
* @param[out] msg_response            - the message that was read
*
* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - otherwise.
*/
GT_STATUS extDrvIpcPoeMsgRead(
    IN   GT_32  msg_opcode,
    IN   GT_U32 msg_request_len,
    IN   GT_U8  *msg_request_PTR, /* Buffer with max length extDrvIpc_MAX_INTERNAL_TX_DATA_MSG_SIZE */
    OUT  GT_U32 *msg_response_len_PTR,
    OUT  GT_U8  msg_response[EXTDRVIPC_MAX_INTERNAL_RX_DATA_MSG_SIZE]
);

/**
* @internal extDrvIpcPoeMsgWrite function
* @endinternal
*
* @brief   Marvell PoE protocol compliant for IPC Tx messages
*
* @param[in] msg_opcode               - Opcode of requested msg
* @param[in] msg_request_len          -
* @param[in] msg_request_PTR          - Buffer of max length
*       DRAGONITE_DTCM_IPC_MAX_INTERNAL_TX_DATA_MSG_SIZE
*

* @retval GT_OK                    - on success,
* @retval GT_FAIL                  - othersise.
*/
GT_STATUS extDrvIpcPoeMsgWrite(
    IN   GT_32  msg_opcode,
    IN   GT_U32 msg_request_len,
    IN   GT_U8  *msg_request_PTR, /* Buffer with max length DRAGONITE_DTCM_IPC_MAX_INTERNAL_TX_DATA_MSG_SIZE */
    IN   GT_BOOL is_debug
);

/**
* @internal extDrvIpcCm3CreateChannel function
* @endinternal
*
* @brief   Re-init CM3 IPc driver; only the IPc section (can be used to clear IPc)
*
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - driver no exists
* @retval GT_FAIL                  - on error.
*/
GT_STATUS extDrvIpcCm3CreateChannel(
    void
);

/**
* @internal extDrvIpcCm3Init function
* @endinternal
*
* @brief   Init IPc driver in order to 
*          communicate with CM3 FW
*
* @param[in] devNum                - Device Number
* @param[in] coreId                - CM3 core ID
*
* @retval GT_OK                    - on success.
* @retval GT_NOT_SUPPORTED         - no service CPU on this PP,
* @retval GT_NO_SUCH               - driver no exists
* @retval GT_FAIL                  - on error.
*/
extern GT_STATUS extDrvIpcCm3Init(
    IN GT_U8                devNum,
    IN GT_U32               coreId
);

/**
* @internal extDrvIpcCm3UnresetSet function
* @endinternal
*
* @brief   Reset/Unreset CM3.
*
* @param[in] unresetEnable            - GT_TRUE - set to un-reset state
*                                       GT_FALSE - set to reset state
* @param[in] coreId                   - CM3 core ID
* @retval                               GT_OK if successful, or
*                                       GT_FAIL otherwise.
*/
GT_STATUS extDrvIpcCm3UnresetSet(
    GT_BOOL unresetEnable,
    GT_U32  coreId
);

/**
* @internal extDrvIpcCm3FwDownload function
* @endinternal
*
* @brief   Download FW to CM3 SRAM
*
* @param[in] coreId  - CM3 core ID
* @param[in] buf  - pointer to FW buffer
* @param[in] size - size of FW
*
*/
GT_STATUS extDrvIpcCm3FwDownload
(
    IN GT_U32   coreId,
    IN GT_VOID  *buf,
    GT_U32      size
);

/**
* @internal extDrvIpc15ByteMsgWrite function
* @endinternal
*
* @brief   CM3 IPc "15 Bytes" message write
*
* @param[in] msg_PTR          - pointer to message buffer
*/
GT_STATUS extDrvIpc15ByteMsgWrite(
    INOUT GT_U8 *msg_PTR
);

/**
* @internal extDrvIpc15BytesMsgRead function
* @endinternal
*
* @brief   CM3 IPc "15 Bytes" message read
*
* @param[in] msg_PTR          - pointer to message buffer
*/
GT_STATUS extDrvIpc15BytesMsgRead(
    INOUT GT_U8 *msg_PTR
);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __gtDragoniteDrvh */




