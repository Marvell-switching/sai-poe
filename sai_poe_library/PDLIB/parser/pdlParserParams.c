// /* ---------------------------------------------------------------------------------------------------------------
//    Generated from sai_poe_yang_module based on revision 2024-04-01:1.01, PoE support added. on 10/04/2024 11:59:36
//    --------------------------------------------------------------------------------------------------------------- */
// #include "../h/pdlib/common/pdlTypes.h"
// #include "../h/pdlib/lib/pdlLib.h"
// #include "../h/pdlib/lib/private/prvPdlLib.h"
// #include "../h/pdlib/xml/private/prvXmlParser.h"
// #include "../h/pdlib/xml/private/prvXmlParserBuilder.h"
// #include "../parser/pdlParser.h"

// // #include <inf/sysconfinf/exp/sysconfinf.h>
// // #include <mngcnf/sysconf/main/inc/sysconf_prv.h>

//     #undef PDL_CHECK_STATUS
//     #define PDL_CHECK_STATUS(__pdlStatus)  PDL_CHECK_STATUS_GEN(__pdlStatus, prvPdlAutoParserDebugFlag)

//     #ifdef RETURN_WRAPPER_MAC
//     #undef RETURN_WRAPPER_MAC
//     #endif
//     #define RETURN_WRAPPER_MAC(_ret_code) PDL_CHECK_STATUS(_ret_code)

//     /* HPRM STRUCT FILLING */
//     /* function definition */
//     extern PDL_STATUS pdlHprmHandler (void ** hash_db_PTR)
//     {
//         PDL_SAI_PLATFORM_PARAMS_STC * project_data_db_PTR;
//         VHASHG_status_ENT hash_status;
//         PDL_STATUS sysconf_status;
//         PDL_FEATURE_HPRM_DATA_STC hash_entry;
//         PDL_ENUM_STR2VALUE_STC * enum_str2value_entry_PTR;
        
//         sysconf_status = pdlInternalDbGet ( &project_data_db_PTR);
//         /* if start */
//         if (sysconf_status != PDL_OK)
//         {
//             OSSYSG_fatal_error("SYSCONFG_hprm_handler - project profile fail to get project data DB");
//         }
//         /* if end */
        
