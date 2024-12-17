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
#include <h/ipc_drv.h>
#include <inttypes.h>
#include <libgen.h>

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
            case PDL_PSEPORT_TYPE_BT_TYPE2_E: /* supports BT standard, but only supplies up to 30W */
                portDbEntryPtr->portStandard = POE_PORT_HW_TYPE_AT_E;
                break;
            case PDL_PSEPORT_TYPE_BT_TYPE3_E:
                portDbEntryPtr->portStandard = POE_PORT_HW_TYPE_BT3_E;
            case PDL_PSEPORT_TYPE_BT_TYPE4_E:
                portDbEntryPtr->portStandard = POE_PORT_HW_TYPE_BT4_E;
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

/**
 * @brief init poe firmware
 * 
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
static POE_OP_RESULT_ENT poeInitFw ()
{
    ExthwgPoeIpcMcuTypeEnt                 exhw_mcuType=ExthwgPoeIpcMcuTypeCm3;
    GT_U32      								dev_num;
    EXTHWG_POE_ret_TYP                          driver_ret_val;
    int32_t                                     time_before, time_after;

    if ((boardInfoDbPtr->data_PTR->poe.poeHwTypeValue == PDL_POE_HARDWARE_TYPE_POE_NOT_SUPPORTED_E) || (boardInfoDbPtr->data_PTR->poe.poeHwTypeValue == PDL_POE_HARDWARE_TYPE_LAST_E)){
        return POE_OP_FAILED_E;
    }

    /*** Default download: assuming transport is IPc - 
        1. Download FW to MCU (CM3)
        2. Take the MCU out from reset
        3. Init and config IPc for transport of messages between host and MCU ***/

    if (boardInfoDbPtr->data_PTR->poe.hostSerialChannelId == PDL_POE_HOST_SERIAL_CHANNEL_ID_IPC_SHARED_MEMORY_E){
        switch (boardInfoDbPtr->data_PTR->poe.mcuType){
        case PDL_POE_MCU_TYPE_CM3_E:
            exhw_mcuType = ExthwgPoeIpcMcuTypeCm3;
            break;
        default:
            exhw_mcuType = ExthwgPoeIpcMcuTypeCm3;
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
        LOG_ERROR("invalid driver return value");
        return POE_OP_FAILED_E;
    }

    exthwgPoeIpcRemoveFwFlagLoaded();
    
    return POE_OP_OK_E;
}

/**
 * @brief General initialize a for the shared memory protocol
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT sharedMemoryInitialize() {
    
    if (poeInitFw() != POE_OP_OK_E) {
        return POE_OP_FAILED_E;
    }

    return POE_OP_OK_E;
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
                                                   fullPath[256] = "/usr/bin/rdac5xpoe.xml";
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

/**
 * @brief General initialize for all the PoE components
 *
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeInitialize(void) {
    
    POE_OP_RESULT_ENT result = POE_OP_OK_E;
    LOG_PRINT("start PoE initialization");

    /* init semaphore */
    rwlock_excl_init(&poe_v3_lock);

    rwlock_excl_acquire(&poe_v3_lock);

    /* init board info (from external db) */
    result = boardInfoInitialize();

    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize board info");
        goto exit;
    }

    LOG_PRINT("successful board info initialization");

    /* init databases */
    result = databaseInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize databases");
        goto exit;
    }

    LOG_PRINT("successful db initialization");

    /* init shared memory */
    result = sharedMemoryInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize shared memory");
        goto exit;
    }

    LOG_PRINT("successful shared memory initialization");

    /* set poe power banks */
    result = poePowerBankInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize power");
        goto exit;
    }

    LOG_PRINT("successful power bank initialization");

    /* set poe port matrix */
    result = poePortMatrixInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize port matrix");
        goto exit;
    }

    LOG_PRINT("successful port matrix initialization");

    /* set poe port standard */
    result = poePortStandardInitialize();
    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to initialize port standard");
        goto exit;
    }

    LOG_PRINT("successful port standard initialization");

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
 * @brief Get the first PSE index
 *
 * @param[out] pseIndex first PSE index
 * 
 * @return #true if operation is successful otherwise false
 *
 */
