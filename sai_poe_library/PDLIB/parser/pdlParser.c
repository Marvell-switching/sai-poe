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
/* ---------------------------------------------------------------------------------------------------------------
   Generated from sai_poe_yang_module based on revision 2024-04-01:1.01, PoE support added. on 20/08/2024 18:12:26
   --------------------------------------------------------------------------------------------------------------- */
#include "pdlib/lib/pdlLib.h"
#include "pdlib/xml/private/prvXmlParser.h"
#include "pdlib/xml/private/prvXmlParserBuilder.h"
#include "pdlib/lib/private/prvPdlLib.h"
#include "pdlParser.h"


    #ifdef RETURN_WRAPPER_MAC
    #undef RETURN_WRAPPER_MAC
    #endif
    #define RETURN_WRAPPER_MAC(_ret_code) return _ret_code

    /* common definitions */
    #ifndef MIN
    #define MIN(a,b) (a>b)?b:a
    #endif
    /* handle endianess */
    static int is_big_endian(void) { unsigned int x = 1; char *c = (char*) &x; return !((int)*c); }
     static UINT_32 swap_32(UINT_32 val) { PDL_PRAGMA_NOALIGN union U_TYP { UINT_32 word; UINT_8 bytes[4]; } PDL_PACKED_STRUCT_END v1, v2; PDL_PRAGMA_ALIGN v1.word = val;  v2.bytes[0] = v1.bytes[3]; v2.bytes[1] = v1.bytes[2]; v2.bytes[2] = v1.bytes[1]; v2.bytes[3] = v1.bytes[0]; return v2.word; }
    static int prvPdlIsBe;
    
    static PDL_SAI_PLATFORM_PARAMS_STC prvPdlSaiPlatform;
    
    /* handle enum conversion structs */
    #define PDL_PSEPORT_TYPE_ENUM_STR2VALUE_CNS 6
    static PDL_ENUM_STR2VALUE_STC pdlPseportTypeEnumStr2Value[] = {
        {PDL_PSEPORT_TYPE_AF_E, "AF"},
        {PDL_PSEPORT_TYPE_AT_E, "AT"},
        {PDL_PSEPORT_TYPE_60W_E, "60W"},
        {PDL_PSEPORT_TYPE_BT_TYPE2_E, "BT-type2"},
        {PDL_PSEPORT_TYPE_BT_TYPE3_E, "BT-type3"},
        {PDL_PSEPORT_TYPE_BT_TYPE4_E, "BT-type4"},
    };
    #define PDL_POE_HARDWARE_TYPE_ENUM_STR2VALUE_CNS 7
    static PDL_ENUM_STR2VALUE_STC pdlPoeHardwareTypeEnumStr2Value[] = {
        {PDL_POE_HARDWARE_TYPE_POE_NOT_SUPPORTED_E, "poe-not-supported"},
        {PDL_POE_HARDWARE_TYPE_POE_SUPPORT_E, "poe-support"},
        {PDL_POE_HARDWARE_TYPE_POE_PLUS_SUPPORT_E, "poe-plus-support"},
        {PDL_POE_HARDWARE_TYPE_POE_60W_SUPPORT_E, "poe-60W-support"},
        {PDL_POE_HARDWARE_TYPE_POE_BT_TYPE2_SUPPORT_E, "poe-bt-type2-support"},
        {PDL_POE_HARDWARE_TYPE_POE_BT_TYPE3_SUPPORT_E, "poe-bt-type3-support"},
        {PDL_POE_HARDWARE_TYPE_POE_BT_TYPE4_SUPPORT_E, "poe-bt-type4-support"},
    };
    #define PDL_POE_MCU_TYPE_ENUM_STR2VALUE_CNS 2
    static PDL_ENUM_STR2VALUE_STC pdlPoeMcuTypeEnumStr2Value[] = {
        {PDL_POE_MCU_TYPE_DRAGONITE_E, "dragonite"},
        {PDL_POE_MCU_TYPE_CM3_E, "cm3"},
    };
    #define PDL_POE_VENDOR_TYPE_ENUM_STR2VALUE_CNS 4
    static PDL_ENUM_STR2VALUE_STC pdlPoeVendorTypeEnumStr2Value[] = {
        {PDL_POE_VENDOR_TYPE_NONE_E, "none"},
        {PDL_POE_VENDOR_TYPE_MICROCHIP_E, "microchip"},
        {PDL_POE_VENDOR_TYPE_TI_E, "ti"},
        {PDL_POE_VENDOR_TYPE_ADI_E, "adi"},
    };
    #define PDL_POE_COMMUNICATION_TYPE_ENUM_STR2VALUE_CNS 3
    static PDL_ENUM_STR2VALUE_STC pdlPoeCommunicationTypeEnumStr2Value[] = {
        {PDL_POE_COMMUNICATION_TYPE_COMMUNICATION_TYPE_SERIAL_E, "communication-type-serial"},
        {PDL_POE_COMMUNICATION_TYPE_COMMUNICATION_TYPE_I2C_E, "communication-type-I2C"},
        {PDL_POE_COMMUNICATION_TYPE_COMMUNICATION_TYPE_MEMORY_E, "communication-type-memory"},
    };
    #define PDL_POE_HOST_SERIAL_CHANNEL_ID_ENUM_STR2VALUE_CNS 4
    static PDL_ENUM_STR2VALUE_STC pdlPoeHostSerialChannelIdEnumStr2Value[] = {
        {PDL_POE_HOST_SERIAL_CHANNEL_ID_UART_E, "uart"},
        {PDL_POE_HOST_SERIAL_CHANNEL_ID_I2C_E, "i2c"},
        {PDL_POE_HOST_SERIAL_CHANNEL_ID_DRAGONITE_SHARED_MEMORY_E, "dragonite-shared-memory"},
        {PDL_POE_HOST_SERIAL_CHANNEL_ID_IPC_SHARED_MEMORY_E, "ipc-shared-memory"},
    };
    /* aggregate enum conversion structs */
    static PDL_ENUM_IDS_ENUM_STR2VALUE_STC pdlEnumIdsEnumStr2Value[] =     {
    {PDL_ENUM_ID_PSEPORT_TYPE_E, &pdlPseportTypeEnumStr2Value[0], PDL_PSEPORT_TYPE_ENUM_STR2VALUE_CNS},
    {PDL_ENUM_ID_POE_HARDWARE_TYPE_E, &pdlPoeHardwareTypeEnumStr2Value[0], PDL_POE_HARDWARE_TYPE_ENUM_STR2VALUE_CNS},
    {PDL_ENUM_ID_POE_MCU_TYPE_E, &pdlPoeMcuTypeEnumStr2Value[0], PDL_POE_MCU_TYPE_ENUM_STR2VALUE_CNS},
    {PDL_ENUM_ID_POE_VENDOR_TYPE_E, &pdlPoeVendorTypeEnumStr2Value[0], PDL_POE_VENDOR_TYPE_ENUM_STR2VALUE_CNS},
    {PDL_ENUM_ID_POE_COMMUNICATION_TYPE_E, &pdlPoeCommunicationTypeEnumStr2Value[0], PDL_POE_COMMUNICATION_TYPE_ENUM_STR2VALUE_CNS},
    {PDL_ENUM_ID_POE_HOST_SERIAL_CHANNEL_ID_E, &pdlPoeHostSerialChannelIdEnumStr2Value[0], PDL_POE_HOST_SERIAL_CHANNEL_ID_ENUM_STR2VALUE_CNS},
    }
