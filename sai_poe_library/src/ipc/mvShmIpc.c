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
* @file mvShmIpc.c
*
* @brief Low-level IPC implementation
*
* @version   1
********************************************************************************
*/

#include <h/ipc/mvShmIpc.h>

#ifndef NULL
#define NULL ((void*)0L)
#endif

/*******************************************************************************
* Environment definitions:
*   IPCU32TOSHM             host U32 value => IPC (LE)
*   IPCSHMTOU32             IPC value (LE) => host U32
*   IPC_SYNC
*
*******************************************************************************/

#ifdef CPU_BE
#  ifdef CPSS_CODE
#    include <cpssCommon/cpssPresteraDefs.h>
#    define IPC_BYTE_SWAP_32BIT(X) CPSS_BYTE_SWAP_32BIT(X)
#  endif
#  ifndef IPC_BYTE_SWAP_32BIT
#    define IPC_BYTE_SWAP_32BIT(_val)     \
          ((((_val)&0xff)<<24) |          \
           (((_val)&0xff00)<<8) |         \
           (((_val)&0xff0000)>>8) |       \
           (((_val)&0xff000000)>>24))
#  endif
#  define IPCU32TOSHM(_val)         IPC_BYTE_SWAP_32BIT(_val)
#  define IPCSHMTOU32(_val)         IPC_BYTE_SWAP_32BIT(_val)
#else
#  define IPCU32TOSHM(_val)       (_val)
#  define IPCSHMTOU32(_val)       (_val)
#endif

#define IPC_SHM_ALIGN(_size)     (((_size)+3)&(~3))

/* Synchronzation primitives */
#define IPC_OFFSETOF(_type,_member) ((IPC_U32)((IPC_UINTPTR_T)&(((_type*)NULL)->_member)))

#ifdef CPSS_CODE
# define IPC_SYNC()             GT_SYNC
#else
# ifdef __GNUC__
#  define IPC_SYNC()           __sync_synchronize()
# else
#  define IPC_SYNC()
# endif
#endif

#define IPC_SHM_MAGIC       0x17354628
#define IPC_SHM_CHANNELS    6

/* message header */
typedef struct IPC_SHM_MSG_STCT {
    IPC_U32      ready;
    IPC_U32      length;
    IPC_U32      data[1];
} IPC_SHM_MSG_STC;

/* Fifo header */
typedef struct IPC_SHM_FIFO_STCT {
    IPC_U32      msgSize;
    IPC_U32      size;
    IPC_U32      head;
    IPC_U32      tail;
    IPC_U32      buffer[1];
} IPC_SHM_FIFO_STC;

/**
 * \brief Shared memory IPC header
 *
 *  This structure is stored on the start of shared memory, accessible by
 *  server and client. Actual offset in shared memory is flexible.
 */
typedef struct IPC_SHM_DATA_STCT {
#ifndef MV_SHM_IPC_DISABLE_BOOTCHANNEL_APIS
    IPC_U32      bootChnHdr;         /*!< bit 31: owner, bits 30..18 - size, 0 == free */
    IPC_U32      bootChnData[63];    /*!< data[0] == opcode */
    IPC_U32      registers[IPC_SHM_NUM_REGS];  /*!< boot channel virtual registers */
#endif /* !defined(MV_SHM_IPC_DISABLE_BOOTCHANNEL_APIS) */
    IPC_U32      magic;
    IPC_U32      size;
    IPC_PTR      heap;               /*!< Pointer to available shared memory offset for allocation */
    IPC_U32      rxReady[2]; /* client/server */
    IPC_PTR      fifos[IPC_SHM_CHANNELS*2];
} IPC_SHM_DATA_STC;

#if 1
#define SHM_DATA_ADDR(_shm,_offset) ((void*)((IPC_UINTPTR_T)(_shm->shm) + (_offset)))
#endif

// #if defined  SHARED_MEMORY && !defined MV_HWS_REDUCED_BUILD
// extern void prvIpcSync
// (
//     IN  void*   cookie,
//     IN  IPC_SHM_SYNC_FUNC_MODE_ENT mode,
//     IN  void*   ptr,
//     IN  IPC_UINTPTR_T targetPtr,
//     IN  IPC_U32 size
// );
// #endif

/**
 * \brief Set to zero a region of shared memory.
 *
 * memset cannot be used since access from crossbar must be on word size and
 * boundary. Also flush cache
 *
 * @param[in] ptr   data address (indirect)
 */
