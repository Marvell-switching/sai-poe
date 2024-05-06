/* Copyright (C) 2023 Marvell International Ltd.
   This program is provided "as is" without any warranty of any kind, and is distributed under the applicable Marvell limited use license agreement. */

/*===========================================================================*/
#ifndef exp_exthw_poe_ipc_h_INCLUDED
#define exp_exthw_poe_ipc_h_INCLUDED
/*!**************************************************RND Template version 4.1
*!                      P A C K A G E       S P E C I F I C A T I O N
*!==========================================================================
*$ TITLE: Dragonite package
*!--------------------------------------------------------------------------
*$ FILpoe_controler/dragonite_ti/src/exp/dragonite_ti_drv.hNAMpoe_controler/dragonite_ti/src/exp/dragonite_ti_drv.h: poe_controler/dragonite_ti/src/exp/dragonite_ti_drv.h
*!--------------------------------------------------------------------------
*$ SYSTEM, SUBSYSTEM: <SysName>
*!--------------------------------------------------------------------------
*$ AUTHORS: lNoam,orib,dmurin,orib
*!--------------------------------------------------------------------------
*$ LATEST UPDATE: 23/06/2022 3:45 PM
*!**************************************************************************
*!
*!**************************************************************************
*!
*$ GENERAL DESCRIPTION:
*!
*$ PROCESS AND ALGORITHM: (local)
*!
*$ PACKAGE GLOBAL SERVICES:
*!     (A list of package global services).
*!
*$ PACKAGE LOCAL SERVICES:  (local)
*!     (A list of package local services).
*!
*$ PACKAGE USAGE:
*!     (How to use the package services,
*!     routines calling order, restrictions, etc.)
*!
*$ ASSUMPTIONS:
*!
*$ SIDE EFFECTS:
*!
*$ RELATED DOCUMENTS:     (local)
*!
*$ REMARKS:               (local)
*!
*!**************************************************************************
*!*/
/*!**************************************************************************
 *$              EXTERNAL DECLARATIONS (IMPORT AND EXPORT)
 *!**************************************************************************
 *!*/
// #include <lib/debug/exp/debug.h>
// #include <../../exp/controller.h>
#include <h/ipc/gtGenTypes.h>
#include <h/ipc/gtDragoniteDrv.h>
/*!**************************************************************************
 *$              PUBLIC DECLARATIONS (EXPORT)
 *!**************************************************************************
 *!*/

/*!**************************************************************************
 *$              PUBLIC VARIABLE DEFINITIONS (EXPORT)
 *!**************************************************************************
 *!*/
/*!**************************************************************************
 *$              PUBLIC FUNCTION DEFINITIONS (EXPORT)
 *!**************************************************************************
 *!*/
/*===========================================================================*/

#define EXTHWG_POE_IPC_MAX_REQUEST_MESSAGE_SIZE_CNS 248
#define EXTHWG_POE_IPC_MAX_RESPONSE_MESSAGE_SIZE_CNS 244

#define EXTHWG_POE_IPC_MEM_BLOCK_SIZE_CNS 512

extern GT_STATUS prvDrvCpssWriteMasked(
    IN  void *drvData,
    IN  GT_U32 addrSpace,
    IN  GT_U32 regAddr,
    IN  GT_U32 data,
    IN  GT_U32 mask);

// extern DEBUGG_id_TYP EXTHWG_POE_debug_ipc_flag;
extern GT_U32 EXTHWG_POE_Ipc_WAIT_FOR_RESPONSE_TIMEOUT_uSec;
extern GT_U32 EXTHWG_POE_Ipc_WAIT_FOR_RESPONSE_NUM_OF_RETRIES;

typedef enum {
    EXTHWG_POE_IPc_MCU_Type_dragonite_E,
    EXTHWG_POE_IPc_MCU_Type_cm3_E,
    EXTHWG_POE_IPc_MCU_Type_last_E
}EXTHWG_POE_IPc_MCU_Type_ENT;


// extern DEBUGG_id_TYP EXTHWG_POE_IPc_debug_msg_flag;