bool poePseGetFirstIndex(uint32_t *pseIndex) {
    KeyValuePair keyValue;
    if(!dict_get_first(pseDbPtr, &keyValue)) {
        return false;
    }

    *pseIndex = keyValue.key;
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
 * @brief Get the next PSE index
 *
 * @param[out] frontPanelIndex next PSE index
 * 
 * @return #true if operation is successful otherwise false
 *
 */
bool poePseGetNextIndex(uint32_t *pseIndex) {
    KeyValuePair nextKeyValue;
    
    if(!dict_get_next(pseDbPtr, (uint64_t)(*pseIndex), &nextKeyValue)) {
        return false;
    }

    *pseIndex = nextKeyValue.key;
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

    LOG_PRINT("port standard %d", valuePtr->portStandard);

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
    LOG_PRINT("port physical index %d (%d)", *physicalIndex, valuePtr->physicalIndexA);

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
 * @brief Initialize port matrix
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
    uint8_t  *buf_ptr;
    POE_V3_MSG_OP_CODE_STC op_code;

    poeV3SetMsgOpCodeMac(op_code, msgLevel, direction, msgId);
    buf_ptr = (uint8_t*)dataPtr;
    if (true != exthwgPoeIpcSendReceiveMsg(op_code.opCodeNum32, dataLen, dataPtr)) {
        LOG_ERROR("failed to send/recieve poe message, msg id %d, direction %d, op code: %d, level %d", msgId, direction, op_code.opCodeNum32, msgLevel);
        return POE_OP_FAILED_E;
    }

    return POE_OP_OK_E;
} 

/**
 * @brief Initialize port standard
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

        LOG_PRINT("port %d, set port standard %d", frontPanelIndex, poePortHwType);

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
 * @brief Initialize power banks
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
 * @param[out] totalPowerMwPtr total power in milliwatts
 * 
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetTotalPower (
    /*!     INPUTS:             */
    int32_t poeDevNum, 
    int32_t *totalPowerMwPtr
)
{
    POE_V3_MSG_SYS_POWER_CONSUMPTION_STC powerConsumptionParams;
    POE_OP_RESULT_ENT result; 

    if(totalPowerMwPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock); 
    
    *totalPowerMwPtr = powerBankList.powerBankWSwap[0];

    LOG_PRINT("total power %d", *totalPowerMwPtr);

    rwlock_excl_release(&poe_v3_lock);
    
    return result;
}

/**
 * @brief Get pse list
 * 
 * @param[in] poeDevNum device number
 * @param[out] totalPowerMwPtr total power in milliwatts
 * 
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetPseList (
    /*!     INPUTS:             */
    int32_t poeDevNum, 
    uint32_t  *countPtr,
    uint64_t *pseListPtr
)
{
    POE_V3_MSG_SYS_POWER_CONSUMPTION_STC powerConsumptionParams;
    POE_OP_RESULT_ENT result = POE_OP_OK_E;
    uint32_t index = 0;

    if(countPtr == NULL || pseListPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock); 
    
    *countPtr = getNumOfPse();

    poePseGetFirstIndex(&index);

    for(int i = 0; i < *countPtr; i++) {
        pseListPtr[i] = (index) | (((uint64_t)SAI_OBJECT_TYPE_POE_PSE) << 32);
        LOG_PRINT("PSE id %d: 0x%" PRIx64, index, pseListPtr[i]);
        poePseGetNextIndex(&index);
    }

    rwlock_excl_release(&poe_v3_lock);
    
    return result;
}