static void IPC_BZERO(IPC_SHM_STC *shm, void *ptr, int size)
{
    int i;
    IPC_U32 zero = 0;
    IPC_SHM_SYNC_FUNC   syncFunc = shm->syncFunc;
#if defined  SHARED_MEMORY && !defined MV_HWS_REDUCED_BUILD
#if !defined ASIC_SIMULATION
    syncFunc = prvIpcSync;
#endif
#endif

    for (i = 0; i < size; i+=4)
    {
        syncFunc(shm->syncCookie, IPC_SHM_SYNC_FUNC_MODE_WRITE_E,
                &zero, ((IPC_UINTPTR_T)ptr)+i, 4);
    }
}

static void ipc_write_32(IPC_SHM_STC *shm, void *addr, IPC_U32 data)
{
    IPC_SHM_SYNC_FUNC   syncFunc = shm->syncFunc;
#if defined  SHARED_MEMORY && !defined MV_HWS_REDUCED_BUILD
#if !defined ASIC_SIMULATION
    syncFunc = prvIpcSync;
#endif
#endif
#if defined(CPU_BE) || defined(MV_CPU_BE)
    data = IPCU32TOSHM(data);
#endif
    syncFunc(shm->syncCookie, IPC_SHM_SYNC_FUNC_MODE_WRITE_E,
                &data, (IPC_UINTPTR_T)addr, 4);
}
static IPC_U32 ipc_read_32(IPC_SHM_STC *shm, void *addr)
{
    IPC_U32 data;
    IPC_SHM_SYNC_FUNC   syncFunc = shm->syncFunc;
#if defined  SHARED_MEMORY && !defined MV_HWS_REDUCED_BUILD && !defined ASIC_SIMULATION
#if !defined ASIC_SIMULATION
    syncFunc = prvIpcSync;
#endif
#endif
    syncFunc(shm->syncCookie, IPC_SHM_SYNC_FUNC_MODE_READ_E,
                &data, (IPC_UINTPTR_T)addr, 4);
#if defined(CPU_BE) || defined(MV_CPU_BE)
    data = IPCSHMTOU32(data);
#endif
    return data;
}


/**
 * \brief Copy a region of memory to shared memory.
 *
 * memcpy cannot be used since access from crossbar must be on word size and
 * boundary. Also flush cache
 */
static void IPC_COPYTO(IPC_SHM_STC *shm, void *ptr, const void *src, int size)
{
        IPC_SHM_SYNC_FUNC   syncFunc = shm->syncFunc;
#if defined  SHARED_MEMORY && !defined MV_HWS_REDUCED_BUILD
#if !defined ASIC_SIMULATION
    syncFunc = prvIpcSync;
#endif
#endif
    if (size == 0)
        return;
    syncFunc(shm->syncCookie, IPC_SHM_SYNC_FUNC_MODE_WRITE_E,
            (void*)((IPC_UINTPTR_T)src), (IPC_UINTPTR_T)ptr, size);
}

/**
 * \brief Copy a region of shared memory.
 *
 * memcpy cannot be used since access from crossbar must be on word size and
 * boundary. Also flush cache
 */
static void IPC_COPYFROM(IPC_SHM_STC *shm, void *dest, void *ptr, int size)
{
    IPC_SHM_SYNC_FUNC   syncFunc = shm->syncFunc;
#if defined  SHARED_MEMORY && !defined MV_HWS_REDUCED_BUILD
#if !defined ASIC_SIMULATION
    syncFunc = prvIpcSync;
#endif
#endif
    if (size == 0)
        return;
    syncFunc(shm->syncCookie, IPC_SHM_SYNC_FUNC_MODE_READ_E,
            dest, (IPC_UINTPTR_T)ptr, size);
}



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
)
{
    IPC_SHM_DATA_STC *shmData;

    shm->shm = (IPC_UINTPTR_T)shm_virt_addr;
    shm->shmLen = size;
    shm->server = server ? 1 : 0;
    shm->syncFunc = syncFuncPtr;
    shm->syncCookie = syncCookie;
    shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    if (server)
    {
        IPC_BZERO(shm, shmData, sizeof(*shmData));
        ipc_write_32(shm, &(shmData->magic), IPC_SHM_MAGIC);
        ipc_write_32(shm, &(shmData->size),  shm->shmLen);
        ipc_write_32(shm, &(shmData->heap),  IPC_SHM_ALIGN(sizeof(IPC_SHM_DATA_STC)));
    }
    else
    {
        /* check magic */
        IPC_U32 magic = ipc_read_32(shm, &(shmData->magic));
        if (magic == IPC_SHM_MAGIC)
        {
            magic++;
            ipc_write_32(shm, &(shmData->magic), magic);
        }
    }
}