/* for debug purposes */
// typedef PKDT struct {
//     uint32_t num_of_elements;
//     uint32_t sum;
// } PKDB EXTHWG_POE_IPc_debug_time_db_STC;
// extern EXTHWG_POE_IPc_debug_time_db_STC EXTHWG_POE_IPc_debug_time_db[50];
// extern bool EXTHWG_POE_IPc_debug_msg_time_enable;

#define EXTHWG_POE_IPc_debug_msg_time_calcIndex(_msg_op_code)    \
    ((0x10 * (_msg_op_code>>24)) + (_msg_op_code & 0xFF))

/*!**************************************************RND Template version 4.1
 *!     F U N C T I O N   D E S I G N   &   I M P L E M E N T A T I O N
 *!==========================================================================
 *$ TITLE: 
 *!--------------------------------------------------------------------------
 *$ FILENAME: 
 *!--------------------------------------------------------------------------
 *$ SYSTEM, SUBSYSTEM: 
 *!--------------------------------------------------------------------------
 *$ AUTHORS: Tammy
 *!--------------------------------------------------------------------------
 *$ LATEST UPDATE: , 9:23 AM CREATION DATE: 26-Jun-2011
 *!**************************************************************************
 *!
 *!**************************************************************************
 *!
 *$ FUNCTION:  EXTHWG_POE_IPc_init
 *!
 *$ GENERAL DESCRIPTION:
 *!
 *$ RETURNS:
 *!
 *$ ALGORITHM:   (local)
 *!
 *$ ASSUMPTIONS:
 *!
 *$ REMARKS:     (local)
 *!
 *!**************************************************************************
 *!*/
extern EXTHWG_POE_ret_TYP EXTHWG_POE_IPc_init(
    /*!     INPUTS:             */
    EXTHWG_POE_IPc_MCU_Type_ENT mcu_type,
    GT_U8                       dragoniteDevNum
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
);

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_reinit
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
extern GT_STATUS EXTHWG_POE_IPc_reinit (

    /*!     INPUTS:             */
    EXTHWG_POE_IPc_MCU_Type_ENT mcu_type
);

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_send_recieve_msg
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
bool EXTHWG_POE_IPc_send_recieve_msg(
    /*!     INPUTS:             */
    bool                             send,
    uint32_t                             op_code_32,
    uint8_t                              data_len,
    /*!     INPUTS / OUTPUTS:   */
    uint8_t                              *data_PTR
    /*!     OUTPUTS:            */
    );

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_DRG_IPc_send_recieve_msg
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
bool EXTHWG_POE_DRG_IPc_send_recieve_msg(
    /*!     INPUTS:             */
    bool                             send,
    uint32_t                             op_code_32,
    uint8_t                              data_len,
    /*!     INPUTS / OUTPUTS:   */
    uint8_t                              *data_PTR
    /*!     OUTPUTS:            */
    );

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_CM3_IPc_send_recieve_msg
*
* DESCRIPTION: 
*      
*
*****************************************************************************/
bool EXTHWG_POE_CM3_IPc_send_recieve_msg(
    /*!     INPUTS:             */
    bool                             send,
    uint32_t                             op_code_32,
    uint8_t                              data_len,
    /*!     INPUTS / OUTPUTS:   */
    uint8_t                              *data_PTR
    /*!     OUTPUTS:            */
    );

#if 0
/*!**************************************************RND Template version 4.1
 *!     F U N C T I O N   D E S I G N   &   I M P L E M E N T A T I O N
 *!==========================================================================
 *$ TITLE: 
 *!--------------------------------------------------------------------------
 *$ FILENAME: 
 *!--------------------------------------------------------------------------
 *$ SYSTEM, SUBSYSTEM: 
 *!--------------------------------------------------------------------------
 *$ AUTHORS: Tammy
 *!--------------------------------------------------------------------------
 *$ LATEST UPDATE: , 9:23 AM CREATION DATE: 26-Jun-2011
 *!**************************************************************************
 *!
 *!**************************************************************************
 *!
 *$ FUNCTION:  EXTHWG_POE_IPc_read
 *!
 *$ GENERAL DESCRIPTION:
 *!
 *$ RETURNS:
 *!
 *$ ALGORITHM:   (local)
 *!
 *$ ASSUMPTIONS:
 *!
 *$ REMARKS:     (local)
 *!
 *!**************************************************************************
 *!*/