/**
 * @brief Get port list
 * 
 * @param[in] poeDevNum device number
 * @param[out] totalPowerMwPtr total power in milliwatts
 * 
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetPortList (
    /*!     INPUTS:             */
    int32_t poeDevNum, 
    uint32_t  *countPtr,
    uint64_t *portListPtr
)
{
    LOG_PRINT("poeDevGetPortList");

    POE_V3_MSG_SYS_POWER_CONSUMPTION_STC powerConsumptionParams;
    POE_OP_RESULT_ENT result = POE_OP_OK_E; 
    uint32_t index = 0;

    if(countPtr == NULL || portListPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock); 
    
    *countPtr = getNumOfPorts();
    LOG_PRINT("poeDevGetPortList - count %d", *countPtr);

    poePortGetFirstIndex(&index);
    portListPtr[0] = index | (((uint64_t)SAI_OBJECT_TYPE_POE_PORT) << 32);
    LOG_PRINT("port id %d: 0x%" PRIx64, 0, portListPtr[0]);

    for(int i = 1; i < *countPtr; i++) {
        if(&portListPtr[i] != NULL) {
            poePortGetNextIndex(&index);
            portListPtr[i] = index | (((uint64_t)SAI_OBJECT_TYPE_POE_PORT) << 32);
        }

        LOG_PRINT("port id %d: 0x%" PRIx64, i, portListPtr[i]);
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
    POE_V3_MSG_SYS_POWER_CONSUMPTION_STC powerConsumptionParams;
    POE_OP_RESULT_ENT result; 

    if(powerConsumptionMwPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock); 
    
    memset(&powerConsumptionParams, 0, sizeof(powerConsumptionParams));
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_POWER_CONSUMPTION_CNS, sizeof(powerConsumptionParams), (UINT_8*)&powerConsumptionParams);
    if(result == POE_OP_OK_E) {
        *powerConsumptionMwPtr = (swap32(powerConsumptionParams.powerConsumptionSwap)) + 0.5;
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
 * @param[out] versionPtr firmware version
 * 
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poeDevGetVersion (
    /*!     INPUTS:             */
    int32_t poeDevNum, 
    char *versionPtr
)
{
    POE_V3_MSG_SYS_SYSTEM_VERSION_STC versionParams;
    POE_OP_RESULT_ENT result; 

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    LOG_PRINT("poeDevGetVersion");
    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&versionParams, 0, sizeof(POE_V3_MSG_SYS_SYSTEM_VERSION_STC));
    memset(&versionParams.pseVersionData, 0xFF, sizeof(versionParams.pseVersionData));
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_SYSTEM_VERSION_CNS, sizeof(versionParams), (uint8_t*)&versionParams);

    if(result == POE_OP_OK_E) {
        snprintf (versionPtr, 20, "%d.%d.%d.%d", 
                    versionParams.poeFwVersion.verBytes[0],
                    versionParams.poeFwVersion.verBytes[1],
                    versionParams.poeFwVersion.verBytes[2], 
                    versionParams.poeFwVersion.verBytes[3]);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);
    LOG_PRINT("poeDevGetVersion %s", versionPtr);

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
{
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
    
    return result;
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
{
    POE_V3_MSG_SYS_POWER_LIMIT_MODE_STC limitModeParams;
    POE_OP_RESULT_ENT result; 

    if(powerLimit!= POWER_LIMIT_MODE_PORT_CNS && powerLimit!= POWER_LIMIT_MODE_CLASS_CNS) {
        LOG_ERROR("invalid power limit mode %d", powerLimit);
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
    POE_V3_MSG_SYS_SYSTEM_VERSION_STC versionParams;
    POE_OP_RESULT_ENT result; 

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    LOG_PRINT("poePseGetSoftwareVersion");
    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&versionParams, 0, sizeof(POE_V3_MSG_SYS_SYSTEM_VERSION_STC));
    memset(versionParams.pseVersionData, 0xFF, sizeof(versionParams.pseVersionData));
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_SYSTEM_VERSION_CNS, sizeof(versionParams), (uint8_t*)&versionParams);

    if(result == POE_OP_OK_E) {
        snprintf (versionPtr, 20, "%d.%d.%d.%d",
                    versionParams.poeFwVersion.verBytes[0],
                    versionParams.poeFwVersion.verBytes[1],
                    versionParams.poeFwVersion.verBytes[2], 
                    versionParams.poeFwVersion.verBytes[3]);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);
    LOG_PRINT("poePseGetSoftwareVersion %s", versionPtr);

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
{
    POE_V3_MSG_SYS_SYSTEM_VERSION_STC versionParams;
    POE_OP_RESULT_ENT result;
    char prefix[12] ={0};

    if(versionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    LOG_PRINT("poePseGetHardwareVersion");
    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&versionParams, 0, sizeof(POE_V3_MSG_SYS_SYSTEM_VERSION_STC));
    memset(versionParams.pseVersionData, 0xFF, sizeof(versionParams.pseVersionData));
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_SYSTEM_VERSION_CNS, sizeof(versionParams), (uint8_t*)&versionParams);

    if(result == POE_OP_OK_E) {
        switch(versionParams.pseVersionData[poePseNum].pseHwVersion) {
            case POE_V3_DEV_HW_VERSION_LTC4291_CNS:
                strcat(prefix, "LTC4291"); 
                break;
            case POE_V3_DEV_HW_VERSION_PD77728_CNS:
                strcat(prefix, "PD77728"); 
                break; 
            default:
                result = POE_OP_FAILED_E;
                break;
        }

        snprintf(versionPtr, 20, "%s - 0x%X", prefix, versionParams.pseVersionData[poePseNum].pseHwVersion<<8 | versionParams.pseVersionData[poePseNum].pseSwVersion);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    rwlock_excl_release(&poe_v3_lock);
    LOG_PRINT("poePseGetHardwareVersion %s", versionPtr);

    return result;
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
{
    POE_V3_MSG_SYS_PSE_TEMPERATURE_STC temperatureParams;
    POE_OP_RESULT_ENT result; 

    if(temperaturePtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    LOG_PRINT("poePseGetTemperature");
    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&temperatureParams, 0, sizeof(temperatureParams));

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_PSE_TEMPERATURE_CNS, sizeof(temperatureParams), (uint8_t*)&temperatureParams);

    if(result == POE_OP_OK_E) {
        *temperaturePtr = swap16(temperatureParams.pseTempSwap[poePseNum]);
    }
    else {
        LOG_ERROR("failed to get data");
    }

    LOG_PRINT("poePseGetTemperature %d, pse %d", *temperaturePtr, poePseNum);
    rwlock_excl_release(&poe_v3_lock);

    return result;
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
{
    POE_V3_MSG_SYS_PSE_STATUS_STC systemStatusParams;
    POE_OP_RESULT_ENT result;

    if(statusPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&systemStatusParams, 0, sizeof(systemStatusParams));
    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_SYSTEM_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_SYS_MSG_PSE_STATUS_CNS, sizeof(systemStatusParams), (uint8_t*)&systemStatusParams);

    if(result == POE_OP_OK_E) {
        if (systemStatusParams.pseStatus[poePseNum] == POE_V3_PSE_STATUS_NOT_PRESENT_CNS || 
            systemStatusParams.pseStatus[poePseNum] > POE_V3_PSE_STATUS_I2C_FAILURE_CNS)
            *statusPtr = POE_V3_PSE_STATUS_NOT_PRESENT_CNS;
        else {
            *statusPtr = systemStatusParams.pseStatus[poePseNum];
        }
    }
    else {
        LOG_ERROR("failed to get data");
    }

    LOG_PRINT("poePseGetStatus %d, pse %d", *statusPtr, poePseNum);
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
POE_OP_RESULT_ENT poePortSetAdminEnable (
    uint32_t frontPanelIndex,
    const bool enable
)
{
    POE_V3_MSG_PORT_ENABLE_STC portParams;
    POE_OP_RESULT_ENT result; 

    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&portParams, 0, sizeof(POE_V3_MSG_PORT_ENABLE_STC));
    portParams.logicPortNum = (uint8_t)frontPanelIndex;
    portParams.portAdminEnableDisable = (enable==true)?POE_V3_PORT_ADMIN_ENABLE_CNS:POE_V3_PORT_ADMIN_DISABLE_CNS;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_SET_CNS, POE_V3_PORT_MSG_PORT_ENABLE_CNS, sizeof(portParams), (uint8_t*)&portParams);

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
    POE_V3_MSG_PORT_ENABLE_STC portParams;
    POE_OP_RESULT_ENT result;

    if(enablePtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    rwlock_excl_acquire(&poe_v3_lock);  

    memset(&portParams, 0, sizeof(POE_V3_MSG_PORT_ENABLE_STC));
    portParams.logicPortNum = (uint8_t)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_PORT_MSG_PORT_ENABLE_CNS, sizeof(portParams), (uint8_t*)&portParams);

    if(result == POE_OP_OK_E) {
        *enablePtr = portParams.portAdminEnableDisable;
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
{
    POE_V3_MSG_PORT_POWER_LIMIT_STC powerLimitParams;
    POE_OP_RESULT_ENT result; 

    rwlock_excl_acquire(&poe_v3_lock); 

    powerLimitParams.logicPortNum = (UINT_8)frontPanelIndex;
    powerLimitParams.powerLimitMwSwap = swap32(powerLimit);

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_SET_CNS, POE_V3_PORT_MSG_PORT_POWER_LIMIT_CNS, sizeof(powerLimitParams), (uint8_t*)&powerLimitParams);

    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to set data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
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
    POE_V3_MSG_PORT_POWER_LIMIT_STC powerLimitParams;
    POE_OP_RESULT_ENT result; 

    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&powerLimitParams, 0, sizeof(powerLimitParams));
    powerLimitParams.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_PORT_MSG_PORT_POWER_LIMIT_CNS, sizeof(powerLimitParams), (uint8_t*)&powerLimitParams);

    if(result == POE_OP_OK_E) {
        *powerLimitPtr = swap32(powerLimitParams.powerLimitMwSwap);
    }

    LOG_PRINT("power limit %d", *powerLimitPtr);

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
POE_OP_RESULT_ENT poePortSetPowerPriority (
    uint32_t frontPanelIndex,
    const uint32_t powerPriority
)
{
    POE_V3_MSG_PORT_PRIORITY_STC portPriorityParams;
    POE_OP_RESULT_ENT result; 

    rwlock_excl_acquire(&poe_v3_lock); 

    portPriorityParams.logicPortNum = (UINT_8)frontPanelIndex;
    portPriorityParams.portPriority = powerPriority;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_SET_CNS, POE_V3_PORT_MSG_PORT_PRIORITY_CNS, sizeof(portPriorityParams), (uint8_t*)&portPriorityParams);

    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to set data");
    }

    rwlock_excl_release(&poe_v3_lock);

    return result;
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
POE_OP_RESULT_ENT poePortGetPowerPriority (
    uint32_t frontPanelIndex,
    uint32_t *powerPriority
)
{
    POE_V3_MSG_PORT_PRIORITY_STC portPriorityParams;
    POE_OP_RESULT_ENT result; 

    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&portPriorityParams, 0, sizeof(portPriorityParams));
    portPriorityParams.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_PORT_MSG_PORT_PRIORITY_CNS, sizeof(portPriorityParams), (uint8_t*)&portPriorityParams);

    if(result != POE_OP_OK_E) {
        LOG_ERROR("failed to set data");
    }

    *powerPriority = portPriorityParams.portPriority;
    LOG_PRINT("power priority %d, port %d", *powerPriority, frontPanelIndex);
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
    POE_V3_MSG_PORT_BT_POWER_CONSUM_INFO_STC powerConsumptionInfo;
    POE_OP_RESULT_ENT result; 

    if(powerConsumptionPtr == NULL) {
        LOG_ERROR("invalid pointer");
        return POE_OP_FAILED_E;
    }

    LOG_PRINT("poePortGetPowerConsumption");
    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&powerConsumptionInfo, 0, sizeof(powerConsumptionInfo));
    powerConsumptionInfo.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_PORT_MSG_POWER_CONSUM_INFO_CNS, sizeof(powerConsumptionInfo), (uint8_t*)&powerConsumptionInfo);

    if(result == POE_OP_OK_E) {
        powerConsumptionPtr->active_channel = powerConsumptionInfo.activeChannel;
        powerConsumptionPtr->voltage = swap32(powerConsumptionInfo.voltVSwap);
        powerConsumptionPtr->current = swap32(powerConsumptionInfo.currentMaSwap);
        powerConsumptionPtr->consumption = swap32(powerConsumptionInfo.consumpMwSwap);
        powerConsumptionPtr->signature_type = swap16(powerConsumptionInfo.signatureTypeSwap);
        powerConsumptionPtr->class_method = swap16(powerConsumptionInfo.classMethodSwap);
        powerConsumptionPtr->measured_class_a = (uint8_t)swap16(powerConsumptionInfo.measuredClassASwap);
        powerConsumptionPtr->assigned_class_a = (uint8_t)swap16(powerConsumptionInfo.assignedClassASwap);
        powerConsumptionPtr->measured_class_a = (uint8_t)swap16(powerConsumptionInfo.measuredClassBSwap);
        powerConsumptionPtr->assigned_class_b = (uint8_t)swap16(powerConsumptionInfo.assignedClassBSwap);
    }

    LOG_PRINT("power consumption %d, port %d", powerConsumptionPtr->consumption, frontPanelIndex);
    LOG_PRINT("power voltage %d, port %d", powerConsumptionPtr->voltage, frontPanelIndex);
    LOG_PRINT("power current %d, port %d", powerConsumptionPtr->current, frontPanelIndex);  
    LOG_PRINT("power active_channel %d, port %d", powerConsumptionPtr->active_channel, frontPanelIndex);
    LOG_PRINT("power signature_type %d, port %d", powerConsumptionPtr->signature_type, frontPanelIndex);
    LOG_PRINT("power class_method %d, port %d", powerConsumptionPtr->class_method, frontPanelIndex);
    LOG_PRINT("power measured_class_a %d, port %d", powerConsumptionPtr->measured_class_a, frontPanelIndex);
    LOG_PRINT("power assigned_class_a %d, port %d", powerConsumptionPtr->assigned_class_a, frontPanelIndex);
    LOG_PRINT("power measured_class_b %d, port %d", powerConsumptionPtr->measured_class_b, frontPanelIndex);
    LOG_PRINT("power assigned_class_b %d, port %d", powerConsumptionPtr->assigned_class_b, frontPanelIndex);

    rwlock_excl_release(&poe_v3_lock);

    return result;
}