/**
 * \brief Allocate shared aligned memory from heap
 *
 * Promote heap pointer to next available shared memory
 */
static IPC_PTR shmIpcAlloc(IPC_SHM_STC *shm, int size)
{
    IPC_PTR ptr = (IPC_PTR)0;
    IPC_PTR heap;
    IPC_U32 shmSize;
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC *)shm->shm;
    size = IPC_SHM_ALIGN(size);

    heap = ipc_read_32(shm, &(shmData->heap));
    shmSize = ipc_read_32(shm, &(shmData->size));
    if (heap+size <= shmSize)
    {
        ptr = heap;
        ipc_write_32(shm, &(shmData->heap), heap + size);
        IPC_BZERO(shm, SHM_DATA_ADDR(shm, ptr), size);
    }
    return ptr;
}

/**
 * \brief Allocate memroy from shared memory heap for message fifo
 *
 * Each fifo composed of IPC_SHM_FIFO_STC followed by message buffers
 *
 * @param size number of message buffers in fifo
 * @param msgsize size of each message buffer
 *
 */
static IPC_PTR shmIpcAllocFifo(IPC_SHM_STC *shm, int size, int msgsize)
{
    int allocsize;
    IPC_PTR ptr;
    IPC_SHM_FIFO_STC *fifo;
    if (size == 0 || msgsize == 0)
        return (IPC_PTR)0;
    msgsize += IPC_OFFSETOF(IPC_SHM_MSG_STC, data);
    msgsize = IPC_SHM_ALIGN(msgsize);
    allocsize = IPC_OFFSETOF(IPC_SHM_FIFO_STC,buffer) + size * msgsize;
    ptr = shmIpcAlloc(shm, allocsize);
    if (!ptr)
        return ptr;
    fifo = SHM_DATA_ADDR(shm,ptr);
    ipc_write_32(shm, &(fifo->size), size);
    ipc_write_32(shm, &(fifo->msgSize), msgsize);
    return ptr;
}

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
* @param[in] txsize                   - max message size in Tx FIFO
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
    IN  int          txsize
)
{
    /* TODO: chheck chn range */
    /* data points to IPC header structure in shared memory */
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    /* 2 fifos per channel */
    IPC_U32 ptr, rxfifo, txfifo;

    rxfifo = chn * 2 + ((shm->server) ? 0 : 1);
    txfifo = chn * 2 + ((shm->server) ? 1 : 0);

    /* verify num of fifo items is power of 2 */
    if ((maxrx != 0 && (maxrx & (maxrx - 1))) || (maxtx != 0 && (maxtx & (maxtx -1))))
        return -3;
    if (ipc_read_32(shm, &(shmData->fifos[rxfifo])) || ipc_read_32(shm, &(shmData->fifos[txfifo])))
        return -1; /* already configured */
    ptr = shmIpcAllocFifo(shm, maxrx, rxsize);
    ipc_write_32(shm, &(shmData->fifos[rxfifo]), ptr);
    ptr = shmIpcAllocFifo(shm, maxtx, txsize);
    ipc_write_32(shm, &(shmData->fifos[txfifo]), ptr);
    if (ipc_read_32(shm, &(shmData->fifos[rxfifo])) == 0 && ipc_read_32(shm, &(shmData->fifos[txfifo])) == 0)
        return -2; /* can't configure */
    return 0;
}

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
* @param[out] lengthPtr - (pointer to) Used Buffer length
* @param[out] sizePtr   - (pointer to) Total buffer size
*
* @retval 0             - on success
*                          -1     - Tx fifo not configured (zero size)
*                          -4     - IPC or CPU is dead
*/
int shmIpcUsedTxBufLengthGet
(
    IN  IPC_SHM_STC *shm,
    IN  int          chn,
    OUT unsigned int *lengthPtr,
    OUT unsigned int *sizePtr
)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    IPC_SHM_FIFO_STC *fifo;
    IPC_U32 fifo_tail, fifo_size, fifo_head, fifoNum;
    IPC_U32 txfifo = chn * 2 + ((shm->server) ? 1 : 0);

    if (chn >= IPC_SHM_CHANNELS)
        return -1;

    fifoNum = txfifo;
    txfifo = ipc_read_32(shm, &(shmData->fifos[fifoNum])); /* offset of TX fifo header in shared memory */
    if ((!txfifo) ||
        (txfifo == 0xFFFFFFFF) /* IPC or CPU is dead */)
        return -4;
    /* Get the virtual address of TX fifo header in application space */
    fifo = (IPC_SHM_FIFO_STC *)SHM_DATA_ADDR(shm, txfifo);

    fifo_head = ipc_read_32(shm, &(fifo->head));
    fifo_tail = ipc_read_32(shm, &(fifo->tail));
    fifo_size = ipc_read_32(shm, &(fifo->size));

    *sizePtr = fifo_size;
    if (fifo_head <= fifo_tail)
    {
        *lengthPtr = fifo_tail - fifo_head;
    }
    else
    {
        *lengthPtr = fifo_tail + fifo_size - fifo_head;
    }
    return 0;
}


