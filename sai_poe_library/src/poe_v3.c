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
#include <h/sai/saipoe.h>
#include <h/ipc_drv.h>

static PDL_FEATURE_DATA_STC        *boardInfoDbPtr;
static XML_PARSER_ROOT_DESCRIPTOR_TYP   xmlRootId;

/* global databases */
Dictionary *deviceDbPtr = NULL, *pseDbPtr = NULL, *portDbPtr = NULL;
poeV3MsgSysPowerBank powerBankList = {0};
/* lock critical sections when reading/writing */
rwlock_excl_t lock;

/**
 * @brief Debug callback
 * 
 * @param[in] funcNamePtr function name pointer
 * @param[in] format
 * 
 * @return void
 */
static void pdLibDebugCallback(const char *funcNamePtr,
                                    const char *format, ...)
{
    va_list     argptr;
    char        log[1024];
    int         len;

    snprintf(log, sizeof(len), "pdlib debug: [%s]", funcNamePtr);
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
    IN  int32_t     signatureSize,
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
    int32_t                *numOfEntriesPtr
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
 * @brief Initialize a database for each of the objects (device/pse/port)
 *
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult databaseInitialize() 
{
    uint64_t key;
    uint32_t numOfEntries = 1, index = 0;
    PDL_PSE_LIST_PARAMS_STC *pseListPtr = NULL;
    PDL_PSEPORT_LIST_PARAMS_STC *pseportList_PTR = NULL;
    PDL_POEBANK_LIST_PARAMS_STC *powerBanksListPtr = NULL;
    bool getNext = TRUE;
    poeOpResult result = poeOpOk;
    
    /* create dictionary for the poe device */
    deviceDbPtr = create_dictionary(numOfEntries);
    if(!deviceDbPtr) {
        result = poeOpFailed;
        LOG_ERROR("failed to create poe device dictionary");
        goto exit;
    }
    
    /* set key value and update dictionary, there will be one poe device object */
    poeDeviceDb *deviceDbEntryPtr = (poeDeviceDb*)malloc(sizeof(poeDeviceDb));
    
    if(!deviceDbEntryPtr) {
        result = poeOpFailed;
        LOG_ERROR("failed to read NULL entry");
        goto exit;
    }

    key = deviceDbEntryPtr->deviceId = 0;

    if(!dict_put(deviceDbPtr, key, (void*)(deviceDbEntryPtr))) {
        result = poeOpFailed;
        LOG_ERROR("failed to insert into poe device dictionary");
        goto exit;
    }

    /* get the number of pse devices, and create the dictionary for the poe pse list */
    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, &numOfEntries)) {
        result = poeOpFailed;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }

    pseDbPtr = create_dictionary(numOfEntries);
    if(!pseDbPtr) {
        result = poeOpFailed;
        LOG_ERROR("failed to create poe pse dictionary");
        goto exit;
    }

    /* get hw data */
    getNext = boardInfoDbGetFirst(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, (void **)&pseListPtr);

    /* for each pse, set key value and update dictionary */
    while(getNext) {
        poePseDb *pseDbEntryPtr = (poePseDb*)malloc(sizeof(poePseDb));

        if(!pseDbEntryPtr) {
            result = poeOpFailed;
            LOG_ERROR("failed to read NULL entry");
            goto exit;
        }
        
        key = pseDbEntryPtr->pseId = pseListPtr->list_keys.pseNumber;

        if(!dict_put(pseDbPtr, key, (void*)(pseDbEntryPtr))) {
            result = poeOpFailed;
            LOG_ERROR("failed to insert into poe device dictionary");
            goto exit;
        }

        /* get hw data */
        getNext = boardInfoDbGetNext(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, (void *)&pseListPtr->list_keys, (void **)&pseListPtr);
    }

    /* get the number of poe ports, and create the dictionary for the poe port list */
    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.pseports.pseportList_PTR, &numOfEntries)) {
        result = poeOpFailed;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }

    portDbPtr = create_dictionary(numOfEntries);
    if(!portDbPtr) {
        result = poeOpFailed;
        LOG_ERROR("failed to create poe port dictionary");
        goto exit;
    }

    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.pselist.pseList_PTR, &numOfEntries)) {
        result = poeOpFailed;
        LOG_ERROR("failed to get num of entries");
        goto exit;
    }

    /* get hw data */
    getNext = boardInfoDbGetFirst(boardInfoDbPtr->data_PTR->poe.pseports.pseportList_PTR, (void **)&pseportList_PTR);

    /* for each port, set key value and update dictionary */
    while(getNext) {
        poePortDb *portDbEntryPtr = (poePortDb*)malloc(sizeof(poePortDb));

        if(!portDbEntryPtr) {
            result = poeOpFailed;
            LOG_ERROR("failed to read NULL entry");
            goto exit;
        }

        key = portDbEntryPtr->frontPanelIndex = pseportList_PTR->list_keys.frontPanelPortIndex;
        switch (pseportList_PTR->portType) {
            case PDL_PSEPORT_TYPE_AT_E:
                portDbEntryPtr->portStandard = poePortHwTypeAt;
                break;
            case PDL_PSEPORT_TYPE_BT_TYPE3_E:
                portDbEntryPtr->portStandard = poePortHwTypeBt3;
                break;
        }

        portDbEntryPtr->physicalIndexA = pseportList_PTR->index1;
        portDbEntryPtr->physicalIndexB = pseportList_PTR->index2;

        if(!dict_put(portDbPtr, key, (void*)(portDbEntryPtr))) {
            result = poeOpFailed;
            LOG_ERROR("failed to insert into poe device dictionary");
            goto exit;
        }

        /* get hw data */
        getNext = boardInfoDbGetNext(boardInfoDbPtr->data_PTR->poe.pseports.pseportList_PTR, (void *)&pseportList_PTR->list_keys, (void **)&pseportList_PTR);
    }

    /* get the number of power banks, and update the power bank list */
    if(!boardInfoDbNumOfEntriesGet(boardInfoDbPtr->data_PTR->poe.poePowerBanks.poebankList_PTR, &numOfEntries)) {
        result = poeOpFailed;
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

/**
 * @brief init poe firmware
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
static poeOpResult poeInitFw ()
{

    ExthwgPoeIpcMcuTypeEnt                 exhw_mcuType=ExthwgPoeIpcMcuTypeCm3;
    GT_U32      								dev_num;
    EXTHWG_POE_ret_TYP                          driver_ret_val;
    int32_t                                     time_before, time_after;

    if ((boardInfoDbPtr->data_PTR->poe.poeHwTypeValue == PDL_POE_HARDWARE_TYPE_POE_NOT_SUPPORTED_E) || (boardInfoDbPtr->data_PTR->poe.poeHwTypeValue == PDL_POE_HARDWARE_TYPE_LAST_E)){
        return poeOpFailed;
    }

    /*** Default download: assuming transport is IPc - 
        1. Download FW to MCU (Dragonite or CM3)
        2. Take the MCU out from reset
        3. Init and config IPc for transport of messages between host and MCU ***/
    /* get the dragonite dev id (which is the local PP dev id) */ 


    dev_num = 0; /* to do ? */

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

        driver_ret_val = exthwgPoeIpcInit(exhw_mcuType, (GT_U8)dev_num);
        
    }
    else if (boardInfoDbPtr->data_PTR->poe.hostSerialChannelId == PDL_POE_HOST_SERIAL_CHANNEL_ID_DRAGONITE_SHARED_MEMORY_E){
        // not supported
    }
    else {
        return poeOpFailed;
    }
    if (driver_ret_val != EXTHWG_POE_ret_ok_CNS) {
        return poeOpFailed;
    }

    exthwgPoeIpcRemoveFwFlagLoaded();
    
    return poeOpOk;
}