/**
 * @brief Convert the HW status to PoE port detection status
 * 
 * @param[in] portStatus Front panel index
 * 
 * @return detectionStatus
 */
uint8_t portHwStatusToDetectionStatus(uint8_t portStatus)
{
    uint8_t detectionStatus = POE_PORT_DETECTION_STATUS_OFF_CNS;

    switch (portStatus) {                                                             
        case POE_V3_PORT_STATUS_OFF_IN_DETECTION_CNS:                  
        case POE_V3_PORT_STATUS_OFF_CAP_DET_INV_SIG_CNS:               
            detectionStatus = POE_PORT_DETECTION_STATUS_SEARCHING_CNS;       
            break;                                                                      
        case POE_V3_PORT_STATUS_ON_RES_DETECT_CNS:                         
        case POE_V3_PORT_STATUS_ON_CAP_DETECT_CNS:
        case POE_V3_PORT_STATUS_ON_4_PAIR_CNS:                        
        case POE_V3_PORT_STATUS_ON_FORCE_4_PAIR_CNS:
        case POE_V3_PORT_STATUS_ON_NON_STD_BT_DEVICE_CNS:                        
            detectionStatus = POE_PORT_DETECTION_STATUS_DELIVERING_POWER_CNS; 
            break;                                                                      
        case POE_V3_PORT_STATUS_OFF_USER_DISABLE_CNS:                      
            detectionStatus = POE_PORT_DETECTION_STATUS_OFF_CNS;        
            break;                                                                                                                                                                                                     
        default:                                                                        
            detectionStatus = POE_PORT_DETECTION_STATUS_FAULT_CNS;      
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
 * @return #POE_OP_OK_E if operation is successful otherwise a different
 *    error code is returned.
 */
POE_OP_RESULT_ENT poePortGetStatus (
    uint32_t frontPanelIndex,
    uint32_t *statusPtr
)
{
    POE_V3_MSG_PORT_STATUS_STC portStatusParams;
    POE_OP_RESULT_ENT result;
    POE_V3_PORT_STATUS   portStatusA;
    POE_V3_PORT_STATUS   portStatusB;
    POE_V3_PORT_STATUS   detectionStatusA;
    POE_V3_PORT_STATUS   detectionStatusB;
    POE_PORT_HW_TYPE_ENT hwType;

    rwlock_excl_acquire(&poe_v3_lock); 

    memset(&portStatusParams, 0xFF, sizeof(portStatusParams));
    portStatusParams.logicPortNum = (UINT_8)frontPanelIndex;

    result = poeV3SendReceiveMsg(POE_V3_MSG_LEVEL_PORT_CNS, POE_V3_MSG_DIR_GET_CNS, POE_V3_PORT_MSG_PORT_STATUS_CNS, sizeof(portStatusParams), (uint8_t*)&portStatusParams);
    
    /* Convert specific HW status, to generic output: off/delivering power/searching/fault */
    if(result == POE_OP_OK_E) {
        hwType = poeGetPortPoeHwType(frontPanelIndex);
        /* If HW type is not BT, get the ALT A status */
        if((hwType != POE_PORT_HW_TYPE_BT3_E) && (hwType != POE_PORT_HW_TYPE_BT4_E)) {
            *statusPtr = portHwStatusToDetectionStatus(portStatusParams.portStatusA);
            LOG_PRINT("port %d status %d, hw status %d", frontPanelIndex, *statusPtr, portStatusParams.portStatusA);
        }
        else {
            detectionStatusA = portHwStatusToDetectionStatus(portStatusParams.portStatusA);
            detectionStatusB = portHwStatusToDetectionStatus(portStatusParams.portStatusB);

            LOG_PRINT("port %d status A %d, hw status %d", frontPanelIndex, detectionStatusA, portStatusParams.portStatusA);
            LOG_PRINT("port %d status B %d, hw status %d", frontPanelIndex, detectionStatusB, portStatusParams.portStatusB);

            if((detectionStatusA == detectionStatusB) || (portStatusParams.portStatusB == POE_V3_PORT_STATUS_ALT_B_SINGLE_SIGNATURE_CNS)) {
                *statusPtr = detectionStatusA;
            }
            else if((detectionStatusA == POE_PORT_DETECTION_STATUS_DELIVERING_POWER_CNS) && (detectionStatusB == POE_PORT_DETECTION_STATUS_SEARCHING_CNS)) {
                *statusPtr = POE_PORT_DETECTION_STATUS_DELIVERING_POWER_CNS;
            }
            else if((detectionStatusA == POE_PORT_DETECTION_STATUS_SEARCHING_CNS) && (detectionStatusB == POE_PORT_DETECTION_STATUS_DELIVERING_POWER_CNS)) {
                *statusPtr = POE_PORT_DETECTION_STATUS_DELIVERING_POWER_CNS;
            }
            else {
                *statusPtr = POE_PORT_DETECTION_STATUS_FAULT_CNS;
            
            }
        }
    }

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