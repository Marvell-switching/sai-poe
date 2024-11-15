/*
 *  Copyright (C) 2024, MARVELL. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

#include <h/poe_v3.h>
#include <h/utils/dictionary.h>
#include <h/utils/lock.h>
#include <PDLIB/h/pdlib/lib/private/prvPdlLib.h>
#include <PDLIB/parser/pdlParser.h>
#include <PDLIB/h/pdlib/init/pdlInit.h>
#include <PDLIB/h/pdlib/lib/pdlLib.h>
#include <h/utils/log.h>
#include <SAI/inc/sai.h>
#include <h/uart_drv.h>
#include <libgen.h>
#include <stdarg.h>

/* include global variables */
/* board info from external file */
static PDL_FEATURE_DATA_STC        *boardInfoDbPtr;
/* xml data root ID */
static XML_PARSER_ROOT_DESCRIPTOR_TYP   xmlRootId;
/* dictionaries for each PoE database */
Dictionary *deviceDbPtr = NULL, *pseDbPtr = NULL, *portDbPtr = NULL;
/* power banks in system */
POE_V3_MSG_SYS_POWER_BANK_STC powerBankList = {0};
/* lock critical sections when reading/writing */
rwlock_excl_t poe_v3_lock;

/**
 * @brief Debug callback
 *
 * @param[in] funcNamePtr function name pointer
 * @param[in] format string format
 *
 * @return void
 */
static void pdLibDebugCallback(const char *funcNamePtr,
                                    const char *format, ...)
{
    va_list     argptr;
    char        log[1024];
    int         len;

    snprintf(log, sizeof(log), "pdlib debug: [%s]", funcNamePtr);
    len = strlen(log);
    vsnprintf(&log[len], sizeof(log) - len, format, argptr);
}

/**
 * @brief Uncompress callback
 *
 * @param[in] archiveFileNamePtr archive file name pointer
 * @param[out] xmlFileNamePtr xml; file name pointer
 * @param[out] signatureFileNamePtr signature file name pointer
 *
 * @return boolean
 */
static BOOLEAN pdLibXmlUncompressCallback(
    IN  char       *archiveFileNamePtr,
    OUT char       *xmlFileNamePtr,
    OUT char       *signatureFileNamePtr
)
{
    char * ch, *xml = xmlFileNamePtr, *sig = signatureFileNamePtr;
    for (ch = archiveFileNamePtr; ch != NULL && *ch != '\0'; ch++, xml++, sig++)
    {
        if (*ch != '.')
        {
            *xml = *sig = *ch;
        }
        else
        {
            strcpy(xml, ".xml");
            strcpy(sig, ".md5");

            return TRUE;
        }
    }

    return FALSE;
}

/**
 * @brief XML signature callback
 *
 * @param[in] xmlFileNamePtr xml file name pointer
 * @param[in] signatureSize signature size
 * @param[out] signaturePtr signature pointer
 *
 * @return boolean
 */
static BOOLEAN pdLibGetXmlSignatureCallback(
    IN  char       *xmlFileNamePtr,
    IN  uint32_t     signatureSize,
    OUT UINT_8     *signaturePtr
)
{
    FILE *xmlFd;
    int32_t fileSize, i, len=0;
    PDL_LIB_MD5_DIGEST_STC md5Digest;

    /*
     * This Secret which has to match with the one provided
     * in the Ezb tool.
     * PDL_LIB_MD5_DIGEST_LENGTH_CNS:16
     */
    UINT_8 xpSaiSignature[]="";
    char step2CombinedStr[(PDL_LIB_MD5_DIGEST_LENGTH_CNS * 2) + sizeof(
                                                                  xpSaiSignature)] = {0};

    xmlFd = fopen(xmlFileNamePtr, "rb");
    if (!xmlFd)
    {
        return FALSE;
    }

    /* Md5 calculation is 2 step process
     * Step 1: Calculate Md5 on Xml content
     * Step 2: Add the secret key to the Md5 generated in Step 1,
     *         and then generate final Md5
     */
    fseek(xmlFd, 0L, SEEK_END);
    fileSize=ftell(xmlFd);
    fseek(xmlFd, 0L, SEEK_SET);
    // Step 1:
    pdlibMd5DigestCompute(&xmlFd, NULL, fileSize, &md5Digest);
    fclose(xmlFd);

    /* convert numeric digest to text */
    for (i = 0 ; i < PDL_LIB_MD5_DIGEST_LENGTH_CNS; i++)
    {
        len+=sprintf(&step2CombinedStr[len], "%02x", md5Digest.value[i]);
    }

    len+=sprintf(&step2CombinedStr[len], "%s", xpSaiSignature);

    //Step 2:
    pdlibMd5DigestCompute(NULL, (UINT_8*)&step2CombinedStr[0],
                          strlen(step2CombinedStr), &md5Digest);

    memcpy(signaturePtr, &md5Digest, signatureSize);

    return TRUE;
}

/**
 * @brief Get first entry from the database
 *
 * @param[in] dbHandler DB handler
 * @param[out] outEntryPtrPtr first entry
 *
 * @return boolean
 */
bool boardInfoDbGetFirst (
    /*!     INPUTS:             */
    PRV_PDLIB_DB_TYP  dbHandler,
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
    void                    **outEntryPtrPtr
)
{
    PDL_STATUS status;

    status = prvPdlibDbGetFirst (dbHandler, outEntryPtrPtr);

    if (status == PDL_NOT_FOUND)
    {
        return FALSE;
    }
    else if (status != PDL_OK)
    {
        return FALSE;
    }

    return TRUE;
}

/**
 * @brief Get next entry from the database
 *
 * @param[in] dbHandler DB handler
 * @param[out] outEntryPtrPtr next entry
 *
 * @return boolean
 */
bool  boardInfoDbGetNext (
    /*!     INPUTS:             */
    PRV_PDLIB_DB_TYP  dbHandler,
    void                    *keyPtr,
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
    void                    **outEntryPtrPtr
)
{
    PDL_STATUS status;
    status = prvPdlibDbGetNext((PRV_PDLIB_DB_TYP)dbHandler, keyPtr, outEntryPtrPtr);

    if(status == PDL_OK) {
        return TRUE;
    }

    return FALSE;
}



/**
 * @brief Get number of entries from the database
 *
 * @param[in] dbHandler DB handler
 * @param[out] numOfEntriesPtr num of entries
 *
 * @return boolean
 */
bool boardInfoDbNumOfEntriesGet (
    /*!     INPUTS:             */
    PRV_PDLIB_DB_TYP  dbHandler,
    /*!     INPUTS / OUTPUTS:   */
    /*!     OUTPUTS:            */
    uint32_t                *numOfEntriesPtr
)
{
    PDL_STATUS status;

    status = prvPdlibDbGetNumOfEntries(dbHandler, numOfEntriesPtr);

    if (status != PDL_OK)
    {
        return FALSE;
    }

    return TRUE;
}

/**
 * @brief Get number of total PSE devices per the specific board
 *
 * @return number of PSEs
 */
uint32_t getNumOfDevices() {
    // supports only one device as of now
    return 1;
}

/**
 * @brief Get number of total PSE devices per the specific board
 *
 * @return number of PSEs
 */
