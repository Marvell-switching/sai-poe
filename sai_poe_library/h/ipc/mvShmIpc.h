/*******************************************************************************
*              (c), Copyright 2016, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
*/
/**
********************************************************************************
* @file mvShmIpc.h
*
* @brief Low-level IPC implementation
*
* @version   1
********************************************************************************
*/
#ifndef __mvShmIpc_h__
#define __mvShmIpc_h__

/*
 * Define the following macro do disable BootChannel support.
 * This will save 384 bytes in IPC shared memory
 *
 * #define MV_SHM_IPC_DISABLE_BOOTCHANNEL_APIS
 */

#if defined(CHX_FAMILY) || defined(PX_FAMILY)
#define CPSS_CODE
#endif

#ifdef CPSS_CODE
#  include <cpss/extServices/os/gtOs/gtGenTypes.h>
#  include <cpss/extServices/private/prvCpssBindFunc.h>
#else /* !CPSS_CODE */
#  ifndef PLAIN_GCC
#    include <stdint.h>
#    include <h/ipc/common.h>
#  endif /* PLAIN_GCC */
#endif

#ifdef CPSS_CODE
#  define IPC_UINTPTR_T GT_UINTPTR
#  define IPC_U32       GT_U32
#else
#  ifdef PLAIN_GCC
#    define IPC_UINTPTR_T __UINTPTR_TYPE__
#    define IPC_U32       __UINT32_TYPE__
#  else
#    define IPC_UINTPTR_T uintptr_t
#    define IPC_U32       uint32_t
#  endif
#endif
#ifndef IN
#  define IN
#endif
#ifndef OUT
#  define OUT
#endif
#ifndef INOUT
#  define INOUT
#endif
#define IPC_PTR       IPC_U32

/*
 * CONSTRAINTS:
 * 1. Only one thread on server or client side can access one channel
 * 2. Only one thread can configure channels on server side
 */

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * The IPC structure MUST match the follows constraints
 *     256 bytes at the begin are allocated for boot channel
 *     4*IPC_SHM_NUM_REGS bytes for IPC virtual registers
 *     4 byte magic number
 */
#define IPC_SHM_MAGIC       0x17354628
#define IPC_SHM_CHANNELS    6
#define IPC_SHM_NUM_REGS    32
#define IPC_RESVD_MAGIC     0x5a5b5c5d

/*
 * Typedef: enum IPC_SHM_SYNC_FUNC_MODE_ENT
 *
 * Description: Defines operations for IPC_SHM_SYNC_FUNC
 *
 * Enumerations:
 *      IPC_SHM_SYNC_FUNC_MODE_READ_E
 *                          - Direct read from target's absolute address
 *                            ptr is pointer to store data to
 *                            targetPtr is target's address
 *                            size is data size to read
 *      IPC_SHM_SYNC_FUNC_MODE_WRITE_E
 *                          - Direct write to target's absolute address
 *                            ptr is pointer to data
 *                            targetPtr is target's address
 *                            size is data size to write
 */
typedef enum {
    IPC_SHM_SYNC_FUNC_MODE_READ_E,
    IPC_SHM_SYNC_FUNC_MODE_WRITE_E
} IPC_SHM_SYNC_FUNC_MODE_ENT;
typedef void (*IPC_SHM_SYNC_FUNC)
(
    IN  void*   cookie,
    IN  IPC_SHM_SYNC_FUNC_MODE_ENT mode,
    IN  void*   ptr,
    IN  IPC_UINTPTR_T targetPtr,
    IN  IPC_U32 size
);

/*
 * typedef: struct IPC_SHM_STC
 *
 * Description: A control structure for low-level IPC
 *
 * Fields:
 *
 *   shm          - virtual address IPC shared memory block
 *   shmLen       - length of IPC shared memory block
 *   server       - role (server/client).
 *                  Each channel is a pair of FIFOs
 *                  For server the FIFOs are Rx,Tx
 *                  For client - Tx, Rx
 *
 * Comments:
 *   This management structure stored in application memory, not on shared mem.
 *   Therefore, a copy of such structure exists both on server and client.
 *   shm points to virtual address of the shared memory, from application space.
 *
 */
typedef struct IPC_SHM_STCT {
    IPC_UINTPTR_T       shm;
    IPC_U32             shmLen;
    int                 server;
    IPC_SHM_SYNC_FUNC   syncFunc;
    void*               syncCookie;
} IPC_SHM_STC;