/**
 * @brief Download poe firmware
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
static poeOpResult poeDownloadFw ()
{

    ExthwgPoeIpcMcuTypeEnt                      exhw_mcuType=ExthwgPoeIpcMcuTypeCm3;
    EXTHWG_POE_ret_TYP                          driver_ret_val;
    int32_t                                     time_before, time_after, num_of_retries = 0, max_num_of_retries = 10;
    BOOLEAN                                     valid_firmware_exist = FALSE, version_ignore_flag = TRUE, expected_userbyte=FALSE;
    BOOLEAN                                     latest_ver_exist = FALSE;
#ifdef _ROS_WM
    char c = 'X';
#endif

    switch (boardInfoDbPtr->data_PTR->poe.mcuType) {
        case PDL_POE_MCU_TYPE_CM3_E:
            exhw_mcuType = ExthwgPoeIpcMcuTypeCm3;
            break;
        case PDL_POE_MCU_TYPE_DRAGONITE_E:
        default:
            exhw_mcuType = ExthwgPoeIpcMcuTypeDragonite;
            break;
    }

    /* if we performed a valid perpetual restart then run firmware only if firmware is volatile */
    if (boardInfoDbPtr->data_PTR->poe.hostSerialChannelId == PDL_POE_HOST_SERIAL_CHANNEL_ID_IPC_SHARED_MEMORY_E){
        driver_ret_val = exthwgPoeIpcRunFirmware(exhw_mcuType, boardInfoDbPtr->data_PTR->poe.fwFileName);
    }
    else if (boardInfoDbPtr->data_PTR->poe.hostSerialChannelId == PDL_POE_HOST_SERIAL_CHANNEL_ID_DRAGONITE_SHARED_MEMORY_E){
        // not supported
    }
    else {
        return poeOpFailed;
    }


    if (driver_ret_val != EXTHWG_POE_ret_ok_CNS) {
        return poeOpFailed;
    }

    sleep(1);// poe_wait(poe_wait_692xx_DownloadFirmwareComplete_E);
    
    return poeOpOk;

}