uint32_t getNumOfPse() {
    uint32_t numOfEntries = 0;

    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, &numOfEntries)) {
        LOG_ERROR("failed to get num of port entries");
        return 0;
    }

    return numOfEntries;
}

/**
 * @brief Get number of total PSE devices per the specific board
 *
 * @return number of PSEs
 */
uint32_t getNumOfPorts() {
    uint32_t numOfEntries = 0;

    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.pseports.pseportList_PTR, &numOfEntries)) {
        LOG_ERROR("failed to get num of port entries");
        return 0;
    }

    return numOfEntries;
}

/**
 * @brief Initialize a database for each of the objects (device/pse/port)
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT databaseInitialize()
{
    uint64_t key;
    uint32_t numOfEntries = 0, index = 0;
    PDL_PSE_LIST_PARAMS_STC *pseListPtr = NULL;
    PDL_PSEPORT_LIST_PARAMS_STC *pseportList_PTR = NULL;
    PDL_POEBANK_LIST_PARAMS_STC *powerBanksListPtr = NULL;
    bool getNext = TRUE;
    POE_OP_RESULT_ENT result = POE_OP_OK_E;

    /* create dictionary for the poe device */
    if((numOfEntries = getNumOfDevices()) < 1) {
        result = POE_OP_FAILED_E;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }
    else {
        deviceDbPtr = create_dictionary(numOfEntries);

        if(!deviceDbPtr) {
            result = POE_OP_FAILED_E;
            LOG_ERROR("failed to create poe device dictionary");
            goto exit;
        }
    }

    /* set key value and update dictionary, there will be one poe device object */
    POE_DEVICE_DB_STC *deviceDbEntryPtr = (POE_DEVICE_DB_STC*)malloc(sizeof(POE_DEVICE_DB_STC));

    if(!deviceDbEntryPtr) {
        result = POE_OP_FAILED_E;
        LOG_ERROR("failed to read NULL entry");
        goto exit;
    }

    key = deviceDbEntryPtr->deviceId = 0;

    if(!dict_put(deviceDbPtr, key, (void*)(deviceDbEntryPtr))) {
        result = POE_OP_FAILED_E;
        LOG_ERROR("failed to insert into poe device dictionary");
        goto exit;
    }

    /* get the number of pse devices, and create the dictionary for the poe pse list */
    if((numOfEntries = getNumOfPse()) < 1) {
        result = POE_OP_FAILED_E;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }
    else {
        pseDbPtr = create_dictionary(numOfEntries);
        if(!pseDbPtr) {
            result = POE_OP_FAILED_E;
            LOG_ERROR("failed to create poe pse dictionary");
            goto exit;
        }
    }



    /* get hw data */
    getNext = boardInfoDbGetFirst(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, (void **)&pseListPtr);

    /* for each pse, set key value and update dictionary */
    while(getNext) {
        POE_PSE_DB *pseDbEntryPtr = (POE_PSE_DB*)malloc(sizeof(POE_PSE_DB));

        if(!pseDbEntryPtr) {
            result = POE_OP_FAILED_E;
            LOG_ERROR("failed to read NULL entry");
            goto exit;
        }

        key = pseDbEntryPtr->pseId = pseListPtr->list_keys.pseNumber;

        if(!dict_put(pseDbPtr, key, (void*)(pseDbEntryPtr))) {
            result = POE_OP_FAILED_E;
            LOG_ERROR("failed to insert into poe device dictionary");
            goto exit;
        }

        /* get hw data */
        getNext = boardInfoDbGetNext(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, (void *)&pseListPtr->list_keys, (void **)&pseListPtr);
    }

    /* get the number of poe ports, and create the dictionary for the poe port list */
    if((numOfEntries = getNumOfPorts()) < 1) {
        result = POE_OP_FAILED_E;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }
    else {
        portDbPtr = create_dictionary(numOfEntries);
        if(!portDbPtr) {
            result = POE_OP_FAILED_E;
            LOG_ERROR("failed to create poe port dictionary");
            goto exit;
        }
    }



    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, &numOfEntries)) {
        result = POE_OP_FAILED_E;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }

    /* get hw data */
    getNext = boardInfoDbGetFirst(boardInfoDbPtr->data_PTR->poe.pseports.pseportList_PTR, (void **)&pseportList_PTR);

    /* for each port, set key value and update dictionary */
    while(getNext) {
        POE_PORT_DB_STC *portDbEntryPtr = (POE_PORT_DB_STC*)malloc(sizeof(POE_PORT_DB_STC));

        if(!portDbEntryPtr) {
            result = POE_OP_FAILED_E;
            LOG_ERROR("failed to read NULL entry");
            goto exit;
        }

        key = portDbEntryPtr->frontPanelIndex = pseportList_PTR->list_keys.frontPanelPortIndex;
        switch (pseportList_PTR->portType) {
            case PDL_PSEPORT_TYPE_AT_E:
                portDbEntryPtr->portStandard = POE_PORT_HW_TYPE_AT_E;
                break;
            case PDL_PSEPORT_TYPE_BT_TYPE3_E:
                portDbEntryPtr->portStandard = POE_PORT_HW_TYPE_BT3_E;
                break;
        }

        portDbEntryPtr->physicalIndexA = pseportList_PTR->index1;
        portDbEntryPtr->physicalIndexB = pseportList_PTR->index2;

        if(!dict_put(portDbPtr, key, (void*)(portDbEntryPtr))) {
            result = POE_OP_FAILED_E;
            LOG_ERROR("failed to insert into poe device dictionary");
            goto exit;
        }

        /* get hw data */
        getNext = boardInfoDbGetNext(boardInfoDbPtr->data_PTR->poe.pseports.pseportList_PTR, (void *)&pseportList_PTR->list_keys, (void **)&pseportList_PTR);
    }

    /* get the number of power banks, and update the power bank list */
    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.poePowerBanks.poebankList_PTR, &numOfEntries)) {
        result = POE_OP_FAILED_E;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }

    /* get hw data */
    getNext = boardInfoDbGetFirst(boardInfoDbPtr->data_PTR->poe.poePowerBanks.poebankList_PTR, (void **)&powerBanksListPtr);

    /* for each pse, set key value and update the array */
    while(getNext) {
        powerBankList.powerBankWSwap[powerBanksListPtr->list_keys.bankNumber] = powerBanksListPtr->bankWatts;

        /* get hw data */
        getNext = boardInfoDbGetNext(boardInfoDbPtr->data_PTR->poe.poePowerBanks.poebankList_PTR, (void *)&powerBanksListPtr->list_keys, (void **)&powerBanksListPtr);
    }