/**
* @internal shmIpcInit function
* @endinternal
*
* @brief   Initialize SHM.
*         Server side also initialize SHM data block (reset SHM, set magick, etc)
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @param[in] shm_virt_addr            - virtual address of shared memory block
* @param[in] size                     - the  of SHM block
* @param[in] server                   - role: 1 - server, 0 - client
* @param[out] shm                     - SHM control structure
* @param[in] syncFuncPtr              - pointer to sync data in/out (optional)
* @param[in] syncCookie               - cookie value for syncFuncPtr
*
*/
void shmIpcInit(
    OUT IPC_SHM_STC *shm,
    IN  void        *shm_virt_addr,
    IN  int          size,
    IN  int          server,
    IN IPC_SHM_SYNC_FUNC   syncFuncPtr,
    IN void*        syncCookie
);

/**
* @internal shmIpcConfigChannel function
* @endinternal
*
* @brief   Configure IPC channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @param[in] shm                      - SHM control structure
* @param[in] chn                      - IPC channel number to configure
* @param[in] maxrx                    - max number of messages in Rx FIFO
*                                      must be power of 2
* @param[in] rxsize                   - max message size in Rx FIFO
* @param[in] maxtx                    - max number of messages in Tx FIFO
*                                      must be power of 2
*                                      txsize      - max message size in Tx FIFO
*
* @retval 0                        - on success
*                                       -1     - already configured\
*                                       -2     - can't configure (no memory left)
*                                       -3     - bad parameter
*/
int shmIpcConfigChannel(
    IN  IPC_SHM_STC *shm,
    IN  int          chn,
    IN  int          maxrx,
    IN  int          rxsize,
    IN  int          maxtx,
    IN  int          txsixe
);

/**
* @internal shmIpcUsedTxBufLengthGet function
* @endinternal
*
* @brief   Get Tx IPC channel length
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @param[in] shm        - SHM control structure
* @param[in] chn        - IPC channel number
* @param[out] lengthPtr  - (pointer to) Used Buffer length
* @param[out] sizePtr    - (pointer to) Total buffer size
*
* @retval 0             - on success
*                          -1     - Tx fifo not configured (zero size)
*                          -3     - bad parameter: message too long
*                          -4     - IPC or CPU is dead
*/
int shmIpcUsedTxBufLengthGet
(
    IN  IPC_SHM_STC *shm,
    IN  int          chn,
    OUT unsigned int *lengthPtr,
    OUT unsigned int *sizePtr
);

/**
* @internal shmIpcSend function
* @endinternal
*
* @brief   Send message to IPC channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @param[in] shm                      - SHM control structure
* @param[in] chn                      - IPC channel number
* @param[in] data                     -  to send
* @param[in] size                     - data size
*
* @retval 0                        - on success
*                                       -1     - Tx fifo not configured (zero size)
*                                       -2     - full
*                                       -3     - bad parameter: message too long
*/
int shmIpcSend(
    IN  IPC_SHM_STC *shm,
    IN  int          chn,
    IN  const void  *data,
    IN  int          size
);

/**
* @internal shmIpcRecv function
* @endinternal
*
* @brief   Receive message from IPC channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @param[in] shm                      - SHM control structure
* @param[in] chn                      - IPC channel number
* @param[in,out] size                     - data buffer
*
* @param[out] data                     -  buffer
* @param[in,out] size                     - received data
*
* @retval 1                        - Received
* @retval 0                        - No data (FIFO empty)
*                                       -1     - Rx fifo not configured (zero size)
*/
int shmIpcRecv(
    IN    IPC_SHM_STC *shm,
    IN    int          chn,
    OUT   void        *data,
    INOUT int         *size
);

/**
* @internal shmIpcRxReady function
* @endinternal
*
* @brief   Check if RX data available in any channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval 0                        - No messages(yet)
* @retval non 0                    - Messages are pending
*/
int shmIpcRxReady(IPC_SHM_STC* shm); /* returns bitmask */

/**
* @internal shmIpcRxChnReady function
* @endinternal
*
* @brief   Check if RX data available in the channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval 0                        - No messages(yet)
* @retval non 0                    - Messages are pending
*/
int shmIpcRxChnReady(IPC_SHM_STC* shm, int chn);


#ifndef MV_SHM_IPC_DISABLE_BOOTCHANNEL_APIS