/**
* @internal shmIpcSend function
* @endinternal
*
* @brief   Send message to IPC channel
*         If the buffer pointed by TX fifo tail is available (ready == 0),
*         message is copied to the buffer, ready set to 1, tail promoted.
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
*                                       -4     - IPC or CPU is dead
*/
int shmIpcSend(
    IN  IPC_SHM_STC *shm,
    IN  int          chn,
    IN  const void  *data,
    IN  int          size
)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    IPC_SHM_FIFO_STC *fifo;
    IPC_SHM_MSG_STC *msgBuffer;
    IPC_U32 msgOffset, fifo_tail, fifo_size;
    IPC_U32 txfifo = chn * 2 + ((shm->server) ? 1 : 0);

    if (chn >= IPC_SHM_CHANNELS)
        return -1;

    txfifo = ipc_read_32(shm, &(shmData->fifos[txfifo])); /* offset of TX fifo header in shared memory */
    if ((!txfifo) ||
        (txfifo == 0xFFFFFFFF) /* IPC or CPU is dead */)
        return -4;
    /* Get the virtual address of TX fifo header in application space */
    fifo = (IPC_SHM_FIFO_STC *)SHM_DATA_ADDR(shm, txfifo);

    /* Ensure message + header can fit into message buffer */
    if (ipc_read_32(shm, &(fifo->msgSize)) < size + IPC_OFFSETOF(IPC_SHM_MSG_STC, data))
    {
        return -3; /* bad parameter: message too long */
    }
    /* Calculate offset of buffer pointed by fifo tail */
    msgOffset = ipc_read_32(shm, &(fifo->tail)) * ipc_read_32(shm, &(fifo->msgSize));
    /* Virtual address of buffer header in application memroy space */
    msgBuffer = (IPC_SHM_MSG_STC*)(((IPC_UINTPTR_T)&(fifo->buffer[0])) + msgOffset);
    if (ipc_read_32(shm, &(msgBuffer->ready)) != 0)
    {
        return -2; /* full */
    }
    /* Copy the message into message buffer */
    IPC_COPYTO(shm, &(msgBuffer->data), data, size);
    ipc_write_32(shm, &(msgBuffer->length), size);

    /* Promote fifo tail (cyclic) */
    fifo_tail = ipc_read_32(shm, &(fifo->tail));
    fifo_size = ipc_read_32(shm, &(fifo->size));
    ipc_write_32(shm, &(fifo->tail), (fifo_tail + 1) & (fifo_size - 1));

    /* Mark buffer as full */
    ipc_write_32(shm, &(msgBuffer->ready), 1);
    IPC_SYNC();

    /* raise rxReady bit */
    {
        IPC_U32 rxReady;
        rxReady = ipc_read_32(shm, &(shmData->rxReady[shm->server]));
        rxReady |= 1 << chn;
        ipc_write_32(shm, &(shmData->rxReady[shm->server]), rxReady);
    }
    /* TODO generate an interrupt??? */

    return 0;
}