exit:
    return result;
}
/*
static POE_OP_RESULT_ENT poeInitFw ()
{

    ExthwgPoeIpcMcuTypeEnt                 exhw_mcuType=ExthwgPoeIpcMcuTypeCm3;
    GT_U32      								dev_num;
    EXTHWG_POE_ret_TYP                          driver_ret_val;
    int32_t                                     time_before, time_after;

    if ((boardInfoDbPtr->data_PTR->poe.poeHwTypeValue == PDL_POE_HARDWARE_TYPE_POE_NOT_SUPPORTED_E) || (boardInfoDbPtr->data_PTR->poe.poeHwTypeValue == PDL_POE_HARDWARE_TYPE_LAST_E)){
        return POE_OP_FAILED_E;
    }

    if (boardInfoDbPtr->data_PTR->poe.hostSerialChannelId == PDL_POE_HOST_SERIAL_CHANNEL_ID_IPC_SHARED_MEMORY_E){
        switch (boardInfoDbPtr->data_PTR->poe.mcuType){
        case PDL_POE_MCU_TYPE_CM3_E:
            exhw_mcuType = ExthwgPoeIpcMcuTypeCm3;
            break;
        case PDL_POE_MCU_TYPE_DRAGONITE_E:
        default:
            exhw_mcuType = ExthwgPoeIpcMcuTypeDragonite;
            break;
        }

        driver_ret_val = exthwgPoeIpcInit(exhw_mcuType, boardInfoDbPtr->data_PTR->poe.fwFileName);

    }
    else if (boardInfoDbPtr->data_PTR->poe.hostSerialChannelId == PDL_POE_HOST_SERIAL_CHANNEL_ID_DRAGONITE_SHARED_MEMORY_E){
        // not supported
    }
    else {
        return POE_OP_FAILED_E;
    }
    if (driver_ret_val != EXTHWG_POE_ret_ok_CNS) {
        return POE_OP_FAILED_E;
    }

    exthwgPoeIpcRemoveFwFlagLoaded();

    return POE_OP_OK_E;
}

POE_OP_RESULT_ENT sharedMemoryInitialize() {

    if (poeInitFw() != POE_OP_OK_E) {
        return POE_OP_FAILED_E;
    }

    return POE_OP_OK_E;
} */

POE_OP_RESULT_ENT UartInitialize() {
    return poeUartInit();
}

extern PDL_STATUS prvPdlCodeParser (XML_PARSER_NODE_DESCRIPTOR_TYP xml_root);
extern PDL_STATUS prvPdlFeaturesDataHandler (void);
extern PDL_STATUS prvPdlFeaturesDataGet (PDL_FEATURE_DATA_STC ** data_PTR);

/**
 * @brief Initialize board info, to receive board specific parameters
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT boardInfoInitialize() {
    char            profileFile[100];
    char            fileName[100];
    PDL_STATUS                                      status;
    XML_PARSER_ROOT_DESCRIPTOR_TYP                  xmlRoot;
    PDLIB_OS_CALLBACK_API_STC                        callbacks;
    char                                           *baseNamePtr, baseName[256],
                                                   fullPath[256] = "/usr/lib/rdac5xpoe.xml";
    strcpy(baseName, fullPath);
    baseNamePtr = dirname(baseName);

    /* Project_profile Init */
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.printStringPtr       = printf;
    callbacks.mallocPtr            = malloc;
    callbacks.freePtr              = free;
    callbacks.debugLogPtr          = pdLibDebugCallback;
    callbacks.arXmlUncompressClbk = pdLibXmlUncompressCallback;
    callbacks.getXmlSignatureClbk = pdLibGetXmlSignatureCallback;

    status = pdlibInit((char *)fullPath, (char *)"saiplt", &callbacks, &xmlRoot);
    if(status != PDL_OK) {
        LOG_ERROR("failed to initialize pdlib");
        return POE_OP_FAILED_E;
    }

    status = prvPdlCodeParser(xmlRoot);
    if(status != PDL_OK) {
        LOG_ERROR("failed to initialize code parser");
        return POE_OP_FAILED_E;
    }

    status = prvPdlFeaturesDataHandler();
    if(status != PDL_OK) {
        LOG_ERROR("failed to set feature data handler");
        return POE_OP_FAILED_E;
    }

    status = prvPdlFeaturesDataGet(&boardInfoDbPtr);
    if(status != PDL_OK) {
        LOG_ERROR("failed to get feature data");
        return POE_OP_FAILED_E;
    }

    return POE_OP_OK_E;
}

int test_power() {
    int32_t index, powerConsumption;
    bool getNext = true;

    /* enable all ports */
    poePortGetFirstIndex(&index);
    while (getNext) {
        poePortSetAdminEnable(index, 1);
        getNext = poePortGetNextIndex(&index);
    }

    // while (true) {
    //     sleep(10);
    //     poeDevGetPowerConsumption(1, &powerConsumption);
    //     printf("power consumption %d \n", powerConsumption);
    // }
}

/**
 * @brief General initialize for all the PoE components
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeInitialize(void) {

    POE_OP_RESULT_ENT result = POE_OP_OK_E;
    LOG_PRINT("start PoE initalization");
    /* init semaphore */
    rwlock_excl_init(&poe_v3_lock);

    rwlock_excl_acquire(&poe_v3_lock);

    /* init board info (from external db) */
    result = boardInfoInitialize();

    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize board info");
        goto exit;
    }

    LOG_PRINT("successful board info initalization");

    /* init databases */
    result = databaseInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize databases");
        goto exit;
    }

    LOG_PRINT("successful db initalization");

    /* init shared memory *//*
    result = sharedMemoryInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize shared memory");
        goto exit;
    } */

    result = UartInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize UART");
        goto exit;
    }

    LOG_PRINT("successful UART initalization");

    /* set poe power banks *//*
    result = poePowerBankInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize power");
        goto exit;
    } */

    LOG_PRINT("successful power bank initalization");

    /* set poe port matrix *//*
    result = poePortMatrixInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize port matrix");
        goto exit;
    } */

    LOG_PRINT("successful port matrix initalization");

    /* set poe port standard *//*
    result = poePortStandardInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize port standard");
        goto exit;
    } */

    /* temporary - remove after checks */
    /* test_power(); */

    LOG_PRINT("successful port standard initalization");

exit:
    rwlock_excl_release(&poe_v3_lock);
    return result;
}

/**
 * @brief Get the first front panel index
 *
 * @param[out] firstFrontPanelIndex first front panel index
 *
 * @return #true if operation is successful otherwise false
 *
 */
bool poePortGetFirstIndex(uint32_t *firstFrontPanelIndex) {
    KeyValuePair keyValue;
    if(!dict_get_first(portDbPtr, &keyValue)) {
        return false;
    }

    *firstFrontPanelIndex = keyValue.key;
    return true;
}

/**
 * @brief Get the next front panel index
 *
 * @param[out] frontPanelIndex next front panel index
 *
 * @return #true if operation is successful otherwise false
 *
 */
bool poePortGetNextIndex(uint32_t *frontPanelIndex) {
    KeyValuePair nextKeyValue;

    if(!dict_get_next(portDbPtr, (uint64_t)(*frontPanelIndex), &nextKeyValue)) {
        return false;
    }

    *frontPanelIndex = nextKeyValue.key;
    return true;
}

/**
 * @brief Get the poe port hardware type
 *
 * @param[in] frontPanelIndex front panel index
 *
 * @return #return HW type
 *
 */