/**
* @internal shmIpcBootChnSend function
* @endinternal
*
* @brief   Send message to IPC boot channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @param[in] shm                      - SHM control structure
* @param[in] retCode                  - return code (header bits 0..7)
* @param[in] msg                      - data to send
* @param[in] size                     - data size
*
* @retval 0                        - on success
*                                       -2     - busy
*                                       -3     - bad parameter: message too long
*/
int shmIpcBootChnSend(
    IN  IPC_SHM_STC *shm,
    IN  int          retCode,
    IN  const void  *msg,
    IN  int          size
);

/**
* @internal shmIpcBootChnRecv function
* @endinternal
*
* @brief   Receive message from IPC boot channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
* @param[in] shm                      - SHM control structure
* @param[in] maxSize                  - data buffer size
*
* @param[out] retCodePtr               - return code (header bits 0..7), can be NULL
*                                      data        - data buffer
*
* @retval >0                       - size of received message received
* @retval 0                        - No data (no messafe)
*                                       -2     - Boot channel busy
*/
int shmIpcBootChnRecv(
    IN  IPC_SHM_STC *shm,
    OUT int         *retCodePtr,
    OUT void        *msg,
    IN  int          maxSize
);

/**
* @internal shmIpcBootChnReady function
* @endinternal
*
* @brief   Check if RX data available in the boot channel
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval 0                        - No messages(yet)
* @retval non 0                    - Messages are pending
*/
int shmIpcBootChnReady(IPC_SHM_STC* shm);

/**
* @internal shmIpcBootChnBusy function
* @endinternal
*
* @brief   Check if boot channel is busy
*         If channel is busy then it is impossible to send data
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval 0                        - Not busy
* @retval non 0                    - Busy
*/
int shmIpcBootChnBusy(IPC_SHM_STC* shm);

/**
* @internal shmIpcRegRead function
* @endinternal
*
* @brief   Read IPC 32bit virtual register
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*                                       Register value (converted from Little Endian to host byte order)
*/
IPC_U32 shmIpcRegRead(IPC_SHM_STC* shm, int reg);

/**
* @internal shmIpcMagicGet function
* @endinternal
*
* @brief  Get IPC channel magic
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval IPC channel magic value
*/
IPC_U32 shmIpcMagicGet(IPC_SHM_STC* shm);

/**
* @internal shmIpcSizeGet function
* @endinternal
*
* @brief  Get IPC channel size
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval IPC channel size value
*/
IPC_U32 shmIpcSizeGet(IPC_SHM_STC* shm);

/**
* @internal shmIpcRegWrite function
* @endinternal
*
* @brief   Write IPC 32bit virtual register
*         Convert from host byte order to Little Endian.
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
*                                       None
*/
void shmIpcRegWrite(IPC_SHM_STC* shm, int reg, IPC_U32 value);

#endif /* !defined(MV_SHM_IPC_DISABLE_BOOTCHANNEL_APIS) */

/**
* @internal shmResvdAreaRegRead function
* @endinternal
*
* @brief   Read IPC 32bit register in reserved area
*         Convert from Little Endian to host byte
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @param[in] shm    - SHM control structure.
* @param[in] regPtr - Pointer to register 0. For exampel on CM3 0x2fffc
* @param[in] reg    - Register number. The registers are enumerated
*                     from the end of SRAM. For example on CM3
*                     register 0 will have address 0x2fffc
*                     register 1 will have address 0x2fff8
*                     register 2 will have address 0x2fff4
*
* @retval Register value (converted from Little Endian to host byte order)
*/
IPC_U32 shmResvdAreaRegRead(
    IPC_SHM_STC *shm,
    IPC_UINTPTR_T regPtr,
    int reg
);

/**
* @internal shmResvdAreaRegWrite function
* @endinternal
*
* @brief   Write IPC 32bit register in reserved area
*         Convert from host byte order to Little Endian.
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
* @param[in] shm    - SHM control structure.
* @param[in] regPtr - Pointer to register 0. For exampel on CM3 0x2fffc
* @param[in] reg    - Register number. The registers are enumerated
*                     from the end of SRAM. For example on CM3
*                     register 0 will have address 0x2fffc
*                     register 1 will have address 0x2fff8
*                     register 2 will have address 0x2fff4
* @param[in] data   - data to write (host byte order)
*/
void shmResvdAreaRegWrite(
    IPC_SHM_STC *shm,
    IPC_UINTPTR_T regPtr,
    int reg,
    IPC_U32 data
);

#endif /* __mvShmIpc_h__ */