/**
 * @brief General initialize a for the shared memory protocol
 *
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult sharedMemoryInitialize() {
    
    poeInitFw();

    poeDownloadFw();

    return poeOpOk;
}

/**
 * @brief Initialize board info, to receive board specific parameters
 *
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult boardInfoInitialize() {
    char            profileFile[100];
    char            fileName[100];
    PDL_STATUS                                      status;
    XML_PARSER_ROOT_DESCRIPTOR_TYP                  xmlRoot;
    PDLIB_OS_CALLBACK_API_STC                        callbacks;
    char                                           *baseNamePtr, baseName[256],
                                                   fullPath[256] = "/local/store/sai-poe/sai_poe_library/board_info/rdac5xpoe.xml";
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
        return poeOpFailed;
    }

    status = prvPdlCodeParser(xmlRoot);
    if(status != PDL_OK) {
        LOG_ERROR("failed to initialize code parser");
        return poeOpFailed;
    }

    status = prvPdlFeaturesDataHandler();
    if(status != PDL_OK) {
        LOG_ERROR("failed to set feature data handler");
        return poeOpFailed;
    }

    status = prvPdlFeaturesDataGet(&boardInfoDbPtr);
    if(status != PDL_OK) {
        LOG_ERROR("failed to get feature data");
        return poeOpFailed;
    }

    return poeOpOk;
}

/**
 * @brief General initialize for all the PoE components
 *
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poeInitialize(void) {
    
    poeOpResult result = poeOpOk;
    /* init semaphore */
    rwlock_excl_init(&lock);

    rwlock_excl_acquire(&lock);

    /* init board info (from external db) */
    result = boardInfoInitialize();
    
    if(result != poeOpOk) {
        LOG_ERROR("failed to initialize board info");
        goto exit;
    }

    /* init databases */
    result = databaseInitialize();
    if(result != poeOpOk) {
        LOG_ERROR("failed to initialize databases");
        goto exit;
    }

    /* init shared memory */
    result = sharedMemoryInitialize();
    if(result != poeOpOk) {
        LOG_ERROR("failed to initialize shared memory");
        goto exit;
    }

    /* set poe power banks */
    result = poePowerBankInitialize();
    if(result != poeOpOk) {
        LOG_ERROR("failed to initialize power");
        goto exit;
    }

    /* set poe port matrix */
    result = poePortMatrixInitialize();
    if(result != poeOpOk) {
        LOG_ERROR("failed to initialize port matrix");
        goto exit;
    }

    /* set poe port standard */
    result = poePortStandardInitialize();
    if(result != poeOpOk) {
        LOG_ERROR("failed to initialize port standard");
        goto exit;
    }

exit:
    rwlock_excl_release(&lock);
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
 * @return #poePortHwType_t if operation is successful otherwise poePortHwTypeInvalid
 *
 */