POE_PORT_HW_TYPE_ENT poeGetPortPoeHwType(uint32_t frontPanelIndex) {
    POE_PORT_DB_STC *valuePtr = (POE_PORT_DB_STC*)dict_get(portDbPtr, (uint64_t)frontPanelIndex);

    if(valuePtr == NULL) {
        return POE_PORT_HW_TYPE_INVALID_E;
    }

    return valuePtr->portStandard;
}

/**
 * @brief Get the physical port index
 *
 * @param[in] frontPanelIndex front panel index
 * @param[out] physicalIndex physical port index
 *
 * @return #true if operation is successful otherwise false
 *
 */
bool poePortGetPhysicalIndex(uint32_t frontPanelIndex, uint32_t *physicalIndex) {
    POE_PORT_DB_STC *valuePtr = (POE_PORT_DB_STC*)dict_get(portDbPtr, (uint64_t)frontPanelIndex);

    if(valuePtr == NULL) {
        return false;
    }

    *physicalIndex = valuePtr->physicalIndexA;

    return true;
}

/**
 * @brief Get the second physical port index (if it exists)
 *
 * @param[in] frontPanelIndex front panel index
 * @param[out] physicalIndex second physical port index
 *
 * @return #true if operation is successful otherwise false
 *
 */
bool poePortGetSecondPhysicalIndex(uint32_t frontPanelIndex, uint32_t *physicalIndex) {
    POE_PORT_DB_STC *valuePtr = (POE_PORT_DB_STC*)dict_get(portDbPtr, (uint64_t)frontPanelIndex);

    if(valuePtr == NULL) {
        return false;
    }

    *physicalIndex = valuePtr->physicalIndexB;

    return true;
}

/**
 * @brief Intialize port matrix
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortMatrixInitialize() {
    uint32_t                          physicalNumberA, physicalNumberB, frontPanelIndex, index = 0;
    POE_PORT_HW_TYPE_ENT               poePortHwType;
    POE_V3_MSG_SYS_PORT_MATRIX_STC setMatrixParams;
    bool getNext = true;

    /* clean matrix params */
    memset(&setMatrixParams, 0xff, sizeof(POE_V3_MSG_SYS_PORT_MATRIX_STC));

    /* for every front panel (logical) poe port in the device, set the correct physical port(s) */
    if(!poePortGetFirstIndex(&frontPanelIndex)) {
        LOG_ERROR("failed to get first index");
        return POE_OP_FAILED_E;
    }

    while (getNext) {

        poePortHwType = poeGetPortPoeHwType(frontPanelIndex);

        if(poePortHwType == POE_PORT_HW_TYPE_INVALID_E) {
            LOG_ERROR("failed to get valid poe type");
            return POE_OP_FAILED_E;
        }

         if(!poePortGetPhysicalIndex(frontPanelIndex, &physicalNumberA)) {
            LOG_ERROR("failed to get physical index");
            return POE_OP_FAILED_E;
         }

        setMatrixParams.physicLogicalPair[index].logicalPort = (uint8_t)frontPanelIndex;
        setMatrixParams.physicLogicalPair[index++].physPort = (uint8_t)physicalNumberA;

        /* check if the port needs 2 channels, if yes, set the second physical port */
        if ((poePortHwType == POE_PORT_HW_TYPE_60W_E) ||
            (poePortHwType == POE_PORT_HW_TYPE_BT3_E) ||
            (poePortHwType == POE_PORT_HW_TYPE_BT4_E)) {

            if(poePortGetSecondPhysicalIndex(frontPanelIndex, &physicalNumberB)) {
                setMatrixParams.physicLogicalPair[index].logicalPort = (uint8_t)frontPanelIndex;
                setMatrixParams.physicLogicalPair[index++].physPort = (uint8_t)physicalNumberB;
            }
        }

        getNext = poePortGetNextIndex(&frontPanelIndex);
    }

    if (index) {
        return poeV3SendReceiveMsg(
            POE_V3_MSG_LEVEL_SYSTEM_CNS,
            POE_V3_MSG_DIR_SET_CNS,
            POE_V3_SYS_MSG_PORT_MATRIX_CNS,
            sizeof(setMatrixParams),
            (uint8_t*)&setMatrixParams);
    }

    LOG_ERROR("failed to get entries");
    return POE_OP_FAILED_E;
}

/**
 * @brief send/receive message to/from the poe firmware
 *
 * @param[in] msgLevel message level (port/system)
 * @param[in] direction get or set
 * @param[in] msgId message id
 * @param[in] dataLen data length
 * @param[out] dataPtr data
 *
 * @return #true if operation is successful otherwise false
 *
 */
POE_OP_RESULT_ENT poeV3SendReceiveMsg (

    /*!     INPUTS:             */
    POE_V3_MSG_LEVEL        msgLevel,
    POE_V3_MSG_DIRECTION    direction,
    uint16_t                                 msgId,
    uint8_t                                  dataLen,
    /*!     INPUTS / OUTPUTS:   */
    uint8_t*                                  dataPtr
    /*!     OUTPUTS:            */
)
{
    POE_V3_MSG_OP_CODE_STC op_code;

    poeV3SetMsgOpCodeMac(op_code, msgLevel, direction, msgId);
    if (!poeUartSendReceiveMsg(op_code.opCodeNum32, dataLen, dataPtr)) {
        LOG_ERROR("failed to send/recieve poe message, msg id %d, direction %d, op code: %d, level %d", msgId, direction, op_code.opCodeNum32, msgLevel);
        return POE_OP_FAILED_E;
    }

    return POE_OP_OK_E;
}