//         hash_status = VHASHG_new(NULL, TRUE, OSMEMG_type_perm_E, hash_db_PTR);
//         /* if start */
//         if (hash_status != VHASHG_status_ok_E)
//         {
//             OSSYSG_fatal_error("SYSCONFG_hprm_handler - project profile fail to create hprms DB");
//         }
//         /* if end */
//         hash_status = VHASHG_set_sorting(*hash_db_PTR, VHASHG_sort_type_strcmp_E);
//         /* if start */
//         if (hash_status != VHASHG_status_ok_E)
//         {
//             OSSYSG_fatal_error("SYSCONFG_hprm_handler - project profile fail to set hprms DB sort type");
//         }
//         /* if end */
//         hash_status = VHASHG_set_maximal_key_size(*hash_db_PTR, SYSCONFP_max_key_size_CNS);
//         /* if start */
//         if (hash_status != VHASHG_status_ok_E)
//         {
//             OSSYSG_fatal_error("SYSCONFG_hprm_handler - project profile fail to set hprms DB maximal key size");
//         }
//         /* if end */
//         /* List is not supported - skip it */
//         /* project_data_db_PTR->poe.pseports.pseportList */
//         /* List is not supported - skip it */
//         /* project_data_db_PTR->poe.poePowerBanks.poebankList */
//         /* List is not supported - skip it */
//         /* project_data_db_PTR->poe.pselist.pseList */
//         /* fill hash entry */
//         if ((project_data_db_PTR->poe.fwFileName_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             hash_entry.data_PTR = (void *)project_data_db_PTR->poe.fwFileName;
//             hash_entry.type = /* HANDLE TYPE USING SIMPLE TYPE */MIB_rlHostParamType_displayString_CNS;
//             hash_entry.data_size = strlen(/* HANDLE SIMPLE TYPE */project_data_db_PTR->poe.fwFileName) + 1;
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poe.fwFileName",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         /* List is not supported - skip it */
//         /* project_data_db_PTR->poe.pseports.pseportList */
//         /* fill hash entry */
//         if ((project_data_db_PTR->poe.hostSerialChannelId_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             /* HANDLE ENUM */
//             /* if start */
//             if (PDL_OK != pdlEnum2StrEntryGet(PDL_ENUM_ID_POE_HOST_SERIAL_CHANNEL_ID_E, project_data_db_PTR->poe.hostSerialChannelId, &enum_str2value_entry_PTR))
//             {
//                 RETURN_WRAPPER_MAC(PDL_ERROR);
//             }
//             /* if end */
//             hash_entry.data_PTR = (void *)enum_str2value_entry_PTR;
//             hash_entry.type = /* HANDLE ENUM */MIB_rlHostParamType_enum_CNS;
//             hash_entry.data_size = sizeof(/* HANDLE ENUM */PDL_ENUM_STR2VALUE_STC);
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poe.hostSerialChannelId",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         /* List is not supported - skip it */
//         /* project_data_db_PTR->poe.poePowerBanks.poebankList */
//         /* fill hash entry */
//         if ((project_data_db_PTR->poe.poeCommunicationTypeValue_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             /* HANDLE ENUM */
//             /* if start */
//             if (PDL_OK != pdlEnum2StrEntryGet(PDL_ENUM_ID_POE_COMMUNICATION_TYPE_E, project_data_db_PTR->poe.poeCommunicationTypeValue, &enum_str2value_entry_PTR))
//             {
//                 RETURN_WRAPPER_MAC(PDL_ERROR);
//             }
//             /* if end */
//             hash_entry.data_PTR = (void *)enum_str2value_entry_PTR;
//             hash_entry.type = /* HANDLE ENUM */MIB_rlHostParamType_enum_CNS;
//             hash_entry.data_size = sizeof(/* HANDLE ENUM */PDL_ENUM_STR2VALUE_STC);
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poe.poeCommunicationTypeValue",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         /* fill hash entry */
//         if ((project_data_db_PTR->poe.pseFwFileName_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             hash_entry.data_PTR = (void *)project_data_db_PTR->poe.pseFwFileName;
//             hash_entry.type = /* HANDLE TYPE USING SIMPLE TYPE */MIB_rlHostParamType_displayString_CNS;
//             hash_entry.data_size = strlen(/* HANDLE SIMPLE TYPE */project_data_db_PTR->poe.pseFwFileName) + 1;
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poe.pseFwFileName",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         /* List is not supported - skip it */
//         /* project_data_db_PTR->poe.pselist.pseList */
//         /* fill hash entry */
//         if ((project_data_db_PTR->poe.poeHwTypeValue_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             /* HANDLE ENUM */
//             /* if start */
//             if (PDL_OK != pdlEnum2StrEntryGet(PDL_ENUM_ID_POE_HARDWARE_TYPE_E, project_data_db_PTR->poe.poeHwTypeValue, &enum_str2value_entry_PTR))
//             {
//                 RETURN_WRAPPER_MAC(PDL_ERROR);
//             }
//             /* if end */
//             hash_entry.data_PTR = (void *)enum_str2value_entry_PTR;
//             hash_entry.type = /* HANDLE ENUM */MIB_rlHostParamType_enum_CNS;
//             hash_entry.data_size = sizeof(/* HANDLE ENUM */PDL_ENUM_STR2VALUE_STC);
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poe.poeHwTypeValue",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         /* fill hash entry */
//         if ((project_data_db_PTR->poe.poeVendor_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             /* HANDLE ENUM */
//             /* if start */
//             if (PDL_OK != pdlEnum2StrEntryGet(PDL_ENUM_ID_POE_VENDOR_TYPE_E, project_data_db_PTR->poe.poeVendor, &enum_str2value_entry_PTR))
//             {
//                 RETURN_WRAPPER_MAC(PDL_ERROR);
//             }
//             /* if end */
//             hash_entry.data_PTR = (void *)enum_str2value_entry_PTR;
//             hash_entry.type = /* HANDLE ENUM */MIB_rlHostParamType_enum_CNS;
//             hash_entry.data_size = sizeof(/* HANDLE ENUM */PDL_ENUM_STR2VALUE_STC);
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poe.poeVendor",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         /* fill hash entry */
//         if ((project_data_db_PTR->poe.mcuType_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             /* HANDLE ENUM */
//             /* if start */
//             if (PDL_OK != pdlEnum2StrEntryGet(PDL_ENUM_ID_POE_MCU_TYPE_E, project_data_db_PTR->poe.mcuType, &enum_str2value_entry_PTR))
//             {
//                 RETURN_WRAPPER_MAC(PDL_ERROR);
//             }
//             /* if end */
//             hash_entry.data_PTR = (void *)enum_str2value_entry_PTR;
//             hash_entry.type = /* HANDLE ENUM */MIB_rlHostParamType_enum_CNS;
//             hash_entry.data_size = sizeof(/* HANDLE ENUM */PDL_ENUM_STR2VALUE_STC);
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poe.mcuType",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         /* fill hash entry */
//         if ((project_data_db_PTR->poeFeatureIsSupported_mask) & PDL_FIELD_HAS_VALUE_CNS)
//         {
//             hash_entry.data_PTR = (void *)&project_data_db_PTR->poeFeatureIsSupported;
//             hash_entry.type = /* HANDLE TYPE USING SIMPLE TYPE */MIB_rlHostParamType_truthValue_CNS;
//             hash_entry.data_size = sizeof(/* HANDLE SIMPLE TYPE */BOOLEAN);
//             hash_status = VHASHG_set_by_string_key(
//                 *hash_db_PTR,
//                 "poeFeatureIsSupported",
//                 sizeof(PDL_FEATURE_HPRM_DATA_STC),
//                 &hash_entry,
//                 NULL);
//             /* if start */
//             if (hash_status != VHASHG_status_ok_E)
//             {
//                 RETURN_WRAPPER_MAC(PDL_NO_SUCH);
//             }
//             /* if end */
//         }
//         return PDL_OK;
//     }