;
    /* dynamic definition for array of data */
    static PDL_FEATURE_DATA_STC prvPdlFeaturesData[PDL_FEATURE_ID_LAST_E];
    /* Feature data Array FILLING */
    /* function definition */
    extern PDL_STATUS prvPdlFeaturesDataHandler (void)
    {
        prvPdlFeaturesData[PDL_FEATURE_ID_POE_E].feature_id = PDL_FEATURE_ID_POE_E;
        prvPdlFeaturesData[PDL_FEATURE_ID_POE_E].is_supported = prvPdlSaiPlatform.poeFeatureIsSupported;
        prvPdlFeaturesData[PDL_FEATURE_ID_POE_E].data_PTR = (PDL_FEATURE_DATA_PARAMS_UNT*)&prvPdlSaiPlatform.poe;
        prvPdlFeaturesData[PDL_FEATURE_ID_POE_E].dataSize = sizeof(prvPdlSaiPlatform.poe);
        prvPdlFeaturesData[PDL_FEATURE_ID_POE_E].is_supported_mask = prvPdlSaiPlatform.poeFeatureIsSupported_mask;

        return PDL_OK;
    }
    /* CHOICE function definition */
    /* CHOICE destroy function definition */
    /* function definition */
    extern PDL_STATUS prvPdlCodeParser (XML_PARSER_NODE_DESCRIPTOR_TYP xml_root)
    {
        /* define generic/temp variables */
        UINT_32 max_size, uint_value;
        UINT_32 i;
        char string_value[PDL_XML_MAX_TAG_LEN + 1];
        
        /* define xml handles and statuses */
        XML_PARSER_RET_CODE_TYP xml_api_status[7];
        XML_PARSER_NODE_DESCRIPTOR_TYP xml_handle[7];
        void * list_entry_handle_PTR[1] = {0};
        void * list_entry_handle_PTR_PTR[1] = {0};
        PRV_PDLIB_DB_TYP list_db_handle_PTR[1] = {0};
        PRV_PDLIB_DB_ATTRIBUTES_STC db_attr;
        PDL_STATUS sysconf_status;
        UINT_32 list_size[1];
        UINT_32 list_entry_count[1];
        
        (void)list_entry_handle_PTR[0];
        (void)list_entry_handle_PTR_PTR[0];
        (void)sysconf_status;
        /* set endian variable */
        prvPdlIsBe = is_big_endian();
        
        /* init data */
        memset(&prvPdlSaiPlatform, 0, sizeof(prvPdlSaiPlatform));
        /* get root */
        xml_handle[0] = XML_PARSER_ROOT2NODE_CONVERT_MAC(xml_root);
        /* find data node */
        xml_api_status[0] = xmlParserFindChildByName(xml_handle[0], (char *)"data", &xml_handle[1]);
        /* if start */
        if (xml_api_status[0] != XML_PARSER_RET_CODE_OK)
        {
            RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
        }
        /* if end */
        xml_handle[0] = xml_handle[1];
        
        /* actual parser code */
        (void)i;
        (void)db_attr;
        (void)swap_32(0);
        xml_api_status[0] = xmlParserFindChildByName(xml_handle[0], (char *)"SAI-Platform", &xml_handle[1]);
        /* HANDLE STRUCT */
        if (xml_api_status[0] == XML_PARSER_RET_CODE_OK)
        { /* if start 2 */
            xml_api_status[1] = xmlParserFindChildByName(xml_handle[1], (char *)"POE-feature-is-supported", &xml_handle[2]);
            /* if start */
            if (xml_api_status[1] == XML_PARSER_RET_CODE_OK)
            {
                /* HANDLE SIMPLE INTEGER TYPE */
                max_size = sizeof(BOOLEAN);
                uint_value = 0;
                xml_api_status[2] = xmlParserGetValue(xml_handle[2], &max_size, &uint_value);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* if start */
                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                    {
                        /* HANDLE ENDIANESS */
                        BOOLEAN x;
                        x  = (BOOLEAN)swap_32(uint_value);
                        uint_value = (UINT_32)x;
                    }
                    /* if end */
                    /* HANDLE SIMPLE INTEGER TYPE */
                    prvPdlSaiPlatform.poeFeatureIsSupported = (BOOLEAN)uint_value;
                    prvPdlSaiPlatform.poeFeatureIsSupported_mask |= PDL_FIELD_HAS_VALUE_CNS;
                }
                /* if end */
            }
            /* if end */
            xml_api_status[1] = xmlParserFindChildByName(xml_handle[1], (char *)"PoE", &xml_handle[2]);
            /* HANDLE STRUCT */
            if (xml_api_status[1] == XML_PARSER_RET_CODE_OK)
            { /* if start 1 */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"poe-hw-type-value", &xml_handle[3]);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* HANDLE ENUM */
                    uint_value = PDL_XML_MAX_TAG_LEN;
                    xml_api_status[3] = xmlParserGetValue(xml_handle[3], &uint_value, &string_value[0]);
                    /* if start */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    {
                        /* handle enum string conversion */
                        /* for loop start */
                        for (i = 0;
                             i < PDL_POE_HARDWARE_TYPE_ENUM_STR2VALUE_CNS;
                             i++)
                        {
                            /* if compare string */
                            /* if start */
                            if (strcmp(string_value, pdlPoeHardwareTypeEnumStr2Value[i].str_value) == 0)
                            {
                                uint_value = pdlPoeHardwareTypeEnumStr2Value[i].int_value;
                                break;
                            }
                            /* if end */
                        }
                        /* for loop end */
                        /* check value was found if */
                        /* if start */
                        if (i == PDL_POE_HARDWARE_TYPE_ENUM_STR2VALUE_CNS)
                        {
                            RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
                        }
                        /* if end */
                        /* HANDLE ENUM */
                        prvPdlSaiPlatform.poe.poeHwTypeValue = (PDL_POE_HARDWARE_TYPE_ENT)uint_value;
                        prvPdlSaiPlatform.poe.poeHwTypeValue_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    }
                    /* if end */
                }
                /* if end */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"mcu-type", &xml_handle[3]);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* HANDLE ENUM */
                    uint_value = PDL_XML_MAX_TAG_LEN;
                    xml_api_status[3] = xmlParserGetValue(xml_handle[3], &uint_value, &string_value[0]);
                    /* if start */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    {
                        /* handle enum string conversion */
                        /* for loop start */
                        for (i = 0;
                             i < PDL_POE_MCU_TYPE_ENUM_STR2VALUE_CNS;
                             i++)
                        {
                            /* if compare string */
                            /* if start */
                            if (strcmp(string_value, pdlPoeMcuTypeEnumStr2Value[i].str_value) == 0)
                            {
                                uint_value = pdlPoeMcuTypeEnumStr2Value[i].int_value;
                                break;
                            }
                            /* if end */
                        }
                        /* for loop end */
                        /* check value was found if */
                        /* if start */
                        if (i == PDL_POE_MCU_TYPE_ENUM_STR2VALUE_CNS)
                        {
                            RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
                        }
                        /* if end */
                        /* HANDLE ENUM */
                        prvPdlSaiPlatform.poe.mcuType = (PDL_POE_MCU_TYPE_ENT)uint_value;
                        prvPdlSaiPlatform.poe.mcuType_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    }
                    /* if end */
                }
                /* if end */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"poe-communication-type-value", &xml_handle[3]);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* HANDLE ENUM */
                    uint_value = PDL_XML_MAX_TAG_LEN;
                    xml_api_status[3] = xmlParserGetValue(xml_handle[3], &uint_value, &string_value[0]);
                    /* if start */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    {
                        /* handle enum string conversion */
                        /* for loop start */
                        for (i = 0;
                             i < PDL_POE_COMMUNICATION_TYPE_ENUM_STR2VALUE_CNS;
                             i++)
                        {
                            /* if compare string */
                            /* if start */
                            if (strcmp(string_value, pdlPoeCommunicationTypeEnumStr2Value[i].str_value) == 0)
                            {
                                uint_value = pdlPoeCommunicationTypeEnumStr2Value[i].int_value;
                                break;
                            }
                            /* if end */
                        }
                        /* for loop end */
                        /* check value was found if */
                        /* if start */
                        if (i == PDL_POE_COMMUNICATION_TYPE_ENUM_STR2VALUE_CNS)
                        {
                            RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
                        }
                        /* if end */
                        /* HANDLE ENUM */
                        prvPdlSaiPlatform.poe.poeCommunicationTypeValue = (PDL_POE_COMMUNICATION_TYPE_ENT)uint_value;
                        prvPdlSaiPlatform.poe.poeCommunicationTypeValue_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    }
                    /* if end */
                }
                /* if end */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"host-serial-channel-id", &xml_handle[3]);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* HANDLE ENUM */
                    uint_value = PDL_XML_MAX_TAG_LEN;
                    xml_api_status[3] = xmlParserGetValue(xml_handle[3], &uint_value, &string_value[0]);
                    /* if start */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    {
                        /* handle enum string conversion */
                        /* for loop start */
                        for (i = 0;
                             i < PDL_POE_HOST_SERIAL_CHANNEL_ID_ENUM_STR2VALUE_CNS;
                             i++)
                        {
                            /* if compare string */
                            /* if start */
                            if (strcmp(string_value, pdlPoeHostSerialChannelIdEnumStr2Value[i].str_value) == 0)
                            {
                                uint_value = pdlPoeHostSerialChannelIdEnumStr2Value[i].int_value;
                                break;
                            }
                            /* if end */
                        }
                        /* for loop end */
                        /* check value was found if */
                        /* if start */
                        if (i == PDL_POE_HOST_SERIAL_CHANNEL_ID_ENUM_STR2VALUE_CNS)
                        {
                            RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
                        }
                        /* if end */
                        /* HANDLE ENUM */
                        prvPdlSaiPlatform.poe.hostSerialChannelId = (PDL_POE_HOST_SERIAL_CHANNEL_ID_ENT)uint_value;
                        prvPdlSaiPlatform.poe.hostSerialChannelId_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    }
                    /* if end */
                }
                /* if end */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"fw-file-name", &xml_handle[3]);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* HANDLE SIMPLE STRING TYPE */
                    max_size = PDL_XML_MAX_TAG_LEN;
                    xml_api_status[3] = xmlParserGetValue(xml_handle[3], &max_size, &string_value[0]);
                    string_value[max_size - 1] = '\0';
                    /* if start */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    {
                        /* HANDLE SIMPLE STRING TYPE */
                        prvPdlSaiPlatform.poe.fwFileName = (char *)prvPdlibOsMalloc(max_size/* contains number of bytes + NULL char */);
                        /* if start */
                        if (prvPdlSaiPlatform.poe.fwFileName == NULL)
                        {
                            RETURN_WRAPPER_MAC(PDL_OUT_OF_CPU_MEM);
                        }
                        /* if end */
                        XML_PARSER_STRCPY_MAC(prvPdlSaiPlatform.poe.fwFileName, string_value);
                        prvPdlSaiPlatform.poe.fwFileName_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    }
                    /* if end */
                }
                /* if end */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"pse-fw-file-name", &xml_handle[3]);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* HANDLE SIMPLE STRING TYPE */
                    max_size = PDL_XML_MAX_TAG_LEN;
                    xml_api_status[3] = xmlParserGetValue(xml_handle[3], &max_size, &string_value[0]);
                    string_value[max_size - 1] = '\0';
                    /* if start */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    {
                        /* HANDLE SIMPLE STRING TYPE */
                        prvPdlSaiPlatform.poe.pseFwFileName = (char *)prvPdlibOsMalloc(max_size/* contains number of bytes + NULL char */);
                        /* if start */
                        if (prvPdlSaiPlatform.poe.pseFwFileName == NULL)
                        {
                            RETURN_WRAPPER_MAC(PDL_OUT_OF_CPU_MEM);
                        }
                        /* if end */
                        XML_PARSER_STRCPY_MAC(prvPdlSaiPlatform.poe.pseFwFileName, string_value);
                        prvPdlSaiPlatform.poe.pseFwFileName_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    }
                    /* if end */
                }
                /* if end */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"poe-vendor", &xml_handle[3]);
                /* if start */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                {
                    /* HANDLE ENUM */
                    uint_value = PDL_XML_MAX_TAG_LEN;
                    xml_api_status[3] = xmlParserGetValue(xml_handle[3], &uint_value, &string_value[0]);
                    /* if start */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    {
                        /* handle enum string conversion */
                        /* for loop start */
                        for (i = 0;
                             i < PDL_POE_VENDOR_TYPE_ENUM_STR2VALUE_CNS;
                             i++)
                        {
                            /* if compare string */
                            /* if start */
                            if (strcmp(string_value, pdlPoeVendorTypeEnumStr2Value[i].str_value) == 0)
                            {
                                uint_value = pdlPoeVendorTypeEnumStr2Value[i].int_value;
                                break;
                            }
                            /* if end */
                        }
                        /* for loop end */
                        /* check value was found if */
                        /* if start */
                        if (i == PDL_POE_VENDOR_TYPE_ENUM_STR2VALUE_CNS)
                        {
                            RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
                        }
                        /* if end */
                        /* HANDLE ENUM */
                        prvPdlSaiPlatform.poe.poeVendor = (PDL_POE_VENDOR_TYPE_ENT)uint_value;
                        prvPdlSaiPlatform.poe.poeVendor_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    }
                    /* if end */
                }
                /* if end */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"POE-power-banks", &xml_handle[3]);
                /* HANDLE STRUCT */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                { /* if start 2 */
                    xml_api_status[3] = xmlParserFindChildByName(xml_handle[3], (char *)"PoEbank-list", &xml_handle[4]);
                    /* HANDLE STRUCT */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    { /* if start 3 */
                        /* LIST STRUCT CODE START */
                        xml_api_status[3] = xmlParserGetTagCount(xml_handle[3], (char *)"PoEbank-list", &list_size[0]);
                        /* if start */
                        if ((xml_api_status[3] != XML_PARSER_RET_CODE_OK) || (list_size[0] == 0))
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        list_entry_handle_PTR[0] = prvPdlibOsMalloc(sizeof(PDL_POEBANK_LIST_PARAMS_STC));
                        /* if start */
                        if (list_entry_handle_PTR[0] == NULL)
                        {
                            RETURN_WRAPPER_MAC(PDL_OUT_OF_CPU_MEM);
                        }
                        /* if end */
                        db_attr.listAttributes.keySize = sizeof(PDL_POEBANK_LIST_KEYS_STC);
                        db_attr.listAttributes.entrySize = sizeof(PDL_POEBANK_LIST_PARAMS_STC);
                        sysconf_status = prvPdlibDbCreate(PRV_PDLIB_DB_TYPE_LIST_E, &db_attr, &list_db_handle_PTR[0]);
                        /* if start */
                        if (sysconf_status != PDL_OK)
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        prvPdlSaiPlatform.poe.poePowerBanks.poebankList_PTR = list_db_handle_PTR[0];
                        list_entry_count[0] = 0;
                        while (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                        {
                            memset(list_entry_handle_PTR[0], 0, sizeof(PDL_POEBANK_LIST_PARAMS_STC));
                            
                            xml_api_status[4] = xmlParserIsEqualName(xml_handle[4], (char *)"PoEbank-list");
                            /* if start */
                            if (xml_api_status[4] != XML_PARSER_RET_CODE_OK)
                            {
                                break;
                            }
                            /* if end */
                            list_entry_count[0] ++;
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"bank-number", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE TYPE USING SIMPLE TYPE */
                                /* HANDLE NON-SIMPLE INTEGER TYPE */
                                max_size = sizeof(PDL_BANK_NUMBER_TYPE_TYP);
                                uint_value = 0;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &max_size, &uint_value);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* if start */
                                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                                    {
                                        /* HANDLE ENDIANESS */
                                        PDL_BANK_NUMBER_TYPE_TYP x;
                                        x  = (PDL_BANK_NUMBER_TYPE_TYP)swap_32(uint_value);
                                        uint_value = (UINT_32)x;
                                    }
                                    /* if end */
                                    /* Handle integer range */
                                    /* if start */
                                    if (uint_value > PDL_BANK_NUMBER_TYPE_MAX_VALUE_CNS)
                                    {
                                        RETURN_WRAPPER_MAC(PDL_OUT_OF_RANGE);
                                    }
                                    /* if end */
                                    /* HANDLE TYPE USING SIMPLE TYPE */
                                    /* HANDLE NON-SIMPLE INTEGER TYPE */
                                    (* (PDL_POEBANK_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).list_keys.bankNumber = (PDL_BANK_NUMBER_TYPE_TYP)uint_value;
                                }
                                /* if end */
                            }
                            /* if end */
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"bank-watts", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE TYPE USING SIMPLE TYPE */
                                /* HANDLE NON-SIMPLE INTEGER TYPE */
                                max_size = sizeof(PDL_BANK_WATTS_TYPE_TYP);
                                uint_value = 0;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &max_size, &uint_value);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* if start */
                                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                                    {
                                        /* HANDLE ENDIANESS */
                                        PDL_BANK_WATTS_TYPE_TYP x;
                                        x  = (PDL_BANK_WATTS_TYPE_TYP)swap_32(uint_value);
                                        uint_value = (UINT_32)x;
                                    }
                                    /* if end */
                                    /* HANDLE TYPE USING SIMPLE TYPE */
                                    /* HANDLE NON-SIMPLE INTEGER TYPE */
                                    (* (PDL_POEBANK_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).bankWatts = (PDL_BANK_WATTS_TYPE_TYP)uint_value;
                                    (* (PDL_POEBANK_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).bankWatts_mask |= PDL_FIELD_HAS_VALUE_CNS;
                                }
                                /* if end */
                            }
                            /* if end */
                            /* LIST STRUCT CODE STOP */
                            /* prvPdlSaiPlatform.poe.poePowerBanks.poebankList_PTR = list_db_handle_PTR[0]; */
                            sysconf_status = prvPdlibDbAdd(list_db_handle_PTR[0], (void *)&(((PDL_POEBANK_LIST_PARAMS_STC*)list_entry_handle_PTR[0])->list_keys), (void *)list_entry_handle_PTR[0], (void **)&list_entry_handle_PTR_PTR[0]);
                            /* if start */
                            if (sysconf_status != PDL_OK)
                            {
                                RETURN_WRAPPER_MAC(PDL_ERROR);
                            }
                            /* if end */
                            xml_api_status[3] = xmlParserGetNextSibling(xml_handle[4], & xml_handle[4]);
                        }
                        prvPdlibOsFree(list_entry_handle_PTR[0]);
                        /* if start */
                        if (list_size[0] != list_entry_count[0])
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        prvPdlSaiPlatform.poe.poePowerBanks.poebankList_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    } /* if end 3 */
                    prvPdlSaiPlatform.poe.poePowerBanks_mask |= PDL_FIELD_HAS_VALUE_CNS;
                } /* if end 2 */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"PSElist", &xml_handle[3]);
                /* HANDLE STRUCT */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                { /* if start 2 */
                    xml_api_status[3] = xmlParserFindChildByName(xml_handle[3], (char *)"PSE-list", &xml_handle[4]);
                    /* HANDLE STRUCT */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    { /* if start 3 */
                        /* LIST STRUCT CODE START */
                        xml_api_status[3] = xmlParserGetTagCount(xml_handle[3], (char *)"PSE-list", &list_size[0]);
                        /* if start */
                        if ((xml_api_status[3] != XML_PARSER_RET_CODE_OK) || (list_size[0] == 0))
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        list_entry_handle_PTR[0] = prvPdlibOsMalloc(sizeof(PDL_PSE_LIST_PARAMS_STC));
                        /* if start */
                        if (list_entry_handle_PTR[0] == NULL)
                        {
                            RETURN_WRAPPER_MAC(PDL_OUT_OF_CPU_MEM);
                        }
                        /* if end */
                        db_attr.listAttributes.keySize = sizeof(PDL_PSE_LIST_KEYS_STC);
                        db_attr.listAttributes.entrySize = sizeof(PDL_PSE_LIST_PARAMS_STC);
                        sysconf_status = prvPdlibDbCreate(PRV_PDLIB_DB_TYPE_LIST_E, &db_attr, &list_db_handle_PTR[0]);
                        /* if start */
                        if (sysconf_status != PDL_OK)
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        prvPdlSaiPlatform.poe.pselist.pseList_PTR = list_db_handle_PTR[0];
                        list_entry_count[0] = 0;
                        while (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                        {
                            memset(list_entry_handle_PTR[0], 0, sizeof(PDL_PSE_LIST_PARAMS_STC));
                            
                            xml_api_status[4] = xmlParserIsEqualName(xml_handle[4], (char *)"PSE-list");
                            /* if start */
                            if (xml_api_status[4] != XML_PARSER_RET_CODE_OK)
                            {
                                break;
                            }
                            /* if end */
                            list_entry_count[0] ++;
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"PSE-number", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE TYPE USING SIMPLE TYPE */
                                /* HANDLE NON-SIMPLE INTEGER TYPE */
                                max_size = sizeof(PDL_PSE_NUMBER_TYPE_TYP);
                                uint_value = 0;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &max_size, &uint_value);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* if start */
                                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                                    {
                                        /* HANDLE ENDIANESS */
                                        PDL_PSE_NUMBER_TYPE_TYP x;
                                        x  = (PDL_PSE_NUMBER_TYPE_TYP)swap_32(uint_value);
                                        uint_value = (UINT_32)x;
                                    }
                                    /* if end */
                                    /* Handle integer range */
                                    /* if start */
                                    if (uint_value > PDL_PSE_NUMBER_TYPE_MAX_VALUE_CNS)
                                    {
                                        RETURN_WRAPPER_MAC(PDL_OUT_OF_RANGE);
                                    }
                                    /* if end */
                                    /* HANDLE TYPE USING SIMPLE TYPE */
                                    /* HANDLE NON-SIMPLE INTEGER TYPE */
                                    (* (PDL_PSE_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).list_keys.pseNumber = (PDL_PSE_NUMBER_TYPE_TYP)uint_value;
                                }
                                /* if end */
                            }
                            /* if end */
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"PSE-address", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE TYPE USING SIMPLE TYPE */
                                /* HANDLE NON-SIMPLE INTEGER TYPE */
                                max_size = sizeof(PDL_PSE_ADDRESS_TYPE_TYP);
                                uint_value = 0;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &max_size, &uint_value);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* if start */
                                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                                    {
                                        /* HANDLE ENDIANESS */
                                        PDL_PSE_ADDRESS_TYPE_TYP x;
                                        x  = (PDL_PSE_ADDRESS_TYPE_TYP)swap_32(uint_value);
                                        uint_value = (UINT_32)x;
                                    }
                                    /* if end */
                                    /* Handle integer range */
                                    /* if start */
                                    if (uint_value > PDL_PSE_ADDRESS_TYPE_MAX_VALUE_CNS)
                                    {
                                        RETURN_WRAPPER_MAC(PDL_OUT_OF_RANGE);
                                    }
                                    /* if end */
                                    /* HANDLE TYPE USING SIMPLE TYPE */
                                    /* HANDLE NON-SIMPLE INTEGER TYPE */
                                    (* (PDL_PSE_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).pseAddress = (PDL_PSE_ADDRESS_TYPE_TYP)uint_value;
                                    (* (PDL_PSE_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).pseAddress_mask |= PDL_FIELD_HAS_VALUE_CNS;
                                }
                                /* if end */
                            }
                            /* if end */
                            /* LIST STRUCT CODE STOP */
                            /* prvPdlSaiPlatform.poe.pselist.pseList_PTR = list_db_handle_PTR[0]; */
                            sysconf_status = prvPdlibDbAdd(list_db_handle_PTR[0], (void *)&(((PDL_PSE_LIST_PARAMS_STC*)list_entry_handle_PTR[0])->list_keys), (void *)list_entry_handle_PTR[0], (void **)&list_entry_handle_PTR_PTR[0]);
                            /* if start */
                            if (sysconf_status != PDL_OK)
                            {
                                RETURN_WRAPPER_MAC(PDL_ERROR);
                            }
                            /* if end */
                            xml_api_status[3] = xmlParserGetNextSibling(xml_handle[4], & xml_handle[4]);
                        }
                        prvPdlibOsFree(list_entry_handle_PTR[0]);
                        /* if start */
                        if (list_size[0] != list_entry_count[0])
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        prvPdlSaiPlatform.poe.pselist.pseList_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    } /* if end 3 */
                    prvPdlSaiPlatform.poe.pselist_mask |= PDL_FIELD_HAS_VALUE_CNS;
                } /* if end 2 */
                xml_api_status[2] = xmlParserFindChildByName(xml_handle[2], (char *)"PSEports", &xml_handle[3]);
                /* HANDLE STRUCT */
                if (xml_api_status[2] == XML_PARSER_RET_CODE_OK)
                { /* if start 2 */
                    xml_api_status[3] = xmlParserFindChildByName(xml_handle[3], (char *)"PSEport-list", &xml_handle[4]);
                    /* HANDLE STRUCT */
                    if (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                    { /* if start 3 */
                        /* LIST STRUCT CODE START */
                        xml_api_status[3] = xmlParserGetTagCount(xml_handle[3], (char *)"PSEport-list", &list_size[0]);
                        /* if start */
                        if ((xml_api_status[3] != XML_PARSER_RET_CODE_OK) || (list_size[0] == 0))
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        list_entry_handle_PTR[0] = prvPdlibOsMalloc(sizeof(PDL_PSEPORT_LIST_PARAMS_STC));
                        /* if start */
                        if (list_entry_handle_PTR[0] == NULL)
                        {
                            RETURN_WRAPPER_MAC(PDL_OUT_OF_CPU_MEM);
                        }
                        /* if end */
                        db_attr.listAttributes.keySize = sizeof(PDL_PSEPORT_LIST_KEYS_STC);
                        db_attr.listAttributes.entrySize = sizeof(PDL_PSEPORT_LIST_PARAMS_STC);
                        sysconf_status = prvPdlibDbCreate(PRV_PDLIB_DB_TYPE_LIST_E, &db_attr, &list_db_handle_PTR[0]);
                        /* if start */
                        if (sysconf_status != PDL_OK)
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        prvPdlSaiPlatform.poe.pseports.pseportList_PTR = list_db_handle_PTR[0];
                        list_entry_count[0] = 0;
                        while (xml_api_status[3] == XML_PARSER_RET_CODE_OK)
                        {
                            memset(list_entry_handle_PTR[0], 0, sizeof(PDL_PSEPORT_LIST_PARAMS_STC));
                            
                            xml_api_status[4] = xmlParserIsEqualName(xml_handle[4], (char *)"PSEport-list");
                            /* if start */
                            if (xml_api_status[4] != XML_PARSER_RET_CODE_OK)
                            {
                                break;
                            }
                            /* if end */
                            list_entry_count[0] ++;
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"front-panel-port-index", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE TYPE USING SIMPLE TYPE */
                                /* HANDLE NON-SIMPLE INTEGER TYPE */
                                max_size = sizeof(PDL_PSEINDEX_TYPE_TYP);
                                uint_value = 0;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &max_size, &uint_value);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* if start */
                                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                                    {
                                        /* HANDLE ENDIANESS */
                                        PDL_PSEINDEX_TYPE_TYP x;
                                        x  = (PDL_PSEINDEX_TYPE_TYP)swap_32(uint_value);
                                        uint_value = (UINT_32)x;
                                    }
                                    /* if end */
                                    /* Handle integer range */
                                    /* if start */
                                    if (uint_value > PDL_PSEINDEX_TYPE_MAX_VALUE_CNS)
                                    {
                                        RETURN_WRAPPER_MAC(PDL_OUT_OF_RANGE);
                                    }
                                    /* if end */
                                    /* HANDLE TYPE USING SIMPLE TYPE */
                                    /* HANDLE NON-SIMPLE INTEGER TYPE */
                                    (* (PDL_PSEPORT_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).list_keys.frontPanelPortIndex = (PDL_PSEINDEX_TYPE_TYP)uint_value;
                                }
                                /* if end */
                            }
                            /* if end */
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"port-type", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE ENUM */
                                uint_value = PDL_XML_MAX_TAG_LEN;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &uint_value, &string_value[0]);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* handle enum string conversion */
                                    /* for loop start */
                                    for (i = 0;
                                         i < PDL_PSEPORT_TYPE_ENUM_STR2VALUE_CNS;
                                         i++)
                                    {
                                        /* if compare string */
                                        /* if start */
                                        if (strcmp(string_value, pdlPseportTypeEnumStr2Value[i].str_value) == 0)
                                        {
                                            uint_value = pdlPseportTypeEnumStr2Value[i].int_value;
                                            break;
                                        }
                                        /* if end */
                                    }
                                    /* for loop end */
                                    /* check value was found if */
                                    /* if start */
                                    if (i == PDL_PSEPORT_TYPE_ENUM_STR2VALUE_CNS)
                                    {
                                        RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
                                    }
                                    /* if end */
                                    /* HANDLE ENUM */
                                    (* (PDL_PSEPORT_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).portType = (PDL_PSEPORT_TYPE_ENT)uint_value;
                                    (* (PDL_PSEPORT_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).portType_mask |= PDL_FIELD_HAS_VALUE_CNS;
                                }
                                /* if end */
                            }
                            /* if end */
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"index1", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE TYPE USING SIMPLE TYPE */
                                /* HANDLE NON-SIMPLE INTEGER TYPE */
                                max_size = sizeof(PDL_PSEINDEX_TYPE_TYP);
                                uint_value = 0;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &max_size, &uint_value);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* if start */
                                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                                    {
                                        /* HANDLE ENDIANESS */
                                        PDL_PSEINDEX_TYPE_TYP x;
                                        x  = (PDL_PSEINDEX_TYPE_TYP)swap_32(uint_value);
                                        uint_value = (UINT_32)x;
                                    }
                                    /* if end */
                                    /* Handle integer range */
                                    /* if start */
                                    if (uint_value > PDL_PSEINDEX_TYPE_MAX_VALUE_CNS)
                                    {
                                        RETURN_WRAPPER_MAC(PDL_OUT_OF_RANGE);
                                    }
                                    /* if end */
                                    /* HANDLE TYPE USING SIMPLE TYPE */
                                    /* HANDLE NON-SIMPLE INTEGER TYPE */
                                    (* (PDL_PSEPORT_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).index1 = (PDL_PSEINDEX_TYPE_TYP)uint_value;
                                    (* (PDL_PSEPORT_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).index1_mask |= PDL_FIELD_HAS_VALUE_CNS;
                                }
                                /* if end */
                            }
                            /* if end */
                            xml_api_status[4] = xmlParserFindChildByName(xml_handle[4], (char *)"index2", &xml_handle[5]);
                            /* if start */
                            if (xml_api_status[4] == XML_PARSER_RET_CODE_OK)
                            {
                                /* HANDLE TYPE USING SIMPLE TYPE */
                                /* HANDLE NON-SIMPLE INTEGER TYPE */
                                max_size = sizeof(PDL_PSEINDEX_TYPE_TYP);
                                uint_value = 0;
                                xml_api_status[5] = xmlParserGetValue(xml_handle[5], &max_size, &uint_value);
                                /* if start */
                                if (xml_api_status[5] == XML_PARSER_RET_CODE_OK)
                                {
                                    /* if start */
                                    if (prvPdlIsBe && (max_size < sizeof(UINT_32)))
                                    {
                                        /* HANDLE ENDIANESS */
                                        PDL_PSEINDEX_TYPE_TYP x;
                                        x  = (PDL_PSEINDEX_TYPE_TYP)swap_32(uint_value);
                                        uint_value = (UINT_32)x;
                                    }
                                    /* if end */
                                    /* Handle integer range */
                                    /* if start */
                                    if (uint_value > PDL_PSEINDEX_TYPE_MAX_VALUE_CNS)
                                    {
                                        RETURN_WRAPPER_MAC(PDL_OUT_OF_RANGE);
                                    }
                                    /* if end */
                                    /* HANDLE TYPE USING SIMPLE TYPE */
                                    /* HANDLE NON-SIMPLE INTEGER TYPE */
                                    (* (PDL_PSEPORT_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).index2 = (PDL_PSEINDEX_TYPE_TYP)uint_value;
                                    (* (PDL_PSEPORT_LIST_PARAMS_STC *)list_entry_handle_PTR[0]).index2_mask |= PDL_FIELD_HAS_VALUE_CNS;
                                }
                                /* if end */
                            }
                            /* if end */
                            /* LIST STRUCT CODE STOP */
                            /* prvPdlSaiPlatform.poe.pseports.pseportList_PTR = list_db_handle_PTR[0]; */
                            sysconf_status = prvPdlibDbAdd(list_db_handle_PTR[0], (void *)&(((PDL_PSEPORT_LIST_PARAMS_STC*)list_entry_handle_PTR[0])->list_keys), (void *)list_entry_handle_PTR[0], (void **)&list_entry_handle_PTR_PTR[0]);
                            /* if start */
                            if (sysconf_status != PDL_OK)
                            {
                                RETURN_WRAPPER_MAC(PDL_ERROR);
                            }
                            /* if end */
                            xml_api_status[3] = xmlParserGetNextSibling(xml_handle[4], & xml_handle[4]);
                        }
                        prvPdlibOsFree(list_entry_handle_PTR[0]);
                        /* if start */
                        if (list_size[0] != list_entry_count[0])
                        {
                            RETURN_WRAPPER_MAC(PDL_ERROR);
                        }
                        /* if end */
                        prvPdlSaiPlatform.poe.pseports.pseportList_mask |= PDL_FIELD_HAS_VALUE_CNS;
                    } /* if end 3 */
                    prvPdlSaiPlatform.poe.pseports_mask |= PDL_FIELD_HAS_VALUE_CNS;
                } /* if end 2 */
                prvPdlSaiPlatform.poe_mask |= PDL_FIELD_HAS_VALUE_CNS;
            } /* if end 1 */
        } /* if end 2 */
        return PDL_OK;
    }
    /* function definition */
    extern PDL_STATUS prvPdlCodeDestroy (void)
    {
        /* define generic/temp variables */
        
        
        /* actual destroy code */
        /* DESTROY SIMPLE STRING TYPE */
        /* if start */
        if (prvPdlSaiPlatform.poe.fwFileName_mask & PDL_FIELD_HAS_VALUE_CNS)
        {
            prvPdlibOsFree(prvPdlSaiPlatform.poe.fwFileName);
            prvPdlSaiPlatform.poe.fwFileName = NULL;
        }
        /* if end */
        prvPdlSaiPlatform.poe.fwFileName_mask &= ~(UINT_8)PDL_FIELD_HAS_VALUE_CNS;
        /* DESTROY SIMPLE STRING TYPE */
        /* if start */
        if (prvPdlSaiPlatform.poe.pseFwFileName_mask & PDL_FIELD_HAS_VALUE_CNS)
        {
            prvPdlibOsFree(prvPdlSaiPlatform.poe.pseFwFileName);
            prvPdlSaiPlatform.poe.pseFwFileName = NULL;
        }
        /* if end */
        prvPdlSaiPlatform.poe.pseFwFileName_mask &= ~(UINT_8)PDL_FIELD_HAS_VALUE_CNS;
        /* if start */
        if (prvPdlSaiPlatform.poe.poePowerBanks.poebankList_PTR != NULL)
        {
            prvPdlibDbDestroy(prvPdlSaiPlatform.poe.poePowerBanks.poebankList_PTR);
            prvPdlSaiPlatform.poe.poePowerBanks.poebankList_PTR = NULL;
        }
        /* if end */
        prvPdlSaiPlatform.poe.poePowerBanks.poebankList_mask &= ~(UINT_8)PDL_FIELD_HAS_VALUE_CNS;
        /* if start */
        if (prvPdlSaiPlatform.poe.pselist.pseList_PTR != NULL)
        {
            prvPdlibDbDestroy(prvPdlSaiPlatform.poe.pselist.pseList_PTR);
            prvPdlSaiPlatform.poe.pselist.pseList_PTR = NULL;
        }
        /* if end */
        prvPdlSaiPlatform.poe.pselist.pseList_mask &= ~(UINT_8)PDL_FIELD_HAS_VALUE_CNS;
        /* if start */
        if (prvPdlSaiPlatform.poe.pseports.pseportList_PTR != NULL)
        {
            prvPdlibDbDestroy(prvPdlSaiPlatform.poe.pseports.pseportList_PTR);
            prvPdlSaiPlatform.poe.pseports.pseportList_PTR = NULL;
        }
        /* if end */
        prvPdlSaiPlatform.poe.pseports.pseportList_mask &= ~(UINT_8)PDL_FIELD_HAS_VALUE_CNS;
        return PDL_OK;
    }
    /* Feature data Array get */
    /* function definition */
    extern PDL_STATUS prvPdlFeaturesDataGet (PDL_FEATURE_DATA_STC ** data_PTR)
    {
        /* if start */
        if (data_PTR == NULL)
        {
            RETURN_WRAPPER_MAC(PDL_ERROR);
        }
        /* if end */

        *data_PTR = &prvPdlFeaturesData[0];
        return PDL_OK;
    }
    extern PDL_STATUS pdlInternalDbGet( PDL_SAI_PLATFORM_PARAMS_STC ** data_PTR)
    {
        /* if start */
        if (data_PTR == NULL)
        {
            RETURN_WRAPPER_MAC(PDL_ERROR);
        }
        /* if end */

        *data_PTR = &prvPdlSaiPlatform;

        return PDL_OK;
    }
    extern PDL_STATUS pdlEnum2StrConvert( 
        PDL_ENUM_IDS_ENT enum_type,
        UINT_32 int_value,
        char ** str_value_PTR
    )
    {
        UINT_32 i,j;
        for (i = 0; i < sizeof(pdlEnumIdsEnumStr2Value)/sizeof(pdlEnumIdsEnumStr2Value[0]); i ++)
        {
            if (pdlEnumIdsEnumStr2Value[i].enumId == enum_type)
            {
                for (j = 0; j < pdlEnumIdsEnumStr2Value[i].arr_size; j ++)
                {
                    if (pdlEnumIdsEnumStr2Value[i].convertArr_PTR[j].int_value == int_value)
                    {
                        *str_value_PTR = (char *)pdlEnumIdsEnumStr2Value[i].convertArr_PTR[j].str_value;
                        return PDL_OK;
                    }
                }
                RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
            }
        }
        RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
    }
    extern PDL_STATUS pdlStr2EnumConvert( 
        PDL_ENUM_IDS_ENT enum_type,
        char * str_value_PTR,
        UINT_32 * int_value_PTR
    )
    {
        UINT_32 i,j;
        for (i = 0; i < sizeof(pdlEnumIdsEnumStr2Value)/sizeof(pdlEnumIdsEnumStr2Value[0]); i ++)
        {
            if (pdlEnumIdsEnumStr2Value[i].enumId == enum_type)
            {
                for (j = 0; j < pdlEnumIdsEnumStr2Value[i].arr_size; j ++)
                {
                    if (strcmp(pdlEnumIdsEnumStr2Value[i].convertArr_PTR[j].str_value, str_value_PTR) == 0)
                    {
                        *int_value_PTR = pdlEnumIdsEnumStr2Value[i].convertArr_PTR[j].int_value;
                        return PDL_OK;
                    }
                }
                RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
            }
        }
        RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
    }
    extern PDL_STATUS pdlEnum2StrEntryGet( 
        PDL_ENUM_IDS_ENT enum_type,
        UINT_32 int_value,
        PDL_ENUM_STR2VALUE_STC ** entry_PTR
    )
    {
        UINT_32 i,j;
        for (i = 0; i < sizeof(pdlEnumIdsEnumStr2Value)/sizeof(pdlEnumIdsEnumStr2Value[0]); i ++)
        {
            if (pdlEnumIdsEnumStr2Value[i].enumId == enum_type)
            {
                for (j = 0; j < pdlEnumIdsEnumStr2Value[i].arr_size; j ++)
                {
                    if (pdlEnumIdsEnumStr2Value[i].convertArr_PTR[j].int_value == int_value)
                    {
                        *entry_PTR = &pdlEnumIdsEnumStr2Value[i].convertArr_PTR[j];
                        return PDL_OK;
                    }
                }
            }
        }
        RETURN_WRAPPER_MAC(PDL_NOT_FOUND);
    }