/**
 * @brief Intialize port standard
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortStandardInitialize() {
    uint32_t                          frontPanelIndex, index = 0;
    POE_PORT_HW_TYPE_ENT      poePortHwType, systemHwCapability;
    POE_V3_MSG_SYS_PORT_SUPPORTED_STD_STC portStandardParams;
    POE_OP_RESULT_ENT status;
    bool getNext = true;

    memset(&portStandardParams, 0xff, sizeof(POE_V3_MSG_SYS_PORT_SUPPORTED_STD_STC));

    if(!poePortGetFirstIndex(&frontPanelIndex)) {
        LOG_ERROR("failed to get first index");
        return POE_OP_FAILED_E;
    }

    while (getNext) {

        poePortHwType = poeGetPortPoeHwType(frontPanelIndex);

        portStandardParams.supportedStdData[index].logicPort = (uint8_t)frontPanelIndex;
        portStandardParams.supportedStdData[index++].portSupportedStd = poePortHwType;

        getNext = poePortGetNextIndex(&frontPanelIndex);
    }

    return poeV3SendReceiveMsg(
            POE_V3_MSG_LEVEL_SYSTEM_CNS,
            POE_V3_MSG_DIR_SET_CNS,
            POE_V3_SYS_MSG_PORT_SUPPORT_STANDARD_CNS,
            sizeof(portStandardParams),
            (uint8_t*)&portStandardParams);
}

/**
 * @brief Intialize power banks
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePowerBankInitialize() {
    uint32_t index = 0;
    POE_V3_MSG_SYS_POWER_BANK_STC powerBankParams;

    for (index = 0; index < POE_MAX_NUM_OF_POWER_BANKS_CNS ; index++) {
        powerBankParams.powerBankWSwap[index] = swap16(powerBankList.powerBankWSwap[index]);
    }

    return poeV3SendReceiveMsg(
            POE_V3_MSG_LEVEL_SYSTEM_CNS,
            POE_V3_MSG_DIR_SET_CNS,
            POE_V3_SYS_MSG_POWER_BANK_CONFIG_CNS,
            sizeof(powerBankParams),
            (uint8_t*)&powerBankParams);
}

/**
 * @brief Get the total system power
 *
 * @param[in] poeDevNum device number
 * @param[out] totalPowerPtr total power in watts
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetTotalPower (
    /*!     INPUTS:             */
    int32_t poeDevNum,
    int32_t *totalPowerPtr
)
{
    POE_V3_MSG_SYS_POWER_SUPPLY_PARAMS_STC power_supply_params = {0};
    POE_OP_RESULT_ENT result;

    if(totalPowerPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    power_supply_params.type = POE_V3_SYS_MSG_POWER_CONSUMPTION_MAIN_CNS;
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_SYS_MSG_POWER_CONSUMPTION_CNS,
                                 sizeof(power_supply_params),
                                 (UINT_8*)&power_supply_params);
    if(result == POE_OP_OK_E) {
        *totalPowerPtr = power_supply_params.total_power;  /* Watt */
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Get the power consumption
 *
 * @param[in] poeDevNum device number
 * @param[out] totalPowerMwPtr active power consumption in milliwatts
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetPowerConsumption (
    /*!     INPUTS:             */
    int32_t poeDevNum,
    int32_t *powerConsumptionMwPtr
)
{
    POE_V3_MSG_SYS_POWER_SUPPLY_PARAMS_STC power_supply_params = {0};
    POE_OP_RESULT_ENT result;

    if(powerConsumptionMwPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    power_supply_params.type = POE_V3_SYS_MSG_POWER_CONSUMPTION_MAIN_CNS;
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_SYS_MSG_POWER_CONSUMPTION_CNS,
                                 sizeof(power_supply_params),
                                 (UINT_8*)&power_supply_params);
    if(result == POE_OP_OK_E) {
        *powerConsumptionMwPtr = ((int32_t)power_supply_params.power_consumption) * 1000;  /* milli Watt */
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Get the system version (firmware)
 *
 * @param[in] poeDevNum device number
 * @param[out] versionPtr frimware version
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetVersion(
    /*!     INPUTS:             */
    int32_t poeDevNum,
    char *versionPtr
)
{
    POE_V3_MSG_SYS_SYSTEM_VERSION_STC versionParams = {0};
    POE_OP_RESULT_ENT result;

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    versionParams.type = POE_V3_SYS_MSG_SYSTEM_VERSION_SOFTWARE_CNS;
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_SYS_MSG_SYSTEM_VERSION_CNS,
                                 sizeof(versionParams),
                                 (uint8_t*)&versionParams);
    if (result == POE_OP_OK_E) {
        snprintf(versionPtr, 20, "%d.%d.%d.%d",
                 versionParams.prod,
                 versionParams.major,
                 versionParams.minor,
                 versionParams.par);
    } else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Get power limit mode (class/port limit)
 *
 * @param[in] poeDevNum device number
 * @param[out] powerLimitPtr power limit
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetPowerLimitMode (
    /*!     INPUTS:             */
    uint32_t poeDevNum,
    uint32_t *powerLimitPtr
)
{/*
    POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC limitModeParams;
    POE_OP_RESULT_ENT result;

    if(powerLimitPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    memset(&limitModeParams, 0, sizeof(POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC));

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_POWER_LIMIT_MODE_CNS, sizeof(limitModeParams), (uint8_t*)&limitModeParams);

    if(result == POE_OP_OK_E) {
        *powerLimitPtr = (uint32_t)limitModeParams.limitMode;
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result; */
    return POE_OP_NOT_SUPPORTED_E;
}

/**
 * @brief Get power limit mode (class/port limit)
 *
 * @param[in] poeDevNum device number
 * @param[in] powerLimit power limit
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevSetPowerLimitMode (
    /*!     INPUTS:             */
    uint32_t poeDevNum,
    uint32_t powerLimit
)
{/*
    POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC limitModeParams;
    POE_OP_RESULT_ENT result;

    if(powerLimit!= POWER_LIMIT_MODE_PORT_CNS && powerLimit!= POWER_LIMIT_MODE_CLASS_CNS) {
        LOG_ERROR("invalid power limit mode %d", powerLimit);
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    memset(&limitModeParams, 0, sizeof(POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC));
    limitModeParams.limitMode = (POWER_LIMIT_MODE)powerLimit;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_SET_CNS, POE_V3_SYS_MSG_POWER_LIMIT_MODE_CNS, sizeof(limitModeParams), (uint8_t*)&limitModeParams);

    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);
    return result;
 */
    return POE_OP_NOT_SUPPORTED_E;
}

/**
 * @brief Get the PSE software version
 *
 * @param[in] poePseNum pse number
 * @param[out] versionPtr pse software version
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePseGetSoftwareVersion (
    /*!     INPUTS:             */
    int32_t poePseNum,
    char *versionPtr
)
{
    POE_V3_MSG_SYS_SYSTEM_VERSION_STC versionParams = {0};
    POE_OP_RESULT_ENT result;

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    versionParams.type = POE_V3_SYS_MSG_SYSTEM_VERSION_SOFTWARE_CNS;
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_SYS_MSG_SYSTEM_VERSION_CNS,
                                 sizeof(versionParams),
                                 (uint8_t*)&versionParams);
    if (result == POE_OP_OK_E) {
        snprintf(versionPtr, 20, "%d.%d.%d.%d",
                 versionParams.prod,
                 versionParams.major,
                 versionParams.minor,
                 versionParams.par);
    } else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Get the PSE hardware version
 *
 * @param[in] poePseNum PSE number
 * @param[out] versionPtr PSE software version
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePseGetHardwareVersion (
    /*!     INPUTS:             */
    int32_t poePseNum,
    char *versionPtr
)
{/*
    POE_V3_MSG_SYS_SYSTEM_VERSION_STC *versionParamsPtr;
    POE_OP_RESULT_ENT result;
    char prefix[12] ={0};

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    memset(versionParamsPtr, 0, sizeof(POE_V3_MSG_SYS_SYSTEM_VERSION_STC));
    memset(versionParamsPtr->pseVersionData, 0xFF, sizeof(versionParamsPtr->pseVersionData));
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_SYSTEM_VERSION_CNS, sizeof(*versionParamsPtr), (uint8_t*)versionParamsPtr);

    if(result == POE_OP_OK_E) {
        switch(versionParamsPtr->pseVersionData[poePseNum].pseHwVersion) {
            case POE_V3_DEV_HW_VERSION_LTC4291_CNS:
                strcat(prefix, "LTC4291");
                break;
            default:
                result = POE_OP_FAILED_E;
                break;
        }

        snprintf(versionPtr, 20, "%s - 0x%X", prefix, versionParamsPtr->pseVersionData[poePseNum].pseHwVersion<<8 | versionParamsPtr->pseVersionData[poePseNum].pseSwVersion);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result; */
    return POE_OP_NOT_SUPPORTED_E;
}

/**
 * @brief Get the PSE temperature
 *
 * @param[in] poePseNum PSE number
 * @param[out] temperature PSE temperature
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePseGetTemperature (
    /*!     INPUTS:             */
    int32_t poePseNum,
    int16_t *temperaturePtr
)
{/*
    POE_V3_MSG_SYS_PSE_TEMPERATURE_STC temperatureParams;
    POE_OP_RESULT_ENT result;

    if(temperaturePtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    memset(temperatureParams.pseTempSwap, 0, sizeof(temperatureParams.pseTempSwap));

    poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_PSE_TEMPERATURE_CNS, sizeof(temperatureParams), (uint8_t*)&temperatureParams);

    if(result == POE_OP_OK_E) {
        *temperaturePtr = swap16(temperatureParams.pseTempSwap[poePseNum]);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result; */
    return POE_OP_NOT_SUPPORTED_E;
}

/**
 * @brief Get the PSE status
 *
 * @param[in] poePseNum PSE number
 * @param[out] *status PSE status
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePseGetStatus (
    /*!     INPUTS:             */
    int32_t poePseNum,
    int16_t *statusPtr
)
{/*
    POE_V3_MSG_SYS_PSE_STATUS_STC systemStatusParams;
    POE_OP_RESULT_ENT result;

    sai_poe_pse_status_t convertStatusToSai[]={
        SAI_POE_PSE_STATUS_TYPE_NOT_PRESENT,
        SAI_POE_PSE_STATUS_TYPE_ACTIVE,
        SAI_POE_PSE_STATUS_TYPE_FAIL
    };

    if(statusPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    memset(&systemStatusParams, 0, sizeof(systemStatusParams));
    poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_PSE_STATUS_CNS, sizeof(systemStatusParams), (uint8_t*)&systemStatusParams);

    if(result == POE_OP_OK_E) {
        if (systemStatusParams.pseStatus[poePseNum] == POE_V3_PSE_STATUS_NOT_PRESENT_CNS ||
            systemStatusParams.pseStatus[poePseNum] > POE_V3_PSE_STATUS_I2C_FAILURE_CNS)
            *statusPtr = SAI_POE_PSE_STATUS_TYPE_NOT_PRESENT;
        else {
            *statusPtr = convertStatusToSai[systemStatusParams.pseStatus[poePseNum]];
        }
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result; */
    return POE_OP_NOT_SUPPORTED_E;
}