poePortHwType poeGetPortPoeHwType(uint32_t frontPanelIndex) { 
    poePortDb *valuePtr = (poePortDb*)dict_get(portDbPtr, (uint64_t)frontPanelIndex);

    if(valuePtr == NULL) {
        return poePortHwTypeInvalid;
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
    poePortDb *valuePtr = (poePortDb*)dict_get(portDbPtr, (uint64_t)frontPanelIndex);

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
    poePortDb *valuePtr = (poePortDb*)dict_get(portDbPtr, (uint64_t)frontPanelIndex);

    if(valuePtr == NULL) {
        return false;
    }

    *physicalIndex = valuePtr->physicalIndexB;

    return true;
}

/**
 * @brief Intialize port matrix
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortMatrixInitialize() {
    uint32_t                          physicalNumberA, physicalNumberB, frontPanelIndex, index = 0;
    poePortHwType               poePortHwType;
    poeV3MsgSysPortMatrix setMatrixParams;
    bool getNext = true;

    /* clean matrix params */
    memset(&setMatrixParams, 0xff, sizeof(poeV3MsgSysPortMatrix));
    
    /* for every front panel (logical) poe port in the device, set the correct physical port */
    if(!poePortGetFirstIndex(&frontPanelIndex)) {
        LOG_ERROR("failed to get first index");
        return poeOpFailed;
    }

    while (getNext) {

        poePortHwType = poeGetPortPoeHwType(frontPanelIndex);

        if(poePortHwType == poePortHwTypeInvalid) {
            LOG_ERROR("failed to get valid poe type");
            return poeOpFailed;
        }

         if(!poePortGetPhysicalIndex(frontPanelIndex, &physicalNumberA)) {
            LOG_ERROR("failed to get physical index");
            return poeOpFailed;
         }

        setMatrixParams.physicLogicalPair[index].logicalPort = (uint8_t)frontPanelIndex;
        setMatrixParams.physicLogicalPair[index++].physPort = (uint8_t)physicalNumberA;
                
        /* if the port supports two channels, set the second physical port */
        if ((poePortHwType == poePortHwType60W) ||
            (poePortHwType == poePortHwTypeBt3) ||
            (poePortHwType == poePortHwTypeBt4)) {
            
            if(!poePortGetSecondPhysicalIndex(frontPanelIndex, &physicalNumberB)) {
                LOG_ERROR("failed to get second index");
                return poeOpFailed;
            }

            setMatrixParams.physicLogicalPair[index].logicalPort = (uint8_t)frontPanelIndex;
            setMatrixParams.physicLogicalPair[index++].physPort = (uint8_t)physicalNumberB;
        }

        getNext = poePortGetNextIndex(&frontPanelIndex);
    }
    
    if (index) {
        return poeV3SendReceiveMsg(
            poeV3MsgLevelSystem, 
            poeV3MsgDirSet,
            poeV3SysMsgPortMatrix,
            sizeof(setMatrixParams),
            (uint8_t*)&setMatrixParams);
    } 

    LOG_ERROR("failed to get entries");
    return poeOpFailed;
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
poeOpResult poeV3SendReceiveMsg (

    /*!     INPUTS:             */    
    poeV3MsgLevel        msgLevel,
    poeV3MsgDirection    direction,
    uint16_t                                 msgId,
    uint8_t                                  dataLen,
    /*!     INPUTS / OUTPUTS:   */
    void*                                   dataPtr
    /*!     OUTPUTS:            */
)
{
    uint8_t  *buf_ptr;
    bool send=(direction==poeV3MsgDirGet)?false:true;
    poeV3MsgOpCode op_code;

    poeV3SetMsgOpCodeMac(op_code, msgLevel, direction, msgId);
    buf_ptr = (uint8_t*)dataPtr;
    if (true != exthwgPoeIpcSendReceiveMsg(send, op_code.opCodeNum32, dataLen, buf_ptr)) {
        LOG_ERROR("failed to send/recieve poe message, msg id %d, direction %d, op code: %d, level %d", msgId, direction, op_code.opCodeNum32, msgLevel);
        return poeOpFailed;
    }

    /* TEMP - return 11 for all data  */
    memset(dataPtr, 11, sizeof(uint8_t));

    return poeOpOk;
} 

/**
 * @brief Intialize port standard
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortStandardInitialize() {
    uint32_t                          frontPanelIndex, index = 0;
    poePortHwType      poePortHwType, systemHwCapability;
    poeV3MsgSysPortSupportedStd portStandardParams;
    poeOpResult status;
    bool getNext = true;

    memset(&portStandardParams, 0xff, sizeof(poeV3MsgSysPortSupportedStd));
    
    if(!poePortGetFirstIndex(&frontPanelIndex)) {
        LOG_ERROR("failed to get first index");
        return poeOpFailed;
    }

    while (getNext) {
        
        poePortHwType = poeGetPortPoeHwType(frontPanelIndex);
        
        portStandardParams.supportedStdData[index].logicPort = (uint8_t)frontPanelIndex;
        portStandardParams.supportedStdData[index++].portSupportedStd = poePortHwType;

        getNext = poePortGetNextIndex(&frontPanelIndex);
    }

    return poeV3SendReceiveMsg(
            poeV3MsgLevelSystem, 
            poeV3MsgDirSet,
            poeV3SysMsgPortSupportStandard,
            sizeof(portStandardParams),
            (uint8_t*)&portStandardParams);
}

/**
 * @brief Intialize power banks
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePowerBankInitialize() {
    uint32_t index = 0;
    poeV3MsgSysPowerBank powerBankParams;

    for (index = 0; index < poeMaxNumOfPowerBanks ; index++) {
        powerBankParams.powerBankWSwap[index] = swap16(powerBankList.powerBankWSwap[index]); 
    }
    
    return poeV3SendReceiveMsg(
            poeV3MsgLevelSystem, 
            poeV3MsgDirSet,
            poeV3SysMsgPowerBankConfig,
            sizeof(powerBankParams),
            (uint8_t*)&powerBankParams);
}

/**
 * @brief Get the total system power
 * 
 * @param[in] poeDevNum device number
 * @param[out] totalPowerMwPtr total power in milliwatts
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poeDevGetTotalPower (
    /*!     INPUTS:             */
    int32_t poeDevNum, 
    int32_t *totalPowerMwPtr
)
{
    poeV3MsgSysPowerConsumption powerConsumptionParams;
    poeOpResult result; 

    if(totalPowerMwPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 
    
    *totalPowerMwPtr = powerBankList.powerBankWSwap[0];

    rwlock_excl_release(&lock);
    
    return result;
}

/**
 * @brief Get the power consumption
 * 
 * @param[in] poeDevNum device number
 * @param[out] totalPowerMwPtr active power consumption in milliwatts
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poeDevGetPowerConsumption (
    /*!     INPUTS:             */
    int32_t poeDevNum, 
    int32_t *powerConsumptionMwPtr
)
{
    poeV3MsgSysPowerConsumption powerConsumptionParams;
    poeOpResult result; 

    if(powerConsumptionMwPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 
    
    memset(&powerConsumptionParams, 0, sizeof(powerConsumptionParams));
    result = poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirGet, poeV3SysMsgPowerConsumption, sizeof(powerConsumptionParams), (UINT_8*)&powerConsumptionParams);

    if(result == poeOpOk) {
        *powerConsumptionMwPtr = (swap32(powerConsumptionParams.powerConsumptionSwap)) + 0.5;
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);
    
    return result;
}