extern EXTHWG_POE_ret_TYP EXTHWG_POE_IPc_read(
	/*!     INPUTS:             */
    uint32_t opcode,
    uint32_t read_request_data_len,
    uint8_t  *read_request_data_PTR /* Buffer with max length EXTHWG_POE_TI_MAX_REQUEST_MESSAGE_SIZE */,

	/*!     INPUTS / OUTPUTS:   */
	/*!     OUTPUTS:            */
    uint32_t *read_response_data_len_PTR,
    uint8_t  *read_response_data_PTR /* Buffer with max length EXTHWG_POE_TI_MAX_RESPONSE_MESSAGE_SIZE */
);



/*!**************************************************RND Template version 4.1
 *!     F U N C T I O N   D E S I G N   &   I M P L E M E N T A T I O N
 *!==========================================================================
 *$ TITLE: 
 *!--------------------------------------------------------------------------
 *$ FILENAME: 
 *!--------------------------------------------------------------------------
 *$ SYSTEM, SUBSYSTEM: 
 *!--------------------------------------------------------------------------
 *$ AUTHORS: Tammy
 *!--------------------------------------------------------------------------
 *$ LATEST UPDATE: , 9:23 AM CREATION DATE: 26-Jun-2011
 *!**************************************************************************
 *!
 *!**************************************************************************
 *!
 *$ FUNCTION:  EXTHWG_POE_IPc_write
 *!
 *$ GENERAL DESCRIPTION:
 *!
 *$ RETURNS:
 *!
 *$ ALGORITHM:   (local)
 *!
 *$ ASSUMPTIONS:
 *!
 *$ REMARKS:     (local)
 *!
 *!**************************************************************************
 *!*/
extern EXTHWG_POE_ret_TYP EXTHWG_POE_IPc_write(
	/*!     INPUTS:             */
    uint32_t opcode,
    uint32_t write_request_data_len,
    uint8_t  *write_request_data_PTR, /* Buffer with max length EXTHWG_POE_TI_MAX_REQUEST_MESSAGE_SIZE */
    bool is_debug

	/*!     INPUTS / OUTPUTS:   */
	/*!     OUTPUTS:            */  
);


extern EXTHWG_POE_ret_TYP  EXTHWG_POE_IPc_download_firmware(
	/*!     INPUTS:             */
	void* buf,
	uint32_t size
	/*!     INPUTS / OUTPUTS:   */
	/*!     OUTPUTS:            */
);
#endif

extern EXTHWG_POE_ret_TYP EXTHWG_POE_IPc_run_firmware(
    /*!     INPUTS:             */
    EXTHWG_POE_IPc_MCU_Type_ENT mcuType,
    char *fw_file_name
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
);


/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_IPc_remove_FW_flag_loaded
*
* DESCRIPTION:   if FW need to be reloaded, need to call this API before 
*                EXTHWG_POE_TI_run_firmware is called
*
*
*****************************************************************************/
extern void EXTHWG_POE_IPc_remove_FW_flag_loaded(void);

/*****************************************************************************
* FUNCTION NAME: EXTHWG_POE_TI_debug_print_mem_block
*
* DESCRIPTION:   Print block of shared memory block
*
*
*****************************************************************************/
extern bool EXTHWG_POE_IPc_debug_print_mem_block(
             /*!     INPUTS:             */
             uint32_t     block_num,
             /*!      INPUTS / OUTPUTS:   */
	         /*!      OUTPUTS:            */
             uint8_t      buf[EXTHWG_POE_IPC_MEM_BLOCK_SIZE_CNS]
);






#endif
/*$ END OF exp_exthw */


