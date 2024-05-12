#include <h/gtDragoniteDrv.h>

#define EXTHWG_POE_IPC_MAX_REQUEST_MESSAGE_SIZE_CNS 248
#define EXTHWG_POE_IPC_MAX_RESPONSE_MESSAGE_SIZE_CNS 244

#define EXTHWG_POE_IPC_MEM_BLOCK_SIZE_CNS 512

extern uint32_t prvDrvCpssWriteMasked(
      void *drvData,
      uint32_t addrSpace,
      uint32_t regAddr,
      uint32_t data,
      uint32_t mask);

extern uint32_t EXTHWG_POE_Ipc_WAIT_FOR_RESPONSE_TIME_uSec;
extern uint32_t EXTHWG_POE_Ipc_WAIT_FOR_RESPONSE_NUM_OF_RETRIES;

typedef enum {
    ExthwgPoeIpcMcuTypeDragonite,
    ExthwgPoeIpcMcuTypeCm3,
    ExthwgPoeIpcMcuTypeLast
} ExthwgPoeIpcMcuTypeEnt;

#define exthwg_poe_ipc_debug_msg_time_calcdex(_msg_op_code)    \
    ((0x10 * (_msg_op_code>>24)) + (_msg_op_code & 0xFF))

/**
 * @brief 
 * 
 * @param[in] mcuType
 * @param[in] dragoniteDevNum
 * 
 * @return 
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcIt(
    ExthwgPoeIpcMcuTypeEnt mcuType,
    uint8_t dragoniteDevNum
);

/**
 * @brief 
 * 
 * @param[in] mcuType
 * 
 * @return 
 */
extern uint32_t exthwgPoeIpcReit (
    ExthwgPoeIpcMcuTypeEnt mcuType
);

/**
 * @brief 
 * 
 * @param[in] send
 * @param[in] opCode32
 * @param[in] dataLen
 * @param[in] dataPtr
 * 
 * @return 
 */
bool exthwgPoeIpcSendReceiveMsg(
    bool send,
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
);

/**
 * @brief 
 * 
 * @param[in] send
 * @param[in] opCode32
 * @param[in] dataLen
 * @param[in] dataPtr
 * 
 * @return 
 */
bool exthwgPoeDrgIpcSendReceiveMsg(
    bool send,
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
);

/**
 * @brief 
 * 
 * @param[in] send
 * @param[in] opCode32
 * @param[in] dataLen
 * @param[in] dataPtr
 * 
 * @return 
 */
bool exthwgPoeCm3IpcSendReceiveMsg(
    bool send,
    uint32_t opCode32,
    uint8_t dataLen,
    uint8_t *dataPtr
);

/**
 * @brief 
 * 
 * @param[in] opcode
 * @param[in] readRequestDataLen
 * @param[in] readRequestDataPtr Buffer with max length EXTHWG_POE_TI_MAX_REQUEST_MESSAGE_SIZE
 * @param[out] readResponseDataLenPtr
 * @param[out] readResponseDataPtr Buffer with max length EXTHWG_POE_TI_MAX_RESPONSE_MESSAGE_SIZE
 * 
 * @return 
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcRead(
    uint32_t opcode,
    uint32_t readRequestDataLen,
    uint8_t *readRequestDataPtr,
    uint32_t *readResponseDataLenPtr,
    uint8_t *readResponseDataPtr
);

/**
 * @brief 
 * 
 * @param[in] opcode
 * @param[in] writeRequestDataLen
 * @param[in] writeRequestDataPtr Buffer with max length EXTHWG_POE_TI_MAX_REQUEST_MESSAGE_SIZE
 * @param[in] isDebug
 * 
 * @return 
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcWrite(
    uint32_t opcode,
    uint32_t writeRequestDataLen,
    uint8_t *writeRequestDataPtr,
    bool isDebug
);

/**
 * @brief 
 * 
 * @param[in] buf
 * @param[in] size
 * @param[in] mcuType
 * 
 * @return 
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcDownloadFirmware(
    void *buf,
    uint32_t size, 
    ExthwgPoeIpcMcuTypeEnt mcuType
);

/**
 * @brief 
 * 
 * @param[in] mcuType
 * @param[in] fwFileName
 * 
 * @return 
 */
extern EXTHWG_POE_ret_TYP exthwgPoeIpcRunFirmware(
    ExthwgPoeIpcMcuTypeEnt mcuType,
    char *fwFileName
);

extern void exthwgPoeIpcRemoveFwFlagLoaded(void);

/**
 * @brief 
 * 
 * @param[in] blockNum
 * @param[in] buf Buffer with max length EXTHWG_POE_IPC_MEM_BLOCK_SIZE_CNS
 * 
 * @return 
 */
extern bool exthwgPoeIpcDebugPrtMemBlock(
    uint32_t blockNum,
    uint8_t buf[EXTHWG_POE_IPC_MEM_BLOCK_SIZE_CNS]
);

/**
 * @brief Initialize the EXTHWG POE IPC module.
 * 
 * @param[in] mcuType The type of MCU for the initialization.
 * @param[in] devNum The device number.
 * 
 * @return EXTHWG_POE_ret_TYP Returns the initialization status.
 */
EXTHWG_POE_ret_TYP exthwgPoeIpcInit(
    ExthwgPoeIpcMcuTypeEnt mcuType,
    uint8_t devNum
);