/**
 * @brief Get the system version (firmware)
 * 
 * @param[in] poeDevNum device number
 * @param[out] versionPtr frimware version
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poeDevGetVersion (
    /*!     INPUTS:             */
    int32_t poeDevNum, 
    char *versionPtr
)
{
    poeV3MsgSysSystemVersion *versionParamsPtr;
    poeOpResult result; 

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 

    memset(versionParamsPtr, 0, sizeof(poeV3MsgSysSystemVersion));
    memset(versionParamsPtr->pseVersionData, 0xFF, sizeof(versionParamsPtr->pseVersionData));
    result = poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirGet, poeV3SysMsgSystemVersion, sizeof(*versionParamsPtr), (uint8_t*)versionParamsPtr);

    if(result == poeOpOk) {
        snprintf (versionPtr, 20, "%d.%d.%d.%d", 
                    versionParamsPtr->poeFwVersion.verBytes[0],
                    versionParamsPtr->poeFwVersion.verBytes[1],
                    versionParamsPtr->poeFwVersion.verBytes[2], 
                    versionParamsPtr->poeFwVersion.verBytes[3]);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Get power limit mode (class/port limit)
 * 
 * @param[in] poeDevNum device number
 * @param[out] powerLimitPtr power limit
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poeDevGetPowerLimitMode (
    /*!     INPUTS:             */
    uint32_t poeDevNum, 
    uint32_t *powerLimitPtr
)
{
    poeV3MsgSysPowerLimitMode limitModeParams;
    poeOpResult result; 

    if(powerLimitPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 

    memset(&limitModeParams, 0, sizeof(poeV3MsgSysPowerLimitMode));

    result = poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirGet, poeV3SysMsgPowerLimitMode, sizeof(limitModeParams), (uint8_t*)&limitModeParams);

    if(result == poeOpOk) {
        *powerLimitPtr = (uint32_t)limitModeParams.limitMode;
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);
    
    return result;
}

/**
 * @brief Get power limit mode (class/port limit)
 * 
 * @param[in] poeDevNum device number
 * @param[out] powerLimitPtr power limit
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poeDevSetPowerLimitMode (
    /*!     INPUTS:             */
    uint32_t poeDevNum, 
    uint32_t powerLimitPtr
)
{
    poeV3MsgSysPowerLimitMode limitModeParams;
    poeOpResult result; 

    if(powerLimitPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 

    memset(&limitModeParams, 0, sizeof(poeV3MsgSysPowerLimitMode));
    limitModeParams.limitMode = (poeV3PowerLimitMode)powerLimitPtr;

    result = poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirSet, poeV3SysMsgPowerLimitMode, sizeof(limitModeParams), (uint8_t*)&limitModeParams);

    if(result != poeOpOk) {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);
    
    return result;
}