/**
 * @brief Get POE port enable/disable state
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[out] enable Enable/disable
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortGetPortStandard (
    uint32_t frontPanelIndex,
    uint32_t *portStandardPtr
)
{
    POE_OP_RESULT_ENT result;

    if(portStandardPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    *portStandardPtr = poeGetPortPoeHwType(frontPanelIndex);

    if(*portStandardPtr == POE_PORT_HW_TYPE_INVALID_E) {
        LOG_ERROR("failed to get port standard");
        result = POE_OP_FAILED_E;
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Set enable/disable on POE port
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[in] enable Enable/disable
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortSetAdminEnable(
    uint32_t frontPanelIndex,
    const bool enable
)
{
    POE_V3_MSG_PORT_PARAMS_SET_STC portParams = {0};
    POE_OP_RESULT_ENT result;

    rwlock_excl_acquire(&poe_v3_lock);

    portParams.logic_port = (uint8_t)frontPanelIndex;
    portParams.enable = enable ? POE_V3_PORT_ADMIN_ENABLE_CNS : POE_V3_PORT_ADMIN_DISABLE_CNS;
    portParams.port_mode = POE_V3_BT_PORT_MODE_NO_CHANGE | POE_V3_BT_PORT_CLASS_ERROR_NO_CHANGE;
    portParams.opmode = POE_V3_OPERATION_MODE_NO_CHANGE;
    portParams.power_mode = POE_V3_BT_PORT_MODE_POWER_NO_CHANGE;
    portParams.priority = POE_V3_PORT_PRIORITY_NO_CHANGE;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_SET_CNS,
                                 POE_V3_PORT_MSG_PORT_PARAMS_CNS,
                                 sizeof(portParams),
                                 (uint8_t*)&portParams);
    LOG_PRINT("port %u: %s [rc=%u]", frontPanelIndex, enable ? "on" : "off", result);
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to set data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Get POE port enable/disable state
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[out] enable Enable/disable
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortGetAdminEnable (
    uint32_t frontPanelIndex,
    bool *enablePtr
)
{
    POE_V3_MSG_PORT_PARAMS_GET_STC portParams = {0};
    POE_OP_RESULT_ENT result;

    if(enablePtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    portParams.logic_port = (uint8_t)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_PORT_MSG_PORT_PARAMS_CNS,
                                 sizeof(portParams),
                                 (uint8_t*)&portParams);
    LOG_PRINT("port %u: %s [rc=%u]", frontPanelIndex, portParams.enable ? "on" : "off", result);
    if(result == POE_OP_OK_E) {
        *enablePtr = portParams.enable;
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Set power limit on POE port
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerLimit Power limit
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortSetPowerLimit (
    uint32_t frontPanelIndex,
    const uint32_t powerLimit
)
{/*
    POE_V3_MSG_PORT_POWER_LIMIT_STC powerLimitParams;
    POE_OP_RESULT_ENT result;

    rwlock_excl_acquire(&poe_v3_lock);

    powerLimitParams.logicPortNum = (UINT_8)frontPanelIndex;
    powerLimitParams.powerLimitMwSwap = swap32(powerLimit);

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_SET_CNS, POE_V3_PORT_MSG_PORT_POWER_LIMIT_CNS, sizeof(powerLimitParams), (uint8_t*)&powerLimitParams);

    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to set data");
    }

    rwlock_excl_release(&poe_v3_lock); */

    return POE_OP_NOT_SUPPORTED_E;
}

