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
#ifndef __PDL_SAI_Platform_AUTO_GENERATED_PARSER_HEADER_FILE__
#define __PDL_SAI_Platform_AUTO_GENERATED_PARSER_HEADER_FILE__
    /** @brief Internal */
    /* typedef start */
    typedef struct
    {
        /** @brief Internal */
        UINT_32 int_value;
        /** @brief Internal */
        const char * str_value;
    } PDL_ENUM_STR2VALUE_STC;
    /* typedef end */
    /** @brief Internal */
    /* typedef start */
    typedef enum
    {
        PDL_ENUM_ID_PSEPORT_TYPE_E,
        PDL_ENUM_ID_POE_HARDWARE_TYPE_E,
        PDL_ENUM_ID_POE_MCU_TYPE_E,
        PDL_ENUM_ID_POE_VENDOR_TYPE_E,
        PDL_ENUM_ID_POE_COMMUNICATION_TYPE_E,
        PDL_ENUM_ID_POE_HOST_SERIAL_CHANNEL_ID_E
    } PDL_ENUM_IDS_ENT;
    /* typedef end */
    /** @brief Internal */
    /* typedef start */
    typedef struct
    {
        /** @brief Internal */
        PDL_ENUM_IDS_ENT enumId;
        /** @brief Internal */
        PDL_ENUM_STR2VALUE_STC * convertArr_PTR;
        /** @brief Internal */
        UINT_32 arr_size;
    } PDL_ENUM_IDS_ENUM_STR2VALUE_STC;
    /* typedef end */
    typedef void * PRV_PDLIB_DB_TYP;
    #define PDL_BANK_NUMBER_TYPE_MIN_VALUE_CNS 0
    #define PDL_BANK_NUMBER_TYPE_MAX_VALUE_CNS 15
    typedef UINT_8 PDL_BANK_NUMBER_TYPE_TYP;

    typedef UINT_16 PDL_BANK_WATTS_TYPE_TYP;

    #define PDL_PSEINDEX_TYPE_MIN_VALUE_CNS 0
    #define PDL_PSEINDEX_TYPE_MAX_VALUE_CNS 127
    typedef UINT_8 PDL_PSEINDEX_TYPE_TYP;

    /**
    * @enumeration PDL_PSEPORT_TYPE_ENT
     *
    * @brief Specifies the PSE Port Type
    */
    typedef enum 
    {
        /** @brief Specifies the PSE Port type is AF (PoE). */
        PDL_PSEPORT_TYPE_AF_E = 1,
        /** @brief Specifies the PSE Port type as AT (PoE Plus). */
        PDL_PSEPORT_TYPE_AT_E = 2,
        /** @brief Specifies the PSE Port type as 60W (UPoE). */
        PDL_PSEPORT_TYPE_60W_E = 3,
        /** @brief Specifies the PSE Port type as BT - Type 2 (up to 30W). */
        PDL_PSEPORT_TYPE_BT_TYPE2_E = 4,
        /** @brief Specifies the PSE Port type as BT - Type 3 (up to 60W). */
        PDL_PSEPORT_TYPE_BT_TYPE3_E = 5,
        /** @brief Specifies the PSE Port type as BT - Type 4 (up to 90W). */
        PDL_PSEPORT_TYPE_BT_TYPE4_E = 6,
        PDL_PSEPORT_TYPE_LAST_E = 7    
    } PDL_PSEPORT_TYPE_ENT;
    /* PDL_ENUM_ID_PSEPORT_TYPE_E */

    #define PDL_PSE_NUMBER_TYPE_MIN_VALUE_CNS 0
    #define PDL_PSE_NUMBER_TYPE_MAX_VALUE_CNS 127
    typedef UINT_8 PDL_PSE_NUMBER_TYPE_TYP;

    #define PDL_PSE_ADDRESS_TYPE_MIN_VALUE_CNS 0
    #define PDL_PSE_ADDRESS_TYPE_MAX_VALUE_CNS 127
    typedef UINT_8 PDL_PSE_ADDRESS_TYPE_TYP;

    /**
    * @enumeration PDL_POE_HARDWARE_TYPE_ENT
     *
    * @brief Specifies the emergency support mode.
    */
    typedef enum 
    {
        /** @brief poe not supported. */
        PDL_POE_HARDWARE_TYPE_POE_NOT_SUPPORTED_E = 0,
        /** @brief poe hardware type. */
        PDL_POE_HARDWARE_TYPE_POE_SUPPORT_E = 1,
        /** @brief poe plus support. */
        PDL_POE_HARDWARE_TYPE_POE_PLUS_SUPPORT_E = 2,
        /** @brief poe 60W support. */
        PDL_POE_HARDWARE_TYPE_POE_60W_SUPPORT_E = 3,
        /** @brief poe bt type 2 support. */
        PDL_POE_HARDWARE_TYPE_POE_BT_TYPE2_SUPPORT_E = 4,
        /** @brief poe bt type 3 support. */
        PDL_POE_HARDWARE_TYPE_POE_BT_TYPE3_SUPPORT_E = 5,
        /** @brief poe bt type 4 support. */
        PDL_POE_HARDWARE_TYPE_POE_BT_TYPE4_SUPPORT_E = 6,
        PDL_POE_HARDWARE_TYPE_LAST_E = 7    
    } PDL_POE_HARDWARE_TYPE_ENT;
    /* PDL_ENUM_ID_POE_HARDWARE_TYPE_E */

    /**
    * @enumeration PDL_POE_MCU_TYPE_ENT
     *
    * @brief Specifies the poe mcu type.
    */
    typedef enum 
    {
        /** @brief dragonite */
        PDL_POE_MCU_TYPE_DRAGONITE_E = 0,
        /** @brief cm3 */
        PDL_POE_MCU_TYPE_CM3_E = 1,
        PDL_POE_MCU_TYPE_LAST_E = 2    
    } PDL_POE_MCU_TYPE_ENT;
    /* PDL_ENUM_ID_POE_MCU_TYPE_E */

    /**
    * @enumeration PDL_POE_VENDOR_TYPE_ENT
     *
    * @brief Specifies the poe vendor.
    */
    typedef enum 
    {
        /** @brief none */
        PDL_POE_VENDOR_TYPE_NONE_E = 0,
        /** @brief microchip */
        PDL_POE_VENDOR_TYPE_MICROCHIP_E = 1,
        /** @brief ti */
        PDL_POE_VENDOR_TYPE_TI_E = 2,
        /** @brief adi */
        PDL_POE_VENDOR_TYPE_ADI_E = 3,
        PDL_POE_VENDOR_TYPE_LAST_E = 4    
    } PDL_POE_VENDOR_TYPE_ENT;
    /* PDL_ENUM_ID_POE_VENDOR_TYPE_E */

    /**
    * @enumeration PDL_POE_COMMUNICATION_TYPE_ENT
     *
    * @brief Specifies the poe communication type
    */
    typedef enum 
    {
        /** @brief serial. */
        PDL_POE_COMMUNICATION_TYPE_COMMUNICATION_TYPE_SERIAL_E = 0,
        /** @brief I2C. */
        PDL_POE_COMMUNICATION_TYPE_COMMUNICATION_TYPE_I2C_E = 1,
        /** @brief memory. */
        PDL_POE_COMMUNICATION_TYPE_COMMUNICATION_TYPE_MEMORY_E = 2,
        PDL_POE_COMMUNICATION_TYPE_LAST_E = 3    
    } PDL_POE_COMMUNICATION_TYPE_ENT;
    /* PDL_ENUM_ID_POE_COMMUNICATION_TYPE_E */

    /**
    * @struct PDL_POEBANK_LIST_PARAMS_STC
     *
    * @brief Specifies a list of PoE Banks.
    */
    /* packed typedef start */
    PDL_PRAGMA_NOALIGN
    typedef PDL_PACKED_STRUCT_START struct
    {
        /* key index 0 */         PDL_BANK_NUMBER_TYPE_TYP bankNumber;
    } PDL_PACKED_STRUCT_END PDL_POEBANK_LIST_KEYS_STC;
    PDL_PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */
         PDL_POEBANK_LIST_KEYS_STC list_keys;
         /** @brief Specifies the Watts provided by the Bank. */
         PDL_BANK_WATTS_TYPE_TYP bankWatts;
         UINT_8 bankWatts_mask;
    } PDL_POEBANK_LIST_PARAMS_STC;
    /* LIST STRUCT DEFINITION */

    /**
    * @enumeration PDL_POE_HOST_SERIAL_CHANNEL_ID_ENT
     *
    * @brief Specifies the poe mcu type.
    */
    typedef enum 
    {
        /** @brief uart */
        PDL_POE_HOST_SERIAL_CHANNEL_ID_UART_E = 0,
        /** @brief i2c */
        PDL_POE_HOST_SERIAL_CHANNEL_ID_I2C_E = 1,
        /** @brief dragonite shared memory */
        PDL_POE_HOST_SERIAL_CHANNEL_ID_DRAGONITE_SHARED_MEMORY_E = 2,
        /** @brief ipc shared memory */
        PDL_POE_HOST_SERIAL_CHANNEL_ID_IPC_SHARED_MEMORY_E = 3,
        PDL_POE_HOST_SERIAL_CHANNEL_ID_LAST_E = 4    
    } PDL_POE_HOST_SERIAL_CHANNEL_ID_ENT;
    /* PDL_ENUM_ID_POE_HOST_SERIAL_CHANNEL_ID_E */

    /* packed typedef start */
    PDL_PRAGMA_NOALIGN
    typedef PDL_PACKED_STRUCT_START struct
    {
        /* key index 0 */         PDL_PSE_NUMBER_TYPE_TYP pseNumber;
    } PDL_PACKED_STRUCT_END PDL_PSE_LIST_KEYS_STC;
    PDL_PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */
         PDL_PSE_LIST_KEYS_STC list_keys;
         /** @brief Specifies the PSE address. */
         PDL_PSE_ADDRESS_TYPE_TYP pseAddress;
         UINT_8 pseAddress_mask;
    } PDL_PSE_LIST_PARAMS_STC;
    /* LIST STRUCT DEFINITION */

    /* packed typedef start */
    PDL_PRAGMA_NOALIGN
    typedef PDL_PACKED_STRUCT_START struct
    {
        /* key index 0 */         PDL_PSEINDEX_TYPE_TYP frontPanelPortIndex;
    } PDL_PACKED_STRUCT_END PDL_PSEPORT_LIST_KEYS_STC;
    PDL_PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */
         PDL_PSEPORT_LIST_KEYS_STC list_keys;
         /** @brief Specifies the PSE Port Type. */
         PDL_PSEPORT_TYPE_ENT portType;
         UINT_8 portType_mask;
         /** @brief Specifies the PSE Port Index 1. */
         PDL_PSEINDEX_TYPE_TYP index1;
         UINT_8 index1_mask;
         /** @brief Specifies the PSE Port Index 2. This index is used only when port-type = '60W' or 'BT' (type 3 or 4). */
         PDL_PSEINDEX_TYPE_TYP index2;
         UINT_8 index2_mask;
    } PDL_PSEPORT_LIST_PARAMS_STC;
    /* LIST STRUCT DEFINITION */

    /**
    * @struct PDL_POE_POWER_BANKS_PARAMS_STC
     *
    * @brief Specifies the power banks configuration.
    */
    typedef struct 
    {
         /* db of type PDL_POEBANK_LIST_PARAMS_STC */
         PRV_PDLIB_DB_TYP poebankList_PTR;
         UINT_8 poebankList_mask;
    } PDL_POE_POWER_BANKS_PARAMS_STC;

    /**
    * @struct PDL_PSELIST_PARAMS_STC
     *
    * @brief Specifies the PSE configuration.
    */
    typedef struct 
    {
         /* db of type PDL_PSE_LIST_PARAMS_STC */
         PRV_PDLIB_DB_TYP pseList_PTR;
         UINT_8 pseList_mask;
    } PDL_PSELIST_PARAMS_STC;

    /**
    * @struct PDL_PSEPORTS_PARAMS_STC
     *
    * @brief Specifies the PSE ports configuration.
    */
    typedef struct 
    {
         /* db of type PDL_PSEPORT_LIST_PARAMS_STC */
         PRV_PDLIB_DB_TYP pseportList_PTR;
         UINT_8 pseportList_mask;
    } PDL_PSEPORTS_PARAMS_STC;

    /**
    * @struct PDL_POE_PARAMS_STC
     *
    * @brief POE feature is supported
    */
    typedef struct 
    {
         /** @brief Specifies which PoE hardware type of device family is supported or not supported. */
         PDL_POE_HARDWARE_TYPE_ENT poeHwTypeValue;
         UINT_8 poeHwTypeValue_mask;
         /** @brief Specifies the PoE mcu type. */
         PDL_POE_MCU_TYPE_ENT mcuType;
         UINT_8 mcuType_mask;
         /** @brief Indicates whether PoE communication type is serial, I2C or memory. */
         PDL_POE_COMMUNICATION_TYPE_ENT poeCommunicationTypeValue;
         UINT_8 poeCommunicationTypeValue_mask;
         /** @brief Specifies the host serial channel id. */
         PDL_POE_HOST_SERIAL_CHANNEL_ID_ENT hostSerialChannelId;
         UINT_8 hostSerialChannelId_mask;
         /** @brief Indicates fw file name. */
         char * fwFileName;
         UINT_8 fwFileName_mask;
         /** @brief Indicates pse fw file name. */
         char * pseFwFileName;
         UINT_8 pseFwFileName_mask;
         /** @brief Specifies the PoE vendor. */
         PDL_POE_VENDOR_TYPE_ENT poeVendor;
         UINT_8 poeVendor_mask;
         /** @brief Specifies the power banks configuration. */
         PDL_POE_POWER_BANKS_PARAMS_STC poePowerBanks;
         UINT_8 poePowerBanks_mask;
         /** @brief Specifies the PSE configuration. */
         PDL_PSELIST_PARAMS_STC pselist;
         UINT_8 pselist_mask;
         /** @brief Specifies the PSE ports configuration. */
         PDL_PSEPORTS_PARAMS_STC pseports;
         UINT_8 pseports_mask;
    } PDL_POE_PARAMS_STC;

    /**
    * @struct PDL_SAI_PLATFORM_PARAMS_STC
     *
    * @brief SAI Platform Yang, this describes the hardware and access for SAI boards.
    */
    typedef struct 
    {
         /** @brief The feature can be configured only if POE is supported. */
         BOOLEAN poeFeatureIsSupported;
         UINT_8 poeFeatureIsSupported_mask;
         /** @brief POE feature is supported */
         PDL_POE_PARAMS_STC poe;
         UINT_8 poe_mask;
    } PDL_SAI_PLATFORM_PARAMS_STC;

    /* FEATURES IDS ENUM DECLARTATION */
    typedef enum {
        PDL_FEATURE_ID_POE_E,
        PDL_FEATURE_ID_LAST_E
    } PDL_FEATURE_ID_ENT;
    /* FEATURES UNION DECLARTATION */
    typedef union {
        PDL_POE_PARAMS_STC poe;
    } PDL_FEATURE_DATA_PARAMS_UNT;
    /* STRUCTURE FOR DATA MAPPING */
    typedef struct {
        PDL_FEATURE_ID_ENT feature_id;
        BOOLEAN is_supported;
        UINT_8 is_supported_mask;
        PDL_FEATURE_DATA_PARAMS_UNT * data_PTR;
        UINT_32 dataSize;
    } PDL_FEATURE_DATA_STC;
#endif/* #ifndef __PDL_SAI_Platform_AUTO_GENERATED_PARSER_HEADER_FILE__ */