/**
 * @brief Get the PSE software version
 * 
 * @param[in] poePseNum pse number
 * @param[out] versionPtr pse software version
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePseGetSoftwareVersion (
    /*!     INPUTS:             */
    int32_t poePseNum, 
    char *versionPtr
)
{
    poeV3MsgSysSystemVersion *versionParamsPtr;
    poeOpResult result; 

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 

    memset(versionParamsPtr, 0, sizeof(poeV3MsgSysSystemVersion));
    memset(versionParamsPtr->pseVersionData, 0xFF, sizeof(versionParamsPtr->pseVersionData));
    result = poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirGet, poeV3SysMsgSystemVersion, sizeof(*versionParamsPtr), (uint8_t*)versionParamsPtr);

    if(result == poeOpOk) {
        snprintf (versionPtr, 20, "%d.%d.%d.%d",
                    versionParamsPtr->poeFwVersion.verBytes[0],
                    versionParamsPtr->poeFwVersion.verBytes[1],
                    versionParamsPtr->poeFwVersion.verBytes[2], 
                    versionParamsPtr->poeFwVersion.verBytes[3]);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Get the PSE hardware version
 * 
 * @param[in] poePseNum PSE number
 * @param[out] versionPtr PSE software version
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePseGetHardwareVersion (
    /*!     INPUTS:             */
    int32_t poePseNum, 
    char *versionPtr
)
{
    poeV3MsgSysSystemVersion *versionParamsPtr;
    poeOpResult result;
    char prefix[12] ={0};

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 

    memset(versionParamsPtr, 0, sizeof(poeV3MsgSysSystemVersion));
    memset(versionParamsPtr->pseVersionData, 0xFF, sizeof(versionParamsPtr->pseVersionData));
    result = poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirGet, poeV3SysMsgSystemVersion, sizeof(*versionParamsPtr), (uint8_t*)versionParamsPtr);

    if(result == poeOpOk) {
        switch(versionParamsPtr->pseVersionData[poePseNum].pseHwVersion) {
            case poeV3DevHwVersionLtc4291:
                strcat(prefix, "LTC4291"); /* bt */
                break;     
            default:
                result = poeOpFailed;
                break;
        }

        snprintf(versionPtr, 20, "%s - 0x%X", prefix, versionParamsPtr->pseVersionData[poePseNum].pseHwVersion<<8 | versionParamsPtr->pseVersionData[poePseNum].pseSwVersion);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Get the PSE temperature
 * 
 * @param[in] poePseNum PSE number
 * @param[out] temperature PSE temperature
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePseGetTemperature (
    /*!     INPUTS:             */
    int32_t poePseNum, 
    int16_t *temperaturePtr
)
{
    poeV3MsgSysPseTemperature temperatureParams;
    poeOpResult result; 

    if(temperaturePtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 

    memcpy(temperatureParams.pseTempSwap, 0, sizeof(temperatureParams.pseTempSwap));

    poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirGet, poeV3SysMsgPseTemperature, sizeof(temperatureParams), (uint8_t*)&temperatureParams);

    if(result == poeOpOk) {
        *temperaturePtr = swap16(temperatureParams.pseTempSwap[poePseNum]);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Get the PSE status
 * 
 * @param[in] poePseNum PSE number
 * @param[out] *status PSE status
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePseGetStatus (
    /*!     INPUTS:             */
    int32_t poePseNum, 
    int16_t *statusPtr
)
{
    poeV3MsgSysPseStatus systemStatusParams;
    poeOpResult result;

    /* Convert v3 POE PSE status values to SAI */
    sai_poe_pse_status_t convertStatusToSai[]={
        SAI_POE_PSE_STATUS_TYPE_NOT_PRESENT,
        SAI_POE_PSE_STATUS_TYPE_ACTIVE,
        SAI_POE_PSE_STATUS_TYPE_FAIL
    };

    if(statusPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock); 

    memset(&systemStatusParams, 0, sizeof(systemStatusParams));
    poeV3SendReceiveMsg(poeV3MsgLevelSystem, poeV3MsgDirGet, poeV3SysMsgPseStatus, sizeof(systemStatusParams), (uint8_t*)&systemStatusParams);

    if(result == poeOpOk) {
        if (systemStatusParams.pseStatus[poePseNum] == poeV3PseStatusNotPresent || 
            systemStatusParams.pseStatus[poePseNum] > poeV3PseStatusI2cFailure)
            *statusPtr = SAI_POE_PSE_STATUS_TYPE_NOT_PRESENT;
        else {
            *statusPtr = convertStatusToSai[systemStatusParams.pseStatus[poePseNum]];
        }
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Get POE port enable/disable state
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[out] enable Enable/disable
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortGetPortStandard (
    uint32_t frontPanelIndex,
    bool *portStandardPtr
)
{
    poeOpResult result;

    if(portStandardPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock);  

    *portStandardPtr = poeGetPortPoeHwType(frontPanelIndex);

    if(*portStandardPtr == poePortHwTypeInvalid) {
        LOG_ERROR("failed to get port standard");
        result = poeOpFailed;
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Set enable/disable on POE port
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[in] enable Enable/disable
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortSetAdminEnable (
    uint32_t frontPanelIndex,
    const bool enable
)
{
    poeV3MsgPortEnable portParams;
    poeOpResult result; 

    rwlock_excl_acquire(&lock); 

    memset(&portParams, 0, sizeof(poeV3MsgPortEnable));
    portParams.logicPortNum = (uint8_t)frontPanelIndex;
    portParams.portAdminEnableDisable = (enable==true)?poeV3PortAdminEnableCns:poeV3PortAdminDisableCns;

    result = poeV3SendReceiveMsg(poeV3MsgLevelPort, poeV3MsgDirSet, poeV3PortMsgPortEnableCns, sizeof(portParams), (uint8_t*)&portParams);

    if(result != poeOpOk) {
        LOG_ERROR("failed to set data");
    }

    rwlock_excl_release(&lock);

    return result;
} 

/**
 * @brief Get POE port enable/disable state
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[out] enable Enable/disable
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortGetAdminEnable (
    uint32_t frontPanelIndex,
    bool *enablePtr
)
{
    poeV3MsgPortEnable portParams;
    poeOpResult result;

    if(enablePtr == NULL) {
        LOG_ERROR("invalid pointer");
        return poeOpFailed;
    }

    rwlock_excl_acquire(&lock);  

    memset(&portParams, 0, sizeof(poeV3MsgPortEnable));
    portParams.logicPortNum = (uint8_t)frontPanelIndex;

    result = poeV3SendReceiveMsg(poeV3MsgLevelPort, poeV3MsgDirGet, poeV3PortMsgPortEnableCns, sizeof(portParams), (uint8_t*)&portParams);

    if(result == poeOpOk) {
        *enablePtr = portParams.portAdminEnableDisable;
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Set power limit on POE port
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerLimit Power limit
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortSetPowerLimit (
    uint32_t frontPanelIndex,
    const uint32_t powerLimit
)
{
    poeV3MsgPortPowerLimit powerLimitParams;
    poeOpResult result; 

    rwlock_excl_acquire(&lock); 

    powerLimitParams.logicPortNum = (UINT_8)frontPanelIndex;
    powerLimitParams.powerLimitMwSwap = swap32(powerLimit);

    result = poeV3SendReceiveMsg(poeV3MsgLevelPort, poeV3MsgDirSet, poeV3PortMsgPortPowerLimitCns, sizeof(powerLimitParams), (uint8_t*)&powerLimitParams);

    if(result != poeOpOk) {
        LOG_ERROR("failed to set data");
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Get power limit on POE port
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerLimit Power limit
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortGetPowerLimit (
    uint32_t frontPanelIndex,
    uint32_t *powerLimitPtr
)
{
    poeV3MsgPortPowerLimit powerLimitParams;
    poeOpResult result; 

    rwlock_excl_acquire(&lock); 

    memset(&powerLimitParams, 0, sizeof(powerLimitParams));
    powerLimitParams.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(poeV3MsgLevelPort, poeV3MsgDirGet, poeV3PortMsgPortPowerLimitCns, sizeof(powerLimitParams), (uint8_t*)&powerLimitParams);

    if(result == poeOpOk) {
        *powerLimitPtr = swap32(powerLimitParams.powerLimitMwSwap);
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Set power limit on POE port
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerLimit Power limit
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortSetPowerPriority (
    uint32_t frontPanelIndex,
    const uint32_t powerPriority
)
{
    poeV3MsgPortPriority portPriorityParams;
    poeOpResult result; 

    rwlock_excl_acquire(&lock); 

    portPriorityParams.logicPortNum = (UINT_8)frontPanelIndex;
    portPriorityParams.portPriority = powerPriority;

    result = poeV3SendReceiveMsg(poeV3MsgLevelPort, poeV3MsgDirSet, poeV3PortMsgPortEnableCns, sizeof(portPriorityParams), (uint8_t*)&portPriorityParams);

    if(result != poeOpOk) {
        LOG_ERROR("failed to set data");
    }

    rwlock_excl_release(&lock);

    return result;
}

/**
 * @brief Set power consumption information on POE port (detailed)
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[in] powerConsumptionPtr Power limit
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortGetPowerConsumption (
    uint32_t frontPanelIndex,
    sai_poe_port_power_consumption_t *powerConsumptionPtr
)
{
    poeV3MsgPortBtPowerConsumInfo powerConsumptionInfo;
    poeOpResult result; 

    /* Convert v3 POE active channel values to SAI */
    sai_poe_port_active_channel_type_t convertStatusToSai[]={
        0xFF,
        SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_A,
        SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_B,
        SAI_POE_PORT_ACTIVE_CHANNEL_TYPE_A_AND_B
    };

    /* Convert v3 POE class method values to SAI */
    sai_poe_port_class_method_type_t convertClassMethodToSai[]={
        0xFF,
        SAI_POE_PORT_CLASS_METHOD_TYPE_REGULAR,
        SAI_POE_PORT_CLASS_METHOD_TYPE_AUTO_CLASS,
    };

    /* Convert v3 POE signature type values to SAI */
    sai_poe_port_signature_type_t convertSignatureTypeToSai[]={
        0xFF,
        SAI_POE_PORT_SIGNATURE_TYPE_SINGLE,
        SAI_POE_PORT_SIGNATURE_TYPE_DUAL
    };

    rwlock_excl_acquire(&lock); 

    memset(&powerConsumptionInfo, 0, sizeof(powerConsumptionInfo));
    powerConsumptionInfo.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(poeV3MsgLevelPort, poeV3MsgDirGet, poeV3PortMsgPowerConsumInfoCns, sizeof(powerConsumptionInfo), (uint8_t*)&powerConsumptionInfo);

    if(result == poeOpOk) {
        powerConsumptionPtr->active_channel = convertStatusToSai[powerConsumptionInfo.activeChannel];
        powerConsumptionPtr->voltage = swap32(powerConsumptionInfo.voltVSwap);
        powerConsumptionPtr->current = swap32(powerConsumptionInfo.currentMaSwap);
        powerConsumptionPtr->consumption = swap32(powerConsumptionInfo.consumpMwSwap);
        powerConsumptionPtr->signature_type = convertSignatureTypeToSai[swap32(powerConsumptionInfo.signatureTypeSwap)];
        powerConsumptionPtr->class_method = convertClassMethodToSai[swap32(powerConsumptionInfo.classMethodSwap)];
        powerConsumptionPtr->measured_class_a = (uint8_t)powerConsumptionInfo.measuredClassASwap;
        powerConsumptionPtr->assigned_class_a = (uint8_t)powerConsumptionInfo.assignedClassASwap;
        powerConsumptionPtr->measured_class_a = (uint8_t)powerConsumptionInfo.measuredClassBSwap;
        powerConsumptionPtr->assigned_class_b = (uint8_t)powerConsumptionInfo.assignedClassBSwap;
    }

    rwlock_excl_release(&lock);

    return result;
}

sai_poe_port_status_t portHwStatusToDetectionStatus(portStatus)
{
    sai_poe_port_status_t detectionStatus = SAI_POE_PORT_STATUS_TYPE_OFF;

    switch (portStatus) {                                                             
        case poeV3PortStatusOffInDetection:                  
        case poeV3PortStatusOffCapDetInvSig:               
            detectionStatus = SAI_POE_PORT_STATUS_TYPE_SEARCHING;       
            break;                                                                      
        case poeV3PortStatusOnResDetect:                         
        case poeV3PortStatusOnCapDetect:                         
        case poeV3PortStatusOn4Pair:
        case poeV3PortStatusOnNonStdBtdevice:                        
            detectionStatus = SAI_POE_PORT_STATUS_TYPE_DELIVERING_POWER; 
            break;                                                                      
        case poeV3PortStatusOffUserDisable:                      
            detectionStatus = SAI_POE_PORT_STATUS_TYPE_OFF;        
            break;                                                                                                                                                                                                     
        default:                                                                        
            detectionStatus = SAI_POE_PORT_STATUS_TYPE_FAULT;      
            break; 
    }

    return detectionStatus;
}                                                                

/**
 * @brief Set status of the POE port
 * 
 * @param[in] frontPanelIndex Front panel index
 * @param[in] statusPtr Port status
 * 
 * @return #poeOpOk if operation is successful otherwise a different
 *    error code is returned.
 */
poeOpResult poePortGetStatus (
    uint32_t frontPanelIndex,
    uint32_t *statusPtr
)
{
    poeV3MsgPortStatus portStatusParams;
    poeOpResult result;
    poeV3PortStatus   portStatusA;
    poeV3PortStatus   portStatusB;
    sai_poe_port_status_t    detectionStatusA;
    sai_poe_port_status_t    detectionStatusB;
    poePortHwType hwType;

    rwlock_excl_acquire(&lock); 

    memset(&portStatusParams, 0, sizeof(portStatusParams));
    portStatusParams.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(poeV3MsgLevelPort, poeV3MsgDirGet, poeV3PortMsgPortStatusCns, sizeof(portStatusParams), (uint8_t*)&portStatusParams);

    /* Convert specific HW status, to generic output: off/delivering power/searching/fault */
    if(result == poeOpOk) {
        hwType = poeGetPortPoeHwType(frontPanelIndex);
        /* If HW type is not BT, get the ALT A status */
        if((hwType != poePortHwTypeBt3) && (hwType != poePortHwTypeBt4)) {
            *statusPtr = portHwStatusToDetectionStatus(portStatusParams.portStatusA);
        }
        {
            detectionStatusA = portHwStatusToDetectionStatus(portStatusParams.portStatusA);
            detectionStatusB = portHwStatusToDetectionStatus(portStatusParams.portStatusB);

            if(detectionStatusA == detectionStatusB) {
                *statusPtr = detectionStatusA;
            }
            else {
                *statusPtr = SAI_POE_PORT_STATUS_TYPE_FAULT;
            
            }
        }
    }

    rwlock_excl_release(&lock);

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
    return (value << 8) | (value >> 8);
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
    return ((value & 0xFF000000) >> 24) |     // Move byte 3 to byte 0
           ((value & 0x00FF0000) >> 8)  |     // Move byte 2 to byte 1
           ((value & 0x0000FF00) << 8)  |     // Move byte 1 to byte 2
           ((value & 0x000000FF) << 24);      // Move byte 0 to byte 3
}


/* TEMP - main() moved to sai_poe for the sai menu options */
// void main() {
//     poe_initialize();
// }