/**
 * @brief Get power limit on POE port
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerLimit Power limit
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortGetPowerLimit (
    uint32_t frontPanelIndex,
    uint32_t *powerLimitPtr
)
{
    POE_V3_MSG_PORT_CLASS_STC powerLimitParams = {0};
    POE_OP_RESULT_ENT result;

    rwlock_excl_acquire(&poe_v3_lock);

    powerLimitParams.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_PORT_MSG_PORT_CLASS_CNS,
                                 sizeof(powerLimitParams),
                                 (uint8_t*)&powerLimitParams);
    if (result == POE_OP_OK_E) {
        *powerLimitPtr = powerLimitParams.powerLimitW;
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}


POE_OP_RESULT_ENT portSaiPowerPriorityToHw(
    uint32_t sai_prio,
    uint8_t *hw_prio
)
{
    switch(sai_prio)
    {
    case SAI_POE_PORT_POWER_PRIORITY_TYPE_LOW:
        *hw_prio = POE_V3_PORT_PRIORITY_LOW_CNS;
        break;
    case SAI_POE_PORT_POWER_PRIORITY_TYPE_HIGH:
        *hw_prio = POE_V3_PORT_PRIORITY_HIGH_CNS;
        break;
    case SAI_POE_PORT_POWER_PRIORITY_TYPE_CRITICAL:
        *hw_prio = POE_V3_PORT_PRIORITY_CRITICAL_CNS;
        break;
    default:
        return POE_OP_FAILED_E;
    }
    return POE_OP_OK_E;
}

POE_OP_RESULT_ENT portHwPowerPriorityToSai(
    uint8_t hw_prio,
    uint32_t *sai_prio
)
{
    switch(hw_prio)
    {
    case POE_V3_PORT_PRIORITY_LOW_CNS:
        *sai_prio = SAI_POE_PORT_POWER_PRIORITY_TYPE_LOW;
        break;
    case POE_V3_PORT_PRIORITY_HIGH_CNS:
        *sai_prio = SAI_POE_PORT_POWER_PRIORITY_TYPE_HIGH;
        break;
    case POE_V3_PORT_PRIORITY_CRITICAL_CNS:
        *sai_prio = SAI_POE_PORT_POWER_PRIORITY_TYPE_CRITICAL;
        break;
    default:
        return POE_OP_FAILED_E;
    }
    return POE_OP_OK_E;
}

/**
 * @brief Set power limit on POE port
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerLimit Power limit
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortSetPowerPriority (
    uint32_t frontPanelIndex,
    const uint32_t powerPriority
)
{
    POE_V3_MSG_PORT_PARAMS_SET_STC portParams = {0};
    POE_OP_RESULT_ENT result;

    rwlock_excl_acquire(&poe_v3_lock);

    portParams.logic_port = (uint8_t)frontPanelIndex;
    portParams.enable = POE_V3_PORT_ADMIN_NO_CHANGE;
    portParams.port_mode = POE_V3_BT_PORT_MODE_NO_CHANGE | POE_V3_BT_PORT_CLASS_ERROR_NO_CHANGE;
    portParams.opmode = POE_V3_OPERATION_MODE_NO_CHANGE;
    portParams.power_mode = POE_V3_BT_PORT_MODE_POWER_NO_CHANGE;
    result = portSaiPowerPriorityToHw(powerPriority, &portParams.priority);
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to translate priority");
        goto exit;
    }

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_SET_CNS,
                                 POE_V3_PORT_MSG_PORT_PARAMS_CNS,
                                 sizeof(portParams),
                                 (uint8_t*)&portParams);
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to set data");
    }
exit:
    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Set power consumption information on POE port (detailed)
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerConsumptionPtr Power limit
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortGetPowerConsumption (
    uint32_t frontPanelIndex,
    sai_poe_port_power_consumption_t *powerConsumptionPtr
)
{
    POE_V3_MSG_PORT_MEASUREMENTS_STC powerConsumptionInfo = {0};
    POE_V3_MSG_PORT_CLASS_STC portClassParams = {0};
    POE_OP_RESULT_ENT result;
/*
    sai_poe_port_active_channel_type_t convertStatusToSai[]={
        0xFF,
        SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_A,
        SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_B,
        SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_A_AND_B
    };
    sai_poe_port_class_method_type_t convertClassMethodToSai[]={
        0xFF,
        SAI_POE_PORT_CLASS_METHOD_TYPE_REGULAR,
        SAI_POE_PORT_CLASS_METHOD_TYPE_AUTO_CLASS,
    };
    sai_poe_port_signature_type_t convertSignatureTypeToSai[]={
        0xFF,
        SAI_POE_PORT_SIGNATURE_TYPE_SINGLE,
        SAI_POE_PORT_SIGNATURE_TYPE_DUAL
    }; */

    rwlock_excl_acquire(&poe_v3_lock);

    powerConsumptionInfo.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_PORT_MSG_PORT_MEASUREMENT_CNS,
                                 sizeof(powerConsumptionInfo),
                                 (uint8_t*)&powerConsumptionInfo);
    if (result == POE_OP_OK_E) {
        powerConsumptionPtr->current = powerConsumptionInfo.current;  /* mA */
        powerConsumptionPtr->voltage = ((uint32_t)powerConsumptionInfo.voltage) * 100;  /* dV to mV */
        powerConsumptionPtr->consumption = ((uint32_t)powerConsumptionInfo.power_consumption) * 100;  /* dW to mW */
    }

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_PORT_MSG_PORT_CLASS_CNS,
                                 sizeof(portClassParams),
                                 (uint8_t*)&portClassParams);
    if (result == POE_OP_OK_E) {
        /* bits[7..4] are class A (primary) */
        powerConsumptionPtr->assigned_class_a = portClassParams.assigned_class >> 4;
        powerConsumptionPtr->measured_class_a = portClassParams.measured_class >> 4;
        /* bits[3..0] are class B (secondary) */
        powerConsumptionPtr->assigned_class_b = portClassParams.assigned_class & 0x0f;
        powerConsumptionPtr->measured_class_b = portClassParams.measured_class & 0x0f;
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

sai_poe_port_status_t portHwStatusToDetectionStatus(uint32_t portStatus)
{
    sai_poe_port_status_t detectionStatus = SAI_POE_PORT_STATUS_TYPE_OFF;

    switch (portStatus)
    {
    /* TODO: add logs to error statuses */
    case 0x06:  // Main supply voltage is high. Mains voltage is higher than Max Voltage limit.
    case 0x07:  // Main supply voltage is low. Mains voltage is lower than Min Voltage limit.
    case 0x08:  // ‘Disable all ports’ pin is active. Hardware pin disables all ports.
    case 0x0C:  // Non-existing port number. Fewer ports are available than the maximum number of ports that the Controller can support. Unavailable ports are considered ‘off’. Currently not used.
    case 0x12:  // Internal hardware fault. Port does not respond. Hardware fault, system initialization or PD69200 lost communication with PD69208 device allocated for this port. (Part of refresh function).
    case 0x1A:  // User setting. User command set port to off.
    case 0x1B:  // Detection is in process. Interim state during line detection. Status will change after detection process is completed.
    case 0x1C:  // Non-802.3AF/AT powered device. Non-standard PD connected.
    case 0x1E:  // Underload state. Underload state according to 802.3AF/AT (current is below Imin).
    case 0x1F:  // Overload state Overload state according to 802.3AF/AT (current is above Icut). OR (PM3 != 0 and (PD class report > user predefined power value)).
    case 0x20:  // Power budget exceeded. Power Management function shuts down port, due to lack of power. Port is shut down or remains off.
    case 0x22:  // Configuration change Port configuration was changed or port mode was changed, causing the port to turn off. This status is momentary (2sec delay). After the delay the port status will be updated according to the new configuration/mode.
    case 0x24:  // Voltage injection into the port. Port fails due to voltage being applied to the port from external source.
    case 0x25:  // Improper Capacitor Detection results or Detection values indicating short Fail due to out-of-range capacitor value or Fail due to detected short value (When mask 0x04 is set).
    case 0x26:  // Discharged load. Port fails due to system voltage supply through other port. Check other port for status 0x24. This error is linked with mask 0x1F enable.
    case 0x34:  // Short condition. Short condition was detected.
    case 0x35:  // Over temperature at the port. Port temperature protection mechanism was activated.
    case 0x36:  // Device is too hot. The die temperature is above safe operating value.
    case 0x43:  // Class Error Illegal class
    case 0x48:  // Recovery UDL Reserved During crash a recovery port delivering power was disconnected due to UDL.
    case 0x49:  // Recovery PG Event Reserved During crash a recovery port delivering power was disconnected due to PG event.
    case 0x4A:  // Recovery OVL Reserved During crash a recovery port delivering power was disconnected due to OVL.
    case 0x4B:  // Recovery SC Reserved During crash a recovery port delivering power was disconnected due to SC.
    case 0x4C:  // Recovery Voltage injection Reserved Voltage was applied to the port from external source, during or before crash.
        detectionStatus = SAI_POE_PORT_STATUS_TYPE_OFF;
        break;

    case 0x11:  // Port is yet undefined. Port is not mapped to physical port or port is in unknown state or PD69200 fail to communicate with PD69208 device allocated for this port.
    case 0x37:  // Unknown device port status. The device returns an unknown port status for the software. Currently not used.
    case 0x3C:  // Power Management-Static. Calculated power > power limit.
    case 0x3D:  // Power Management-Static –ovl Port Power up was denied due to (PD class report power > user predefined power value). Note: Power denied counter will advance.
    case 0x41:  // Power denied: Hardware power limit Port was not turned on due to hardware power limit (PD class power > Hardware class limit) Example: PoH PD over M device port.
    case 0x44:  // Port turn off during host crash Reserved Port is off – After host crash the port is off and waits for host command to proceed with new detection cycles. This status appears due to OVL,UDL or Short events during host crash
    case 0x45:  // Delivered power port was forced to be shut down at host crash Reserved Port is off – After host crash the port is off and waits for host command to proceed with new detection cycles. The port was delivering power before host crash but was configured to be forced shut when host crashes.
    case 0x46:  // An enabled port was forced to be shut down at host crash Reserved Port is off – after host crash the port is off and waits for host command to proceed with new detection cycles. The port was enabled and not delivering power before host crash and was configured to be forced shut when host crashes.
    case 0x47:  // Force Power Crash Error Reserved Port is at force power error, according to IEEE test mode error. The port was forced power and host crash occurred.
        detectionStatus = SAI_POE_PORT_STATUS_TYPE_FAULT;
        break;

    // New port statuses for BT ports:
    case 0x80:  // 2P Port delivering non IEEE non IEEE PD was detected using 2P matrix in BT mode
    case 0x81:  // 2P Port delivering IEEE 802.3BT-compliant PD was detected using 2P matrix
    case 0x82:  // 4P Port that deliver only 2 Pair non IEEE Signature failure on Alt-B, allowing power only on Alt-A (Non IEEE or Legacy PD).
    case 0x83:  // 4P Port delivering 2P non IEEE non IEEE PD was detected using 4P matrix in BT mode and power as 2Pair
    case 0x84:  // 4P Port delivering 4P non IEEE non IEEE PD was detected using 4P matrix in BT mode and power as 4Pair
    case 0x85:  // 4P Port delivering 2P IEEE SSPD 802.3BT- SSPD was detected using 4P matrix and operate as 2P if requested class =< 4
    case 0x86:  // 4P Port delivering 4P IEEE SSPD 802.3BT- SSPD was detected using 4P matrix and operate as 4P if requested class > 4
    case 0x87:  // 4P Port delivering 2P IEEE DSPD in1st phase. 802.3BT- DSPD was detected using 4P matrix and operate as 2P due to 4pair candidate validation in two cycles.
    case 0x88:  // 4P Port delivering 2P IEEE DSPD 802.3BT- DSPD was detected using 4P matrix and operate as 2P
    case 0x89:  // 4P Port delivering 4P IEEE DSPD 802.3BT- DSPD was detected using 4P matrix and operate as 4P
    case 0x90:  // Force Power BT 2P Port matrix 2P and delivers power due to force power command
    case 0x91:  // Force Power BT 4P Port matrix 4P and delivers power on both pair sets due to force power command
    case 0xA0:  // Force Power BT Error Force power command was set, one of the port pair sets stop delivering power, from at least one reason out of various reasons (System related, Device related, port related or Pair set related)
    case 0xA7:  // Connection Check error This error will be reported only in 4 pair port when invalid connection check signature was detected and the port will not proceed to detection. In such case detection fail counter will be incremented.
        detectionStatus = SAI_POE_PORT_STATUS_TYPE_DELIVERING_POWER;
        break;

    case 0xA8:  // Open Port is not connected
        detectionStatus = SAI_POE_PORT_STATUS_TYPE_SEARCHING;
        break;

    default:
        detectionStatus = SAI_POE_PORT_STATUS_TYPE_FAULT;
    }

    return detectionStatus;
}

/**
 * @brief Set status of the POE port
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[in] statusPtr Port status
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortGetStatus (
    uint32_t frontPanelIndex,
    uint32_t *statusPtr
)
{
    POE_V3_MSG_PORT_PARAMS_GET_STC portParams = {0};
    POE_OP_RESULT_ENT result;

    if(statusPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    portParams.logic_port = (uint8_t)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_PORT_MSG_PORT_PARAMS_CNS,
                                 sizeof(portParams),
                                 (uint8_t*)&portParams);
    if (result == POE_OP_OK_E) {
        *statusPtr = portHwStatusToDetectionStatus(portParams.status);
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Get power priority of the POE port
 *
 * @param[in] frontPanelIndex Front panel index
 * @param[in] priorityPtr Port priority
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortGetPowerPriority (
    uint32_t frontPanelIndex,
    uint32_t *priorityPtr
)
{
    POE_V3_MSG_PORT_PARAMS_GET_STC portParams = {0};
    sai_poe_port_power_priority_t sai_prio;
    POE_OP_RESULT_ENT result;

    if(priorityPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);

    portParams.logic_port = (uint8_t)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS,
                                 POE_V3_MSG_DIR_GET_CNS,
                                 POE_V3_PORT_MSG_PORT_PARAMS_CNS,
                                 sizeof(portParams),
                                 (uint8_t*)&portParams);
    if (result != POE_OP_OK_E) {
        goto exit;
    }

    result = portHwPowerPriorityToSai(portParams.priority, priorityPtr);
    if (result != POE_OP_OK_E) {
        LOG_ERROR("Failed to convert HW port prio (0x%02x) to SAI port prio", portParams.priority);
        goto exit;
    }

exit:
    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief swap uint16_t
 *
 * @param[in] value uint16_t value
 *
 * @return swapped uint16_t value
 *
 */
uint16_t swap16(uint16_t value) {
    return ((value & 0xFF) << 8) | ((value & 0xFF00) >> 8);
}

/**
 * @brief swap uint32_t
 *
 * @param[in] value uint32_t value
 *
 * @return swapped uint32_t value
 *
 */
uint32_t swap32(uint32_t value) {
#pragma pack(push, 1)
    union U_TYP {
        UINT_32 Word;
        UINT_8  Bytes[4];
    } v1, v2;
#pragma pack(pop)

    v1.Word = value;

    v2.Bytes[0] = v1.Bytes[3];
    v2.Bytes[1] = v1.Bytes[2];
    v2.Bytes[2] = v1.Bytes[1];
    v2.Bytes[3] = v1.Bytes[0];

    return v2.Word;
}