/**
* @internal shmIpcRecv function
* @endinternal
*
* @brief   Receive message from IPC channel
*         If the buffer pointed by RX fifo head is available (ready == 1),
*         message is copied from the buffer, ready set to 0, head promoted.
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
)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    IPC_SHM_FIFO_STC *fifo;
    IPC_SHM_MSG_STC *msgBuffer;
    IPC_U32 msgOffset, fifo_size, fifo_head;
    int dataSize;
    IPC_U32 rxfifo = chn * 2 + ((shm->server) ? 0 : 1);

    if (chn >= IPC_SHM_CHANNELS * 2)
        return -1;

    rxfifo = ipc_read_32(shm, &(shmData->fifos[rxfifo])); /* offset of TX fifo header in shared memory */
    if (!rxfifo)
        return -1;
    /* Get the virtual address of RX fifo header in application space */
    fifo = (IPC_SHM_FIFO_STC *)SHM_DATA_ADDR(shm, rxfifo);

    fifo_head = ipc_read_32(shm, &(fifo->head));
    /* Calculate offset of buffer pointed by fifo head */
    msgOffset = fifo_head * ipc_read_32(shm, &(fifo->msgSize));
    /* Virtual address of buffer header in application memroy space */
    msgBuffer = (IPC_SHM_MSG_STC*)(((IPC_UINTPTR_T)&(fifo->buffer[0])) + msgOffset);
    if (ipc_read_32(shm, &(msgBuffer->ready)) == 0)
    {
        return 0; /* not message ready */
    }

    /* Copy up to *size bytes from message buffer */
    dataSize = ipc_read_32(shm, &(msgBuffer->length));
    if (size != NULL)
    {
        if (*size < dataSize)
            dataSize = *size;
    }
    IPC_COPYFROM(shm, data, msgBuffer->data, dataSize);
    if (size != NULL)
        *size = dataSize;

    /* Promote fifo head */
    fifo_size = ipc_read_32(shm, &(fifo->size));
    fifo_head = (fifo_head + 1) & (fifo_size -1);
    ipc_write_32(shm, &(fifo->head), fifo_head);

    /* Mark buffer as empty */
    ipc_write_32(shm, &(msgBuffer->ready), 0);
    IPC_SYNC();

    /* Check if next message buffer is full. If empty - clean channel rxReady bit */
    msgOffset = fifo_head * ipc_read_32(shm , &(fifo->msgSize));
    msgBuffer = (IPC_SHM_MSG_STC*)(((IPC_UINTPTR_T)&(fifo->buffer[0])) + msgOffset);
    if (ipc_read_32(shm, &(msgBuffer->ready)) == 0)
    {
        IPC_U32 rxReady;
        rxReady = ipc_read_32(shm, &(shmData->rxReady[shm->server ^ 1]));
        rxReady &= ~ (1 << chn);
        ipc_write_32(shm, &(shmData->rxReady[shm->server ^ 1]), rxReady);
    }
    return 1;
}
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
int shmIpcRxReady(IPC_SHM_STC* shm) /* returns bitmask */
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    return ipc_read_32(shm, &(shmData->rxReady[shm->server ^ 1]));
}

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
int shmIpcRxChnReady(IPC_SHM_STC* shm, int chn)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    return ipc_read_32(shm, &(shmData->rxReady[shm->server ^ 1])) & (1<<chn);
}

#ifndef MV_SHM_IPC_DISABLE_BOOTCHANNEL_APIS
/**
* @internal shmIpcBootChnSend function
* @endinternal
*
* @brief   Send message to IPC boot channel
*         Boot channel has only one message buffer, shaed for Rx and Tx by both
*         server and client.
*         bootChnHdr field holds ownership bit (31), msg size (30:18), and ret code.
*         New message can be sent only if msg size and ret code are clean.
*         Message is copied into buffer, size and ret code updated and Owenership
*         bit is set to identify destination:
*         Ownership bit='1' - msg destination is client, and vice versa
*         Once destination party read the message, size + ret code fields are cleared.
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
* @retval -2                       - on busy
* @retval -3                       - bad parameter: message too long
*/
int shmIpcBootChnSend(
    IN  IPC_SHM_STC *shm,
    IN  int          retCode,
    IN  const void  *msg,
    IN  int          size
)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    IPC_U32 hdr;

    /* check buffer size field. Only if size = 0, msg can be sent */
    if ((ipc_read_32(shm, &(shmData->bootChnHdr)) & 0x7fffffff) != 0)
        return -2; /* busy */
    if ((unsigned)size > sizeof(shmData->bootChnData))
        return -3; /* bad parameter: message too long */

    /* copy msg to buffer,  */
    IPC_COPYTO(shm, shmData->bootChnData, msg, size);
    /* Update size, ret code and ownership fields */
    hdr = (size << 18) | (retCode & 0xff);
    if (shm->server)
        hdr |= 0x80000000;
    IPC_SYNC();
    ipc_write_32(shm, &(shmData->bootChnHdr), hdr);
    IPC_SYNC();
    return 0;
}

/**
* @internal shmIpcBootChnRecv function
* @endinternal
*
* @brief   Receive message from IPC boot channel
*         Verify size field > 0, and ownership bit points to correct party:
*         Ownership bit='1' - msg destination is client, and vice versa
*         After reading contents, clear size + ret code field to mark buffer empty.
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
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
)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    IPC_U32 hdr, size;
    hdr = ipc_read_32(shm, &(shmData->bootChnHdr));
    if (!hdr)
        return 0; /* no message ready */
    size = (hdr >> 18) & 0x1fff;
    if (retCodePtr != NULL)
        *retCodePtr = hdr & 0xff;
    /* Checking ownership bit to know if this msg is for us or other side */
    hdr = (hdr >> 31) & 1;
    if ((IPC_U32)(shm->server) != hdr)
    {
        /* Message is for us, copy content and clear size + ret code fields */
        if ((IPC_U32)maxSize < size)
            size = maxSize;
        IPC_COPYFROM(shm, msg, shmData->bootChnData, size);
        /* Mark buffer as empty / free */
        ipc_write_32(shm, &(shmData->bootChnHdr), shm->server ? 0 : 0x80000000);
        return size;
    }
    return -2; /* busy */
}

/**
* @internal shmIpcBootChnReady function
* @endinternal
*
* @brief   Check if RX data available in the boot channel
*         Verify size field > 0, and ownership bit points to correct party:
*         Ownership bit='1' - msg destination is client, and vice versa
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
* @retval 0                        - No messages(yet)
* @retval non 0                    - Messages are pending
*/
int shmIpcBootChnReady(IPC_SHM_STC* shm)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    IPC_U32 hdr;
    hdr = ipc_read_32(shm, &(shmData->bootChnHdr));
    if ((hdr & 0x7ffc0000) == 0)
        return 0;
    return (((int)((hdr >> 31) & 1)) == (shm->server^1));
}

/**
* @internal shmIpcBootChnBusy function
* @endinternal
*
* @brief   Check if boot channel is busy
*         If channel is busy then it is impossible to send data
*         Verify size field is clear and ownership bit is '0'.
*         This can happen only after server has read a message.
*         Since FW side is normally the server, and may return message as response,
*         host will always see the channel as busy after calling shmIpcBootChnRecv
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval 0                        - Not busy
* @retval non 0                    - Busy
*/
int shmIpcBootChnBusy(IPC_SHM_STC* shm)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);
    return (ipc_read_32(shm, &(shmData->bootChnHdr)) == 0) ? 1 : 0;
}


/**
* @internal shmIpcRegRead function
* @endinternal
*
* @brief   Read IPC 32bit virtual register
*
* @note   APPLICABLE DEVICES:      xCat3; AC5; Lion2; Bobcat2; Caelum; Aldrin; AC3X; Bobcat3; Aldrin2; Falcon; AC5P; AC5X; Harrier; Ironman; Pipe.
* @note   NOT APPLICABLE DEVICES:  None.
*
*
* @retval  Register value (converted from Little Endian to host byte order)
*/
IPC_U32 shmIpcRegRead(IPC_SHM_STC* shm, int reg)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);

    return ipc_read_32(shm, &(shmData->registers[reg]));
}

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
IPC_U32 shmIpcMagicGet(IPC_SHM_STC* shm)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);

    return ipc_read_32(shm, &(shmData->magic));
}

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
IPC_U32 shmIpcSizeGet(IPC_SHM_STC* shm)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);

    return ipc_read_32(shm, &(shmData->size));
}

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
void shmIpcRegWrite(IPC_SHM_STC* shm, int reg, IPC_U32 value)
{
    IPC_SHM_DATA_STC *shmData = (IPC_SHM_DATA_STC*)(shm->shm);

    ipc_write_32(shm, &(shmData->registers[reg]), value);
}

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
)
{
    if ((regPtr == (IPC_UINTPTR_T)0) && (reg > 0))
        return (IPC_U32)0;
    regPtr -= reg*sizeof(IPC_U32);
    return ipc_read_32(shm, (void*)regPtr);
}

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
* @param[in] shm    - SHM control structure. Applicable if
*                     IPC_SHM_DIRECT_MEM_ACCESS_ONLY not defined
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
)
{
    if ((regPtr == (IPC_UINTPTR_T)0) && (reg > 0))
        return;
    regPtr -= reg*sizeof(IPC_U32);
    ipc_write_32(shm, (void*)regPtr, data);
}

