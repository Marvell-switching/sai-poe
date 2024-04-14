/* -------------------------------------------------------------------------------------------------------
   Generated from MTS-Project-Profile-Yang-Module based on revision 2023-09-05:2.42 on 05/09/2023 17:09:42
   ------------------------------------------------------------------------------------------------------- */
#ifndef __SYSCONFG_MTS_Project_AUTO_GENERATED_PARSER_HEADER_FILE__
#define __SYSCONFG_MTS_Project_AUTO_GENERATED_PARSER_HEADER_FILE__
    /* typedef start */
    typedef struct
    {
        UINT_32 int_value;
        const char * str_value;
    } SYSCONFG_enum_str2value_STC;
    /* typedef end */
    /* typedef start */
    typedef enum
    {
        SYSCONFG_enum_id_rx_training_type_E,
        SYSCONFG_enum_id_flow_control_mode_type_E,
        SYSCONFG_enum_id_flow_control_management_mode_type_E,
        SYSCONFG_enum_id_show_inventory_mode_E,
        SYSCONFG_enum_id_max_consumption_type_E,
        SYSCONFG_enum_id_cpld_update_mode_E,
        SYSCONFG_enum_id_port_lock_limitation_mode_type_E,
        SYSCONFG_enum_id_port_lock_violation_action_type_E,
        SYSCONFG_enum_id_port_lock_secure_address_type_E,
        SYSCONFG_enum_id_port_lock_secure_address_on_unlock_type_E,
        SYSCONFG_enum_id_loopback_detection_destination_mode_type_E,
        SYSCONFG_enum_id_loopback_detection_source_mode_type_E,
        SYSCONFG_enum_id_Bridge_default_MC_vlan_mode_type_E,
        SYSCONFG_enum_id_cpu_drop_precedence_type_E,
        SYSCONFG_enum_id_cpu_traffic_flow_type_E,
        SYSCONFG_enum_id_led_display_mode_type_E,
        SYSCONFG_enum_id_led_display_default_pattern_type_E,
        SYSCONFG_enum_id_port_led_mode_type_E,
        SYSCONFG_enum_id_udld_port_mode_type_E,
        SYSCONFG_enum_id_vlan_acceptable_frame_type_E,
        SYSCONFG_enum_id_vlan_human_type_E,
        SYSCONFG_enum_id_vlan_port_model_type_E,
        SYSCONFG_enum_id_vlan_default_port_mode_type_E,
        SYSCONFG_enum_id_vlan_switchport_mode_type_E,
        SYSCONFG_enum_id_vlan_default_trunk_port_mode_membership_type_E,
        SYSCONFG_enum_id_vlan_voice_cos_mode_type_E,
        SYSCONFG_enum_id_vlan_voice_admin_state_type_E,
        SYSCONFG_enum_id_vrrp_version_type_E,
        SYSCONFG_enum_id_voip_cos_mode_E,
        SYSCONFG_enum_id_auto_neg_role_E,
        SYSCONFG_enum_id_lldp_port_id_format_type_E,
        SYSCONFG_enum_id_lldp_advertise_ma_selection_manner_type_E,
        SYSCONFG_enum_id_sampling_resolution_type_E,
        SYSCONFG_enum_id_public_key_auto_generation_algorithm_E,
        SYSCONFG_enum_id_scp_default_authentication_method_E,
        SYSCONFG_enum_id_copy_different_SKU_directive_type_E,
        SYSCONFG_enum_id_copy_default_directive_access_type_E,
        SYSCONFG_enum_id_cdp_advertised_version_type_E,
        SYSCONFG_enum_id_cdp_default_device_id_format_type_E,
        SYSCONFG_enum_id_poe_communication_mode_E,
        SYSCONFG_enum_id_poe_disconnect_method_E,
        SYSCONFG_enum_id_poe_emergency_support_mode_E,
        SYSCONFG_enum_id_poe_port_max_limit_supported_E,
        SYSCONFG_enum_id_poe_port_limit_mode_E,
        SYSCONFG_enum_id_poe_ps_rps_mode_E,
        SYSCONFG_enum_id_poe_tbp_port_status_default_action_mode_E,
        SYSCONFG_enum_id_poe_power_management_default_mode_E,
        SYSCONFG_enum_id_poe_guard_band_mode_E,
        SYSCONFG_enum_id_poe_error_handling_mode_type_E,
        SYSCONFG_enum_id_poe_lldp_tx_pattern_type_E,
        SYSCONFG_enum_id_default_pk_algorithm_type_E,
        SYSCONFG_enum_id_aaa_default_encoding_algorithm_type_E,
        SYSCONFG_enum_id_aaa_hashing_algorithm_type_E,
        SYSCONFG_enum_id_aaa_hashing_method_type_E,
        SYSCONFG_enum_id_unit_type_E,
        SYSCONFG_enum_id_start_condition_type_E,
        SYSCONFG_enum_id_target_type_E,
        SYSCONFG_enum_id_smart_port_type_E,
        SYSCONFG_enum_id_smart_port_enable_E,
        SYSCONFG_enum_id_read_default_directive_type_E,
        SYSCONFG_enum_id_system_mode_type_E,
        SYSCONFG_enum_id_dot1x_port_default_mode_type_E,
        SYSCONFG_enum_id_dot1x_host_default_mode_type_E,
        SYSCONFG_enum_id_mac_address_format_type_E,
        SYSCONFG_enum_id_cli_interface_type_E,
        SYSCONFG_enum_id_lag_balance_layer_type_E,
        SYSCONFG_enum_id_lacp_port_membership_in_lag_type_E,
        SYSCONFG_enum_id_lag_creation_type_E,
        SYSCONFG_enum_id_authentication_method_type_E,
        SYSCONFG_enum_id_tcp_syn_protection_mode_type_E,
        SYSCONFG_enum_id_sec_suite_supported_rules_type_E,
        SYSCONFG_enum_id_web_authentication_privilege_level_type_E,
        SYSCONFG_enum_id_header_action_type_E,
        SYSCONFG_enum_id_mld_version_type_E,
        SYSCONFG_enum_id_cost_type_E,
        SYSCONFG_enum_id_protocol_type_E,
        SYSCONFG_enum_id_flood_method_type_E
    } SYSCONFG_enum_ids_ENT;
    /* typedef end */
    /* typedef start */
    typedef struct
    {
        SYSCONFG_enum_ids_ENT enum_id;
        SYSCONFG_enum_str2value_STC * convertArr_PTR;
        UINT_32 arr_size;
    } SYSCONFG_enum_ids_enum_str2value_STC;
    /* typedef end */
    typedef void * SYSCONFG_DB_HANDLE_TYP;
    typedef enum 
    {
        SYSCONFG_rx_training_type_signal_detect_not_supported_E = 1,
        SYSCONFG_rx_training_type_signal_detect_by_interrupts_E = 2,
        SYSCONFG_rx_training_type_signal_detect_by_link_change_E = 3,
        SYSCONFG_rx_training_type_last_E = 4    
    } SYSCONFG_rx_training_type_ENT;
    /* SYSCONFG_enum_id_rx_training_type_E */

    typedef enum 
    {
        SYSCONFG_flow_control_mode_type_on_E = 1,
        SYSCONFG_flow_control_mode_type_off_E = 2,
        SYSCONFG_flow_control_mode_type_auto_negotiation_E = 3,
        SYSCONFG_flow_control_mode_type_last_E = 4    
    } SYSCONFG_flow_control_mode_type_ENT;
    /* SYSCONFG_enum_id_flow_control_mode_type_E */

    typedef enum 
    {
        SYSCONFG_flow_control_management_mode_type_per_port_E = 1,
        SYSCONFG_flow_control_management_mode_type_global_E = 2,
        SYSCONFG_flow_control_management_mode_type_last_E = 3    
    } SYSCONFG_flow_control_management_mode_type_ENT;
    /* SYSCONFG_enum_id_flow_control_management_mode_type_E */

    typedef struct 
    {
         UINT_32 cpss_pool_size;
         UINT_8 cpss_pool_size_mask;
         UINT_32 dpss_pool_size;
         UINT_8 dpss_pool_size_mask;
    } SYSCONFG_HAL_OS_params_STC;

    typedef enum 
    {
        SYSCONFG_show_inventory_mode_not_supported_E = 1,
        SYSCONFG_show_inventory_mode_present_E = 2,
        SYSCONFG_show_inventory_mode_loss_E = 3,
        SYSCONFG_show_inventory_mode_last_E = 4    
    } SYSCONFG_show_inventory_mode_ENT;
    /* SYSCONFG_enum_id_show_inventory_mode_E */

    typedef enum 
    {
        SYSCONFG_max_consumption_type_core_E = 1,
        SYSCONFG_max_consumption_type_IS_E = 2,
        SYSCONFG_max_consumption_type_last_E = 3    
    } SYSCONFG_max_consumption_type_ENT;
    /* SYSCONFG_enum_id_max_consumption_type_E */

    typedef struct 
    {
         BOOLEAN is_http_over_BNEP_supported;
         UINT_8 is_http_over_BNEP_supported_mask;
         BOOLEAN is_ssh_over_BNEP_supported;
         UINT_8 is_ssh_over_BNEP_supported_mask;
         BOOLEAN is_telnet_over_BNEP_supported;
         UINT_8 is_telnet_over_BNEP_supported_mask;
         RSG_ip_addr_TYP BNEP_default_IP;
         UINT_8 BNEP_default_IP_mask;
         BOOLEAN is_DHCP_server_supported;
         UINT_8 is_DHCP_server_supported_mask;
    } SYSCONFG_BNEP_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_Protocol_Filtering_params_STC;

    typedef struct 
    {
         BOOLEAN option_82_rx_on_untrusted_port_is_enabled;
         UINT_8 option_82_rx_on_untrusted_port_is_enabled_mask;
         UINT_32 maximum_number_of_entries;
         UINT_8 maximum_number_of_entries_mask;
         BOOLEAN dhcp_snooping_file_is_enabled;
         UINT_8 dhcp_snooping_file_is_enabled_mask;
         BOOLEAN verify_mac_address;
         UINT_8 verify_mac_address_mask;
         BOOLEAN dhcp_snooping_is_enabled_by_default;
         UINT_8 dhcp_snooping_is_enabled_by_default_mask;
    } SYSCONFG_DHCP_snooping_params_STC;

    typedef enum 
    {
        SYSCONFG_cpld_update_mode_mode_auto_E = 0,
        SYSCONFG_cpld_update_mode_mode_trigger_E = 1,
        SYSCONFG_cpld_update_mode_mode_auto_background_E = 2,
        SYSCONFG_cpld_update_mode_last_E = 3    
    } SYSCONFG_cpld_update_mode_ENT;
    /* SYSCONFG_enum_id_cpld_update_mode_E */

    typedef enum 
    {
        SYSCONFG_port_lock_limitation_mode_type_lock_secure_E = 1,
        SYSCONFG_port_lock_limitation_mode_type_max_addresses_E = 2,
        SYSCONFG_port_lock_limitation_mode_type_secure_permanent_E = 3,
        SYSCONFG_port_lock_limitation_mode_type_secure_delete_on_reset_E = 4,
        SYSCONFG_port_lock_limitation_mode_type_last_E = 5    
    } SYSCONFG_port_lock_limitation_mode_type_ENT;
    /* SYSCONFG_enum_id_port_lock_limitation_mode_type_E */

    typedef enum 
    {
        SYSCONFG_port_lock_violation_action_type_discard_E = 1,
        SYSCONFG_port_lock_violation_action_type_forward_E = 2,
        SYSCONFG_port_lock_violation_action_type_discard_shutdown_E = 3,
        SYSCONFG_port_lock_violation_action_type_last_E = 4    
    } SYSCONFG_port_lock_violation_action_type_ENT;
    /* SYSCONFG_enum_id_port_lock_violation_action_type_E */

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_Open_flow_params_STC;

    typedef struct 
    {
         UINT_32 max_prl_entries_per_interface;
         UINT_8 max_prl_entries_per_interface_mask;
         UINT_32 solicitation_interval_seconds;
         UINT_8 solicitation_interval_seconds_mask;
         UINT_32 maximum_num_of_interfaces;
         UINT_8 maximum_num_of_interfaces_mask;
         UINT_32 robustness_value;
         UINT_8 robustness_value_mask;
         char * dns_name;
         UINT_8 dns_name_mask;
    } SYSCONFG_ISATAP_Tunnel_params_STC;

    typedef struct 
    {
         UINT_32 config_watchdog_time_interval;
         UINT_8 config_watchdog_time_interval_mask;
         UINT_32 config_watchdog_counter_max;
         UINT_8 config_watchdog_counter_max_mask;
         UINT_32 stack_watchdog_keepalive_interval;
         UINT_8 stack_watchdog_keepalive_interval_mask;
         UINT_32 RX_Watchdog_timeout_value;
         UINT_8 RX_Watchdog_timeout_value_mask;
         BOOLEAN RX_Watchdog_is_enabled;
         UINT_8 RX_Watchdog_is_enabled_mask;
    } SYSCONFG_Config_Watchdog_params_STC;

    typedef struct 
    {
         BOOLEAN permitted_rules_counters_are_supported;
         UINT_8 permitted_rules_counters_are_supported_mask;
         UINT_32 retry_frequency;
         UINT_8 retry_frequency_mask;
         BOOLEAN ip_source_guard_is_enabled_by_default;
         UINT_8 ip_source_guard_is_enabled_by_default_mask;
    } SYSCONFG_IP_source_guard_params_STC;

    typedef enum 
    {
        SYSCONFG_port_lock_secure_address_type_dynamic_E = 1,
        SYSCONFG_port_lock_secure_address_type_static_E = 2,
        SYSCONFG_port_lock_secure_address_type_last_E = 3    
    } SYSCONFG_port_lock_secure_address_type_ENT;
    /* SYSCONFG_enum_id_port_lock_secure_address_type_E */

    typedef enum 
    {
        SYSCONFG_port_lock_secure_address_on_unlock_type_delete_E = 1,
        SYSCONFG_port_lock_secure_address_on_unlock_type_change_to_dynamic_E = 2,
        SYSCONFG_port_lock_secure_address_on_unlock_type_last_E = 3    
    } SYSCONFG_port_lock_secure_address_on_unlock_type_ENT;
    /* SYSCONFG_enum_id_port_lock_secure_address_on_unlock_type_E */

    typedef struct 
    {
         BOOLEAN lock_secure;
         UINT_8 lock_secure_mask;
         BOOLEAN secure_permanent;
         UINT_8 secure_permanent_mask;
         BOOLEAN max_addresses;
         UINT_8 max_addresses_mask;
         BOOLEAN secure_delete_on_reset;
         UINT_8 secure_delete_on_reset_mask;
         SYSCONFG_port_lock_limitation_mode_type_ENT default_limitation_mode;
         UINT_8 default_limitation_mode_mask;
    } SYSCONFG_limitation_modes_supported_params_STC;

    typedef enum 
    {
        SYSCONFG_loopback_detection_destination_mode_type_port_source_mac_address_E = 1,
        SYSCONFG_loopback_detection_destination_mode_type_base_mac_address_E = 2,
        SYSCONFG_loopback_detection_destination_mode_type_broadcast_mac_address_E = 4,
        SYSCONFG_loopback_detection_destination_mode_type_predefined_multicast_address_E = 8,
        SYSCONFG_loopback_detection_destination_mode_type_user_defined_address_E = 16,
        SYSCONFG_loopback_detection_destination_mode_type_last_E = 17    
    } SYSCONFG_loopback_detection_destination_mode_type_ENT;
    /* SYSCONFG_enum_id_loopback_detection_destination_mode_type_E */

    typedef struct 
    {
         UINT_16 six2four_maximum_number_of_interfaces;
         UINT_8 six2four_maximum_number_of_interfaces_mask;
    } SYSCONFG_Six2four_Tunnel_params_STC;

    typedef struct 
    {
         BOOLEAN admin_blocked;
         UINT_8 admin_blocked_mask;
         BOOLEAN port_default_enable;
         UINT_8 port_default_enable_mask;
         BOOLEAN default_enable;
         UINT_8 default_enable_mask;
    } SYSCONFG_Green_Energy_Detect_params_STC;

    typedef enum 
    {
        SYSCONFG_loopback_detection_source_mode_type_port_source_mac_address_E = 1,
        SYSCONFG_loopback_detection_source_mode_type_base_mac_address_E = 2,
        SYSCONFG_loopback_detection_source_mode_type_last_E = 3    
    } SYSCONFG_loopback_detection_source_mode_type_ENT;
    /* SYSCONFG_enum_id_loopback_detection_source_mode_type_E */

    typedef struct 
    {
         BOOLEAN posix_file_system_supported;
         UINT_8 posix_file_system_supported_mask;
         UINT_32 system_reserved_storage;
         UINT_8 system_reserved_storage_mask;
    } SYSCONFG_management_params_STC;

    typedef struct 
    {
         UINT_32 max_mtu;
         UINT_8 max_mtu_mask;
         UINT_32 min_mtu;
         UINT_8 min_mtu_mask;
         UINT_32 def_mtu;
         UINT_8 def_mtu_mask;
    } SYSCONFG_mtu_values_params_STC;

    typedef struct 
    {
         BOOLEAN arp_inspection_is_enabled_by_default;
         UINT_8 arp_inspection_is_enabled_by_default_mask;
         UINT_32 maximum_number_of_arp_inspection_lists;
         UINT_8 maximum_number_of_arp_inspection_lists_mask;
         BOOLEAN forward_arp_packets_that_not_found;
         UINT_8 forward_arp_packets_that_not_found_mask;
         UINT_32 log_interval;
         UINT_8 log_interval_mask;
         BOOLEAN statistics_are_supported;
         UINT_8 statistics_are_supported_mask;
         BOOLEAN packets_validation;
         UINT_8 packets_validation_mask;
    } SYSCONFG_ARP_inspection_params_STC;

    typedef enum 
    {
        SYSCONFG_Bridge_default_MC_vlan_mode_type_mac_E = 1,
        SYSCONFG_Bridge_default_MC_vlan_mode_type_ip_group_E = 2,
        SYSCONFG_Bridge_default_MC_vlan_mode_type_ip_source_group_E = 3,
        SYSCONFG_Bridge_default_MC_vlan_mode_type_last_E = 4    
    } SYSCONFG_Bridge_default_MC_vlan_mode_type_ENT;
    /* SYSCONFG_enum_id_Bridge_default_MC_vlan_mode_type_E */

    typedef struct 
    {
         BOOLEAN SSH_session_logging_enabled;
         UINT_8 SSH_session_logging_enabled_mask;
         char * version_string;
         UINT_8 version_string_mask;
         UINT_32 public_key_size;
         UINT_8 public_key_size_mask;
    } SYSCONFG_SSH_params_STC;

    typedef struct 
    {
         UINT_16 max_mac_addresses_max_num;
         UINT_8 max_mac_addresses_max_num_mask;
         UINT_16 max_mac_addresses_default_num;
         UINT_8 max_mac_addresses_default_num_mask;
    } SYSCONFG_limitation_mode_max_addresses_params_STC;

    typedef struct 
    {
         UINT_32 coa_max_num_of_multiple_sessions;
         UINT_8 coa_max_num_of_multiple_sessions_mask;
         UINT_16 coa_max_number_of_requests;
         UINT_8 coa_max_number_of_requests_mask;
         UINT_8 coa_max_number_of_clients;
         UINT_8 coa_max_number_of_clients_mask;
         BOOLEAN coa_vsa_disable_host_port_is_supported;
         UINT_8 coa_vsa_disable_host_port_is_supported_mask;
         BOOLEAN coa_vsa_reauthenticate_host_is_supported;
         UINT_8 coa_vsa_reauthenticate_host_is_supported_mask;
         UINT_16 coa_max_udp_port;
         UINT_8 coa_max_udp_port_mask;
         UINT_16 coa_udp_port;
         UINT_8 coa_udp_port_mask;
         BOOLEAN coa_vsa_change_user_privilege_level_is_supported;
         UINT_8 coa_vsa_change_user_privilege_level_is_supported_mask;
         BOOLEAN coa_attribute_event_timestamp_drop_packet_is_supported;
         UINT_8 coa_attribute_event_timestamp_drop_packet_is_supported_mask;
         BOOLEAN coa_disconnect_with_other_than_must_attribute_action_nak;
         UINT_8 coa_disconnect_with_other_than_must_attribute_action_nak_mask;
         BOOLEAN coa_vsa_bounce_host_port_is_supported;
         UINT_8 coa_vsa_bounce_host_port_is_supported_mask;
         BOOLEAN coa_multiple_sessions_is_supported;
         UINT_8 coa_multiple_sessions_is_supported_mask;
         BOOLEAN coa_ignore_command_is_supported;
         UINT_8 coa_ignore_command_is_supported_mask;
    } SYSCONFG_Radius_CoA_params_STC;

    #define SYSCONFG_CPU_QUEUE_ID_TYPE_MIN_VALUE_CNS 0
    #define SYSCONFG_CPU_QUEUE_ID_TYPE_MAX_VALUE_CNS 7
    typedef UINT_8 SYSCONFG_cpu_queue_id_type_TYP;

    typedef struct 
    {
         char * username;
         UINT_8 username_mask;
         char * script_args;
         UINT_8 script_args_mask;
         UINT_32 watchdog_time_interval_ms;
         UINT_8 watchdog_time_interval_ms_mask;
         char * script_path;
         UINT_8 script_path_mask;
         UINT_32 max_script_invocation_attempts;
         UINT_8 max_script_invocation_attempts_mask;
         UINT_32 max_script_invocation_time_ms;
         UINT_8 max_script_invocation_time_ms_mask;
    } SYSCONFG_MTPLAP_health_check_params_STC;

    #define SYSCONFG_CPU_PACKETS_WEIGHT_TYPE_MIN_VALUE_CNS 0
    #define SYSCONFG_CPU_PACKETS_WEIGHT_TYPE_MAX_VALUE_CNS 8
    typedef UINT_8 SYSCONFG_cpu_packets_weight_type_TYP;

    typedef struct 
    {
         UINT_32 threshold;
         UINT_8 threshold_mask;
         BOOLEAN admin_blocked;
         UINT_8 admin_blocked_mask;
         BOOLEAN port_default_enable;
         UINT_8 port_default_enable_mask;
         BOOLEAN default_enable;
         UINT_8 default_enable_mask;
    } SYSCONFG_Green_Short_Reach_params_STC;

    typedef struct 
    {
         UINT_32 flash_id;
         UINT_8 flash_id_mask;
    } SYSCONFG_Secure_Boot_params_STC;

    typedef struct 
    {
         BOOLEAN core_dump_enabled;
         UINT_8 core_dump_enabled_mask;
         RSG_ip_addr_TYP linux_ptp_ipv4_netmask;
         UINT_8 linux_ptp_ipv4_netmask_mask;
         UINT_16 linux_reserved_l4_ports_range_end;
         UINT_8 linux_reserved_l4_ports_range_end_mask;
         UINT_16 linux_http_web_port;
         UINT_8 linux_http_web_port_mask;
         UINT_16 linux_reserved_l4_ports_range_start;
         UINT_8 linux_reserved_l4_ports_range_start_mask;
         RSG_ip_addr_TYP linux_ptp_ipv4_address;
         UINT_8 linux_ptp_ipv4_address_mask;
         RSG_ip_addr_TYP mts_ptp_ipv4_netmask;
         UINT_8 mts_ptp_ipv4_netmask_mask;
         RSG_ip_addr_TYP mts_ptp_ipv4_address;
         UINT_8 mts_ptp_ipv4_address_mask;
         UINT_16 linux_https_web_port;
         UINT_8 linux_https_web_port_mask;
         BOOLEAN MTPLAP_health_check_feature_is_supported;
         UINT_8 MTPLAP_health_check_feature_is_supported_mask;
         char * active_pkey_file_name;
         UINT_8 active_pkey_file_name_mask;
         SYSCONFG_MTPLAP_health_check_params_STC MTPLAP_health_check;
         UINT_8 MTPLAP_health_check_mask;
         char * active_cert_file_name;
         UINT_8 active_cert_file_name_mask;
    } SYSCONFG_MTPLAP_params_STC;

    typedef struct 
    {
         BOOLEAN forward;
         UINT_8 forward_mask;
         BOOLEAN discard;
         UINT_8 discard_mask;
         SYSCONFG_port_lock_violation_action_type_ENT default_violation_action;
         UINT_8 default_violation_action_mask;
         BOOLEAN discard_shutdown;
         UINT_8 discard_shutdown_mask;
    } SYSCONFG_violation_actions_supported_params_STC;

    #define SYSCONFG_CPU_DMA_BUFFERS_TYPE_MIN_VALUE_CNS 1
    #define SYSCONFG_CPU_DMA_BUFFERS_TYPE_MAX_VALUE_CNS 512
    typedef UINT_16 SYSCONFG_cpu_dma_buffers_type_TYP;

    #define SYSCONFG_CPU_RATE_LIMIT_INDEX_TYPE_MIN_VALUE_CNS 1
    #define SYSCONFG_CPU_RATE_LIMIT_INDEX_TYPE_MAX_VALUE_CNS 31
    typedef UINT_8 SYSCONFG_cpu_rate_limit_index_type_TYP;

    typedef struct 
    {
         UINT_32 maximum_number_of_trust_qos_mappings;
         UINT_8 maximum_number_of_trust_qos_mappings_mask;
         UINT_32 maximum_number_of_egress_queues_scheduling_profiles;
         UINT_8 maximum_number_of_egress_queues_scheduling_profiles_mask;
         UINT_32 maximum_number_of_qos_profiles;
         UINT_8 maximum_number_of_qos_profiles_mask;
    } SYSCONFG_QOS_params_STC;

    typedef struct 
    {
         BOOLEAN mask_led_supported;
         UINT_8 mask_led_supported_mask;
         BOOLEAN ports_leds_power_saving_supported;
         UINT_8 ports_leds_power_saving_supported_mask;
    } SYSCONFG_Green_LED_params_STC;

    #define SYSCONFG_CPU_RATE_LIMIT_RATE_TYPE_MIN_VALUE_CNS 1
    #define SYSCONFG_CPU_RATE_LIMIT_RATE_TYPE_MAX_VALUE_CNS 2048
    typedef UINT_16 SYSCONFG_cpu_rate_limit_rate_type_TYP;

    typedef struct 
    {
         UINT_32 violation_traps_frequency_default;
         UINT_8 violation_traps_frequency_default_mask;
         BOOLEAN discard_shutdown_trap;
         UINT_8 discard_shutdown_trap_mask;
         BOOLEAN forward_trap;
         UINT_8 forward_trap_mask;
         BOOLEAN discard_trap;
         UINT_8 discard_trap_mask;
         BOOLEAN violation_traps_default_enabled;
         UINT_8 violation_traps_default_enabled_mask;
    } SYSCONFG_violation_traps_supported_params_STC;

    typedef struct 
    {
         BOOLEAN ipv6_supported;
         UINT_8 ipv6_supported_mask;
         BOOLEAN enabled_by_default;
         UINT_8 enabled_by_default_mask;
         char * redirect_url;
         UINT_8 redirect_url_mask;
    } SYSCONFG_FindIT_params_STC;

    typedef enum 
    {
        SYSCONFG_cpu_drop_precedence_type_green_E = 1,
        SYSCONFG_cpu_drop_precedence_type_yellow_E = 2,
        SYSCONFG_cpu_drop_precedence_type_last_E = 3    
    } SYSCONFG_cpu_drop_precedence_type_ENT;
    /* SYSCONFG_enum_id_cpu_drop_precedence_type_E */

    typedef enum 
    {
        SYSCONFG_cpu_traffic_flow_type_httpTome_E = 1,
        SYSCONFG_cpu_traffic_flow_type_sshTome_E = 2,
        SYSCONFG_cpu_traffic_flow_type_telnetTome_E = 3,
        SYSCONFG_cpu_traffic_flow_type_snmpTome_E = 4,
        SYSCONFG_cpu_traffic_flow_type_pvst_E = 5,
        SYSCONFG_cpu_traffic_flow_type_stp_E = 6,
        SYSCONFG_cpu_traffic_flow_type_udld_E = 7,
        SYSCONFG_cpu_traffic_flow_type_ieeeLacp_E = 8,
        SYSCONFG_cpu_traffic_flow_type_ieeeOther_E = 9,
        SYSCONFG_cpu_traffic_flow_type_cdp_E = 10,
        SYSCONFG_cpu_traffic_flow_type_ieee1x_E = 11,
        SYSCONFG_cpu_traffic_flow_type_dhcpSnooping_E = 12,
        SYSCONFG_cpu_traffic_flow_type_arpInspection_E = 13,
        SYSCONFG_cpu_traffic_flow_type_ipv6FhsNdp_E = 14,
        SYSCONFG_cpu_traffic_flow_type_ipv6FhsDhcpv6_E = 15,
        SYSCONFG_cpu_traffic_flow_type_ipv6FhsData_E = 16,
        SYSCONFG_cpu_traffic_flow_type_htttpWebAuth_E = 17,
        SYSCONFG_cpu_traffic_flow_type_ucIpTome_E = 18,
        SYSCONFG_cpu_traffic_flow_type_ucMacTome_E = 19,
        SYSCONFG_cpu_traffic_flow_type_ipv4UcUk_E = 20,
        SYSCONFG_cpu_traffic_flow_type_arpTome_E = 21,
        SYSCONFG_cpu_traffic_flow_type_arpBc_E = 22,
        SYSCONFG_cpu_traffic_flow_type_ipRoutPort_E = 23,
        SYSCONFG_cpu_traffic_flow_type_ipv4McTome_E = 24,
        SYSCONFG_cpu_traffic_flow_type_ipv6McTome_E = 25,
        SYSCONFG_cpu_traffic_flow_type_ipm2cpu_E = 26,
        SYSCONFG_cpu_traffic_flow_type_mldSnoopng_E = 27,
        SYSCONFG_cpu_traffic_flow_type_igmpSnooping_E = 28,
        SYSCONFG_cpu_traffic_flow_type_iscsiSnooping_E = 29,
        SYSCONFG_cpu_traffic_flow_type_sflow_E = 30,
        SYSCONFG_cpu_traffic_flow_type_ipHopbyhop_E = 31,
        SYSCONFG_cpu_traffic_flow_type_ipMtu_E = 32,
        SYSCONFG_cpu_traffic_flow_type_ipErr_E = 33,
        SYSCONFG_cpu_traffic_flow_type_l2ProtTunnel_E = 34,
        SYSCONFG_cpu_traffic_flow_type_aclLog_E = 35,
        SYSCONFG_cpu_traffic_flow_type_voip_E = 36,
        SYSCONFG_cpu_traffic_flow_type_other_E = 37,
        SYSCONFG_cpu_traffic_flow_type_bpe_E = 38,
        SYSCONFG_cpu_traffic_flow_type_ipv6Ndp_E = 39,
        SYSCONFG_cpu_traffic_flow_type_stackDiscovery_E = 40,
        SYSCONFG_cpu_traffic_flow_type_stackControl_E = 41,
        SYSCONFG_cpu_traffic_flow_type_last_E = 42    
    } SYSCONFG_cpu_traffic_flow_type_ENT;
    /* SYSCONFG_enum_id_cpu_traffic_flow_type_E */

    typedef enum 
    {
        SYSCONFG_led_display_mode_type_ports_blink_E = 1,
        SYSCONFG_led_display_mode_type_ports_solid_on_E = 2,
        SYSCONFG_led_display_mode_type_system_solid_on_E = 3,
        SYSCONFG_led_display_mode_type_last_E = 4    
    } SYSCONFG_led_display_mode_type_ENT;
    /* SYSCONFG_enum_id_led_display_mode_type_E */

    typedef struct 
    {
         SYSCONFG_port_lock_secure_address_on_unlock_type_ENT secure_address_on_unlock;
         UINT_8 secure_address_on_unlock_mask;
         SYSCONFG_port_lock_secure_address_type_ENT secure_address_type;
         UINT_8 secure_address_type_mask;
    } SYSCONFG_advanced_params_STC;

    typedef enum 
    {
        SYSCONFG_led_display_default_pattern_type_blink_all_E = 1,
        SYSCONFG_led_display_default_pattern_type_alternating_E = 2,
        SYSCONFG_led_display_default_pattern_type_system_solid_on_E = 3,
        SYSCONFG_led_display_default_pattern_type_last_E = 4    
    } SYSCONFG_led_display_default_pattern_type_ENT;
    /* SYSCONFG_enum_id_led_display_default_pattern_type_E */

    typedef struct 
    {
         BOOLEAN ipv6_supported;
         UINT_8 ipv6_supported_mask;
         BOOLEAN enabled_by_default;
         UINT_8 enabled_by_default_mask;
         char * redirect_url;
         UINT_8 redirect_url_mask;
    } SYSCONFG_Cloud_Manager_params_STC;

    typedef struct 
    {
         UINT_32 stability_check_min_window_duration_msec;
         UINT_8 stability_check_min_window_duration_msec_mask;
         UINT_32 failure_tolerance;
         UINT_8 failure_tolerance_mask;
         BOOLEAN high_speeds;
         UINT_8 high_speeds_mask;
         BOOLEAN high_speed_with_multi_lanes_options;
         UINT_8 high_speed_with_multi_lanes_options_mask;
         UINT_32 stability_check_max_duration_msec;
         UINT_8 stability_check_max_duration_msec_mask;
         UINT_32 stability_check_num_of_samples_in_window;
         UINT_8 stability_check_num_of_samples_in_window_mask;
         BOOLEAN polling_mode;
         UINT_8 polling_mode_mask;
         UINT_32 polling_interval_duration_msec;
         UINT_8 polling_interval_duration_msec_mask;
    } SYSCONFG_Port_Manager_params_STC;

    typedef enum 
    {
        SYSCONFG_port_led_mode_type_ports_blink_only_E = 1,
        SYSCONFG_port_led_mode_type_ports_solid_on_only_E = 2,
        SYSCONFG_port_led_mode_type_ports_blink_or_solid_on_E = 3,
        SYSCONFG_port_led_mode_type_last_E = 4    
    } SYSCONFG_port_led_mode_type_ENT;
    /* SYSCONFG_enum_id_port_led_mode_type_E */

    typedef enum 
    {
        SYSCONFG_udld_port_mode_type_normal_E = 1,
        SYSCONFG_udld_port_mode_type_aggressive_E = 2,
        SYSCONFG_udld_port_mode_type_disable_E = 3,
        SYSCONFG_udld_port_mode_type_last_E = 4    
    } SYSCONFG_udld_port_mode_type_ENT;
    /* SYSCONFG_enum_id_udld_port_mode_type_E */

    #define SYSCONFG_VLAN_TAG_TYPE_MIN_VALUE_CNS 1
    #define SYSCONFG_VLAN_TAG_TYPE_MAX_VALUE_CNS 4094
    typedef UINT_16 SYSCONFG_vlan_tag_type_TYP;

    typedef enum 
    {
        SYSCONFG_vlan_acceptable_frame_type_all_E = 1,
        SYSCONFG_vlan_acceptable_frame_type_tagged_only_E = 2,
        SYSCONFG_vlan_acceptable_frame_type_untagged_only_E = 3,
        SYSCONFG_vlan_acceptable_frame_type_last_E = 4    
    } SYSCONFG_vlan_acceptable_frame_type_ENT;
    /* SYSCONFG_enum_id_vlan_acceptable_frame_type_E */

    typedef struct 
    {
         UINT_32 default_ap_traps_frequency;
         UINT_8 default_ap_traps_frequency_mask;
         BOOLEAN high_speed_with_multi_lanes_options;
         UINT_8 high_speed_with_multi_lanes_options_mask;
    } SYSCONFG_Ap_params_STC;

    typedef enum 
    {
        SYSCONFG_vlan_human_type_ifIndex_E = 1,
        SYSCONFG_vlan_human_type_tag_E = 2,
        SYSCONFG_vlan_human_type_name_E = 3,
        SYSCONFG_vlan_human_type_last_E = 4    
    } SYSCONFG_vlan_human_type_ENT;
    /* SYSCONFG_enum_id_vlan_human_type_E */

    typedef struct 
    {
         SYSCONFG_limitation_mode_max_addresses_params_STC limitation_mode_max_addresses;
         UINT_8 limitation_mode_max_addresses_mask;
         SYSCONFG_limitation_modes_supported_params_STC limitation_modes_supported;
         UINT_8 limitation_modes_supported_mask;
         SYSCONFG_violation_traps_supported_params_STC violation_traps_supported;
         UINT_8 violation_traps_supported_mask;
         SYSCONFG_advanced_params_STC advanced;
         UINT_8 advanced_mask;
         SYSCONFG_violation_actions_supported_params_STC violation_actions_supported;
         UINT_8 violation_actions_supported_mask;
    } SYSCONFG_Port_Lock_params_STC;

    typedef enum 
    {
        SYSCONFG_vlan_port_model_type_IS_E = 1,
        SYSCONFG_vlan_port_model_type_MTS_E = 2,
        SYSCONFG_vlan_port_model_type_last_E = 3    
    } SYSCONFG_vlan_port_model_type_ENT;
    /* SYSCONFG_enum_id_vlan_port_model_type_E */

    typedef enum 
    {
        SYSCONFG_vlan_default_port_mode_type_general_E = 1,
        SYSCONFG_vlan_default_port_mode_type_access_E = 2,
        SYSCONFG_vlan_default_port_mode_type_trunk_E = 3,
        SYSCONFG_vlan_default_port_mode_type_IS_general_E = 10,
        SYSCONFG_vlan_default_port_mode_type_IS_access_E = 11,
        SYSCONFG_vlan_default_port_mode_type_IS_trunk_E = 12,
        SYSCONFG_vlan_default_port_mode_type_last_E = 13    
    } SYSCONFG_vlan_default_port_mode_type_ENT;
    /* SYSCONFG_enum_id_vlan_default_port_mode_type_E */

    typedef enum 
    {
        SYSCONFG_vlan_switchport_mode_type_L2_E = 1,
        SYSCONFG_vlan_switchport_mode_type_L3_E = 2,
        SYSCONFG_vlan_switchport_mode_type_last_E = 3    
    } SYSCONFG_vlan_switchport_mode_type_ENT;
    /* SYSCONFG_enum_id_vlan_switchport_mode_type_E */

    typedef enum 
    {
        SYSCONFG_vlan_default_trunk_port_mode_membership_type_all_E = 1,
        SYSCONFG_vlan_default_trunk_port_mode_membership_type_default_vlan_E = 2,
        SYSCONFG_vlan_default_trunk_port_mode_membership_type_last_E = 3    
    } SYSCONFG_vlan_default_trunk_port_mode_membership_type_ENT;
    /* SYSCONFG_enum_id_vlan_default_trunk_port_mode_membership_type_E */

    typedef struct 
    {
         BOOLEAN multicast_enabled_by_default;
         UINT_8 multicast_enabled_by_default_mask;
         RSG_ipv6_addr_TYP ipm_fdb_ipv6_sip_mask;
         UINT_8 ipm_fdb_ipv6_sip_mask_mask;
         SYSCONFG_Bridge_default_MC_vlan_mode_type_ENT default_multicast_admin_vlan_mode;
         UINT_8 default_multicast_admin_vlan_mode_mask;
         SYSCONFG_Bridge_default_MC_vlan_mode_type_ENT default_multicast_oper_vlan_mode;
         UINT_8 default_multicast_oper_vlan_mode_mask;
         UINT_32 max_num_multicast_mac_entries;
         UINT_8 max_num_multicast_mac_entries_mask;
         RSG_ipv6_addr_TYP ipm_fdb_ipv6_dip_mask;
         UINT_8 ipm_fdb_ipv6_dip_mask_mask;
         BOOLEAN igmp_snoop_qr_global_address_supported;
         UINT_8 igmp_snoop_qr_global_address_supported_mask;
    } SYSCONFG_Bridge_MC_params_STC;

    typedef struct 
    {
         UINT_32 lpm_memory_size;
         UINT_8 lpm_memory_size_mask;
         BOOLEAN ECMP_is_supported;
         UINT_8 ECMP_is_supported_mask;
         UINT_32 max_num_of_ecmp_entries;
         UINT_8 max_num_of_ecmp_entries_mask;
    } SYSCONFG_Inet_common_parameters_params_STC;

    typedef enum 
    {
        SYSCONFG_vlan_voice_cos_mode_type_src_E = 1,
        SYSCONFG_vlan_voice_cos_mode_type_all_E = 2,
        SYSCONFG_vlan_voice_cos_mode_type_last_E = 3    
    } SYSCONFG_vlan_voice_cos_mode_type_ENT;
    /* SYSCONFG_enum_id_vlan_voice_cos_mode_type_E */

    typedef UINT_32 SYSCONFG_vlan_private_supported_applications_bits_type_TYP;
#define SYSCONFG_VLAN_PRIVATE_SUPPORTED_APPLICATIONS_BITS_TYPE_IP_SOURCE_GUARD_CNS (1 << 3)
    #define SYSCONFG_VLAN_PRIVATE_SUPPORTED_APPLICATIONS_BITS_TYPE_ARP_INSPECTION_CNS (1 << 2)
    #define SYSCONFG_VLAN_PRIVATE_SUPPORTED_APPLICATIONS_BITS_TYPE_DHCP_SNOOPING_CNS (1 << 1)
    #define SYSCONFG_VLAN_PRIVATE_SUPPORTED_APPLICATIONS_BITS_TYPE_IGMP_SNOOPING_CNS (1 << 0)

    typedef enum 
    {
        SYSCONFG_vlan_voice_admin_state_type_disabled_E = 1,
        SYSCONFG_vlan_voice_admin_state_type_auto_enabled_E = 2,
        SYSCONFG_vlan_voice_admin_state_type_auto_triggered_E = 3,
        SYSCONFG_vlan_voice_admin_state_type_oui_enabled_E = 4,
        SYSCONFG_vlan_voice_admin_state_type_last_E = 5    
    } SYSCONFG_vlan_voice_admin_state_type_ENT;
    /* SYSCONFG_enum_id_vlan_voice_admin_state_type_E */

    typedef struct 
    {
         UINT_32 IPM_FFT_max_num_mll;
         UINT_8 IPM_FFT_max_num_mll_mask;
         BOOLEAN validate_igmp_report_src_addr;
         UINT_8 validate_igmp_report_src_addr_mask;
         UINT_32 IPM_FFT_dflt_num_of_ipv4_route_entries;
         UINT_8 IPM_FFT_dflt_num_of_ipv4_route_entries_mask;
         BOOLEAN pim_ipv6_supported;
         UINT_8 pim_ipv6_supported_mask;
         UINT_32 IPM_FFT_dflt_num_of_ipv6_route_entries;
         UINT_8 IPM_FFT_dflt_num_of_ipv6_route_entries_mask;
         BOOLEAN IPM_FFT_on_trunk_is_supported;
         UINT_8 IPM_FFT_on_trunk_is_supported_mask;
         BOOLEAN mld_proxy_supported;
         UINT_8 mld_proxy_supported_mask;
         UINT_32 max_num_igmp_proxy_src_addr;
         UINT_8 max_num_igmp_proxy_src_addr_mask;
         UINT_32 IPM_FFT_max_num_of_encaps_tunnels;
         UINT_8 IPM_FFT_max_num_of_encaps_tunnels_mask;
         UINT_32 IPM_FFT_max_num_oifs_of_decaps_iif_groups;
         UINT_8 IPM_FFT_max_num_oifs_of_decaps_iif_groups_mask;
    } SYSCONFG_IPM_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_vidx_entries;
         UINT_8 maximum_number_of_vidx_entries_mask;
    } SYSCONFG_Vidx_params_STC;

    typedef enum 
    {
        SYSCONFG_vrrp_version_type_version_2_and_3_E = 1,
        SYSCONFG_vrrp_version_type_version_2_E = 2,
        SYSCONFG_vrrp_version_type_version_3_E = 3,
        SYSCONFG_vrrp_version_type_last_E = 4    
    } SYSCONFG_vrrp_version_type_ENT;
    /* SYSCONFG_enum_id_vrrp_version_type_E */

    typedef enum 
    {
        SYSCONFG_voip_cos_mode_queue_E = 1,
        SYSCONFG_voip_cos_mode_vpt_E = 2,
        SYSCONFG_voip_cos_mode_dscp_E = 3,
        SYSCONFG_voip_cos_mode_last_E = 4    
    } SYSCONFG_voip_cos_mode_ENT;
    /* SYSCONFG_enum_id_voip_cos_mode_E */

    typedef enum 
    {
        SYSCONFG_auto_neg_role_master_E = 1,
        SYSCONFG_auto_neg_role_slave_E = 2,
        SYSCONFG_auto_neg_role_last_E = 3    
    } SYSCONFG_auto_neg_role_ENT;
    /* SYSCONFG_enum_id_auto_neg_role_E */

    typedef struct 
    {
         BOOLEAN icmp_redirect_enabled_by_default;
         UINT_8 icmp_redirect_enabled_by_default_mask;
         SYSCONFG_mtu_values_params_STC mtu_values;
         UINT_8 mtu_values_mask;
         BOOLEAN uc_forwarding_enabled_by_default;
         UINT_8 uc_forwarding_enabled_by_default_mask;
         UINT_32 max_num_of_static_routes;
         UINT_8 max_num_of_static_routes_mask;
         BOOLEAN mc_forwarding_enabled_by_default;
         UINT_8 mc_forwarding_enabled_by_default_mask;
         UINT_32 oob_dhcp_default_route_metric;
         UINT_8 oob_dhcp_default_route_metric_mask;
         UINT_32 inband_dhcp_default_route_metric;
         UINT_8 inband_dhcp_default_route_metric_mask;
         UINT_32 inband_default_static_route_metric;
         UINT_8 inband_default_static_route_metric_mask;
         UINT_32 oob_default_static_route_metric;
         UINT_8 oob_default_static_route_metric_mask;
         BOOLEAN static_route_tracking_is_supported;
         UINT_8 static_route_tracking_is_supported_mask;
         BOOLEAN mtu_configuration_supported;
         UINT_8 mtu_configuration_supported_mask;
    } SYSCONFG_IPv4_stack_params_STC;

    typedef enum 
    {
        SYSCONFG_lldp_port_id_format_type_port_id_format_macAddress_E = 3,
        SYSCONFG_lldp_port_id_format_type_port_id_format_ifName_E = 5,
        SYSCONFG_lldp_port_id_format_type_port_id_format_local_E = 7,
        SYSCONFG_lldp_port_id_format_type_last_E = 8    
    } SYSCONFG_lldp_port_id_format_type_ENT;
    /* SYSCONFG_enum_id_lldp_port_id_format_type_E */

    typedef UINT_32 SYSCONFG_optional_tlvs_tx_default_enabled_bits_type_TYP;
#define SYSCONFG_OPTIONAL_TLVS_TX_DEFAULT_ENABLED_BITS_TYPE_PORT_DESC_CNS (1 << 0)
    #define SYSCONFG_OPTIONAL_TLVS_TX_DEFAULT_ENABLED_BITS_TYPE_SYS_NAME_CNS (1 << 1)
    #define SYSCONFG_OPTIONAL_TLVS_TX_DEFAULT_ENABLED_BITS_TYPE_SYS_DESC_CNS (1 << 2)
    #define SYSCONFG_OPTIONAL_TLVS_TX_DEFAULT_ENABLED_BITS_TYPE_SYS_CAP_CNS (1 << 3)

    typedef enum 
    {
        SYSCONFG_lldp_advertise_ma_selection_manner_type_none_E = 0,
        SYSCONFG_lldp_advertise_ma_selection_manner_type_auto_E = 1,
        SYSCONFG_lldp_advertise_ma_selection_manner_type_last_E = 2    
    } SYSCONFG_lldp_advertise_ma_selection_manner_type_ENT;
    /* SYSCONFG_enum_id_lldp_advertise_ma_selection_manner_type_E */

    typedef struct 
    {
         UINT_16 ospf_maximum_number_of_areas;
         UINT_8 ospf_maximum_number_of_areas_mask;
         UINT_16 ospf_maximum_number_of_interfaces;
         UINT_8 ospf_maximum_number_of_interfaces_mask;
         UINT_8 ospf_maximum_number_of_processes;
         UINT_8 ospf_maximum_number_of_processes_mask;
    } SYSCONFG_OSPF_params_STC;

    typedef UINT_32 SYSCONFG_supported_speeds_bits_type_TYP;
#define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__10M_CNS (1 << 0)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__100M_CNS (1 << 1)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__1G_CNS (1 << 2)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__2500M_CNS (1 << 3)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__5G_CNS (1 << 4)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__10G_CNS (1 << 5)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__20G_CNS (1 << 6)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__40G_CNS (1 << 7)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__100G_CNS (1 << 8)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__25G_CNS (1 << 9)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__50G_CNS (1 << 10)
    #define SYSCONFG_SUPPORTED_SPEEDS_BITS_TYPE__200G_CNS (1 << 11)

    typedef enum 
    {
        SYSCONFG_sampling_resolution_type_seconds_E = 1,
        SYSCONFG_sampling_resolution_type_minutes_E = 2,
        SYSCONFG_sampling_resolution_type_hours_E = 3,
        SYSCONFG_sampling_resolution_type_days_E = 4,
        SYSCONFG_sampling_resolution_type_weeks_E = 5,
        SYSCONFG_sampling_resolution_type_last_E = 6    
    } SYSCONFG_sampling_resolution_type_ENT;
    /* SYSCONFG_enum_id_sampling_resolution_type_E */

    typedef enum 
    {
        SYSCONFG_public_key_auto_generation_algorithm_none_E = 100,
        SYSCONFG_public_key_auto_generation_algorithm_rsa_E = 1,
        SYSCONFG_public_key_auto_generation_algorithm_dsa_E = 2,
        SYSCONFG_public_key_auto_generation_algorithm_ec_E = 4,
        SYSCONFG_public_key_auto_generation_algorithm_all_E = 99,
        SYSCONFG_public_key_auto_generation_algorithm_last_E = 100    
    } SYSCONFG_public_key_auto_generation_algorithm_ENT;
    /* SYSCONFG_enum_id_public_key_auto_generation_algorithm_E */

    typedef struct 
    {
         UINT_8 ospfv3_maximum_number_of_processes;
         UINT_8 ospfv3_maximum_number_of_processes_mask;
         UINT_16 ospfv3_maximum_number_of_interfaces;
         UINT_8 ospfv3_maximum_number_of_interfaces_mask;
         UINT_16 ospfv3_maximum_number_of_areas;
         UINT_8 ospfv3_maximum_number_of_areas_mask;
    } SYSCONFG_OSPFv3_params_STC;

    typedef enum 
    {
        SYSCONFG_scp_default_authentication_method_public_key_rsa_E = 1,
        SYSCONFG_scp_default_authentication_method_public_key_dsa_E = 2,
        SYSCONFG_scp_default_authentication_method_password_E = 3,
        SYSCONFG_scp_default_authentication_method_last_E = 4    
    } SYSCONFG_scp_default_authentication_method_ENT;
    /* SYSCONFG_enum_id_scp_default_authentication_method_E */

    typedef enum 
    {
        SYSCONFG_copy_different_SKU_directive_type_all_permitted_E = 0,
        SYSCONFG_copy_different_SKU_directive_type_exact_permitted_E = 1,
        SYSCONFG_copy_different_SKU_directive_type_last_E = 2    
    } SYSCONFG_copy_different_SKU_directive_type_ENT;
    /* SYSCONFG_enum_id_copy_different_SKU_directive_type_E */

    typedef struct 
    {
         SYSCONFG_vrrp_version_type_ENT vrrp_supported_version;
         UINT_8 vrrp_supported_version_mask;
         UINT_16 maximum_number_of_vrrp_routers;
         UINT_8 maximum_number_of_vrrp_routers_mask;
         SYSCONFG_vrrp_version_type_ENT vrrp_default_version;
         UINT_8 vrrp_default_version_mask;
         BOOLEAN vrrp_tracking_is_supported;
         UINT_8 vrrp_tracking_is_supported_mask;
    } SYSCONFG_Vrrp_params_STC;

    typedef struct 
    {
         SYSCONFG_public_key_auto_generation_algorithm_ENT public_key_auto_generation;
         UINT_8 public_key_auto_generation_mask;
         BOOLEAN enabled_by_default;
         UINT_8 enabled_by_default_mask;
         UINT_32 max_num_of_clients_public_keys;
         UINT_8 max_num_of_clients_public_keys_mask;
    } SYSCONFG_SSH_Server_params_STC;

    typedef enum 
    {
        SYSCONFG_copy_default_directive_access_type_exclude_E = 0,
        SYSCONFG_copy_default_directive_access_type_encrypted_E = 1,
        SYSCONFG_copy_default_directive_access_type_plaintext_E = 2,
        SYSCONFG_copy_default_directive_access_type_last_E = 3    
    } SYSCONFG_copy_default_directive_access_type_ENT;
    /* SYSCONFG_enum_id_copy_default_directive_access_type_E */

    typedef enum 
    {
        SYSCONFG_cdp_advertised_version_type_version1_E = 1,
        SYSCONFG_cdp_advertised_version_type_version2_E = 2,
        SYSCONFG_cdp_advertised_version_type_last_E = 3    
    } SYSCONFG_cdp_advertised_version_type_ENT;
    /* SYSCONFG_enum_id_cdp_advertised_version_type_E */

    typedef enum 
    {
        SYSCONFG_cdp_default_device_id_format_type_serial_number_E = 1,
        SYSCONFG_cdp_default_device_id_format_type_mac_address_E = 2,
        SYSCONFG_cdp_default_device_id_format_type_other_E = 3,
        SYSCONFG_cdp_default_device_id_format_type_last_E = 4    
    } SYSCONFG_cdp_default_device_id_format_type_ENT;
    /* SYSCONFG_enum_id_cdp_default_device_id_format_type_E */

    typedef struct 
    {
         BOOLEAN local_image_supported;
         UINT_8 local_image_supported_mask;
         BOOLEAN log_image_change_is_supported;
         UINT_8 log_image_change_is_supported_mask;
    } SYSCONFG_Images_params_STC;

    typedef struct 
    {
         SYSCONFG_public_key_auto_generation_algorithm_ENT public_key_auto_generation;
         UINT_8 public_key_auto_generation_mask;
         SYSCONFG_scp_default_authentication_method_ENT default_authentication_method;
         UINT_8 default_authentication_method_mask;
    } SYSCONFG_SCP_params_STC;

    typedef struct 
    {
         BOOLEAN is_all_ifs_enabled;
         UINT_8 is_all_ifs_enabled_mask;
         UINT_32 max_num_rtp_sessions;
         UINT_8 max_num_rtp_sessions_mask;
         BOOLEAN is_sccp_supported;
         UINT_8 is_sccp_supported_mask;
         UINT_32 cos_value;
         UINT_8 cos_value_mask;
         SYSCONFG_voip_cos_mode_ENT cos_mode;
         UINT_8 cos_mode_mask;
         BOOLEAN is_enabled;
         UINT_8 is_enabled_mask;
         BOOLEAN is_h323_supported;
         UINT_8 is_h323_supported_mask;
         BOOLEAN is_sip_supported;
         UINT_8 is_sip_supported_mask;
    } SYSCONFG_Voip_params_STC;

    typedef enum 
    {
        SYSCONFG_poe_communication_mode_communication_mode_blocking_E = 0,
        SYSCONFG_poe_communication_mode_communication_mode_non_blocking_E = 1,
        SYSCONFG_poe_communication_mode_last_E = 2    
    } SYSCONFG_poe_communication_mode_ENT;
    /* SYSCONFG_enum_id_poe_communication_mode_E */

    typedef enum 
    {
        SYSCONFG_poe_disconnect_method_lowest_priority_port_disconnect_E = 1,
        SYSCONFG_poe_disconnect_method_next_port_disconnect_E = 2,
        SYSCONFG_poe_disconnect_method_last_E = 3    
    } SYSCONFG_poe_disconnect_method_ENT;
    /* SYSCONFG_enum_id_poe_disconnect_method_E */

    typedef enum 
    {
        SYSCONFG_poe_emergency_support_mode_emergency_support_hardware_E = 0,
        SYSCONFG_poe_emergency_support_mode_emergency_support_software_E = 1,
        SYSCONFG_poe_emergency_support_mode_emergency_support_static_E = 2,
        SYSCONFG_poe_emergency_support_mode_last_E = 3    
    } SYSCONFG_poe_emergency_support_mode_ENT;
    /* SYSCONFG_enum_id_poe_emergency_support_mode_E */

    typedef struct 
    {
         BOOLEAN show_per_interface_command;
         UINT_8 show_per_interface_command_mask;
         BOOLEAN show_tech_support_chassis_supported;
         UINT_8 show_tech_support_chassis_supported_mask;
         BOOLEAN stop_on_macro_failure;
         UINT_8 stop_on_macro_failure_mask;
    } SYSCONFG_LCLI_params_STC;

    typedef struct 
    {
         UINT_32 arp_host_default_timeout_in_seconds;
         UINT_8 arp_host_default_timeout_in_seconds_mask;
         UINT_16 arp_request_rate_limiter_bucket_size;
         UINT_8 arp_request_rate_limiter_bucket_size_mask;
         UINT_32 arp_maximum_timeout_in_seconds;
         UINT_8 arp_maximum_timeout_in_seconds_mask;
         UINT_32 arp_router_default_timeout_in_seconds;
         UINT_8 arp_router_default_timeout_in_seconds_mask;
         UINT_16 arp_request_rate_limiter_bucket_refill;
         UINT_8 arp_request_rate_limiter_bucket_refill_mask;
         UINT_16 arp_minimum_timeout_in_seconds;
         UINT_8 arp_minimum_timeout_in_seconds_mask;
         UINT_32 arp_default_timeout_in_seconds;
         UINT_8 arp_default_timeout_in_seconds_mask;
    } SYSCONFG_Arp_params_STC;

    typedef enum 
    {
        SYSCONFG_poe_port_max_limit_supported_poe_port_max_limit_supported_E = 0,
        SYSCONFG_poe_port_max_limit_supported_poe_port_max_limit_not_supported_E = 1,
        SYSCONFG_poe_port_max_limit_supported_last_E = 2    
    } SYSCONFG_poe_port_max_limit_supported_ENT;
    /* SYSCONFG_enum_id_poe_port_max_limit_supported_E */

    typedef struct 
    {
         UINT_32 maximum_object_number;
         UINT_8 maximum_object_number_mask;
         BOOLEAN nexthop_keyword_is_supported;
         UINT_8 nexthop_keyword_is_supported_mask;
         UINT_32 frequency_range_from;
         UINT_8 frequency_range_from_mask;
         BOOLEAN host_unreachable_error_is_supported;
         UINT_8 host_unreachable_error_is_supported_mask;
         UINT_32 delay_range_from;
         UINT_8 delay_range_from_mask;
         UINT_32 delay_range_to;
         UINT_8 delay_range_to_mask;
         UINT_32 maximum_operations_number;
         UINT_8 maximum_operations_number_mask;
         UINT_32 frequency_range_to;
         UINT_8 frequency_range_to_mask;
         UINT_32 frequency_default;
         UINT_8 frequency_default_mask;
         UINT_32 timeout_range_to;
         UINT_8 timeout_range_to_mask;
         UINT_32 timeout_default;
         UINT_8 timeout_default_mask;
         UINT_32 timeout_range_from;
         UINT_8 timeout_range_from_mask;
    } SYSCONFG_SLA_params_STC;

    typedef enum 
    {
        SYSCONFG_poe_port_limit_mode_port_limit_E = 0,
        SYSCONFG_poe_port_limit_mode_class_limit_E = 5,
        SYSCONFG_poe_port_limit_mode_max_limit_E = 6,
        SYSCONFG_poe_port_limit_mode_last_E = 7    
    } SYSCONFG_poe_port_limit_mode_ENT;
    /* SYSCONFG_enum_id_poe_port_limit_mode_E */

    typedef struct 
    {
         UINT_8 number_of_agents;
         UINT_8 number_of_agents_mask;
    } SYSCONFG_RCLI_params_STC;

    typedef enum 
    {
        SYSCONFG_poe_ps_rps_mode_poe_ps_only_E = 0,
        SYSCONFG_poe_ps_rps_mode_poe_ps_and_rps_E = 1,
        SYSCONFG_poe_ps_rps_mode_poe_max_ps_rps_E = 2,
        SYSCONFG_poe_ps_rps_mode_poe_min_ps_rps_E = 3,
        SYSCONFG_poe_ps_rps_mode_last_E = 4    
    } SYSCONFG_poe_ps_rps_mode_ENT;
    /* SYSCONFG_enum_id_poe_ps_rps_mode_E */

    typedef enum 
    {
        SYSCONFG_poe_tbp_port_status_default_action_mode_poe_tbp_port_status_default_action_up_E = 1,
        SYSCONFG_poe_tbp_port_status_default_action_mode_poe_tbp_port_status_default_action_down_E = 2,
        SYSCONFG_poe_tbp_port_status_default_action_mode_last_E = 3    
    } SYSCONFG_poe_tbp_port_status_default_action_mode_ENT;
    /* SYSCONFG_enum_id_poe_tbp_port_status_default_action_mode_E */

    typedef enum 
    {
        SYSCONFG_poe_power_management_default_mode_dynamic_E = 1,
        SYSCONFG_poe_power_management_default_mode_static_E = 2,
        SYSCONFG_poe_power_management_default_mode_last_E = 3    
    } SYSCONFG_poe_power_management_default_mode_ENT;
    /* SYSCONFG_enum_id_poe_power_management_default_mode_E */

    typedef enum 
    {
        SYSCONFG_poe_guard_band_mode_not_supported_E = 0,
        SYSCONFG_poe_guard_band_mode_dynamic_E = 1,
        SYSCONFG_poe_guard_band_mode_static_E = 2,
        SYSCONFG_poe_guard_band_mode_last_E = 3    
    } SYSCONFG_poe_guard_band_mode_ENT;
    /* SYSCONFG_enum_id_poe_guard_band_mode_E */

    typedef enum 
    {
        SYSCONFG_poe_error_handling_mode_type_fatal_error_E = 0,
        SYSCONFG_poe_error_handling_mode_type_disable_poe_system_E = 1,
        SYSCONFG_poe_error_handling_mode_type_disable_poe_port_E = 2,
        SYSCONFG_poe_error_handling_mode_type_last_E = 3    
    } SYSCONFG_poe_error_handling_mode_type_ENT;
    /* SYSCONFG_enum_id_poe_error_handling_mode_type_E */

    typedef enum 
    {
        SYSCONFG_poe_lldp_tx_pattern_type_regular_noPattern_E = 0,
        SYSCONFG_poe_lldp_tx_pattern_type_pattern_4bt_1at_E = 1,
        SYSCONFG_poe_lldp_tx_pattern_type_last_E = 2    
    } SYSCONFG_poe_lldp_tx_pattern_type_ENT;
    /* SYSCONFG_enum_id_poe_lldp_tx_pattern_type_E */

    typedef enum 
    {
        SYSCONFG_default_pk_algorithm_type_rsa_E = 0,
        SYSCONFG_default_pk_algorithm_type_ec_E = 1,
        SYSCONFG_default_pk_algorithm_type_last_E = 2    
    } SYSCONFG_default_pk_algorithm_type_ENT;
    /* SYSCONFG_enum_id_default_pk_algorithm_type_E */

    typedef UINT_32 SYSCONFG_aaa_hashing_algorithm_supported_bits_type_TYP;
#define SYSCONFG_AAA_HASHING_ALGORITHM_SUPPORTED_BITS_TYPE_SHA1_CNS (1 << 1)
    #define SYSCONFG_AAA_HASHING_ALGORITHM_SUPPORTED_BITS_TYPE_SHA512_CNS (1 << 2)

    typedef enum 
    {
        SYSCONFG_aaa_default_encoding_algorithm_type_hex_E = 0,
        SYSCONFG_aaa_default_encoding_algorithm_type_base64_E = 1,
        SYSCONFG_aaa_default_encoding_algorithm_type_last_E = 2    
    } SYSCONFG_aaa_default_encoding_algorithm_type_ENT;
    /* SYSCONFG_enum_id_aaa_default_encoding_algorithm_type_E */

    typedef enum 
    {
        SYSCONFG_aaa_hashing_algorithm_type_sha1_E = 1,
        SYSCONFG_aaa_hashing_algorithm_type_sha512_E = 2,
        SYSCONFG_aaa_hashing_algorithm_type_last_E = 3    
    } SYSCONFG_aaa_hashing_algorithm_type_ENT;
    /* SYSCONFG_enum_id_aaa_hashing_algorithm_type_E */

    typedef struct 
    {
         SYSCONFG_vlan_tag_type_TYP default_vlan_vlan_id;
         UINT_8 default_vlan_vlan_id_mask;
         BOOLEAN default_vlan_membership_management_is_supported;
         UINT_8 default_vlan_membership_management_is_supported_mask;
         BOOLEAN default_vlan_port_tagging_is_supported;
         UINT_8 default_vlan_port_tagging_is_supported_mask;
    } SYSCONFG_Vlan_Default_Vlan_params_STC;

    typedef enum 
    {
        SYSCONFG_aaa_hashing_method_type_sha1_E = 1,
        SYSCONFG_aaa_hashing_method_type_sha512_E = 2,
        SYSCONFG_aaa_hashing_method_type_superhash_E = 3,
        SYSCONFG_aaa_hashing_method_type_last_E = 4    
    } SYSCONFG_aaa_hashing_method_type_ENT;
    /* SYSCONFG_enum_id_aaa_hashing_method_type_E */

    typedef UINT_32 SYSCONFG_stack_enabled_supported_speed_type_TYP;
#define SYSCONFG_STACK_ENABLED_SUPPORTED_SPEED_TYPE__1G_CNS (1 << 0)
    #define SYSCONFG_STACK_ENABLED_SUPPORTED_SPEED_TYPE__10G_CNS (1 << 1)

    typedef struct 
    {
         BOOLEAN voice_vlan_default_oui_is_enabled;
         UINT_8 voice_vlan_default_oui_is_enabled_mask;
         SYSCONFG_vlan_tag_type_TYP voice_vlan_default_vlan_id;
         UINT_8 voice_vlan_default_vlan_id_mask;
         SYSCONFG_vlan_voice_admin_state_type_ENT voice_vlan_default_admin_state;
         UINT_8 voice_vlan_default_admin_state_mask;
         BOOLEAN voice_vlan_with_cos_is_supported;
         UINT_8 voice_vlan_with_cos_is_supported_mask;
         BOOLEAN voice_vlan_cos_mode_is_supported;
         UINT_8 voice_vlan_cos_mode_is_supported_mask;
         UINT_16 voice_vlan_maximum_number_of_oui_entries;
         UINT_8 voice_vlan_maximum_number_of_oui_entries_mask;
         SYSCONFG_vlan_voice_cos_mode_type_ENT voice_vlan_default_cos_mode;
         UINT_8 voice_vlan_default_cos_mode_mask;
         BOOLEAN voice_vlan_secure_mode_is_supported;
         UINT_8 voice_vlan_secure_mode_is_supported_mask;
    } SYSCONFG_Vlan_Voice_Vlan_params_STC;

    typedef enum 
    {
        SYSCONFG_unit_type_stand_alone_E = 0,
        SYSCONFG_unit_type_controller_E = 1,
        SYSCONFG_unit_type_member_E = 2,
        SYSCONFG_unit_type_diagnostic_E = 3,
        SYSCONFG_unit_type_manufacturing_test_E = 4,
        SYSCONFG_unit_type_last_E = 5    
    } SYSCONFG_unit_type_ENT;
    /* SYSCONFG_enum_id_unit_type_E */

    typedef enum 
    {
        SYSCONFG_start_condition_type_cdb_empty_E = 0,
        SYSCONFG_start_condition_type_file_name_changed_E = 1,
        SYSCONFG_start_condition_type_last_E = 2    
    } SYSCONFG_start_condition_type_ENT;
    /* SYSCONFG_enum_id_start_condition_type_E */

    typedef enum 
    {
        SYSCONFG_target_type_start_up_cdb_E = 0,
        SYSCONFG_target_type_running_cdb_E = 1,
        SYSCONFG_target_type_last_E = 2    
    } SYSCONFG_target_type_ENT;
    /* SYSCONFG_enum_id_target_type_E */

    typedef struct 
    {
         UINT_8 voice_vlan_auto_default_dscp;
         UINT_8 voice_vlan_auto_default_dscp_mask;
         BOOLEAN voice_vlan_auto_md5_authentication_is_enabled_by_default;
         UINT_8 voice_vlan_auto_md5_authentication_is_enabled_by_default_mask;
         UINT_8 voice_vlan_auto_default_vpt;
         UINT_8 voice_vlan_auto_default_vpt_mask;
         UINT_8 voice_vlan_auto_syslog_interval;
         UINT_8 voice_vlan_auto_syslog_interval_mask;
         UINT_16 voice_vlan_auto_maximum_number_of_uc_devices;
         UINT_8 voice_vlan_auto_maximum_number_of_uc_devices_mask;
         SYSCONFG_vlan_tag_type_TYP voice_vlan_auto_default_vlan_id;
         UINT_8 voice_vlan_auto_default_vlan_id_mask;
    } SYSCONFG_Vlan_Voice_Auto_Vlan_params_STC;

    typedef struct 
    {
         UINT_32 ssl_client_maximum_number_of_ca_certificates_dynamic;
         UINT_8 ssl_client_maximum_number_of_ca_certificates_dynamic_mask;
         UINT_32 ssl_client_maximum_number_of_ca_certificates_static;
         UINT_8 ssl_client_maximum_number_of_ca_certificates_static_mask;
         char * ssl_client_ca_certificates_bundle_name;
         UINT_8 ssl_client_ca_certificates_bundle_name_mask;
         SYSCONFG_default_pk_algorithm_type_ENT default_pk_algorithm;
         UINT_8 default_pk_algorithm_mask;
         UINT_32 ssl_client_maximum_number_of_ca_certificates_revoked;
         UINT_8 ssl_client_maximum_number_of_ca_certificates_revoked_mask;
         UINT_32 default_rsa_key_length;
         UINT_8 default_rsa_key_length_mask;
         UINT_32 minimum_rsa_key_length;
         UINT_8 minimum_rsa_key_length_mask;
    } SYSCONFG_SSL_params_STC;

    typedef enum 
    {
        SYSCONFG_smart_port_type_Printer_E = 0,
        SYSCONFG_smart_port_type_Desktop_E = 1,
        SYSCONFG_smart_port_type_Guest_E = 2,
        SYSCONFG_smart_port_type_Server_E = 3,
        SYSCONFG_smart_port_type_Host_E = 4,
        SYSCONFG_smart_port_type_IP_camera_E = 5,
        SYSCONFG_smart_port_type_IP_phone_E = 6,
        SYSCONFG_smart_port_type_IP_phone_desktop_E = 7,
        SYSCONFG_smart_port_type_Switch_E = 8,
        SYSCONFG_smart_port_type_Router_E = 9,
        SYSCONFG_smart_port_type_AP_E = 10,
        SYSCONFG_smart_port_type_last_E = 11    
    } SYSCONFG_smart_port_type_ENT;
    /* SYSCONFG_enum_id_smart_port_type_E */

    typedef enum 
    {
        SYSCONFG_smart_port_enable_Controlled_E = 0,
        SYSCONFG_smart_port_enable_Enabled_E = 1,
        SYSCONFG_smart_port_enable_Disabled_E = 2,
        SYSCONFG_smart_port_enable_last_E = 3    
    } SYSCONFG_smart_port_enable_ENT;
    /* SYSCONFG_enum_id_smart_port_enable_E */

    typedef struct 
    {
         UINT_32 up_timer;
         UINT_8 up_timer_mask;
         UINT_32 init_down_timer;
         UINT_8 init_down_timer_mask;
         UINT_32 first_up_timer;
         UINT_8 first_up_timer_mask;
         UINT_32 init_down_flapping_timer;
         UINT_8 init_down_flapping_timer_mask;
         UINT_32 start_fast_down_timer;
         UINT_8 start_fast_down_timer_mask;
         UINT_32 first_validate_down_timer;
         UINT_8 first_validate_down_timer_mask;
         UINT_32 validate_down_timer;
         UINT_8 validate_down_timer_mask;
    } SYSCONFG_Link_stability_params_STC;

    typedef enum 
    {
        SYSCONFG_read_default_directive_type_exclude_E = 0,
        SYSCONFG_read_default_directive_type_encrypted_E = 1,
        SYSCONFG_read_default_directive_type_plaintext_E = 2,
        SYSCONFG_read_default_directive_type_last_E = 3    
    } SYSCONFG_read_default_directive_type_ENT;
    /* SYSCONFG_enum_id_read_default_directive_type_E */

    typedef enum 
    {
        SYSCONFG_system_mode_type_flow_control_E = 0,
        SYSCONFG_system_mode_type_hol_E = 1,
        SYSCONFG_system_mode_type_last_E = 2    
    } SYSCONFG_system_mode_type_ENT;
    /* SYSCONFG_enum_id_system_mode_type_E */

    typedef struct 
    {
         UINT_16 private_vlan_maximum_number_of_primaries;
         UINT_8 private_vlan_maximum_number_of_primaries_mask;
         UINT_16 private_vlan_maximum_number_of_communities;
         UINT_8 private_vlan_maximum_number_of_communities_mask;
         SYSCONFG_vlan_private_supported_applications_bits_type_TYP private_vlan_supported_applications;
         UINT_8 private_vlan_supported_applications_mask;
         UINT_16 private_vlan_maximum_number_of_secondaries;
         UINT_8 private_vlan_maximum_number_of_secondaries_mask;
    } SYSCONFG_Vlan_Private_Vlan_params_STC;

    typedef struct 
    {
         UINT_8 maximum_number_of_services;
         UINT_8 maximum_number_of_services_mask;
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
    } SYSCONFG_Bonjour_params_STC;

    typedef enum 
    {
        SYSCONFG_dot1x_port_default_mode_type_force_authorized_E = 0,
        SYSCONFG_dot1x_port_default_mode_type_force_unauthorized_E = 1,
        SYSCONFG_dot1x_port_default_mode_type_auto_E = 2,
        SYSCONFG_dot1x_port_default_mode_type_last_E = 3    
    } SYSCONFG_dot1x_port_default_mode_type_ENT;
    /* SYSCONFG_enum_id_dot1x_port_default_mode_type_E */

    typedef struct 
    {
         UINT_32 connection_timeout;
         UINT_8 connection_timeout_mask;
         UINT_32 link_workaround_timer_value_in_seconds;
         UINT_8 link_workaround_timer_value_in_seconds_mask;
    } SYSCONFG_LMP_params_STC;

    typedef enum 
    {
        SYSCONFG_dot1x_host_default_mode_type_single_E = 0,
        SYSCONFG_dot1x_host_default_mode_type_multiple_E = 1,
        SYSCONFG_dot1x_host_default_mode_type_multi_sessions_E = 2,
        SYSCONFG_dot1x_host_default_mode_type_last_E = 3    
    } SYSCONFG_dot1x_host_default_mode_type_ENT;
    /* SYSCONFG_enum_id_dot1x_host_default_mode_type_E */

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_PNP_agent_params_STC;

    typedef UINT_32 SYSCONFG_single_host_violation_bits_type_TYP;
#define SYSCONFG_SINGLE_HOST_VIOLATION_BITS_TYPE_DISCARD_CNS (1 << 3)
    #define SYSCONFG_SINGLE_HOST_VIOLATION_BITS_TYPE_FORWARD_NORMAL_CNS (1 << 2)
    #define SYSCONFG_SINGLE_HOST_VIOLATION_BITS_TYPE_DISCARD_AND_SHUTDOWN_CNS (1 << 1)

    typedef struct 
    {
         BOOLEAN guest_vlan_timeout_is_suppported;
         UINT_8 guest_vlan_timeout_is_suppported_mask;
         BOOLEAN vlan_unauthenticated_is_supported;
         UINT_8 vlan_unauthenticated_is_supported_mask;
         BOOLEAN vlan_dot1x_dva_is_tagged_indication_supported;
         UINT_8 vlan_dot1x_dva_is_tagged_indication_supported_mask;
         BOOLEAN vlan_guest_is_supported;
         UINT_8 vlan_guest_is_supported_mask;
         UINT_16 guest_vlan_default_vlan_id;
         UINT_8 guest_vlan_default_vlan_id_mask;
         UINT_8 guest_vlan_default_timeout;
         UINT_8 guest_vlan_default_timeout_mask;
         BOOLEAN vlan_dot1x_dva_is_supported;
         UINT_8 vlan_dot1x_dva_is_supported_mask;
    } SYSCONFG_Vlan_Dot1x_Extensions_params_STC;

    typedef enum 
    {
        SYSCONFG_mac_address_format_type_colon_separated_E = 0,
        SYSCONFG_mac_address_format_type_minus_separated_E = 1,
        SYSCONFG_mac_address_format_type_dot_separated_E = 2,
        SYSCONFG_mac_address_format_type_last_E = 3    
    } SYSCONFG_mac_address_format_type_ENT;
    /* SYSCONFG_enum_id_mac_address_format_type_E */

    typedef struct 
    {
         UINT_32 maximum_number_of_user_rules;
         UINT_8 maximum_number_of_user_rules_mask;
         UINT_32 maximum_number_of_channels;
         UINT_8 maximum_number_of_channels_mask;
    } SYSCONFG_Security_sensitive_data_params_STC;

    typedef struct 
    {
         SYSCONFG_unit_type_ENT unit_type_in_stack;
         UINT_8 unit_type_in_stack_mask;
         UINT_16 maximum_number_of_units;
         UINT_8 maximum_number_of_units_mask;
    } SYSCONFG_Unit_params_STC;

    typedef struct 
    {
         BOOLEAN divided_system_is_supported;
         UINT_8 divided_system_is_supported_mask;
         SYSCONFG_system_mode_type_ENT first_system_default_mode;
         UINT_8 first_system_default_mode_mask;
         SYSCONFG_system_mode_type_ENT second_system_default_mode;
         UINT_8 second_system_default_mode_mask;
    } SYSCONFG_Buffer_management_params_STC;

    typedef enum 
    {
        SYSCONFG_cli_interface_type_Port_10M_E = 0,
        SYSCONFG_cli_interface_type_Port_100M_E = 1,
        SYSCONFG_cli_interface_type_Port_1G_E = 2,
        SYSCONFG_cli_interface_type_Port_2500M_E = 3,
        SYSCONFG_cli_interface_type_Port_5G_E = 4,
        SYSCONFG_cli_interface_type_Port_10G_E = 5,
        SYSCONFG_cli_interface_type_Trunk_E = 6,
        SYSCONFG_cli_interface_type_Vlan_E = 7,
        SYSCONFG_cli_interface_type_Tunnel_E = 8,
        SYSCONFG_cli_interface_type_Loopback_E = 9,
        SYSCONFG_cli_interface_type_Port_20G_E = 10,
        SYSCONFG_cli_interface_type_Port_40G_E = 11,
        SYSCONFG_cli_interface_type_Port_100G_E = 12,
        SYSCONFG_cli_interface_type_Port_25G_E = 13,
        SYSCONFG_cli_interface_type_Port_50G_E = 14,
        SYSCONFG_cli_interface_type_last_E = 15    
    } SYSCONFG_cli_interface_type_ENT;
    /* SYSCONFG_enum_id_cli_interface_type_E */

    typedef struct 
    {
         BOOLEAN is_reload_exist_per_unit;
         UINT_8 is_reload_exist_per_unit_mask;
         BOOLEAN Stack_auto_version_update_is_supported;
         UINT_8 Stack_auto_version_update_is_supported_mask;
         SYSCONFG_Link_stability_params_STC Link_stability;
         UINT_8 Link_stability_mask;
         SYSCONFG_stack_enabled_supported_speed_type_TYP stack_enabled_supported_speed;
         UINT_8 stack_enabled_supported_speed_mask;
         BOOLEAN Link_stability_feature_is_supported;
         UINT_8 Link_stability_feature_is_supported_mask;
         SYSCONFG_LMP_params_STC LMP;
         UINT_8 LMP_mask;
         BOOLEAN Unit_feature_is_supported;
         UINT_8 Unit_feature_is_supported_mask;
         BOOLEAN is_speed_exist_per_unit;
         UINT_8 is_speed_exist_per_unit_mask;
         char * Stack_controller_unit_name;
         UINT_8 Stack_controller_unit_name_mask;
         UINT_8 maximum_number_of_cascade_ports;
         UINT_8 maximum_number_of_cascade_ports_mask;
         BOOLEAN nsf_mode_is_supported;
         UINT_8 nsf_mode_is_supported_mask;
         BOOLEAN Fast_failover_is_supported;
         UINT_8 Fast_failover_is_supported_mask;
         char * Stack_backup_unit_name;
         UINT_8 Stack_backup_unit_name_mask;
         UINT_16 nsf_timer_in_seconds;
         UINT_8 nsf_timer_in_seconds_mask;
         BOOLEAN LMP_feature_is_supported;
         UINT_8 LMP_feature_is_supported_mask;
         BOOLEAN Hybrid_stack_mode_is_supported;
         UINT_8 Hybrid_stack_mode_is_supported_mask;
         BOOLEAN standalone_mode_is_supported;
         UINT_8 standalone_mode_is_supported_mask;
         SYSCONFG_Unit_params_STC Unit;
         UINT_8 Unit_mask;
         BOOLEAN duplicate_id_reset_to_factory_defaults;
         UINT_8 duplicate_id_reset_to_factory_defaults_mask;
    } SYSCONFG_Stack_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_PTP_exception_workaround_params_STC;

    typedef enum 
    {
        SYSCONFG_lag_balance_layer_type_layer2_and_layer3_E = 1,
        SYSCONFG_lag_balance_layer_type_layer2_E = 2,
        SYSCONFG_lag_balance_layer_type_layer3_E = 3,
        SYSCONFG_lag_balance_layer_type_layer2_and_layer3_and_layer4_E = 4,
        SYSCONFG_lag_balance_layer_type_last_E = 5    
    } SYSCONFG_lag_balance_layer_type_ENT;
    /* SYSCONFG_enum_id_lag_balance_layer_type_E */

    typedef struct 
    {
         BOOLEAN vlan_mapping_tunnel_is_suppported;
         UINT_8 vlan_mapping_tunnel_is_suppported_mask;
         BOOLEAN vlan_mapping_one_to_one_is_suppported;
         UINT_8 vlan_mapping_one_to_one_is_suppported_mask;
         RSG_mac_addr_TYP vlan_mapping_layer2_protocol_mac_address;
         UINT_8 vlan_mapping_layer2_protocol_mac_address_mask;
         BOOLEAN vlan_mapping_layer2_protocol_tunnel_is_suppported;
         UINT_8 vlan_mapping_layer2_protocol_tunnel_is_suppported_mask;
         BOOLEAN vlan_mapping_ethertype_configuration_is_suppported;
         UINT_8 vlan_mapping_ethertype_configuration_is_suppported_mask;
         UINT_16 vlan_mapping_default_number_of_entries;
         UINT_8 vlan_mapping_default_number_of_entries_mask;
         UINT_16 vlan_mapping_minimum_number_of_entries;
         UINT_8 vlan_mapping_minimum_number_of_entries_mask;
         UINT_16 vlan_mapping_maximum_number_of_entries;
         UINT_8 vlan_mapping_maximum_number_of_entries_mask;
    } SYSCONFG_Vlan_Mapping_params_STC;

    typedef enum 
    {
        SYSCONFG_lacp_port_membership_in_lag_type_active_peer_E = 0,
        SYSCONFG_lacp_port_membership_in_lag_type_no_active_peer_E = 1,
        SYSCONFG_lacp_port_membership_in_lag_type_only_first_port_active_E = 2,
        SYSCONFG_lacp_port_membership_in_lag_type_last_E = 3    
    } SYSCONFG_lacp_port_membership_in_lag_type_ENT;
    /* SYSCONFG_enum_id_lacp_port_membership_in_lag_type_E */

    typedef enum 
    {
        SYSCONFG_lag_creation_type_lag_creation_is_not_supported_E = 0,
        SYSCONFG_lag_creation_type_lag_creation_supports_static_lag_or_lacp_E = 1,
        SYSCONFG_lag_creation_type_last_E = 2    
    } SYSCONFG_lag_creation_type_ENT;
    /* SYSCONFG_enum_id_lag_creation_type_E */

    typedef struct 
    {
         UINT_32 default_queue;
         UINT_8 default_queue_mask;
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
         BOOLEAN ipv6_is_supported;
         UINT_8 ipv6_is_supported_mask;
         UINT_32 maximum_number_of_iscsi_flows;
         UINT_8 maximum_number_of_iscsi_flows_mask;
    } SYSCONFG_iSCSI_Qos_params_STC;

    typedef struct 
    {
         UINT_8 number_of_name_servers_for_oob;
         UINT_8 number_of_name_servers_for_oob_mask;
         UINT_8 maximum_number_of_retransmissions;
         UINT_8 maximum_number_of_retransmissions_mask;
         UINT_8 number_of_static_cache_entries_for_oob;
         UINT_8 number_of_static_cache_entries_for_oob_mask;
         UINT_8 number_of_dynamic_cache_entries_for_oob;
         UINT_8 number_of_dynamic_cache_entries_for_oob_mask;
         UINT_8 maximum_number_of_pending_msgs;
         UINT_8 maximum_number_of_pending_msgs_mask;
         UINT_8 number_of_ncache_entries_for_oob;
         UINT_8 number_of_ncache_entries_for_oob_mask;
         UINT_8 number_of_name_servers;
         UINT_8 number_of_name_servers_mask;
         char * default_domain_name;
         UINT_8 default_domain_name_mask;
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
         UINT_16 number_of_domain_names;
         UINT_8 number_of_domain_names_mask;
         UINT_8 minimum_retransmission_interval;
         UINT_8 minimum_retransmission_interval_mask;
         UINT_8 number_of_domain_names_for_oob;
         UINT_8 number_of_domain_names_for_oob_mask;
    } SYSCONFG_DNS_client_params_STC;

    typedef struct 
    {
         UINT_16 multicast_tv_vlan_ip_multicast_size;
         UINT_8 multicast_tv_vlan_ip_multicast_size_mask;
    } SYSCONFG_Vlan_Multicast_Tv_Vlan_params_STC;

    typedef UINT_32 SYSCONFG_snmp_version_bits_type_TYP;
#define SYSCONFG_SNMP_VERSION_BITS_TYPE_VERSION_ONE_CNS (1 << 7)
    #define SYSCONFG_SNMP_VERSION_BITS_TYPE_VERSION_TWO_CNS (1 << 6)
    #define SYSCONFG_SNMP_VERSION_BITS_TYPE_VERSION_THREE_CNS (1 << 5)

    typedef enum 
    {
        SYSCONFG_authentication_method_type_none_E = 0,
        SYSCONFG_authentication_method_type_md5_E = 1,
        SYSCONFG_authentication_method_type_sha_E = 2,
        SYSCONFG_authentication_method_type_last_E = 3    
    } SYSCONFG_authentication_method_type_ENT;
    /* SYSCONFG_enum_id_authentication_method_type_E */

    typedef enum 
    {
        SYSCONFG_tcp_syn_protection_mode_type_none_E = 0,
        SYSCONFG_tcp_syn_protection_mode_type_disabled_E = 1,
        SYSCONFG_tcp_syn_protection_mode_type_report_E = 2,
        SYSCONFG_tcp_syn_protection_mode_type_block_E = 3,
        SYSCONFG_tcp_syn_protection_mode_type_last_E = 4    
    } SYSCONFG_tcp_syn_protection_mode_type_ENT;
    /* SYSCONFG_enum_id_tcp_syn_protection_mode_type_E */

    typedef struct 
    {
         BOOLEAN is_dummy_synchronization_enabled;
         UINT_8 is_dummy_synchronization_enabled_mask;
    } SYSCONFG_DFS_params_STC;

    typedef enum 
    {
        SYSCONFG_sec_suite_supported_rules_type_no_rule_is_supported_E = 0,
        SYSCONFG_sec_suite_supported_rules_type_global_rules_are_supported_E = 1,
        SYSCONFG_sec_suite_supported_rules_type_interface_rules_are_supported_E = 2,
        SYSCONFG_sec_suite_supported_rules_type_all_rules_are_supported_E = 3,
        SYSCONFG_sec_suite_supported_rules_type_last_E = 4    
    } SYSCONFG_sec_suite_supported_rules_type_ENT;
    /* SYSCONFG_enum_id_sec_suite_supported_rules_type_E */

    typedef struct 
    {
         UINT_16 mac_base_vlan_maximum_number_of_mappings;
         UINT_8 mac_base_vlan_maximum_number_of_mappings_mask;
         UINT_16 mac_base_vlan_maximum_number_of_ranges_and_groups;
         UINT_8 mac_base_vlan_maximum_number_of_ranges_and_groups_mask;
    } SYSCONFG_Vlan_Mac_Base_Vlan_params_STC;

    typedef struct 
    {
         UINT_32 maximum_image_size;
         UINT_8 maximum_image_size_mask;
         UINT_32 maximum_language_data_size;
         UINT_8 maximum_language_data_size_mask;
         UINT_8 maximum_number_of_languages;
         UINT_8 maximum_number_of_languages_mask;
    } SYSCONFG_WBA_params_STC;

    typedef enum 
    {
        SYSCONFG_web_authentication_privilege_level_type_none_E = 0,
        SYSCONFG_web_authentication_privilege_level_type_read_E = 1,
        SYSCONFG_web_authentication_privilege_level_type_read_write_E = 15,
        SYSCONFG_web_authentication_privilege_level_type_last_E = 16    
    } SYSCONFG_web_authentication_privilege_level_type_ENT;
    /* SYSCONFG_enum_id_web_authentication_privilege_level_type_E */

    typedef enum 
    {
        SYSCONFG_header_action_type_not_sending_header_to_syslog_server_E = 1,
        SYSCONFG_header_action_type_sending_header_to_syslog_server_E = 2,
        SYSCONFG_header_action_type_last_E = 3    
    } SYSCONFG_header_action_type_ENT;
    /* SYSCONFG_enum_id_header_action_type_E */

    typedef struct 
    {
         UINT_16 maximum_number_of_entries;
         UINT_8 maximum_number_of_entries_mask;
    } SYSCONFG_UDP_relay_params_STC;

    typedef enum 
    {
        SYSCONFG_mld_version_type_version_1_E = 1,
        SYSCONFG_mld_version_type_version_2_E = 2,
        SYSCONFG_mld_version_type_last_E = 3    
    } SYSCONFG_mld_version_type_ENT;
    /* SYSCONFG_enum_id_mld_version_type_E */

    typedef struct 
    {
         UINT_16 subnet_base_vlan_maximum_number_of_mappings;
         UINT_8 subnet_base_vlan_maximum_number_of_mappings_mask;
         UINT_16 subnet_base_vlan_maximum_number_of_ranges_and_groups;
         UINT_8 subnet_base_vlan_maximum_number_of_ranges_and_groups_mask;
    } SYSCONFG_Vlan_Subnet_Base_Vlan_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         UINT_32 ifindex;
    } PKDB SYSCONFG_change_pset_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_change_pset_list_keys_STC list_keys;
    } SYSCONFG_change_pset_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         /* db of type SYSCONFG_change_pset_list_params_STC */ SYSCONFG_DB_HANDLE_TYP change_pset_list_PTR;
         UINT_8 change_pset_list_mask;
    } SYSCONFG_link_change_pset_params_STC;

    typedef struct 
    {
         UINT_32 max_mtu;
         UINT_8 max_mtu_mask;
         UINT_32 min_mtu;
         UINT_8 min_mtu_mask;
         UINT_32 def_mtu;
         UINT_8 def_mtu_mask;
    } SYSCONFG_ipv6_mtu_values_params_STC;

    typedef struct 
    {
         SYSCONFG_link_change_pset_params_STC link_change_pset;
         UINT_8 link_change_pset_mask;
         SYSCONFG_rx_training_type_ENT supported_type;
         UINT_8 supported_type_mask;
    } SYSCONFG_Rx_Training_params_STC;

    typedef struct 
    {
         BOOLEAN syn_fin_tcp_packets_deny_is_enabled_by_default;
         UINT_8 syn_fin_tcp_packets_deny_is_enabled_by_default_mask;
         UINT_32 default_tcp_syn_protection_threshold_time;
         UINT_8 default_tcp_syn_protection_threshold_time_mask;
         SYSCONFG_sec_suite_supported_rules_type_ENT security_suite_support_rules_mode;
         UINT_8 security_suite_support_rules_mode_mask;
         UINT_32 minimum_tcp_syn_protection_threshold_time;
         UINT_8 minimum_tcp_syn_protection_threshold_time_mask;
         UINT_32 maximum_number_of_entries;
         UINT_8 maximum_number_of_entries_mask;
         BOOLEAN tcp_syn_protection_is_supported;
         UINT_8 tcp_syn_protection_is_supported_mask;
         UINT_32 minimum_tcp_syn_protection_auto_recovery_time;
         UINT_8 minimum_tcp_syn_protection_auto_recovery_time_mask;
         UINT_32 maximum_tcp_syn_protection_threshold_time;
         UINT_8 maximum_tcp_syn_protection_threshold_time_mask;
         UINT_32 maximum_tcp_syn_protection_auto_recovery_time;
         UINT_8 maximum_tcp_syn_protection_auto_recovery_time_mask;
         UINT_32 default_tcp_syn_protection_auto_recovery_time;
         UINT_8 default_tcp_syn_protection_auto_recovery_time_mask;
         BOOLEAN syn_fin_tcp_packets_deny_is_supported;
         UINT_8 syn_fin_tcp_packets_deny_is_supported_mask;
         UINT_32 tcp_syn_protection_report_syslog_interval_timeout;
         UINT_8 tcp_syn_protection_report_syslog_interval_timeout_mask;
         SYSCONFG_tcp_syn_protection_mode_type_ENT default_tcp_syn_protection_mode;
         UINT_8 default_tcp_syn_protection_mode_mask;
    } SYSCONFG_Security_suite_params_STC;

    typedef struct 
    {
         UINT_16 maximum_number_of_neighbors;
         UINT_8 maximum_number_of_neighbors_mask;
         BOOLEAN mc_forwarding_enabled_by_default;
         UINT_8 mc_forwarding_enabled_by_default_mask;
         UINT_32 maximum_number_of_general_prefixes;
         UINT_8 maximum_number_of_general_prefixes_mask;
         BOOLEAN uc_forwarding_supported;
         UINT_8 uc_forwarding_supported_mask;
         UINT_32 minimum_stale_neighbor_age_threshold;
         UINT_8 minimum_stale_neighbor_age_threshold_mask;
         SYSCONFG_ipv6_mtu_values_params_STC ipv6_mtu_values;
         UINT_8 ipv6_mtu_values_mask;
         BOOLEAN uc_forwarding_enabled_by_default;
         UINT_8 uc_forwarding_enabled_by_default_mask;
         UINT_32 maximum_number_of_interfaces;
         UINT_8 maximum_number_of_interfaces_mask;
         UINT_32 maximum_number_of_addresses;
         UINT_8 maximum_number_of_addresses_mask;
         UINT_32 memory_pool_size;
         UINT_8 memory_pool_size_mask;
         BOOLEAN mc_forwarding_supported;
         UINT_8 mc_forwarding_supported_mask;
         UINT_8 maximum_number_of_ipv6_multicast_addresses_per_interface;
         UINT_8 maximum_number_of_ipv6_multicast_addresses_per_interface_mask;
         UINT_32 maximum_number_of_default_gateways;
         UINT_8 maximum_number_of_default_gateways_mask;
         SYSCONFG_mld_version_type_ENT mld_default_version;
         UINT_8 mld_default_version_mask;
         UINT_32 maximum_number_of_static_routes;
         UINT_8 maximum_number_of_static_routes_mask;
         BOOLEAN multiple_link_local_addresses_is_supported;
         UINT_8 multiple_link_local_addresses_is_supported_mask;
         BOOLEAN mtu_configuration_supported;
         UINT_8 mtu_configuration_supported_mask;
    } SYSCONFG_IPv6_stack_params_STC;

    typedef struct 
    {
         BOOLEAN failure_traps_is_enabled_by_default;
         UINT_8 failure_traps_is_enabled_by_default_mask;
         BOOLEAN password_is_supported;
         UINT_8 password_is_supported_mask;
         BOOLEAN restrictions_is_supported;
         UINT_8 restrictions_is_supported_mask;
         BOOLEAN success_traps_is_supported;
         UINT_8 success_traps_is_supported_mask;
         BOOLEAN success_traps_is_enabled_by_default;
         UINT_8 success_traps_is_enabled_by_default_mask;
         BOOLEAN pure_radius_is_supported;
         UINT_8 pure_radius_is_supported_mask;
         BOOLEAN failure_traps_is_supported;
         UINT_8 failure_traps_is_supported_mask;
    } SYSCONFG_Dot1x_mac_authentication_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         char mpn[128];
    } PKDB SYSCONFG_fiber_gbic_description_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_fiber_gbic_description_list_keys_STC list_keys;
         char * pid;
         UINT_8 pid_mask;
         char * description;
         UINT_8 description_mask;
         char * vid;
         UINT_8 vid_mask;
    } SYSCONFG_fiber_gbic_description_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         UINT_32 prevention_timer_delay_msec;
         UINT_8 prevention_timer_delay_msec_mask;
         UINT_32 max_burst_count;
         UINT_8 max_burst_count_mask;
         UINT_32 burst_window_duration_msec;
         UINT_8 burst_window_duration_msec_mask;
         UINT_32 max_events_in_window;
         UINT_8 max_events_in_window_mask;
    } SYSCONFG_Signal_Stability_params_STC;

    typedef struct 
    {
         BOOLEAN Dynamic_acl_enabled_by_default;
         UINT_8 Dynamic_acl_enabled_by_default_mask;
         BOOLEAN Dynamic_acl_mac_filter_id_supported;
         UINT_8 Dynamic_acl_mac_filter_id_supported_mask;
         BOOLEAN Dynamic_acl_ipv6_filter_id_supported;
         UINT_8 Dynamic_acl_ipv6_filter_id_supported_mask;
         BOOLEAN Dynamic_acl_ipv4_filter_id_supported;
         UINT_8 Dynamic_acl_ipv4_filter_id_supported_mask;
    } SYSCONFG_Dynamic_acl_params_STC;

    typedef struct 
    {
         UINT_32 default_number_of_route_entries;
         UINT_8 default_number_of_route_entries_mask;
    } SYSCONFG_IPv4_fft_params_STC;

    typedef struct 
    {
         UINT_32 burst_window_duration;
         UINT_8 burst_window_duration_mask;
         UINT_32 max_lc_in_window;
         UINT_8 max_lc_in_window_mask;
         BOOLEAN default_value;
         UINT_8 default_value_mask;
         UINT_32 max_burst_count;
         UINT_8 max_burst_count_mask;
         UINT_32 in_burst_violation_count;
         UINT_8 in_burst_violation_count_mask;
         UINT_32 in_burst_violation_time;
         UINT_8 in_burst_violation_time_mask;
         BOOLEAN in_burst_violation_supported;
         UINT_8 in_burst_violation_supported_mask;
    } SYSCONFG_Link_Flapping_Prevention_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_global_addresses;
         UINT_8 maximum_number_of_global_addresses_mask;
         UINT_32 default_number_of_interfaces;
         UINT_8 default_number_of_interfaces_mask;
         UINT_32 fft_red_boundary;
         UINT_8 fft_red_boundary_mask;
         UINT_32 maximum_number_of_prefixes;
         UINT_8 maximum_number_of_prefixes_mask;
         UINT_32 default_number_of_prefixes;
         UINT_8 default_number_of_prefixes_mask;
         UINT_32 default_number_of_route_entries;
         UINT_8 default_number_of_route_entries_mask;
         UINT_32 default_number_of_global_addresses;
         UINT_8 default_number_of_global_addresses_mask;
         UINT_32 minimum_number_of_nextHop_entries;
         UINT_8 minimum_number_of_nextHop_entries_mask;
         UINT_32 minimum_number_of_prefixes;
         UINT_8 minimum_number_of_prefixes_mask;
         UINT_32 maximum_number_of_interfaces;
         UINT_8 maximum_number_of_interfaces_mask;
         UINT_32 maximum_number_of_nextHop_entries;
         UINT_8 maximum_number_of_nextHop_entries_mask;
         UINT_32 minimum_number_of_interfaces;
         UINT_8 minimum_number_of_interfaces_mask;
         UINT_32 fft_yellow_boundary;
         UINT_8 fft_yellow_boundary_mask;
         UINT_32 minimum_number_of_global_addresses;
         UINT_8 minimum_number_of_global_addresses_mask;
         UINT_32 default_number_of_nextHop_entries;
         UINT_8 default_number_of_nextHop_entries_mask;
    } SYSCONFG_IPv6_fft_params_STC;

    typedef struct 
    {
         SYSCONFG_flow_control_management_mode_type_ENT flow_control_management_mode;
         UINT_8 flow_control_management_mode_mask;
         SYSCONFG_flow_control_mode_type_ENT flow_control_default_mode;
         UINT_8 flow_control_default_mode_mask;
    } SYSCONFG_Flow_Control_params_STC;

    typedef struct 
    {
         BOOLEAN rejected_users_file_supported;
         UINT_8 rejected_users_file_supported_mask;
         UINT_16 max_number_of_saved_rejected_users;
         UINT_8 max_number_of_saved_rejected_users_mask;
         UINT_16 max_number_of_unknown_nas_entries;
         UINT_8 max_number_of_unknown_nas_entries_mask;
         BOOLEAN accounting_log_file_supported;
         UINT_8 accounting_log_file_supported_mask;
         UINT_16 max_number_of_radius_server_users;
         UINT_8 max_number_of_radius_server_users_mask;
         UINT_16 max_number_of_eap_sessions;
         UINT_8 max_number_of_eap_sessions_mask;
         BOOLEAN acl_attribute_supported;
         UINT_8 acl_attribute_supported_mask;
         UINT_16 max_number_of_supported_radius_clients;
         UINT_8 max_number_of_supported_radius_clients_mask;
         UINT_16 max_number_of_radius_sessions;
         UINT_8 max_number_of_radius_sessions_mask;
         UINT_16 max_number_of_saved_accounting_logs;
         UINT_8 max_number_of_saved_accounting_logs_mask;
         UINT_16 max_number_of_radius_server_groups;
         UINT_8 max_number_of_radius_server_groups_mask;
    } SYSCONFG_Radius_server_params_STC;

    typedef struct 
    {
         BOOLEAN fiber_eeprom_supported;
         UINT_8 fiber_eeprom_supported_mask;
         BOOLEAN fiber_access_to_i2c_address_a2_is_allowed;
         UINT_8 fiber_access_to_i2c_address_a2_is_allowed_mask;
         /* db of type SYSCONFG_fiber_gbic_description_list_params_STC */ SYSCONFG_DB_HANDLE_TYP fiber_gbic_description_list_PTR;
         UINT_8 fiber_gbic_description_list_mask;
         BOOLEAN fiber_show_cascade_ports;
         UINT_8 fiber_show_cascade_ports_mask;
         UINT_32 fiber_polling_counter_factor;
         UINT_8 fiber_polling_counter_factor_mask;
         BOOLEAN fiber_gbics_support;
         UINT_8 fiber_gbics_support_mask;
         SYSCONFG_show_inventory_mode_ENT fiber_show_inventory_mode;
         UINT_8 fiber_show_inventory_mode_mask;
         BOOLEAN fiber_present_msg_support;
         UINT_8 fiber_present_msg_support_mask;
         BOOLEAN fiber_loss_indication_support;
         UINT_8 fiber_loss_indication_support_mask;
         UINT_32 fiber_polling_interval_ms;
         UINT_8 fiber_polling_interval_ms_mask;
         BOOLEAN fiber_tx_operation_support;
         UINT_8 fiber_tx_operation_support_mask;
    } SYSCONFG_Fiber_params_STC;

    typedef struct 
    {
         SYSCONFG_Radius_CoA_params_STC Radius_CoA;
         UINT_8 Radius_CoA_mask;
         BOOLEAN radius_coa_feature_is_supported;
         UINT_8 radius_coa_feature_is_supported_mask;
         BOOLEAN attribute_framed_ipv4_address_is_supported;
         UINT_8 attribute_framed_ipv4_address_is_supported_mask;
         BOOLEAN audit_session_id_is_supported;
         UINT_8 audit_session_id_is_supported_mask;
         BOOLEAN attribute_framed_ipv6_address_is_supported;
         UINT_8 attribute_framed_ipv6_address_is_supported_mask;
    } SYSCONFG_Radius_client_params_STC;

    typedef struct 
    {
         BOOLEAN Green_Energy_Detect_feature_is_supported;
         UINT_8 Green_Energy_Detect_feature_is_supported_mask;
         BOOLEAN Green_LED_feature_is_supported;
         UINT_8 Green_LED_feature_is_supported_mask;
         SYSCONFG_Green_Short_Reach_params_STC Green_Short_Reach;
         UINT_8 Green_Short_Reach_mask;
         BOOLEAN Green_Short_Reach_feature_is_supported;
         UINT_8 Green_Short_Reach_feature_is_supported_mask;
         SYSCONFG_Green_LED_params_STC Green_LED;
         UINT_8 Green_LED_mask;
         SYSCONFG_Green_Energy_Detect_params_STC Green_Energy_Detect;
         UINT_8 Green_Energy_Detect_mask;
         SYSCONFG_max_consumption_type_ENT max_consumption_type_value;
         UINT_8 max_consumption_type_value_mask;
    } SYSCONFG_Green_params_STC;

    typedef struct 
    {
         char * default_acl_name;
         UINT_8 default_acl_name_mask;
         char * default_open_acl_name;
         UINT_8 default_open_acl_name_mask;
         BOOLEAN radius_cisco_vsa_is_supported;
         UINT_8 radius_cisco_vsa_is_supported_mask;
         BOOLEAN reject_dynamic_acl_not_any_source_ip;
         UINT_8 reject_dynamic_acl_not_any_source_ip_mask;
    } SYSCONFG_ISE_params_STC;

    typedef struct 
    {
         BOOLEAN eee_default_enable;
         UINT_8 eee_default_enable_mask;
         BOOLEAN port_eee_default_enable;
         UINT_8 port_eee_default_enable_mask;
         BOOLEAN eee_lldp_default_enable;
         UINT_8 eee_lldp_default_enable_mask;
    } SYSCONFG_EEE_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_prefix_list_entries;
         UINT_8 maximum_number_of_prefix_list_entries_mask;
    } SYSCONFG_IPv4_prefix_list_params_STC;

    typedef struct 
    {
         SYSCONFG_led_display_default_pattern_type_ENT led_display_default_pattern;
         UINT_8 led_display_default_pattern_mask;
         UINT_16 led_display_minimum_interval;
         UINT_8 led_display_minimum_interval_mask;
         SYSCONFG_led_display_mode_type_ENT led_display_mode;
         UINT_8 led_display_mode_mask;
         UINT_16 led_display_default_interval;
         UINT_8 led_display_default_interval_mask;
         UINT_32 led_display_maximum_interval;
         UINT_8 led_display_maximum_interval_mask;
    } SYSCONFG_Locate_Unit_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_prefix_list_entries;
         UINT_8 maximum_number_of_prefix_list_entries_mask;
    } SYSCONFG_IPv6_prefix_list_params_STC;

    typedef struct 
    {
         UINT_16 led_display_minimum_interval;
         UINT_8 led_display_minimum_interval_mask;
         SYSCONFG_port_led_mode_type_ENT led_display_mode;
         UINT_8 led_display_mode_mask;
         UINT_16 led_display_default_interval;
         UINT_8 led_display_default_interval_mask;
         UINT_16 led_display_maximum_interval;
         UINT_8 led_display_maximum_interval_mask;
    } SYSCONFG_Locate_Port_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_aces;
         UINT_8 maximum_number_of_aces_mask;
         BOOLEAN source_and_destination_ip_addresses_are_used;
         UINT_8 source_and_destination_ip_addresses_are_used_mask;
    } SYSCONFG_IP_standard_acl_params_STC;

    typedef struct 
    {
         SYSCONFG_udld_port_mode_type_ENT default_copper_port_mode;
         UINT_8 default_copper_port_mode_mask;
         UINT_32 global_neighbor;
         UINT_8 global_neighbor_mask;
         SYSCONFG_udld_port_mode_type_ENT default_fiber_port_mode;
         UINT_8 default_fiber_port_mode_mask;
    } SYSCONFG_UDLD_params_STC;

    typedef struct 
    {
         UINT_32 default_ifindex;
         UINT_8 default_ifindex_mask;
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
         UINT_32 maximum_size_of_sntp_servers_list;
         UINT_8 maximum_size_of_sntp_servers_list_mask;
         UINT_32 maximum_size_of_dns_servers_list;
         UINT_8 maximum_size_of_dns_servers_list_mask;
         UINT_32 maximum_size_of_domain_search_list;
         UINT_8 maximum_size_of_domain_search_list_mask;
    } SYSCONFG_DHCPv6_client_params_STC;

    typedef struct 
    {
         BOOLEAN sgmii_wa_required;
         UINT_8 sgmii_wa_required_mask;
         UINT_32 phy_wa_polling_interval;
         UINT_8 phy_wa_polling_interval_mask;
    } SYSCONFG_hw_interface_params_STC;

    typedef char * SYSCONFG_vendor_oui_TYP;

    typedef struct 
    {
         UINT_32 maximum_destinations_per_interface;
         UINT_8 maximum_destinations_per_interface_mask;
         UINT_32 maximum_global_destinations;
         UINT_8 maximum_global_destinations_mask;
    } SYSCONFG_DHCPv6_relay_params_STC;

    typedef char * SYSCONFG_sub_vendor_oui_TYP;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_I2C_Syslog_params_STC;

    typedef struct 
    {
         UINT_8 loopback_detection_protocol_identifier;
         UINT_8 loopback_detection_protocol_identifier_mask;
         BOOLEAN loopback_detection_is_enabled_per_port_by_default;
         UINT_8 loopback_detection_is_enabled_per_port_by_default_mask;
         UINT_8 loopback_detection_default_timeout_interval;
         UINT_8 loopback_detection_default_timeout_interval_mask;
         RSG_mac_addr_TYP loopback_detection_predefined_multicast_mac_address;
         UINT_8 loopback_detection_predefined_multicast_mac_address_mask;
         BOOLEAN loopback_detection_is_enabled_by_default;
         UINT_8 loopback_detection_is_enabled_by_default_mask;
         char * loopback_detection_sub_vendor_oui;
         UINT_8 loopback_detection_sub_vendor_oui_mask;
         SYSCONFG_loopback_detection_source_mode_type_ENT loopback_detection_source_mode;
         UINT_8 loopback_detection_source_mode_mask;
         UINT_8 loopback_detection_protocol_version;
         UINT_8 loopback_detection_protocol_version_mask;
         SYSCONFG_loopback_detection_destination_mode_type_ENT loopback_detection_destination_mode;
         UINT_8 loopback_detection_destination_mode_mask;
         UINT_8 loopback_detection_minimum_transmit_timeout_interval;
         UINT_8 loopback_detection_minimum_transmit_timeout_interval_mask;
         char * loopback_detection_vendor_oui;
         UINT_8 loopback_detection_vendor_oui_mask;
         UINT_8 loopback_detection_stability_timeout_interval;
         UINT_8 loopback_detection_stability_timeout_interval_mask;
         BOOLEAN loopback_detection_promiscuous_mode;
         UINT_8 loopback_detection_promiscuous_mode_mask;
    } SYSCONFG_Loopback_Detection_params_STC;

    typedef struct 
    {
         UINT_32 allocated_memory_size;
         UINT_8 allocated_memory_size_mask;
    } SYSCONFG_Metaswitch_Routing_Protocols_Suite_params_STC;

    typedef struct 
    {
         SYSCONFG_auto_neg_role_ENT default_master_slave_preference;
         UINT_8 default_master_slave_preference_mask;
    } SYSCONFG_auto_neg_preference_params_STC;

    typedef struct 
    {
         BOOLEAN storm_control_global_configuration_feature_is_supported;
         UINT_8 storm_control_global_configuration_feature_is_supported_mask;
         UINT_8 storm_control_global_default_rate_in_percentage;
         UINT_8 storm_control_global_default_rate_in_percentage_mask;
         BOOLEAN storm_control_counters_are_supported;
         UINT_8 storm_control_counters_are_supported_mask;
         BOOLEAN storm_control_global_is_enabled_by_default;
         UINT_8 storm_control_global_is_enabled_by_default_mask;
    } SYSCONFG_Storm_Control_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_Routemap_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         SYSCONFG_cpu_queue_id_type_TYP cpu_queue_id;
    } PKDB SYSCONFG_cpu_queue_info_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_cpu_queue_info_list_keys_STC list_keys;
         SYSCONFG_cpu_dma_buffers_type_TYP cpu_dma_buffers;
         UINT_8 cpu_dma_buffers_mask;
         SYSCONFG_cpu_packets_weight_type_TYP cpu_packets_weight;
         UINT_8 cpu_packets_weight_mask;
    } SYSCONFG_cpu_queue_info_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         BOOLEAN poe_powered_pd_ports_supported;
         UINT_8 poe_powered_pd_ports_supported_mask;
         UINT_32 poe_periodic_polling_ports_statistics_ms;
         UINT_8 poe_periodic_polling_ports_statistics_ms_mask;
         BOOLEAN poe_consumption_levels_threshold_supported;
         UINT_8 poe_consumption_levels_threshold_supported_mask;
         BOOLEAN legacy_per_port_default_enabled;
         UINT_8 legacy_per_port_default_enabled_mask;
         UINT_32 poe_usage_threshold;
         UINT_8 poe_usage_threshold_mask;
         BOOLEAN legacy_per_port_supported;
         UINT_8 legacy_per_port_supported_mask;
         SYSCONFG_poe_lldp_tx_pattern_type_ENT lldp_tx_pattern;
         UINT_8 lldp_tx_pattern_mask;
         SYSCONFG_poe_ps_rps_mode_ENT poe_ps_rps_mode_value;
         UINT_8 poe_ps_rps_mode_value_mask;
         BOOLEAN poe_port_fault_led_supported;
         UINT_8 poe_port_fault_led_supported_mask;
         BOOLEAN poe_sna_supported;
         UINT_8 poe_sna_supported_mask;
         BOOLEAN poe_pse_power_management_supported;
         UINT_8 poe_pse_power_management_supported_mask;
         SYSCONFG_poe_error_handling_mode_type_ENT error_handling_mode;
         UINT_8 error_handling_mode_mask;
         UINT_32 poe_periodic_polling_get_changes_interval_ms;
         UINT_8 poe_periodic_polling_get_changes_interval_ms_mask;
         SYSCONFG_poe_port_limit_mode_ENT poe_port_mode_value;
         UINT_8 poe_port_mode_value_mask;
         BOOLEAN high_power_default_enabled;
         UINT_8 high_power_default_enabled_mask;
         BOOLEAN poe_port_admin_enable;
         UINT_8 poe_port_admin_enable_mask;
         SYSCONFG_poe_port_max_limit_supported_ENT poe_max_limit_supported;
         UINT_8 poe_max_limit_supported_mask;
         BOOLEAN poe_double_check_port_status;
         UINT_8 poe_double_check_port_status_mask;
         UINT_32 poe_allocation_allowed_threshold;
         UINT_8 poe_allocation_allowed_threshold_mask;
         BOOLEAN poe_telemetry_from_db;
         UINT_8 poe_telemetry_from_db_mask;
         BOOLEAN poe_ignore_fail_num_of_poe_devices;
         UINT_8 poe_ignore_fail_num_of_poe_devices_mask;
         BOOLEAN poe_port_params_from_hw;
         UINT_8 poe_port_params_from_hw_mask;
         UINT_32 poe_oper_per_sec_for_task_overload;
         UINT_8 poe_oper_per_sec_for_task_overload_mask;
         BOOLEAN poe_port_class_limit_supported;
         UINT_8 poe_port_class_limit_supported_mask;
         BOOLEAN power_management_supported;
         UINT_8 power_management_supported_mask;
         BOOLEAN poe_poll_port_counters_supported;
         UINT_8 poe_poll_port_counters_supported_mask;
         BOOLEAN port_limit_supported;
         UINT_8 port_limit_supported_mask;
         UINT_32 poe_unit_sna_event_mid_threshold;
         UINT_8 poe_unit_sna_event_mid_threshold_mask;
         BOOLEAN exit_from_expired_mode;
         UINT_8 exit_from_expired_mode_mask;
         UINT_32 poe_poll_port_counters_interval_gap;
         UINT_8 poe_poll_port_counters_interval_gap_mask;
         BOOLEAN poe_present_port_counters_from_hw;
         UINT_8 poe_present_port_counters_from_hw_mask;
         UINT_32 poe_port_power_limit;
         UINT_8 poe_port_power_limit_mask;
         UINT_32 poe_poll_port_counters_interval;
         UINT_8 poe_poll_port_counters_interval_mask;
         UINT_32 poe_periodic_polling_get_power_changes_interval_ms;
         UINT_8 poe_periodic_polling_get_power_changes_interval_ms_mask;
         UINT_32 poe_power_negotiation_cable_length;
         UINT_8 poe_power_negotiation_cable_length_mask;
         BOOLEAN high_power_supported;
         UINT_8 high_power_supported_mask;
         UINT_32 poe_periodic_polling_vop_ms;
         UINT_8 poe_periodic_polling_vop_ms_mask;
         BOOLEAN poe_perpetual_supported;
         UINT_8 poe_perpetual_supported_mask;
         SYSCONFG_poe_disconnect_method_ENT poe_disconnect_method_value;
         UINT_8 poe_disconnect_method_value_mask;
         UINT_32 poe_unit_sna_event_high_threshold;
         UINT_8 poe_unit_sna_event_high_threshold_mask;
         UINT_32 poe_periodic_polling_change_power_threshold_w;
         UINT_8 poe_periodic_polling_change_power_threshold_w_mask;
         SYSCONFG_poe_tbp_port_status_default_action_mode_ENT poe_tbp_port_status_default_action;
         UINT_8 poe_tbp_port_status_default_action_mask;
         UINT_32 poe_default_guard_band_value;
         UINT_8 poe_default_guard_band_value_mask;
         UINT_32 poe_port_default_power_limit;
         UINT_8 poe_port_default_power_limit_mask;
         SYSCONFG_poe_guard_band_mode_ENT poe_guard_band_mode;
         UINT_8 poe_guard_band_mode_mask;
         SYSCONFG_poe_emergency_support_mode_ENT poe_emergency_support_value;
         UINT_8 poe_emergency_support_value_mask;
         UINT_32 poe_periodic_polling_interval_ms;
         UINT_8 poe_periodic_polling_interval_ms_mask;
         BOOLEAN poe_notification_enable_by_default;
         UINT_8 poe_notification_enable_by_default_mask;
         BOOLEAN l2_half_priority_supported;
         UINT_8 l2_half_priority_supported_mask;
         SYSCONFG_poe_power_management_default_mode_ENT power_management_default_mode;
         UINT_8 power_management_default_mode_mask;
         BOOLEAN poe_pool_disconnect_status;
         UINT_8 poe_pool_disconnect_status_mask;
         SYSCONFG_poe_communication_mode_ENT poe_communication_mode_value;
         UINT_8 poe_communication_mode_value_mask;
         BOOLEAN poe_legacy_supported;
         UINT_8 poe_legacy_supported_mask;
         BOOLEAN poe_advertise_AF_on_class_4_by_default;
         UINT_8 poe_advertise_AF_on_class_4_by_default_mask;
         BOOLEAN time_based_poe_supported;
         UINT_8 time_based_poe_supported_mask;
         BOOLEAN poe_pse_update_supported;
         UINT_8 poe_pse_update_supported_mask;
         UINT_32 port_error_recovery_max_retries;
         UINT_8 port_error_recovery_max_retries_mask;
         UINT_32 poe_port_params_db_update_interval_ms;
         UINT_8 poe_port_params_db_update_interval_ms_mask;
         BOOLEAN poe_class_error_detection_vop_support;
         UINT_8 poe_class_error_detection_vop_support_mask;
         UINT_32 poe_poll_timeout_for_task_overload_ms;
         UINT_8 poe_poll_timeout_for_task_overload_ms_mask;
    } SYSCONFG_POE_params_STC;

    typedef struct 
    {
         UINT_8 special_bpdu_maximum_number_of_entries;
         UINT_8 special_bpdu_maximum_number_of_entries_mask;
    } SYSCONFG_Special_Bpdu_params_STC;

    typedef struct 
    {
         UINT_8 ipv4_default_number_of_policy_routes;
         UINT_8 ipv4_default_number_of_policy_routes_mask;
         UINT_8 ipv6_default_number_of_policy_routes;
         UINT_8 ipv6_default_number_of_policy_routes_mask;
    } SYSCONFG_PBR_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         SYSCONFG_cpu_rate_limit_index_type_TYP cpu_rate_limit_index;
    } PKDB SYSCONFG_cpu_rate_limit_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_cpu_rate_limit_list_keys_STC list_keys;
         char * cpu_rate_limit_description;
         UINT_8 cpu_rate_limit_description_mask;
         SYSCONFG_cpu_rate_limit_rate_type_TYP cpu_rate_limit_rate;
         UINT_8 cpu_rate_limit_rate_mask;
    } SYSCONFG_cpu_rate_limit_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         SYSCONFG_cpld_update_mode_ENT cpld_update_update_mode;
         UINT_8 cpld_update_update_mode_mask;
         BOOLEAN cpld_update_only_newer;
         UINT_8 cpld_update_only_newer_mask;
    } SYSCONFG_CPLD_Update_params_STC;

    typedef enum 
    {
        SYSCONFG_cost_type_stp8021d1998_E = 1,
        SYSCONFG_cost_type_stp8021t2001_E = 2,
        SYSCONFG_cost_type_last_E = 3    
    } SYSCONFG_cost_type_ENT;
    /* SYSCONFG_enum_id_cost_type_E */

    typedef struct 
    {
         UINT_32 maximum_policies;
         UINT_8 maximum_policies_mask;
         UINT_32 maximum_vlan_specified_port_attachemnts;
         UINT_8 maximum_vlan_specified_port_attachemnts_mask;
    } SYSCONFG_DHCPv6_guard_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         SYSCONFG_cpu_traffic_flow_type_ENT cpu_traffic_flow;
    } PKDB SYSCONFG_cpu_traffic_flow_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_cpu_traffic_flow_list_keys_STC list_keys;
         SYSCONFG_cpu_rate_limit_index_type_TYP cpu_rate_limit_index;
         UINT_8 cpu_rate_limit_index_mask;
         SYSCONFG_cpu_queue_id_type_TYP cpu_queue_id;
         UINT_8 cpu_queue_id_mask;
         SYSCONFG_cpu_drop_precedence_type_ENT cpu_drop_precedence;
         UINT_8 cpu_drop_precedence_mask;
    } SYSCONFG_cpu_traffic_flow_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         UINT_8 span_maximum_number_of_sessions;
         UINT_8 span_maximum_number_of_sessions_mask;
         BOOLEAN rspan_is_supported;
         UINT_8 rspan_is_supported_mask;
         UINT_8 span_maximum_number_of_sources_per_session;
         UINT_8 span_maximum_number_of_sources_per_session_mask;
    } SYSCONFG_Span_params_STC;

    typedef enum 
    {
        SYSCONFG_protocol_type_stp_E = 1,
        SYSCONFG_protocol_type_rstp_E = 2,
        SYSCONFG_protocol_type_mstp_E = 3,
        SYSCONFG_protocol_type_pvst_E = 4,
        SYSCONFG_protocol_type_rpvst_E = 5,
        SYSCONFG_protocol_type_last_E = 6    
    } SYSCONFG_protocol_type_ENT;
    /* SYSCONFG_enum_id_protocol_type_E */

    typedef enum 
    {
        SYSCONFG_flood_method_type_classic_E = 1,
        SYSCONFG_flood_method_type_bridging_E = 2,
        SYSCONFG_flood_method_type_last_E = 3    
    } SYSCONFG_flood_method_type_ENT;
    /* SYSCONFG_enum_id_flood_method_type_E */

    typedef struct 
    {
         BOOLEAN dying_gasp_sw_supported;
         UINT_8 dying_gasp_sw_supported_mask;
    } SYSCONFG_Dying_gasp_params_STC;

    typedef struct 
    {
         /* db of type SYSCONFG_cpu_traffic_flow_list_params_STC */ SYSCONFG_DB_HANDLE_TYP cpu_traffic_flow_list_PTR;
         UINT_8 cpu_traffic_flow_list_mask;
         UINT_8 cpu_rate_limit_interval;
         UINT_8 cpu_rate_limit_interval_mask;
         SYSCONFG_cpu_rate_limit_index_type_TYP cpu_undefined_traffic_flow_cpu_rate_limit_index;
         UINT_8 cpu_undefined_traffic_flow_cpu_rate_limit_index_mask;
         /* db of type SYSCONFG_cpu_queue_info_list_params_STC */ SYSCONFG_DB_HANDLE_TYP cpu_queue_info_list_PTR;
         UINT_8 cpu_queue_info_list_mask;
         /* db of type SYSCONFG_cpu_rate_limit_list_params_STC */ SYSCONFG_DB_HANDLE_TYP cpu_rate_limit_list_PTR;
         UINT_8 cpu_rate_limit_list_mask;
         BOOLEAN cpu_rate_limit_is_enabled_by_default;
         UINT_8 cpu_rate_limit_is_enabled_by_default_mask;
         BOOLEAN cpu_counters_supported;
         UINT_8 cpu_counters_supported_mask;
         BOOLEAN cpu_rate_limit_management_support;
         UINT_8 cpu_rate_limit_management_support_mask;
    } SYSCONFG_Traffic_To_CPU_params_STC;

    typedef struct 
    {
         UINT_32 maximum_policies;
         UINT_8 maximum_policies_mask;
         UINT_32 maximum_vlan_specified_port_attachemnts;
         UINT_8 maximum_vlan_specified_port_attachemnts_mask;
    } SYSCONFG_FHS_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         UINT_16 ifindex;
    } PKDB SYSCONFG_auto_edge_port_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_auto_edge_port_list_keys_STC list_keys;
    } SYSCONFG_auto_edge_port_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         SYSCONFG_BNEP_params_STC BNEP;
         UINT_8 BNEP_mask;
         BOOLEAN Bluetooth_enabled_by_default;
         UINT_8 Bluetooth_enabled_by_default_mask;
         BOOLEAN BLE_HPS_is_supported;
         UINT_8 BLE_HPS_is_supported_mask;
         UINT_32 Default_PIN;
         UINT_8 Default_PIN_mask;
         BOOLEAN BNEP_feature_is_supported;
         UINT_8 BNEP_feature_is_supported_mask;
    } SYSCONFG_Bluetooth_params_STC;

    typedef struct 
    {
         UINT_8 fdb_hash_chain_length_resolution;
         UINT_8 fdb_hash_chain_length_resolution_mask;
         UINT_8 fdb_violation_delay_factor;
         UINT_8 fdb_violation_delay_factor_mask;
         UINT_8 fdb_collision_syslog_rate_limit;
         UINT_8 fdb_collision_syslog_rate_limit_mask;
         UINT_16 fdb_default_aging_time;
         UINT_8 fdb_default_aging_time_mask;
         UINT_16 fdb_maximum_aging_time;
         UINT_8 fdb_maximum_aging_time_mask;
         UINT_16 fdb_minimum_aging_time;
         UINT_8 fdb_minimum_aging_time_mask;
         UINT_32 fdb_maximum_size;
         UINT_8 fdb_maximum_size_mask;
         UINT_32 fdb_maximum_static_delete_on_reset_addresses;
         UINT_8 fdb_maximum_static_delete_on_reset_addresses_mask;
         UINT_8 fdb_maximum_hash_chain_length;
         UINT_8 fdb_maximum_hash_chain_length_mask;
         BOOLEAN fdb_bulk_is_supported;
         UINT_8 fdb_bulk_is_supported_mask;
         UINT_8 fdb_hash_chain_length;
         UINT_8 fdb_hash_chain_length_mask;
         UINT_8 fdb_minimum_hash_chain_length;
         UINT_8 fdb_minimum_hash_chain_length_mask;
         BOOLEAN fdb_storm_prevention_is_enabled;
         UINT_8 fdb_storm_prevention_is_enabled_mask;
         BOOLEAN fdb_manager_is_supported;
         UINT_8 fdb_manager_is_supported_mask;
    } SYSCONFG_Fdb_params_STC;

    typedef struct 
    {
         UINT_32 maximum_policies;
         UINT_8 maximum_policies_mask;
         UINT_32 maximum_vlan_specified_port_attachemnts;
         UINT_8 maximum_vlan_specified_port_attachemnts_mask;
    } SYSCONFG_RA_guard_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         SYSCONFG_protocol_type_ENT protocol_type_index;
    } PKDB SYSCONFG_supported_protocol_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_supported_protocol_list_keys_STC list_keys;
    } SYSCONFG_supported_protocol_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         BOOLEAN dummy_is_link_status_and_suspend;
         UINT_8 dummy_is_link_status_and_suspend_mask;
    } SYSCONFG_ErrDisable_led_params_STC;

    typedef struct 
    {
         UINT_32 maximum_policies;
         UINT_8 maximum_policies_mask;
         UINT_32 maximum_vlan_specified_port_attachemnts;
         UINT_8 maximum_vlan_specified_port_attachemnts_mask;
    } SYSCONFG_ND_inspection_params_STC;

    typedef struct 
    {
         BOOLEAN root_guard_supported;
         UINT_8 root_guard_supported_mask;
         BOOLEAN mstp_logical_instances_supported;
         UINT_8 mstp_logical_instances_supported_mask;
         BOOLEAN enabled_on_ports;
         UINT_8 enabled_on_ports_mask;
         /* db of type SYSCONFG_supported_protocol_list_params_STC */ SYSCONFG_DB_HANDLE_TYP supported_protocol_list_PTR;
         UINT_8 supported_protocol_list_mask;
         BOOLEAN port_must_belong_to_vlan_by_default;
         UINT_8 port_must_belong_to_vlan_by_default_mask;
         SYSCONFG_cost_type_ENT default_cost_format;
         UINT_8 default_cost_format_mask;
         UINT_8 max_mstp_instances;
         UINT_8 max_mstp_instances_mask;
         BOOLEAN stp_disabled_port_state_supported;
         UINT_8 stp_disabled_port_state_supported_mask;
         UINT_16 mstp_max_logical_instance;
         UINT_8 mstp_max_logical_instance_mask;
         BOOLEAN edge_port_in_stp_supported;
         UINT_8 edge_port_in_stp_supported_mask;
         SYSCONFG_protocol_type_ENT default_protocol;
         UINT_8 default_protocol_mask;
         UINT_32 max_stp_hw_instances;
         UINT_8 max_stp_hw_instances_mask;
         BOOLEAN flood_bpdu_by_default;
         UINT_8 flood_bpdu_by_default_mask;
         BOOLEAN loopback_guard_enabled_by_default;
         UINT_8 loopback_guard_enabled_by_default_mask;
         BOOLEAN tcn_guard_supported;
         UINT_8 tcn_guard_supported_mask;
         SYSCONFG_flood_method_type_ENT flood_bpdu_method;
         UINT_8 flood_bpdu_method_mask;
         BOOLEAN loopback_guard_supported;
         UINT_8 loopback_guard_supported_mask;
         BOOLEAN bpdu_guard_supported;
         UINT_8 bpdu_guard_supported_mask;
         BOOLEAN enabled;
         UINT_8 enabled_mask;
         UINT_32 max_user_stp_instances;
         UINT_8 max_user_stp_instances_mask;
         UINT_32 pvst_max_vlans;
         UINT_8 pvst_max_vlans_mask;
         /* db of type SYSCONFG_auto_edge_port_list_params_STC */ SYSCONFG_DB_HANDLE_TYP auto_edge_port_list_PTR;
         UINT_8 auto_edge_port_list_mask;
    } SYSCONFG_Stp_params_STC;

    typedef struct 
    {
         UINT_32 num_of_rx_bufs_jumbo_frames_disabled;
         UINT_8 num_of_rx_bufs_jumbo_frames_disabled_mask;
         UINT_32 num_of_tx_bufs_jumbo_frames_enabled;
         UINT_8 num_of_tx_bufs_jumbo_frames_enabled_mask;
         UINT_32 num_of_tx_bufs_jumbo_frames_disabled;
         UINT_8 num_of_tx_bufs_jumbo_frames_disabled_mask;
         UINT_32 max_num_of_udi_bufs;
         UINT_8 max_num_of_udi_bufs_mask;
         BOOLEAN jumbo_frame_enabled_by_default;
         UINT_8 jumbo_frame_enabled_by_default_mask;
         BOOLEAN mini_jumbo_frame_enabled_by_default;
         UINT_8 mini_jumbo_frame_enabled_by_default_mask;
         UINT_32 num_of_rx_bufs_jumbo_frames_enabled;
         UINT_8 num_of_rx_bufs_jumbo_frames_enabled_mask;
    } SYSCONFG_Jumbo_Frame_params_STC;

    typedef struct 
    {
         UINT_32 maximum_policies;
         UINT_8 maximum_policies_mask;
         UINT_32 maximum_prefixes;
         UINT_8 maximum_prefixes_mask;
         UINT_32 maximum_bindings;
         UINT_8 maximum_bindings_mask;
         UINT_32 maximum_vlan_specified_port_attachemnts;
         UINT_8 maximum_vlan_specified_port_attachemnts_mask;
    } SYSCONFG_NBI_params_STC;

    typedef struct 
    {
         BOOLEAN Signal_Stability_feature_is_supported;
         UINT_8 Signal_Stability_feature_is_supported_mask;
         SYSCONFG_auto_neg_preference_params_STC auto_neg_preference;
         UINT_8 auto_neg_preference_mask;
         BOOLEAN POE_feature_is_supported;
         UINT_8 POE_feature_is_supported_mask;
         SYSCONFG_EEE_params_STC EEE;
         UINT_8 EEE_mask;
         BOOLEAN Fiber_feature_is_supported;
         UINT_8 Fiber_feature_is_supported_mask;
         SYSCONFG_Jumbo_Frame_params_STC Jumbo_Frame;
         UINT_8 Jumbo_Frame_mask;
         SYSCONFG_Fiber_params_STC Fiber;
         UINT_8 Fiber_mask;
         SYSCONFG_Signal_Stability_params_STC Signal_Stability;
         UINT_8 Signal_Stability_mask;
         SYSCONFG_ErrDisable_led_params_STC ErrDisable_led;
         UINT_8 ErrDisable_led_mask;
         BOOLEAN Ap_feature_is_supported;
         UINT_8 Ap_feature_is_supported_mask;
         SYSCONFG_Port_Manager_params_STC Port_Manager;
         UINT_8 Port_Manager_mask;
         SYSCONFG_Locate_Unit_params_STC Locate_Unit;
         UINT_8 Locate_Unit_mask;
         SYSCONFG_Rx_Training_params_STC Rx_Training;
         UINT_8 Rx_Training_mask;
         BOOLEAN Rx_Training_feature_is_supported;
         UINT_8 Rx_Training_feature_is_supported_mask;
         BOOLEAN ErrDisable_led_feature_is_supported;
         UINT_8 ErrDisable_led_feature_is_supported_mask;
         BOOLEAN Port_Manager_feature_is_supported;
         UINT_8 Port_Manager_feature_is_supported_mask;
         SYSCONFG_Flow_Control_params_STC Flow_Control;
         UINT_8 Flow_Control_mask;
         SYSCONFG_Locate_Port_params_STC Locate_Port;
         UINT_8 Locate_Port_mask;
         BOOLEAN Locate_Port_feature_is_supported;
         UINT_8 Locate_Port_feature_is_supported_mask;
         BOOLEAN Green_feature_is_supported;
         UINT_8 Green_feature_is_supported_mask;
         BOOLEAN auto_neg_preference_feature_is_supported;
         UINT_8 auto_neg_preference_feature_is_supported_mask;
         BOOLEAN I2C_Syslog_feature_is_supported;
         UINT_8 I2C_Syslog_feature_is_supported_mask;
         SYSCONFG_I2C_Syslog_params_STC I2C_Syslog;
         UINT_8 I2C_Syslog_mask;
         SYSCONFG_Dying_gasp_params_STC Dying_gasp;
         UINT_8 Dying_gasp_mask;
         SYSCONFG_Green_params_STC Green;
         UINT_8 Green_mask;
         BOOLEAN CPLD_Update_feature_is_supported;
         UINT_8 CPLD_Update_feature_is_supported_mask;
         SYSCONFG_hw_interface_params_STC hw_interface;
         UINT_8 hw_interface_mask;
         BOOLEAN Bluetooth_feature_is_supported;
         UINT_8 Bluetooth_feature_is_supported_mask;
         BOOLEAN Locate_Unit_feature_is_supported;
         UINT_8 Locate_Unit_feature_is_supported_mask;
         BOOLEAN Jumbo_Frame_feature_is_supported;
         UINT_8 Jumbo_Frame_feature_is_supported_mask;
         SYSCONFG_POE_params_STC POE;
         UINT_8 POE_mask;
         SYSCONFG_Link_Flapping_Prevention_params_STC Link_Flapping_Prevention;
         UINT_8 Link_Flapping_Prevention_mask;
         BOOLEAN Flow_Control_feature_is_supported;
         UINT_8 Flow_Control_feature_is_supported_mask;
         BOOLEAN EEE_feature_is_supported;
         UINT_8 EEE_feature_is_supported_mask;
         BOOLEAN Dying_Gasp_feature_is_supported;
         UINT_8 Dying_Gasp_feature_is_supported_mask;
         SYSCONFG_Bluetooth_params_STC Bluetooth;
         UINT_8 Bluetooth_mask;
         SYSCONFG_Ap_params_STC Ap;
         UINT_8 Ap_mask;
         BOOLEAN UDLD_feature_is_supported;
         UINT_8 UDLD_feature_is_supported_mask;
         BOOLEAN Link_Flapping_Prevention_feature_is_supported;
         UINT_8 Link_Flapping_Prevention_feature_is_supported_mask;
         SYSCONFG_UDLD_params_STC UDLD;
         UINT_8 UDLD_mask;
         SYSCONFG_CPLD_Update_params_STC CPLD_Update;
         UINT_8 CPLD_Update_mask;
         BOOLEAN hw_interface_feature_is_supported;
         UINT_8 hw_interface_feature_is_supported_mask;
    } SYSCONFG_L1_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         char ouiPrefix[128];
    } PKDB SYSCONFG_oui_default_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_oui_default_list_keys_STC list_keys;
         char * description;
         UINT_8 description_mask;
    } SYSCONFG_oui_default_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         UINT_32 maximum_number_of_vlans_enabled;
         UINT_8 maximum_number_of_vlans_enabled_mask;
         UINT_32 maximum_policies;
         UINT_8 maximum_policies_mask;
         UINT_32 maximum_vlan_specified_port_attachemnts;
         UINT_8 maximum_vlan_specified_port_attachemnts_mask;
    } SYSCONFG_Source_guard_params_STC;

    typedef struct 
    {
         UINT_8 maximum_number_of_oui_and_mac_addresses;
         UINT_8 maximum_number_of_oui_and_mac_addresses_mask;
         UINT_16 maximum_number_of_learned_mac_addresses;
         UINT_8 maximum_number_of_learned_mac_addresses_mask;
         /* db of type SYSCONFG_oui_default_list_params_STC */ SYSCONFG_DB_HANDLE_TYP oui_default_list_PTR;
         UINT_8 oui_default_list_mask;
    } SYSCONFG_Vlan_Surveillance_Vlan_params_STC;

    typedef struct 
    {
         SYSCONFG_vlan_switchport_mode_type_ENT vlan_switchport_mode;
         UINT_8 vlan_switchport_mode_mask;
         SYSCONFG_Vlan_Voice_Auto_Vlan_params_STC Vlan_Voice_Auto_Vlan;
         UINT_8 Vlan_Voice_Auto_Vlan_mask;
         SYSCONFG_vlan_default_port_mode_type_ENT vlan_default_port_mode;
         UINT_8 vlan_default_port_mode_mask;
         BOOLEAN Vlan_Voice_Vlan_Auto_feature_is_supported;
         UINT_8 Vlan_Voice_Vlan_Auto_feature_is_supported_mask;
         BOOLEAN vlan_triple_play_is_supported;
         UINT_8 vlan_triple_play_is_supported_mask;
         SYSCONFG_vlan_port_model_type_ENT vlan_port_model_mode;
         UINT_8 vlan_port_model_mode_mask;
         BOOLEAN Vlan_Mapping_feature_is_supported;
         UINT_8 Vlan_Mapping_feature_is_supported_mask;
         BOOLEAN Vlan_Multicast_Tv_Vlan_feature_is_supported;
         UINT_8 Vlan_Multicast_Tv_Vlan_feature_is_supported_mask;
         SYSCONFG_Vlan_Default_Vlan_params_STC Vlan_Default_Vlan;
         UINT_8 Vlan_Default_Vlan_mask;
         BOOLEAN vlan_ingress_filtering_default_value;
         UINT_8 vlan_ingress_filtering_default_value_mask;
         BOOLEAN vlan_pve_group_is_supported;
         UINT_8 vlan_pve_group_is_supported_mask;
         SYSCONFG_vlan_acceptable_frame_type_ENT vlan_acceptable_frame_mode;
         UINT_8 vlan_acceptable_frame_mode_mask;
         BOOLEAN vlan_general_mode_only_is_supported;
         UINT_8 vlan_general_mode_only_is_supported_mask;
         UINT_32 number_of_vlans;
         UINT_8 number_of_vlans_mask;
         SYSCONFG_Vlan_Voice_Vlan_params_STC Vlan_Voice_Vlan;
         UINT_8 Vlan_Voice_Vlan_mask;
         BOOLEAN Vlan_Private_Vlan_feature_is_supported;
         UINT_8 Vlan_Private_Vlan_feature_is_supported_mask;
         BOOLEAN Vlan_Default_Vlan_feature_is_supported;
         UINT_8 Vlan_Default_Vlan_feature_is_supported_mask;
         SYSCONFG_Vlan_Multicast_Tv_Vlan_params_STC Vlan_Multicast_Tv_Vlan;
         UINT_8 Vlan_Multicast_Tv_Vlan_mask;
         SYSCONFG_vlan_default_trunk_port_mode_membership_type_ENT vlan_default_trunk_port_mode_membership;
         UINT_8 vlan_default_trunk_port_mode_membership_mask;
         SYSCONFG_Vlan_Mapping_params_STC Vlan_Mapping;
         UINT_8 Vlan_Mapping_mask;
         BOOLEAN vlan_dot1v_is_supported;
         UINT_8 vlan_dot1v_is_supported_mask;
         BOOLEAN vlan_auto_creation_is_supported;
         UINT_8 vlan_auto_creation_is_supported_mask;
         SYSCONFG_Vlan_Dot1x_Extensions_params_STC Vlan_Dot1x_Extensions;
         UINT_8 Vlan_Dot1x_Extensions_mask;
         BOOLEAN Vlan_Mac_Base_Vlan_feature_is_supported;
         UINT_8 Vlan_Mac_Base_Vlan_feature_is_supported_mask;
         BOOLEAN vlan_pve_is_supported;
         UINT_8 vlan_pve_is_supported_mask;
         BOOLEAN vlan_qinq_is_supported;
         UINT_8 vlan_qinq_is_supported_mask;
         SYSCONFG_Vlan_Mac_Base_Vlan_params_STC Vlan_Mac_Base_Vlan;
         UINT_8 Vlan_Mac_Base_Vlan_mask;
         SYSCONFG_vlan_human_type_ENT vlan_human_mode;
         UINT_8 vlan_human_mode_mask;
         BOOLEAN Vlan_Voice_Vlan_feature_is_supported;
         UINT_8 Vlan_Voice_Vlan_feature_is_supported_mask;
         BOOLEAN Vlan_Dot1x_Extensions_feature_is_supported;
         UINT_8 Vlan_Dot1x_Extensions_feature_is_supported_mask;
         BOOLEAN Vlan_Subnet_Base_Vlan_feature_is_supported;
         UINT_8 Vlan_Subnet_Base_Vlan_feature_is_supported_mask;
         SYSCONFG_Vlan_Surveillance_Vlan_params_STC Vlan_Surveillance_Vlan;
         UINT_8 Vlan_Surveillance_Vlan_mask;
         UINT_16 vlan_dynamic_number_of_mac_entries;
         UINT_8 vlan_dynamic_number_of_mac_entries_mask;
         BOOLEAN vlan_acceptable_frame_type_untagged_is_supported;
         UINT_8 vlan_acceptable_frame_type_untagged_is_supported_mask;
         BOOLEAN Vlan_Surveillance_Vlan_feature_is_supported;
         UINT_8 Vlan_Surveillance_Vlan_feature_is_supported_mask;
         SYSCONFG_Vlan_Subnet_Base_Vlan_params_STC Vlan_Subnet_Base_Vlan;
         UINT_8 Vlan_Subnet_Base_Vlan_mask;
         SYSCONFG_Vlan_Private_Vlan_params_STC Vlan_Private_Vlan;
         UINT_8 Vlan_Private_Vlan_mask;
    } SYSCONFG_Vlan_params_STC;

    typedef struct 
    {
         UINT_16 maximum_number_of_tunnel_termination_entries;
         UINT_8 maximum_number_of_tunnel_termination_entries_mask;
         BOOLEAN Six2four_Tunnel_feature_is_supported;
         UINT_8 Six2four_Tunnel_feature_is_supported_mask;
         BOOLEAN ipv6_configured_tunnel_is_supported;
         UINT_8 ipv6_configured_tunnel_is_supported_mask;
         UINT_16 maximum_number_of_tunnel_mac_to_me_entries;
         UINT_8 maximum_number_of_tunnel_mac_to_me_entries_mask;
         SYSCONFG_Six2four_Tunnel_params_STC Six2four_Tunnel;
         UINT_8 Six2four_Tunnel_mask;
         BOOLEAN ISATAP_feature_is_supported;
         UINT_8 ISATAP_feature_is_supported_mask;
         UINT_16 maximum_number_of_tunnel_start_entries;
         UINT_8 maximum_number_of_tunnel_start_entries_mask;
         BOOLEAN ipv6_hardware_tunnel_is_enabled;
         UINT_8 ipv6_hardware_tunnel_is_enabled_mask;
         SYSCONFG_ISATAP_Tunnel_params_STC ISATAP_Tunnel;
         UINT_8 ISATAP_Tunnel_mask;
    } SYSCONFG_Tunnel_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         UINT_16 ifindex;
    } PKDB SYSCONFG_internal_ports_set_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_internal_ports_set_keys_STC list_keys;
    } SYSCONFG_internal_ports_set_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_LLDP_Snoop_params_STC;

    typedef struct 
    {
         /* db of type SYSCONFG_internal_ports_set_params_STC */ SYSCONFG_DB_HANDLE_TYP internal_ports_set_PTR;
         UINT_8 internal_ports_set_mask;
    } SYSCONFG_Internal_port_params_STC;

    typedef struct 
    {
         BOOLEAN pvid_tlv_default_enable;
         UINT_8 pvid_tlv_default_enable_mask;
         UINT_32 poe_num_of_obs;
         UINT_8 poe_num_of_obs_mask;
         BOOLEAN med_netpolicy_voice_auto_show;
         UINT_8 med_netpolicy_voice_auto_show_mask;
         UINT_32 lldp_med_maximum_number_of_network_policies;
         UINT_8 lldp_med_maximum_number_of_network_policies_mask;
         SYSCONFG_lldp_advertise_ma_selection_manner_type_ENT ma_advertise_selection_manner_by_default;
         UINT_8 ma_advertise_selection_manner_by_default_mask;
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
         BOOLEAN notification_default_enabled;
         UINT_8 notification_default_enabled_mask;
         BOOLEAN ma_auto_select_is_supported;
         UINT_8 ma_auto_select_is_supported_mask;
         BOOLEAN lldp_med_default_enable;
         UINT_8 lldp_med_default_enable_mask;
         BOOLEAN med_netpolicy_voice_auto;
         UINT_8 med_netpolicy_voice_auto_mask;
         UINT_32 lldp_med_maximum_number_of_location_IDs;
         UINT_8 lldp_med_maximum_number_of_location_IDs_mask;
         BOOLEAN dot1_tlv_is_supported;
         UINT_8 dot1_tlv_is_supported_mask;
         SYSCONFG_optional_tlvs_tx_default_enabled_bits_type_TYP optional_tlvs_tx_default_enabled;
         UINT_8 optional_tlvs_tx_default_enabled_mask;
         UINT_8 lldp_med_fast_start_duration;
         UINT_8 lldp_med_fast_start_duration_mask;
         UINT_32 maximum_ht_vlan_entries_amount;
         UINT_8 maximum_ht_vlan_entries_amount_mask;
         BOOLEAN transmit_default_IP_on_all_ports_by_default;
         UINT_8 transmit_default_IP_on_all_ports_by_default_mask;
         UINT_32 maximum_number_of_neighbor_hosts;
         UINT_8 maximum_number_of_neighbor_hosts_mask;
         BOOLEAN lldp_med_topology_change_notification;
         UINT_8 lldp_med_topology_change_notification_mask;
         BOOLEAN lldp_pdu_flooding_mode_is_supported;
         UINT_8 lldp_pdu_flooding_mode_is_supported_mask;
         BOOLEAN med_extpoe_tlv_default_enable;
         UINT_8 med_extpoe_tlv_default_enable_mask;
         BOOLEAN poe_4wire_tlv_default_enable;
         UINT_8 poe_4wire_tlv_default_enable_mask;
         SYSCONFG_lldp_port_id_format_type_ENT port_id_default_format;
         UINT_8 port_id_default_format_mask;
         BOOLEAN dot3_power_via_mdi_tlv_default_enable;
         UINT_8 dot3_power_via_mdi_tlv_default_enable_mask;
         UINT_16 txDelay_default_value;
         UINT_8 txDelay_default_value_mask;
         BOOLEAN med_netpolicy_tlv_default_enable;
         UINT_8 med_netpolicy_tlv_default_enable_mask;
    } SYSCONFG_LLDP_params_STC;

    typedef struct 
    {
         BOOLEAN Internal_port_feature_is_supported;
         UINT_8 Internal_port_feature_is_supported_mask;
         BOOLEAN tbp_supported;
         UINT_8 tbp_supported_mask;
         SYSCONFG_Internal_port_params_STC Internal_port;
         UINT_8 Internal_port_mask;
         SYSCONFG_supported_speeds_bits_type_TYP oob_supported_speeds;
         UINT_8 oob_supported_speeds_mask;
         SYSCONFG_supported_speeds_bits_type_TYP supported_speeds;
         UINT_8 supported_speeds_mask;
         UINT_32 recovery_defRecovery_Timeout;
         UINT_8 recovery_defRecovery_Timeout_mask;
         UINT_32 last_logical_port_ifIndex;
         UINT_8 last_logical_port_ifIndex_mask;
         BOOLEAN recovery_is_supported;
         UINT_8 recovery_is_supported_mask;
         UINT_8 tbp_port_status_default_action;
         UINT_8 tbp_port_status_default_action_mask;
         BOOLEAN oob_supported;
         UINT_8 oob_supported_mask;
         UINT_32 first_logical_port_ifIndex;
         UINT_8 first_logical_port_ifIndex_mask;
         SYSCONFG_supported_speeds_bits_type_TYP port_supported_speeds_bitmap;
         UINT_8 port_supported_speeds_bitmap_mask;
         BOOLEAN recovery_is_enabled_by_default;
         UINT_8 recovery_is_enabled_by_default_mask;
         UINT_8 tbp_max_number_ranges_on_port;
         UINT_8 tbp_max_number_ranges_on_port_mask;
    } SYSCONFG_Port_params_STC;

    typedef struct 
    {
         char * cdp_device_id_format_other;
         UINT_8 cdp_device_id_format_other_mask;
         SYSCONFG_cdp_default_device_id_format_type_ENT cdp_default_device_id_format;
         UINT_8 cdp_default_device_id_format_mask;
         BOOLEAN cdp_is_enabled;
         UINT_8 cdp_is_enabled_mask;
         SYSCONFG_cdp_advertised_version_type_ENT cdp_advertised_version;
         UINT_8 cdp_advertised_version_mask;
         UINT_16 cdp_secondary_cache_size;
         UINT_8 cdp_secondary_cache_size_mask;
         UINT_16 cdp_main_cache_size;
         UINT_8 cdp_main_cache_size_mask;
    } SYSCONFG_Cdp_params_STC;

    typedef struct 
    {
         UINT_16 maximum_number_of_static_sessions;
         UINT_8 maximum_number_of_static_sessions_mask;
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
         UINT_16 maximum_number_of_active_fcf;
         UINT_8 maximum_number_of_active_fcf_mask;
         UINT_16 maximum_number_of_dynamic_sessions;
         UINT_8 maximum_number_of_dynamic_sessions_mask;
         UINT_16 maximum_number_of_fcf_in_global_mac_list;
         UINT_8 maximum_number_of_fcf_in_global_mac_list_mask;
    } SYSCONFG_FIP_params_STC;

    typedef struct 
    {
         BOOLEAN control_bridge;
         UINT_8 control_bridge_mask;
         BOOLEAN upstream_trunk_is_supported;
         UINT_8 upstream_trunk_is_supported_mask;
         UINT_16 maximum_number_of_multicast_echannels;
         UINT_8 maximum_number_of_multicast_echannels_mask;
         UINT_16 maximum_number_of_unicast_echannels;
         UINT_8 maximum_number_of_unicast_echannels_mask;
    } SYSCONFG_PE_params_STC;

    typedef struct 
    {
         UINT_32 default_up_status_timer_in_milliseconds;
         UINT_8 default_up_status_timer_in_milliseconds_mask;
         UINT_32 default_down_status_timer_in_milliseconds;
         UINT_8 default_down_status_timer_in_milliseconds_mask;
    } SYSCONFG_L2_Link_stability_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_pfc_priorities;
         UINT_8 maximum_number_of_pfc_priorities_mask;
         BOOLEAN dcbx_is_supported;
         UINT_8 dcbx_is_supported_mask;
         BOOLEAN qcn_is_supported;
         UINT_8 qcn_is_supported_mask;
         BOOLEAN ets_is_supported;
         UINT_8 ets_is_supported_mask;
         BOOLEAN pfc_is_supported;
         UINT_8 pfc_is_supported_mask;
    } SYSCONFG_DCE_params_STC;

    typedef struct 
    {
         BOOLEAN sflow_global_sampling_sessions_is_supported;
         UINT_8 sflow_global_sampling_sessions_is_supported_mask;
         UINT_8 sflow_max_number_of_global_sampling_sessions;
         UINT_8 sflow_max_number_of_global_sampling_sessions_mask;
    } SYSCONFG_SFLOW_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_MAC_security_params_STC;

    typedef struct 
    {
         BOOLEAN radius_attributes_acl_name_is_supported;
         UINT_8 radius_attributes_acl_name_is_supported_mask;
         UINT_16 maximum_number_of_credentials;
         UINT_8 maximum_number_of_credentials_mask;
         BOOLEAN default_system_authentication_control_is_enabled;
         UINT_8 default_system_authentication_control_is_enabled_mask;
         BOOLEAN multi_sessions_host_mode_is_supported;
         UINT_8 multi_sessions_host_mode_is_supported_mask;
         UINT_16 maximum_sessions_number;
         UINT_8 maximum_sessions_number_mask;
         SYSCONFG_single_host_violation_bits_type_TYP single_host_violation_action_mode_is_supported;
         UINT_8 single_host_violation_action_mode_is_supported_mask;
         UINT_16 eap_request_default_entries_number;
         UINT_8 eap_request_default_entries_number_mask;
         BOOLEAN multi_sessions_legacy_is_supported;
         UINT_8 multi_sessions_legacy_is_supported_mask;
         BOOLEAN authentication_open_mode_is_supported;
         UINT_8 authentication_open_mode_is_supported_mask;
         SYSCONFG_Dot1x_mac_authentication_params_STC Dot1x_mac_authentication;
         UINT_8 Dot1x_mac_authentication_mask;
         SYSCONFG_single_host_violation_bits_type_TYP single_host_violation_trap_mode_is_supported;
         UINT_8 single_host_violation_trap_mode_is_supported_mask;
         BOOLEAN system_monitor_vlan_mode_is_supported;
         UINT_8 system_monitor_vlan_mode_is_supported_mask;
         BOOLEAN default_multi_sessions_legacy_mode_is_enabled;
         UINT_8 default_multi_sessions_legacy_mode_is_enabled_mask;
         BOOLEAN supplicant_is_supported;
         UINT_8 supplicant_is_supported_mask;
         SYSCONFG_dot1x_host_default_mode_type_ENT host_default_mode;
         UINT_8 host_default_mode_mask;
         BOOLEAN time_based_is_supported;
         UINT_8 time_based_is_supported_mask;
         SYSCONFG_dot1x_port_default_mode_type_ENT port_default_mode;
         UINT_8 port_default_mode_mask;
         BOOLEAN Dot1x_mac_authentication_feature_is_supported;
         UINT_8 Dot1x_mac_authentication_feature_is_supported_mask;
    } SYSCONFG_Dot1x_params_STC;

    typedef struct 
    {
         UINT_16 maximum_number_of_ports_in_static_lag;
         UINT_8 maximum_number_of_ports_in_static_lag_mask;
         BOOLEAN load_balance_per_lag;
         UINT_8 load_balance_per_lag_mask;
         UINT_32 first_lag_ifIndex;
         UINT_8 first_lag_ifIndex_mask;
         SYSCONFG_lacp_port_membership_in_lag_type_ENT lacp_port_membership_in_lag_mode;
         UINT_8 lacp_port_membership_in_lag_mode_mask;
         SYSCONFG_lag_creation_type_ENT lag_creation_supported_mode;
         UINT_8 lag_creation_supported_mode_mask;
         UINT_16 maximum_number_of_candidates_ports_in_lacp;
         UINT_8 maximum_number_of_candidates_ports_in_lacp_mask;
         BOOLEAN lacp_membership_restrictions_is_supported;
         UINT_8 lacp_membership_restrictions_is_supported_mask;
         UINT_16 number_of_lags;
         UINT_8 number_of_lags_mask;
         SYSCONFG_lag_balance_layer_type_ENT default_lag_balance_layer;
         UINT_8 default_lag_balance_layer_mask;
    } SYSCONFG_LAG_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_communities;
         UINT_8 maximum_number_of_communities_mask;
         BOOLEAN communities_are_supported;
         UINT_8 communities_are_supported_mask;
         BOOLEAN traffic_segmentation_is_supported;
         UINT_8 traffic_segmentation_is_supported_mask;
    } SYSCONFG_Protected_ports_params_STC;

    typedef struct 
    {
         BOOLEAN DHCP_spoofing_is_supported;
         UINT_8 DHCP_spoofing_is_supported_mask;
         SYSCONFG_ARP_inspection_params_STC ARP_inspection;
         UINT_8 ARP_inspection_mask;
         SYSCONFG_IP_source_guard_params_STC IP_source_guard;
         UINT_8 IP_source_guard_mask;
         SYSCONFG_DHCP_snooping_params_STC DHCP_snooping;
         UINT_8 DHCP_snooping_mask;
         BOOLEAN DHCP_snooping_feature_is_supported;
         UINT_8 DHCP_snooping_feature_is_supported_mask;
         BOOLEAN ARP_inspection_feature_is_supported;
         UINT_8 ARP_inspection_feature_is_supported_mask;
         BOOLEAN IP_source_guard_feature_is_supported;
         UINT_8 IP_source_guard_feature_is_supported_mask;
    } SYSCONFG_Bridge_security_applications_params_STC;

    typedef struct 
    {
         SYSCONFG_MAC_security_params_STC MAC_security;
         UINT_8 MAC_security_mask;
         SYSCONFG_DCE_params_STC DCE;
         UINT_8 DCE_mask;
         SYSCONFG_Span_params_STC Span;
         UINT_8 Span_mask;
         SYSCONFG_Port_Lock_params_STC Port_Lock;
         UINT_8 Port_Lock_mask;
         BOOLEAN PE_feature_is_supported;
         UINT_8 PE_feature_is_supported_mask;
         BOOLEAN Bridge_MC_feature_is_supported;
         UINT_8 Bridge_MC_feature_is_supported_mask;
         BOOLEAN Storm_Control_feature_is_supported;
         UINT_8 Storm_Control_feature_is_supported_mask;
         SYSCONFG_Vidx_params_STC Vidx;
         UINT_8 Vidx_mask;
         BOOLEAN Stp_feature_is_supported;
         UINT_8 Stp_feature_is_supported_mask;
         SYSCONFG_Traffic_To_CPU_params_STC Traffic_To_CPU;
         UINT_8 Traffic_To_CPU_mask;
         BOOLEAN Port_feature_is_supported;
         UINT_8 Port_feature_is_supported_mask;
         BOOLEAN Vlan_feature_is_supported;
         UINT_8 Vlan_feature_is_supported_mask;
         BOOLEAN SFLOW_feature_is_supported;
         UINT_8 SFLOW_feature_is_supported_mask;
         BOOLEAN L2_Link_stability_feature_is_supported;
         UINT_8 L2_Link_stability_feature_is_supported_mask;
         SYSCONFG_LLDP_Snoop_params_STC LLDP_Snoop;
         UINT_8 LLDP_Snoop_mask;
         SYSCONFG_Loopback_Detection_params_STC Loopback_Detection;
         UINT_8 Loopback_Detection_mask;
         BOOLEAN LAG_feature_is_supported;
         UINT_8 LAG_feature_is_supported_mask;
         BOOLEAN MAC_security_feature_is_supported;
         UINT_8 MAC_security_feature_is_supported_mask;
         BOOLEAN Span_feature_is_supported;
         UINT_8 Span_feature_is_supported_mask;
         BOOLEAN LLDP_Snoop_feature_is_supported;
         UINT_8 LLDP_Snoop_feature_is_supported_mask;
         BOOLEAN Traffic_To_CPU_feature_is_supported;
         UINT_8 Traffic_To_CPU_feature_is_supported_mask;
         BOOLEAN FIP_feature_is_supported;
         UINT_8 FIP_feature_is_supported_mask;
         BOOLEAN Cdp_feature_is_supported;
         UINT_8 Cdp_feature_is_supported_mask;
         SYSCONFG_PE_params_STC PE;
         UINT_8 PE_mask;
         SYSCONFG_Cdp_params_STC Cdp;
         UINT_8 Cdp_mask;
         BOOLEAN Protected_ports_feature_is_supported;
         UINT_8 Protected_ports_feature_is_supported_mask;
         SYSCONFG_FIP_params_STC FIP;
         UINT_8 FIP_mask;
         SYSCONFG_Fdb_params_STC Fdb;
         UINT_8 Fdb_mask;
         BOOLEAN Special_Bpdu_feature_is_supported;
         UINT_8 Special_Bpdu_feature_is_supported_mask;
         SYSCONFG_SFLOW_params_STC SFLOW;
         UINT_8 SFLOW_mask;
         BOOLEAN DCE_feature_is_supported;
         UINT_8 DCE_feature_is_supported_mask;
         SYSCONFG_Tunnel_params_STC Tunnel;
         UINT_8 Tunnel_mask;
         BOOLEAN Bridge_security_applications_feature_is_supported;
         UINT_8 Bridge_security_applications_feature_is_supported_mask;
         SYSCONFG_Dot1x_params_STC Dot1x;
         UINT_8 Dot1x_mask;
         BOOLEAN LLDP_feature_is_supported;
         UINT_8 LLDP_feature_is_supported_mask;
         SYSCONFG_Stp_params_STC Stp;
         UINT_8 Stp_mask;
         SYSCONFG_Special_Bpdu_params_STC Special_Bpdu;
         UINT_8 Special_Bpdu_mask;
         SYSCONFG_Storm_Control_params_STC Storm_Control;
         UINT_8 Storm_Control_mask;
         BOOLEAN Vidx_feature_is_supported;
         UINT_8 Vidx_feature_is_supported_mask;
         BOOLEAN Port_Lock_feature_is_supported;
         UINT_8 Port_Lock_feature_is_supported_mask;
         SYSCONFG_LLDP_params_STC LLDP;
         UINT_8 LLDP_mask;
         SYSCONFG_Bridge_MC_params_STC Bridge_MC;
         UINT_8 Bridge_MC_mask;
         BOOLEAN Loopback_Detection_feature_is_supported;
         UINT_8 Loopback_Detection_feature_is_supported_mask;
         SYSCONFG_LAG_params_STC LAG;
         UINT_8 LAG_mask;
         BOOLEAN Fdb_feature_is_supported;
         UINT_8 Fdb_feature_is_supported_mask;
         SYSCONFG_Vlan_params_STC Vlan;
         UINT_8 Vlan_mask;
         BOOLEAN Tunnel_feature_is_supported;
         UINT_8 Tunnel_feature_is_supported_mask;
         SYSCONFG_L2_Link_stability_params_STC L2_Link_stability;
         UINT_8 L2_Link_stability_mask;
         SYSCONFG_Protected_ports_params_STC Protected_ports;
         UINT_8 Protected_ports_mask;
         SYSCONFG_Port_params_STC Port;
         UINT_8 Port_mask;
         SYSCONFG_Bridge_security_applications_params_STC Bridge_security_applications;
         UINT_8 Bridge_security_applications_mask;
         BOOLEAN Dot1x_feature_is_supported;
         UINT_8 Dot1x_feature_is_supported_mask;
    } SYSCONFG_L2_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         SYSCONFG_aaa_hashing_method_type_ENT hashing_algorithm_name;
    } PKDB SYSCONFG_hash_method_to_hash_type_dict_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_hash_method_to_hash_type_dict_list_keys_STC list_keys;
         UINT_32 id_number;
         UINT_8 id_number_mask;
    } SYSCONFG_hash_method_to_hash_type_dict_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         BOOLEAN superhash_sha1_to_default;
         UINT_8 superhash_sha1_to_default_mask;
         UINT_32 delay_between_logins;
         UINT_8 delay_between_logins_mask;
         /* db of type SYSCONFG_hash_method_to_hash_type_dict_list_params_STC */ SYSCONFG_DB_HANDLE_TYP hash_method_to_hash_type_dict_list_PTR;
         UINT_8 hash_method_to_hash_type_dict_list_mask;
         BOOLEAN login_failed_attempts_quiet_period_supported;
         UINT_8 login_failed_attempts_quiet_period_supported_mask;
         BOOLEAN reauthentication_during_password_change;
         UINT_8 reauthentication_during_password_change_mask;
         BOOLEAN salted_hashed_passwords_syntax;
         UINT_8 salted_hashed_passwords_syntax_mask;
         SYSCONFG_aaa_hashing_algorithm_supported_bits_type_TYP hashing_algorithms_supported;
         UINT_8 hashing_algorithms_supported_mask;
         SYSCONFG_aaa_hashing_algorithm_type_ENT default_hashing_algorithm;
         UINT_8 default_hashing_algorithm_mask;
         BOOLEAN delete_config_during_downgrade_if_insecure;
         UINT_8 delete_config_during_downgrade_if_insecure_mask;
         BOOLEAN delay_between_logins_supported;
         UINT_8 delay_between_logins_supported_mask;
         BOOLEAN reauthentication_during_other_users_password_change;
         UINT_8 reauthentication_during_other_users_password_change_mask;
         SYSCONFG_aaa_default_encoding_algorithm_type_ENT default_encoding_algorithm;
         UINT_8 default_encoding_algorithm_mask;
    } SYSCONFG_AAA_params_STC;

    typedef struct 
    {
         SYSCONFG_Radius_server_params_STC Radius_server;
         UINT_8 Radius_server_mask;
         SYSCONFG_Source_guard_params_STC Source_guard;
         UINT_8 Source_guard_mask;
         SYSCONFG_AAA_params_STC AAA;
         UINT_8 AAA_mask;
         SYSCONFG_IPv6_stack_params_STC IPv6_stack;
         UINT_8 IPv6_stack_mask;
         BOOLEAN IPv4_stack_feature_is_supported;
         UINT_8 IPv4_stack_feature_is_supported_mask;
         BOOLEAN Vrrp_feature_is_supported;
         UINT_8 Vrrp_feature_is_supported_mask;
         SYSCONFG_DHCPv6_guard_params_STC DHCPv6_guard;
         UINT_8 DHCPv6_guard_mask;
         BOOLEAN Inet_common_parameters_feature_is_supported;
         UINT_8 Inet_common_parameters_feature_is_supported_mask;
         BOOLEAN Metaswitch_Routing_Protocols_Suite_feature_is_supported;
         UINT_8 Metaswitch_Routing_Protocols_Suite_feature_is_supported_mask;
         SYSCONFG_Vrrp_params_STC Vrrp;
         UINT_8 Vrrp_mask;
         BOOLEAN IPv6_fft_feature_is_supported;
         UINT_8 IPv6_fft_feature_is_supported_mask;
         BOOLEAN OSPF_feature_is_supported;
         UINT_8 OSPF_feature_is_supported_mask;
         BOOLEAN RA_guard_feature_is_supported;
         UINT_8 RA_guard_feature_is_supported_mask;
         BOOLEAN IPv6_stack_feature_is_supported;
         UINT_8 IPv6_stack_feature_is_supported_mask;
         SYSCONFG_ISE_params_STC ISE;
         UINT_8 ISE_mask;
         BOOLEAN IPv4_fft_feature_is_supported;
         UINT_8 IPv4_fft_feature_is_supported_mask;
         BOOLEAN DHCPv6_guard_feature_is_supported;
         UINT_8 DHCPv6_guard_feature_is_supported_mask;
         BOOLEAN IP_standard_acl_feature_is_supported;
         UINT_8 IP_standard_acl_feature_is_supported_mask;
         BOOLEAN NBI_feature_is_supported;
         UINT_8 NBI_feature_is_supported_mask;
         SYSCONFG_RA_guard_params_STC RA_guard;
         UINT_8 RA_guard_mask;
         BOOLEAN DHCPv6_client_feature_is_supported;
         UINT_8 DHCPv6_client_feature_is_supported_mask;
         SYSCONFG_IPv4_fft_params_STC IPv4_fft;
         UINT_8 IPv4_fft_mask;
         BOOLEAN IPM_feature_is_supported;
         UINT_8 IPM_feature_is_supported_mask;
         BOOLEAN Voip_feature_is_supported;
         UINT_8 Voip_feature_is_supported_mask;
         SYSCONFG_IPv6_prefix_list_params_STC IPv6_prefix_list;
         UINT_8 IPv6_prefix_list_mask;
         BOOLEAN ND_inspection_feature_is_supported;
         UINT_8 ND_inspection_feature_is_supported_mask;
         SYSCONFG_OSPFv3_params_STC OSPFv3;
         UINT_8 OSPFv3_mask;
         SYSCONFG_NBI_params_STC NBI;
         UINT_8 NBI_mask;
         BOOLEAN PBR_feature_is_supported;
         UINT_8 PBR_feature_is_supported_mask;
         SYSCONFG_FHS_params_STC FHS;
         UINT_8 FHS_mask;
         BOOLEAN Routemap_feature_is_supported;
         UINT_8 Routemap_feature_is_supported_mask;
         BOOLEAN IPv4_prefix_list_feature_is_supported;
         UINT_8 IPv4_prefix_list_feature_is_supported_mask;
         SYSCONFG_OSPF_params_STC OSPF;
         UINT_8 OSPF_mask;
         BOOLEAN IPv6_prefix_list_feature_is_supported;
         UINT_8 IPv6_prefix_list_feature_is_supported_mask;
         SYSCONFG_Voip_params_STC Voip;
         UINT_8 Voip_mask;
         BOOLEAN Radius_server_feature_is_supported;
         UINT_8 Radius_server_feature_is_supported_mask;
         BOOLEAN ISE_feature_is_supported;
         UINT_8 ISE_feature_is_supported_mask;
         BOOLEAN Arp_feature_is_supported;
         UINT_8 Arp_feature_is_supported_mask;
         BOOLEAN AAA_feature_is_supported;
         UINT_8 AAA_feature_is_supported_mask;
         SYSCONFG_PBR_params_STC PBR;
         UINT_8 PBR_mask;
         BOOLEAN OSPFv3_feature_is_supported;
         UINT_8 OSPFv3_feature_is_supported_mask;
         SYSCONFG_Radius_client_params_STC Radius_client;
         UINT_8 Radius_client_mask;
         SYSCONFG_IPv4_stack_params_STC IPv4_stack;
         UINT_8 IPv4_stack_mask;
         SYSCONFG_IPv4_prefix_list_params_STC IPv4_prefix_list;
         UINT_8 IPv4_prefix_list_mask;
         SYSCONFG_Routemap_params_STC Routemap;
         UINT_8 Routemap_mask;
         SYSCONFG_Arp_params_STC Arp;
         UINT_8 Arp_mask;
         BOOLEAN Source_guard_feature_is_supported;
         UINT_8 Source_guard_feature_is_supported_mask;
         SYSCONFG_ND_inspection_params_STC ND_inspection;
         UINT_8 ND_inspection_mask;
         BOOLEAN FHS_feature_is_supported;
         UINT_8 FHS_feature_is_supported_mask;
         SYSCONFG_IPv6_fft_params_STC IPv6_fft;
         UINT_8 IPv6_fft_mask;
         SYSCONFG_Inet_common_parameters_params_STC Inet_common_parameters;
         UINT_8 Inet_common_parameters_mask;
         BOOLEAN Radius_client_feature_is_supported;
         UINT_8 Radius_client_feature_is_supported_mask;
         SYSCONFG_IPM_params_STC IPM;
         UINT_8 IPM_mask;
         BOOLEAN DHCPv6_relay_feature_is_supported;
         UINT_8 DHCPv6_relay_feature_is_supported_mask;
         SYSCONFG_DHCPv6_relay_params_STC DHCPv6_relay;
         UINT_8 DHCPv6_relay_mask;
         SYSCONFG_IP_standard_acl_params_STC IP_standard_acl;
         UINT_8 IP_standard_acl_mask;
         SYSCONFG_DHCPv6_client_params_STC DHCPv6_client;
         UINT_8 DHCPv6_client_mask;
         SYSCONFG_Metaswitch_Routing_Protocols_Suite_params_STC Metaswitch_Routing_Protocols_Suite;
         UINT_8 Metaswitch_Routing_Protocols_Suite_mask;
    } SYSCONFG_L3_params_STC;

    typedef struct 
    {
         BOOLEAN Stack_feature_is_supported;
         UINT_8 Stack_feature_is_supported_mask;
         SYSCONFG_Stack_params_STC Stack;
         UINT_8 Stack_mask;
    } SYSCONFG_Stacking_applications_params_STC;

    typedef struct 
    {
         BOOLEAN SLA_feature_is_supported;
         UINT_8 SLA_feature_is_supported_mask;
         BOOLEAN Bonjour_feature_is_supported;
         UINT_8 Bonjour_feature_is_supported_mask;
         SYSCONFG_PTP_exception_workaround_params_STC PTP_exception_workaround;
         UINT_8 PTP_exception_workaround_mask;
         SYSCONFG_Bonjour_params_STC Bonjour;
         UINT_8 Bonjour_mask;
         SYSCONFG_DNS_client_params_STC DNS_client;
         UINT_8 DNS_client_mask;
         SYSCONFG_UDP_relay_params_STC UDP_relay;
         UINT_8 UDP_relay_mask;
         SYSCONFG_WBA_params_STC WBA;
         UINT_8 WBA_mask;
         SYSCONFG_SSH_Server_params_STC SSH_Server;
         UINT_8 SSH_Server_mask;
         BOOLEAN PNP_agent_feature_is_supported;
         UINT_8 PNP_agent_feature_is_supported_mask;
         BOOLEAN SSL_feature_is_supported;
         UINT_8 SSL_feature_is_supported_mask;
         BOOLEAN SSH_Server_feature_is_supported;
         UINT_8 SSH_Server_feature_is_supported_mask;
         BOOLEAN UDP_relay_feature_is_supported;
         UINT_8 UDP_relay_feature_is_supported_mask;
         SYSCONFG_SCP_params_STC SCP;
         UINT_8 SCP_mask;
         SYSCONFG_PNP_agent_params_STC PNP_agent;
         UINT_8 PNP_agent_mask;
         BOOLEAN DNS_client_feature_is_supported;
         UINT_8 DNS_client_feature_is_supported_mask;
         BOOLEAN WBA_feature_is_supported;
         UINT_8 WBA_feature_is_supported_mask;
         BOOLEAN PTP_exception_workaround_feature_is_supported;
         UINT_8 PTP_exception_workaround_feature_is_supported_mask;
         SYSCONFG_SLA_params_STC SLA;
         UINT_8 SLA_mask;
         BOOLEAN SCP_feature_is_supported;
         UINT_8 SCP_feature_is_supported_mask;
         BOOLEAN SSH_feature_is_supported;
         UINT_8 SSH_feature_is_supported_mask;
         SYSCONFG_SSL_params_STC SSL;
         UINT_8 SSL_mask;
         SYSCONFG_SSH_params_STC SSH;
         UINT_8 SSH_mask;
    } SYSCONFG_IP_Applications_params_STC;

    typedef struct 
    {
         SYSCONFG_Open_flow_params_STC Open_flow;
         UINT_8 Open_flow_mask;
         SYSCONFG_Dynamic_acl_params_STC Dynamic_acl;
         UINT_8 Dynamic_acl_mask;
         SYSCONFG_Security_suite_params_STC Security_suite;
         UINT_8 Security_suite_mask;
         BOOLEAN Open_flow_feature_is_supported;
         UINT_8 Open_flow_feature_is_supported_mask;
         BOOLEAN Protocol_Filtering_feature_is_supported;
         UINT_8 Protocol_Filtering_feature_is_supported_mask;
         BOOLEAN Security_suite_feature_is_supported;
         UINT_8 Security_suite_feature_is_supported_mask;
         SYSCONFG_Protocol_Filtering_params_STC Protocol_Filtering;
         UINT_8 Protocol_Filtering_mask;
         BOOLEAN Dynamic_acl_feature_is_supported;
         UINT_8 Dynamic_acl_feature_is_supported_mask;
    } SYSCONFG_Policy_Applications_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         SYSCONFG_cli_interface_type_ENT cli_interface_type_enum;
    } PKDB SYSCONFG_custom_ifnames_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_custom_ifnames_list_keys_STC list_keys;
         char * cli_interface_long_name;
         UINT_8 cli_interface_long_name_mask;
         char * cli_interface_help;
         UINT_8 cli_interface_help_mask;
         char * cli_interface_short_name;
         UINT_8 cli_interface_short_name_mask;
    } SYSCONFG_custom_ifnames_list_params_STC;
    /* LIST STRUCT DEFINITION */

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         char from_url[128];
    } PKDB SYSCONFG_redirections_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_redirections_list_keys_STC list_keys;
         char * to_url;
         UINT_8 to_url_mask;
    } SYSCONFG_redirections_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         BOOLEAN password_recovery_cli_file_is_supported;
         UINT_8 password_recovery_cli_file_is_supported_mask;
         char * trunk_prefix;
         UINT_8 trunk_prefix_mask;
         BOOLEAN default_range_mode;
         UINT_8 default_range_mode_mask;
         UINT_8 maximal_user_privilege;
         UINT_8 maximal_user_privilege_mask;
         char * password_recovery_cli_file_name;
         UINT_8 password_recovery_cli_file_name_mask;
         char * trunk_short_prefix;
         UINT_8 trunk_short_prefix_mask;
         BOOLEAN custom_ifnames_supported;
         UINT_8 custom_ifnames_supported_mask;
         BOOLEAN custom_ifnames_no_prefix;
         UINT_8 custom_ifnames_no_prefix_mask;
         BOOLEAN is_slot_num_ifindex_name_prefix_required;
         UINT_8 is_slot_num_ifindex_name_prefix_required_mask;
         BOOLEAN is_remote_only;
         UINT_8 is_remote_only_mask;
         BOOLEAN short_ifIndex_names_are_supported;
         UINT_8 short_ifIndex_names_are_supported_mask;
         BOOLEAN output_modifiers_supported;
         UINT_8 output_modifiers_supported_mask;
         UINT_8 maximum_number_of_instances;
         UINT_8 maximum_number_of_instances_mask;
         UINT_32 maximum_number_of_history_records;
         UINT_8 maximum_number_of_history_records_mask;
         UINT_8 slot_num_ifindex_name_prefix;
         UINT_8 slot_num_ifindex_name_prefix_mask;
         SYSCONFG_mac_address_format_type_ENT default_mac_address_output_type;
         UINT_8 default_mac_address_output_type_mask;
         char * default_settings_after_show_config;
         UINT_8 default_settings_after_show_config_mask;
         UINT_8 instance_history_buffer_size;
         UINT_8 instance_history_buffer_size_mask;
         BOOLEAN stack_style_unit_and_port_only;
         UINT_8 stack_style_unit_and_port_only_mask;
         BOOLEAN is_special_ifnames;
         UINT_8 is_special_ifnames_mask;
         /* db of type SYSCONFG_custom_ifnames_list_params_STC */ SYSCONFG_DB_HANDLE_TYP custom_ifnames_list_PTR;
         UINT_8 custom_ifnames_list_mask;
         char * web_trunk_prefix;
         UINT_8 web_trunk_prefix_mask;
    } SYSCONFG_GCLI_params_STC;

    typedef struct 
    {
         UINT_32 XML_number_of_nodes;
         UINT_8 XML_number_of_nodes_mask;
         char * languages_list;
         UINT_8 languages_list_mask;
         BOOLEAN OAS_supported;
         UINT_8 OAS_supported_mask;
         UINT_8 max_number_of_localization_languages;
         UINT_8 max_number_of_localization_languages_mask;
         BOOLEAN cors_is_supported;
         UINT_8 cors_is_supported_mask;
         BOOLEAN mts_web_path_enabled;
         UINT_8 mts_web_path_enabled_mask;
         UINT_32 XML_number_of_attributes;
         UINT_8 XML_number_of_attributes_mask;
         char * mts_web_path;
         UINT_8 mts_web_path_mask;
         char * authentication_page;
         UINT_8 authentication_page_mask;
         char * default_page;
         UINT_8 default_page_mask;
         BOOLEAN redirect_HTTP_to_HTTPS;
         UINT_8 redirect_HTTP_to_HTTPS_mask;
         BOOLEAN localization_supported;
         UINT_8 localization_supported_mask;
         BOOLEAN HTTPS_session_logging_enabled;
         UINT_8 HTTPS_session_logging_enabled_mask;
         BOOLEAN Rest_API_class_supported;
         UINT_8 Rest_API_class_supported_mask;
         /* db of type SYSCONFG_redirections_list_params_STC */ SYSCONFG_DB_HANDLE_TYP redirections_list_PTR;
         UINT_8 redirections_list_mask;
    } SYSCONFG_Web_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_Passwd_Encrypt_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         UINT_32 index;
    } PKDB SYSCONFG_sntp_default_server_names_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_sntp_default_server_names_list_keys_STC list_keys;
         char * server_name;
         UINT_8 server_name_mask;
    } SYSCONFG_sntp_default_server_names_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         UINT_8 max_num_of_periodic_ranges;
         UINT_8 max_num_of_periodic_ranges_mask;
         BOOLEAN is_weeklist_periodic_supported;
         UINT_8 is_weeklist_periodic_supported_mask;
         UINT_8 max_num_of_time_ranges;
         UINT_8 max_num_of_time_ranges_mask;
         BOOLEAN is_day_periodic_supported;
         UINT_8 is_day_periodic_supported_mask;
    } SYSCONFG_TBI_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         UINT_32 index;
    } PKDB SYSCONFG_sntp_pnp_default_server_names_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_sntp_pnp_default_server_names_list_keys_STC list_keys;
         char * server_name;
         UINT_8 server_name_mask;
    } SYSCONFG_sntp_pnp_default_server_names_list_params_STC;
    /* LIST STRUCT DEFINITION */

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         char file_name[128];
    } PKDB SYSCONFG_indirect_file_name_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_indirect_file_name_list_keys_STC list_keys;
    } SYSCONFG_indirect_file_name_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         UINT_16 time_interval_in_min;
         UINT_8 time_interval_in_min_mask;
         BOOLEAN default_enabled;
         UINT_8 default_enabled_mask;
    } SYSCONFG_Mirror_Configuration_File_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         char file_name[128];
    } PKDB SYSCONFG_default_file_name_list_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_default_file_name_list_keys_STC list_keys;
    } SYSCONFG_default_file_name_list_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         UINT_32 snaPortUtilEvent_high_threshold;
         UINT_8 snaPortUtilEvent_high_threshold_mask;
         UINT_32 num_of_week_samples;
         UINT_8 num_of_week_samples_mask;
         UINT_32 num_of_day_samples;
         UINT_8 num_of_day_samples_mask;
         SYSCONFG_sampling_resolution_type_ENT snaPortUtilEvent_sampling_resolution;
         UINT_8 snaPortUtilEvent_sampling_resolution_mask;
         UINT_32 num_of_extended_weekly_samples;
         UINT_8 num_of_extended_weekly_samples_mask;
         UINT_32 num_of_min_samples;
         UINT_8 num_of_min_samples_mask;
         UINT_8 min_sampling_interval;
         UINT_8 min_sampling_interval_mask;
         BOOLEAN enabled_by_default;
         UINT_8 enabled_by_default_mask;
         UINT_32 snaPortUtilEvent_mid_threshold;
         UINT_8 snaPortUtilEvent_mid_threshold_mask;
         UINT_32 num_of_hour_samples;
         UINT_8 num_of_hour_samples_mask;
         BOOLEAN port_enabled_by_default;
         UINT_8 port_enabled_by_default_mask;
         UINT_32 num_of_sec_samples;
         UINT_8 num_of_sec_samples_mask;
    } SYSCONFG_Port_Statistics_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         SYSCONFG_smart_port_type_ENT smart_port_type_enum;
    } PKDB SYSCONFG_smart_port_types_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_smart_port_types_keys_STC list_keys;
         char * smart_port_type_name;
         UINT_8 smart_port_type_name_mask;
         char * smart_port_macro_name;
         UINT_8 smart_port_macro_name_mask;
    } SYSCONFG_smart_port_types_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         UINT_8 Env_Monitor_Shutdown_Time;
         UINT_8 Env_Monitor_Shutdown_Time_mask;
         BOOLEAN rps_supported;
         UINT_8 rps_supported_mask;
         BOOLEAN Env_Monitor_Poe_Supported;
         UINT_8 Env_Monitor_Poe_Supported_mask;
         BOOLEAN fan_direction_supported;
         UINT_8 fan_direction_supported_mask;
         BOOLEAN Env_Monitor_Shutdown_Enable;
         UINT_8 Env_Monitor_Shutdown_Enable_mask;
         BOOLEAN Show_only_specific_sensor;
         UINT_8 Show_only_specific_sensor_mask;
    } SYSCONFG_EnvMonitor_params_STC;

    /* packed typedef start */
    PRAGMA_NOALIGN
    typedef PKDT struct
    {
        /* key index 0 */         UINT_16 smart_port_id;
    } PKDB SYSCONFG_smart_port_preset_names_keys_STC;
    PRAGMA_ALIGN
    /* packed typedef end */
    /* LIST KEYS STRUCT DEFINITION */typedef struct 
    {
         /* list key */ SYSCONFG_smart_port_preset_names_keys_STC list_keys;
         char * macro_value;
         UINT_8 macro_value_mask;
         SYSCONFG_smart_port_type_ENT macro_name;
         UINT_8 macro_name_mask;
         BOOLEAN user_configurable;
         UINT_8 user_configurable_mask;
         char * name;
         UINT_8 name_mask;
    } SYSCONFG_smart_port_preset_names_params_STC;
    /* LIST STRUCT DEFINITION */

    typedef struct 
    {
         char * excluded_community_names;
         UINT_8 excluded_community_names_mask;
         UINT_32 snmp_community_supported_number;
         UINT_8 snmp_community_supported_number_mask;
         BOOLEAN ip_address_is_allowed;
         UINT_8 ip_address_is_allowed_mask;
    } SYSCONFG_SNMP_Community_params_STC;

    typedef struct 
    {
         /* db of type SYSCONFG_sntp_pnp_default_server_names_list_params_STC */ SYSCONFG_DB_HANDLE_TYP sntp_pnp_default_server_names_list_PTR;
         UINT_8 sntp_pnp_default_server_names_list_mask;
         UINT_32 retry_timeout_interval;
         UINT_8 retry_timeout_interval_mask;
         UINT_32 max_unicast_servers;
         UINT_8 max_unicast_servers_mask;
         UINT_32 number_of_retries;
         UINT_8 number_of_retries_mask;
         BOOLEAN unicast_default_enabled;
         UINT_8 unicast_default_enabled_mask;
         /* db of type SYSCONFG_sntp_default_server_names_list_params_STC */ SYSCONFG_DB_HANDLE_TYP sntp_default_server_names_list_PTR;
         UINT_8 sntp_default_server_names_list_mask;
         BOOLEAN port_configuration_enable;
         UINT_8 port_configuration_enable_mask;
         UINT_16 sntp_default_port_number;
         UINT_8 sntp_default_port_number_mask;
    } SYSCONFG_SNTP_params_STC;

    typedef struct 
    {
         SYSCONFG_copy_default_directive_access_type_ENT copy_default_directive;
         UINT_8 copy_default_directive_mask;
         SYSCONFG_copy_different_SKU_directive_type_ENT copy_different_SKU_directive;
         UINT_8 copy_different_SKU_directive_mask;
         char * copy_http_upload_suffix;
         UINT_8 copy_http_upload_suffix_mask;
         char * copy_backupconf_file_name;
         UINT_8 copy_backupconf_file_name_mask;
    } SYSCONFG_Copy_params_STC;

    typedef struct 
    {
         SYSCONFG_target_type_ENT target;
         UINT_8 target_mask;
         /* db of type SYSCONFG_default_file_name_list_params_STC */ SYSCONFG_DB_HANDLE_TYP default_file_name_list_PTR;
         UINT_8 default_file_name_list_mask;
         BOOLEAN multi_file_read_is_supported;
         UINT_8 multi_file_read_is_supported_mask;
         SYSCONFG_start_condition_type_ENT start_condition;
         UINT_8 start_condition_mask;
         BOOLEAN remove_force_flag_after_reload;
         UINT_8 remove_force_flag_after_reload_mask;
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
         /* db of type SYSCONFG_indirect_file_name_list_params_STC */ SYSCONFG_DB_HANDLE_TYP indirect_file_name_list_PTR;
         UINT_8 indirect_file_name_list_mask;
    } SYSCONFG_Auto_config_params_STC;

    typedef struct 
    {
         BOOLEAN is_enabled_by_default;
         UINT_8 is_enabled_by_default_mask;
    } SYSCONFG_Auto_update_params_STC;

    typedef struct 
    {
         BOOLEAN backup_configuration_is_supported;
         UINT_8 backup_configuration_is_supported_mask;
         BOOLEAN scp_is_supported;
         UINT_8 scp_is_supported_mask;
         BOOLEAN usb_is_supported;
         UINT_8 usb_is_supported_mask;
    } SYSCONFG_Auto_upgrade_params_STC;

    typedef struct 
    {
         BOOLEAN auto_smartport_supported;
         UINT_8 auto_smartport_supported_mask;
         SYSCONFG_smart_port_enable_ENT auto_smartport_initial_state;
         UINT_8 auto_smartport_initial_state_mask;
         /* db of type SYSCONFG_smart_port_types_params_STC */ SYSCONFG_DB_HANDLE_TYP smart_port_types_PTR;
         UINT_8 smart_port_types_mask;
         BOOLEAN persistency_enabled;
         UINT_8 persistency_enabled_mask;
         /* db of type SYSCONFG_smart_port_preset_names_params_STC */ SYSCONFG_DB_HANDLE_TYP smart_port_preset_names_PTR;
         UINT_8 smart_port_preset_names_mask;
    } SYSCONFG_Port_event_params_STC;

    typedef struct 
    {
         BOOLEAN system_fan_direction_is_supported;
         UINT_8 system_fan_direction_is_supported_mask;
         BOOLEAN multi_sensors_is_supported;
         UINT_8 multi_sensors_is_supported_mask;
         BOOLEAN rtc_is_supported;
         UINT_8 rtc_is_supported_mask;
    } SYSCONFG_Environment_params_STC;

    typedef struct 
    {
         UINT_8 timeout_in_seconds;
         UINT_8 timeout_in_seconds_mask;
    } SYSCONFG_Auto_save_params_STC;

    typedef struct 
    {
         UINT_32 debug_log_size;
         UINT_8 debug_log_size_mask;
         UINT_32 debug_id_size;
         UINT_8 debug_id_size_mask;
    } SYSCONFG_Generic_debug_params_STC;

    typedef struct 
    {
         UINT_8 maximum_number_of_components;
         UINT_8 maximum_number_of_components_mask;
    } SYSCONFG_Component_mapper_params_STC;

    typedef struct 
    {
         char * SKU_prefix;
         UINT_8 SKU_prefix_mask;
         BOOLEAN CLI_version_is_supported;
         UINT_8 CLI_version_is_supported_mask;
         BOOLEAN SKU_is_supported;
         UINT_8 SKU_is_supported_mask;
    } SYSCONFG_Configuration_file_header_params_STC;

    typedef struct 
    {
         BOOLEAN MOTD_is_supported;
         UINT_8 MOTD_is_supported_mask;
         BOOLEAN login_is_supported;
         UINT_8 login_is_supported_mask;
         BOOLEAN exec_is_supported;
         UINT_8 exec_is_supported_mask;
         UINT_32 string_global_maximum_length;
         UINT_8 string_global_maximum_length_mask;
    } SYSCONFG_Banner_params_STC;

    typedef struct 
    {
         SYSCONFG_Security_sensitive_data_params_STC Security_sensitive_data;
         UINT_8 Security_sensitive_data_mask;
         BOOLEAN Security_sensitive_data_feature_is_supported;
         UINT_8 Security_sensitive_data_feature_is_supported_mask;
         SYSCONFG_read_default_directive_type_ENT read_default_directive;
         UINT_8 read_default_directive_mask;
    } SYSCONFG_Security_management_params_STC;

    typedef struct 
    {
         BOOLEAN supported_in_delphi;
         UINT_8 supported_in_delphi_mask;
         UINT_32 undo_secondary_database_memory_size;
         UINT_8 undo_secondary_database_memory_size_mask;
         UINT_32 undo_database_memory_size;
         UINT_8 undo_database_memory_size_mask;
    } SYSCONFG_SNMP_transaction_params_STC;

    typedef struct 
    {
         BOOLEAN authentication_sha224_is_supported;
         UINT_8 authentication_sha224_is_supported_mask;
         BOOLEAN authentication_security_level_is_supported;
         UINT_8 authentication_security_level_is_supported_mask;
         BOOLEAN no_authentication_security_level_is_supported;
         UINT_8 no_authentication_security_level_is_supported_mask;
         BOOLEAN authentication_sha512_is_supported;
         UINT_8 authentication_sha512_is_supported_mask;
         BOOLEAN privacy_aes_is_supported;
         UINT_8 privacy_aes_is_supported_mask;
         BOOLEAN authentication_md5_is_supported;
         UINT_8 authentication_md5_is_supported_mask;
         BOOLEAN authentication_sha384_is_supported;
         UINT_8 authentication_sha384_is_supported_mask;
         BOOLEAN privacy_security_level_is_supported;
         UINT_8 privacy_security_level_is_supported_mask;
         BOOLEAN privacy_des_is_supported;
         UINT_8 privacy_des_is_supported_mask;
         BOOLEAN authentication_sha1_is_supported;
         UINT_8 authentication_sha1_is_supported_mask;
         BOOLEAN authentication_sha256_is_supported;
         UINT_8 authentication_sha256_is_supported_mask;
    } SYSCONFG_SNMP_user_params_STC;

    typedef struct 
    {
         char * default_read;
         UINT_8 default_read_mask;
         BOOLEAN groups_supported;
         UINT_8 groups_supported_mask;
         BOOLEAN views_supported;
         UINT_8 views_supported_mask;
         BOOLEAN snmp_syslog_on_configuration_enabled;
         UINT_8 snmp_syslog_on_configuration_enabled_mask;
         BOOLEAN read_write_supported;
         UINT_8 read_write_supported_mask;
         BOOLEAN show_all_groups;
         UINT_8 show_all_groups_mask;
         char * default_super;
         UINT_8 default_super_mask;
         BOOLEAN super_supported;
         UINT_8 super_supported_mask;
         char * default_write;
         UINT_8 default_write_mask;
         BOOLEAN read_only_supported;
         UINT_8 read_only_supported_mask;
    } SYSCONFG_SNMP_access_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_clients;
         UINT_8 maximum_number_of_clients_mask;
         UINT_32 number_of_blocks_in_hardware;
         UINT_8 number_of_blocks_in_hardware_mask;
    } SYSCONFG_CNC_params_STC;

    typedef struct 
    {
         UINT_32 maximum_number_of_clients;
         UINT_8 maximum_number_of_clients_mask;
         BOOLEAN third_party_devices_is_supported;
         UINT_8 third_party_devices_is_supported_mask;
    } SYSCONFG_SNA_agent_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_Handle_private_mib_root_params_STC;

    typedef struct 
    {
         UINT_32 led_mode_button_polling_multiplier;
         UINT_8 led_mode_button_polling_multiplier_mask;
         UINT_32 fan_polling_multiplier;
         UINT_8 fan_polling_multiplier_mask;
         UINT_32 ps_polling_multiplier;
         UINT_8 ps_polling_multiplier_mask;
         UINT_32 sensor_polling_retries;
         UINT_8 sensor_polling_retries_mask;
         UINT_32 sensors_polling_multipler;
         UINT_8 sensors_polling_multipler_mask;
         UINT_32 fan_polling_retries;
         UINT_8 fan_polling_retries_mask;
         UINT_32 polling_interval_in_ms;
         UINT_8 polling_interval_in_ms_mask;
         UINT_32 factory_reset_default_multiplier;
         UINT_8 factory_reset_default_multiplier_mask;
    } SYSCONFG_Env_poll_params_STC;

    typedef struct 
    {
         UINT_8 maximum_number_of_clients;
         UINT_8 maximum_number_of_clients_mask;
    } SYSCONFG_Unexpected_restart_alert_params_STC;

    typedef struct 
    {
         UINT_32 maximum_consequent_snmp_sets;
         UINT_8 maximum_consequent_snmp_sets_mask;
    } SYSCONFG_Unit_test_params_STC;

    typedef struct 
    {
         BOOLEAN local_database_authentication;
         UINT_8 local_database_authentication_mask;
    } SYSCONFG_Debug_authentication_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_SNMP_client_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_SNMP_traps_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_TIME_logging_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_DEBUG_logging_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_Components_versions_params_STC;

    typedef struct 
    {
         SYSCONFG_authentication_method_type_ENT default_authentication_method;
         UINT_8 default_authentication_method_mask;
         BOOLEAN BOOTP_authentication_key_change_is_allowed;
         UINT_8 BOOTP_authentication_key_change_is_allowed_mask;
         SYSCONFG_snmp_version_bits_type_TYP snmp_version;
         UINT_8 snmp_version_mask;
         char * authentication_password;
         UINT_8 authentication_password_mask;
         BOOLEAN BOOTP_private_key_change_is_allowed;
         UINT_8 BOOTP_private_key_change_is_allowed_mask;
         BOOLEAN high_snmpv3_testing_level;
         UINT_8 high_snmpv3_testing_level_mask;
         UINT_32 maximum_number_of_snmpv3_hosts;
         UINT_8 maximum_number_of_snmpv3_hosts_mask;
         BOOLEAN snmp_is_enbaled_by_default;
         UINT_8 snmp_is_enbaled_by_default_mask;
         BOOLEAN radlan_private_MIB_is_accessible;
         UINT_8 radlan_private_MIB_is_accessible_mask;
         char * defaultSUCommunity;
         UINT_8 defaultSUCommunity_mask;
         UINT_32 default_snmp_udp_port_number;
         UINT_8 default_snmp_udp_port_number_mask;
         char * defaultROCommunity;
         UINT_8 defaultROCommunity_mask;
         UINT_32 maximum_number_of_simultaneous_sorted_tables;
         UINT_8 maximum_number_of_simultaneous_sorted_tables_mask;
         UINT_32 maximum_number_of_keys_per_sorted_table;
         UINT_8 maximum_number_of_keys_per_sorted_table_mask;
         UINT_32 maximum_number_of_inform_receivers;
         UINT_8 maximum_number_of_inform_receivers_mask;
         BOOLEAN managers_ip_mask_is_supported;
         UINT_8 managers_ip_mask_is_supported_mask;
         UINT_32 maximum_number_of_snmp_clients;
         UINT_8 maximum_number_of_snmp_clients_mask;
         char * defaultRWCommunity;
         UINT_8 defaultRWCommunity_mask;
         char * privacy_password;
         UINT_8 privacy_password_mask;
         char * default_user;
         UINT_8 default_user_mask;
         UINT_32 maximum_number_of_simultaneous_notifications;
         UINT_8 maximum_number_of_simultaneous_notifications_mask;
    } SYSCONFG_SNMP_params_STC;

    typedef struct 
    {
         UINT_8 cli_session_small_blocks_allocation_ratio;
         UINT_8 cli_session_small_blocks_allocation_ratio_mask;
         UINT_8 web_session_medium_blocks_allocation_ratio;
         UINT_8 web_session_medium_blocks_allocation_ratio_mask;
         UINT_8 web_session_small_blocks_allocation_ratio;
         UINT_8 web_session_small_blocks_allocation_ratio_mask;
         UINT_8 web_session_big_blocks_allocation_ratio;
         UINT_8 web_session_big_blocks_allocation_ratio_mask;
         UINT_32 cli_session_memory_pool_size;
         UINT_8 cli_session_memory_pool_size_mask;
         UINT_8 cli_session_big_blocks_allocation_ratio;
         UINT_8 cli_session_big_blocks_allocation_ratio_mask;
         UINT_8 cli_session_medium_blocks_allocation_ratio;
         UINT_8 cli_session_medium_blocks_allocation_ratio_mask;
         UINT_32 web_session_memory_pool_size;
         UINT_8 web_session_memory_pool_size_mask;
    } SYSCONFG_Delphi_script_params_STC;

    typedef struct 
    {
         BOOLEAN keep_alive_is_enabled;
         UINT_8 keep_alive_is_enabled_mask;
         UINT_8 number_of_services;
         UINT_8 number_of_services_mask;
         BOOLEAN static_error_collector_page_display;
         UINT_8 static_error_collector_page_display_mask;
         SYSCONFG_web_authentication_privilege_level_type_ENT default_web_authentication_privilege_level;
         UINT_8 default_web_authentication_privilege_level_mask;
         BOOLEAN cache_revalidate_is_supported;
         UINT_8 cache_revalidate_is_supported_mask;
         BOOLEAN security_via_get_system_URL_is_supported;
         UINT_8 security_via_get_system_URL_is_supported_mask;
         BOOLEAN hard_timeout_is_supported;
         UINT_8 hard_timeout_is_supported_mask;
         UINT_8 maximum_service_sockets_per_user;
         UINT_8 maximum_service_sockets_per_user_mask;
    } SYSCONFG_Embeded_Web_params_STC;

    typedef struct 
    {
         BOOLEAN place_holder;
         UINT_8 place_holder_mask;
    } SYSCONFG_DDF_params_STC;

    typedef struct 
    {
         UINT_8 default_polling_interval;
         UINT_8 default_polling_interval_mask;
         UINT_8 maximum_num_of_events_pollers;
         UINT_8 maximum_num_of_events_pollers_mask;
    } SYSCONFG_SNMP_events_log_params_STC;

    typedef struct 
    {
         BOOLEAN management_two_interface_id_are_supported;
         UINT_8 management_two_interface_id_are_supported_mask;
         char * default_management_acl_name;
         UINT_8 default_management_acl_name_mask;
         BOOLEAN management_access_is_enabled_by_other_applications;
         UINT_8 management_access_is_enabled_by_other_applications_mask;
    } SYSCONFG_Management_ACL_params_STC;

    typedef struct 
    {
         UINT_8 maximum_aggregation_list_size;
         UINT_8 maximum_aggregation_list_size_mask;
         SYSCONFG_header_action_type_ENT default_header_action;
         UINT_8 default_header_action_mask;
         BOOLEAN aggregation_enabled_by_default;
         UINT_8 aggregation_enabled_by_default_mask;
         UINT_32 maximum_file_entries;
         UINT_8 maximum_file_entries_mask;
         UINT_32 maximum_number_of_syslog_servers;
         UINT_8 maximum_number_of_syslog_servers_mask;
         UINT_32 minimum_severity_to_console;
         UINT_8 minimum_severity_to_console_mask;
         UINT_32 minimum_severity_of_message_to_server;
         UINT_8 minimum_severity_of_message_to_server_mask;
         BOOLEAN message_logged_to_flash;
         UINT_8 message_logged_to_flash_mask;
         BOOLEAN counters_per_severity_is_supported;
         UINT_8 counters_per_severity_is_supported_mask;
         UINT_32 default_aggregation_aging_time;
         UINT_8 default_aggregation_aging_time_mask;
         UINT_32 minimum_severity_to_alarm_threshold;
         UINT_8 minimum_severity_to_alarm_threshold_mask;
         char * severity_to_character_mapping;
         UINT_8 severity_to_character_mapping_mask;
         UINT_32 minimum_severity_to_memory_cache;
         UINT_8 minimum_severity_to_memory_cache_mask;
         BOOLEAN origin_id_configuration_is_supported;
         UINT_8 origin_id_configuration_is_supported_mask;
         BOOLEAN aggregation_is_supported;
         UINT_8 aggregation_is_supported_mask;
         BOOLEAN header_configuration_is_supported;
         UINT_8 header_configuration_is_supported_mask;
         UINT_32 minimum_severity_to_flash_file;
         UINT_8 minimum_severity_to_flash_file_mask;
    } SYSCONFG_Syslog_params_STC;

    typedef struct 
    {
         SYSCONFG_Web_params_STC Web;
         UINT_8 Web_mask;
         SYSCONFG_Debug_authentication_params_STC Debug_authentication;
         UINT_8 Debug_authentication_mask;
         BOOLEAN TIME_logging_is_supported;
         UINT_8 TIME_logging_is_supported_mask;
         SYSCONFG_SNMP_events_log_params_STC SNMP_events_log;
         UINT_8 SNMP_events_log_mask;
         BOOLEAN Security_management_feature_is_supported;
         UINT_8 Security_management_feature_is_supported_mask;
         SYSCONFG_TIME_logging_params_STC TIME_logging;
         UINT_8 TIME_logging_mask;
         SYSCONFG_Embeded_Web_params_STC Embeded_Web;
         UINT_8 Embeded_Web_mask;
         BOOLEAN Banner_feature_is_supported;
         UINT_8 Banner_feature_is_supported_mask;
         SYSCONFG_Env_poll_params_STC Env_poll;
         UINT_8 Env_poll_mask;
         BOOLEAN Generic_debug_feature_is_supported;
         UINT_8 Generic_debug_feature_is_supported_mask;
         BOOLEAN Handle_private_mib_root_is_supported;
         UINT_8 Handle_private_mib_root_is_supported_mask;
         BOOLEAN SNMP_traps_is_supported;
         UINT_8 SNMP_traps_is_supported_mask;
         BOOLEAN RCLI_feature_is_supported;
         UINT_8 RCLI_feature_is_supported_mask;
         SYSCONFG_Mirror_Configuration_File_params_STC Mirror_Configuration_File;
         UINT_8 Mirror_Configuration_File_mask;
         BOOLEAN LCLI_feature_is_supported;
         UINT_8 LCLI_feature_is_supported_mask;
         SYSCONFG_SNMP_client_params_STC SNMP_client;
         UINT_8 SNMP_client_mask;
         BOOLEAN Copy_feature_is_supported;
         UINT_8 Copy_feature_is_supported_mask;
         SYSCONFG_Auto_config_params_STC Auto_config;
         UINT_8 Auto_config_mask;
         BOOLEAN Unexpected_restart_alert_feature_is_supported;
         UINT_8 Unexpected_restart_alert_feature_is_supported_mask;
         BOOLEAN GCLI_feature_is_supported;
         UINT_8 GCLI_feature_is_supported_mask;
         BOOLEAN Delphi_script_is_supported;
         UINT_8 Delphi_script_is_supported_mask;
         BOOLEAN Port_event_feature_is_supported;
         UINT_8 Port_event_feature_is_supported_mask;
         SYSCONFG_DEBUG_logging_params_STC DEBUG_logging;
         UINT_8 DEBUG_logging_mask;
         SYSCONFG_DDF_params_STC DDF;
         UINT_8 DDF_mask;
         BOOLEAN SNMP_transaction_feature_is_supported;
         UINT_8 SNMP_transaction_feature_is_supported_mask;
         BOOLEAN Auto_config_feature_is_supported;
         UINT_8 Auto_config_feature_is_supported_mask;
         SYSCONFG_Security_management_params_STC Security_management;
         UINT_8 Security_management_mask;
         SYSCONFG_Delphi_script_params_STC Delphi_script;
         UINT_8 Delphi_script_mask;
         BOOLEAN Auto_save_feature_is_supported;
         UINT_8 Auto_save_feature_is_supported_mask;
         BOOLEAN Components_versions_is_supported;
         UINT_8 Components_versions_is_supported_mask;
         BOOLEAN DEBUG_logging_is_supported;
         UINT_8 DEBUG_logging_is_supported_mask;
         BOOLEAN SNA_agent_feature_is_supported;
         UINT_8 SNA_agent_feature_is_supported_mask;
         BOOLEAN SNMP_Community_feature_is_supported;
         UINT_8 SNMP_Community_feature_is_supported_mask;
         BOOLEAN Environment_feature_is_supported;
         UINT_8 Environment_feature_is_supported_mask;
         BOOLEAN SNMP_access_feature_is_supported;
         UINT_8 SNMP_access_feature_is_supported_mask;
         BOOLEAN Component_mapper_feature_is_supported;
         UINT_8 Component_mapper_feature_is_supported_mask;
         SYSCONFG_Auto_upgrade_params_STC Auto_upgrade;
         UINT_8 Auto_upgrade_mask;
         SYSCONFG_TBI_params_STC TBI;
         UINT_8 TBI_mask;
         SYSCONFG_Syslog_params_STC Syslog;
         UINT_8 Syslog_mask;
         SYSCONFG_Images_params_STC Images;
         UINT_8 Images_mask;
         SYSCONFG_Auto_save_params_STC Auto_save;
         UINT_8 Auto_save_mask;
         BOOLEAN SNMP_user_feature_is_supported;
         UINT_8 SNMP_user_feature_is_supported_mask;
         BOOLEAN Port_Statistics_feature_is_supported;
         UINT_8 Port_Statistics_feature_is_supported_mask;
         SYSCONFG_Component_mapper_params_STC Component_mapper;
         UINT_8 Component_mapper_mask;
         SYSCONFG_EnvMonitor_params_STC EnvMonitor;
         UINT_8 EnvMonitor_mask;
         SYSCONFG_Environment_params_STC Environment;
         UINT_8 Environment_mask;
         BOOLEAN Web_feature_is_supported;
         UINT_8 Web_feature_is_supported_mask;
         BOOLEAN Images_feature_is_supported;
         UINT_8 Images_feature_is_supported_mask;
         SYSCONFG_Passwd_Encrypt_params_STC Passwd_Encrypt;
         UINT_8 Passwd_Encrypt_mask;
         SYSCONFG_SNA_agent_params_STC SNA_agent;
         UINT_8 SNA_agent_mask;
         SYSCONFG_SNMP_user_params_STC SNMP_user;
         UINT_8 SNMP_user_mask;
         SYSCONFG_Configuration_file_header_params_STC Configuration_file_header;
         UINT_8 Configuration_file_header_mask;
         BOOLEAN Syslog_is_supported;
         UINT_8 Syslog_is_supported_mask;
         SYSCONFG_RCLI_params_STC RCLI;
         UINT_8 RCLI_mask;
         SYSCONFG_SNMP_access_params_STC SNMP_access;
         UINT_8 SNMP_access_mask;
         BOOLEAN SNMP_is_supported;
         UINT_8 SNMP_is_supported_mask;
         SYSCONFG_SNMP_transaction_params_STC SNMP_transaction;
         UINT_8 SNMP_transaction_mask;
         BOOLEAN TBI_feature_is_supported;
         UINT_8 TBI_feature_is_supported_mask;
         BOOLEAN Management_ACL_is_supported;
         UINT_8 Management_ACL_is_supported_mask;
         SYSCONFG_LCLI_params_STC LCLI;
         UINT_8 LCLI_mask;
         SYSCONFG_SNMP_params_STC SNMP;
         UINT_8 SNMP_mask;
         SYSCONFG_Port_Statistics_params_STC Port_Statistics;
         UINT_8 Port_Statistics_mask;
         BOOLEAN Configuration_file_header_feature_is_supported;
         UINT_8 Configuration_file_header_feature_is_supported_mask;
         SYSCONFG_Components_versions_params_STC Components_versions;
         UINT_8 Components_versions_mask;
         BOOLEAN Auto_update_feature_is_supported;
         UINT_8 Auto_update_feature_is_supported_mask;
         BOOLEAN Unit_test_feature_is_supported;
         UINT_8 Unit_test_feature_is_supported_mask;
         SYSCONFG_Port_event_params_STC Port_event;
         UINT_8 Port_event_mask;
         SYSCONFG_SNMP_Community_params_STC SNMP_Community;
         UINT_8 SNMP_Community_mask;
         BOOLEAN EnvMonitor_feature_is_supported;
         UINT_8 EnvMonitor_feature_is_supported_mask;
         BOOLEAN Passwd_Encrypt_feature_is_supported;
         UINT_8 Passwd_Encrypt_feature_is_supported_mask;
         BOOLEAN SNTP_feature_is_supported;
         UINT_8 SNTP_feature_is_supported_mask;
         BOOLEAN Auto_upgrade_feature_is_supported;
         UINT_8 Auto_upgrade_feature_is_supported_mask;
         SYSCONFG_Auto_update_params_STC Auto_update;
         UINT_8 Auto_update_mask;
         SYSCONFG_GCLI_params_STC GCLI;
         UINT_8 GCLI_mask;
         BOOLEAN Env_poll_feature_is_supported;
         UINT_8 Env_poll_feature_is_supported_mask;
         BOOLEAN SNMP_events_log_is_supported;
         UINT_8 SNMP_events_log_is_supported_mask;
         SYSCONFG_Generic_debug_params_STC Generic_debug;
         UINT_8 Generic_debug_mask;
         SYSCONFG_Unit_test_params_STC Unit_test;
         UINT_8 Unit_test_mask;
         BOOLEAN DDF_is_supported;
         UINT_8 DDF_is_supported_mask;
         SYSCONFG_Copy_params_STC Copy;
         UINT_8 Copy_mask;
         SYSCONFG_Banner_params_STC Banner;
         UINT_8 Banner_mask;
         BOOLEAN SNMP_client_is_supported;
         UINT_8 SNMP_client_is_supported_mask;
         SYSCONFG_SNTP_params_STC SNTP;
         UINT_8 SNTP_mask;
         BOOLEAN CNC_feature_is_supported;
         UINT_8 CNC_feature_is_supported_mask;
         SYSCONFG_SNMP_traps_params_STC SNMP_traps;
         UINT_8 SNMP_traps_mask;
         BOOLEAN Debug_authentication_is_supported;
         UINT_8 Debug_authentication_is_supported_mask;
         SYSCONFG_CNC_params_STC CNC;
         UINT_8 CNC_mask;
         BOOLEAN Embeded_Web_is_supported;
         UINT_8 Embeded_Web_is_supported_mask;
         BOOLEAN Mirror_Configuration_File_feature_is_supported;
         UINT_8 Mirror_Configuration_File_feature_is_supported_mask;
         SYSCONFG_Unexpected_restart_alert_params_STC Unexpected_restart_alert;
         UINT_8 Unexpected_restart_alert_mask;
         SYSCONFG_Handle_private_mib_root_params_STC Handle_private_mib_root;
         UINT_8 Handle_private_mib_root_mask;
         SYSCONFG_Management_ACL_params_STC Management_ACL;
         UINT_8 Management_ACL_mask;
    } SYSCONFG_Management_Applications_params_STC;

    typedef struct 
    {
         BOOLEAN iSCSI_Qos_feature_is_supported;
         UINT_8 iSCSI_Qos_feature_is_supported_mask;
         BOOLEAN Config_Watchdog_feature_is_supported;
         UINT_8 Config_Watchdog_feature_is_supported_mask;
         SYSCONFG_management_params_STC management;
         UINT_8 management_mask;
         SYSCONFG_QOS_params_STC QOS;
         UINT_8 QOS_mask;
         SYSCONFG_Config_Watchdog_params_STC Config_Watchdog;
         UINT_8 Config_Watchdog_mask;
         BOOLEAN QOS_feature_is_supported;
         UINT_8 QOS_feature_is_supported_mask;
         BOOLEAN Secure_Boot_feature_is_supported;
         UINT_8 Secure_Boot_feature_is_supported_mask;
         BOOLEAN management_feature_is_supported;
         UINT_8 management_feature_is_supported_mask;
         SYSCONFG_iSCSI_Qos_params_STC iSCSI_Qos;
         UINT_8 iSCSI_Qos_mask;
         BOOLEAN DFS_feature_is_supported;
         UINT_8 DFS_feature_is_supported_mask;
         SYSCONFG_Buffer_management_params_STC Buffer_management;
         UINT_8 Buffer_management_mask;
         SYSCONFG_DFS_params_STC DFS;
         UINT_8 DFS_mask;
         BOOLEAN Buffer_management_feature_is_supported;
         UINT_8 Buffer_management_feature_is_supported_mask;
         SYSCONFG_Secure_Boot_params_STC Secure_Boot;
         UINT_8 Secure_Boot_mask;
    } SYSCONFG_System_params_STC;

    typedef struct 
    {
         BOOLEAN Cloud_Manager_feature_is_supported;
         UINT_8 Cloud_Manager_feature_is_supported_mask;
         SYSCONFG_FindIT_params_STC FindIT;
         UINT_8 FindIT_mask;
         BOOLEAN FindIT_feature_is_supported;
         UINT_8 FindIT_feature_is_supported_mask;
         BOOLEAN MTPLAP_feature_is_supported;
         UINT_8 MTPLAP_feature_is_supported_mask;
         SYSCONFG_Cloud_Manager_params_STC Cloud_Manager;
         UINT_8 Cloud_Manager_mask;
         SYSCONFG_MTPLAP_params_STC MTPLAP;
         UINT_8 MTPLAP_mask;
    } SYSCONFG_Third_Pary_Applications_params_STC;

    typedef struct 
    {
         SYSCONFG_HAL_OS_params_STC HAL_OS;
         UINT_8 HAL_OS_mask;
         BOOLEAN HAL_OS_feature_is_supported;
         UINT_8 HAL_OS_feature_is_supported_mask;
    } SYSCONFG_Infrastructure_params_STC;

    typedef struct 
    {
         SYSCONFG_Infrastructure_params_STC Infrastructure;
         UINT_8 Infrastructure_mask;
         SYSCONFG_Stacking_applications_params_STC Stacking_applications;
         UINT_8 Stacking_applications_mask;
         SYSCONFG_System_params_STC System;
         UINT_8 System_mask;
         SYSCONFG_Third_Pary_Applications_params_STC Third_Pary_Applications;
         UINT_8 Third_Pary_Applications_mask;
         SYSCONFG_L2_params_STC L2;
         UINT_8 L2_mask;
         SYSCONFG_Policy_Applications_params_STC Policy_Applications;
         UINT_8 Policy_Applications_mask;
         SYSCONFG_IP_Applications_params_STC IP_Applications;
         UINT_8 IP_Applications_mask;
         SYSCONFG_L1_params_STC L1;
         UINT_8 L1_mask;
         SYSCONFG_Management_Applications_params_STC Management_Applications;
         UINT_8 Management_Applications_mask;
         SYSCONFG_L3_params_STC L3;
         UINT_8 L3_mask;
    } SYSCONFG_MTS_Project_params_STC;

    /* FEATURES IDS ENUM DECLARTATION */
    typedef enum {
        SYSCONFG_feature_id_configuration_file_header_E,
        SYSCONFG_feature_id_web_E,
        SYSCONFG_feature_id_inet_common_parameters_E,
        SYSCONFG_feature_id_pnp_agent_E,
        SYSCONFG_feature_id_rx_training_E,
        SYSCONFG_feature_id_security_sensitive_data_E,
        SYSCONFG_feature_id_component_mapper_E,
        SYSCONFG_feature_id_vlan_E,
        SYSCONFG_feature_id_port_manager_E,
        SYSCONFG_feature_id_ospfv3_E,
        SYSCONFG_feature_id_debug_authentication_E,
        SYSCONFG_feature_id_unit_test_E,
        SYSCONFG_feature_id_udp_relay_E,
        SYSCONFG_feature_id_special_bpdu_E,
        SYSCONFG_feature_id_ospf_E,
        SYSCONFG_feature_id_ipv4_stack_E,
        SYSCONFG_feature_id_protocol_filtering_E,
        SYSCONFG_feature_id_fip_E,
        SYSCONFG_feature_id_delphi_script_E,
        SYSCONFG_feature_id_auto_update_E,
        SYSCONFG_feature_id_ipv6_stack_E,
        SYSCONFG_feature_id_vlan_voice_auto_vlan_E,
        SYSCONFG_feature_id_env_poll_E,
        SYSCONFG_feature_id_dot1x_mac_authentication_E,
        SYSCONFG_feature_id_dot1x_E,
        SYSCONFG_feature_id_lag_E,
        SYSCONFG_feature_id_port_event_E,
        SYSCONFG_feature_id_vlan_private_vlan_E,
        SYSCONFG_feature_id_mtplap_E,
        SYSCONFG_feature_id_envmonitor_E,
        SYSCONFG_feature_id_arp_E,
        SYSCONFG_feature_id_environment_E,
        SYSCONFG_feature_id_copy_E,
        SYSCONFG_feature_id_vlan_voice_vlan_E,
        SYSCONFG_feature_id_embeded_web_E,
        SYSCONFG_feature_id_link_flapping_prevention_E,
        SYSCONFG_feature_id_ipm_E,
        SYSCONFG_feature_id_findit_E,
        SYSCONFG_feature_id_open_flow_E,
        SYSCONFG_feature_id_dhcpv6_client_E,
        SYSCONFG_feature_id_snmp_client_E,
        SYSCONFG_feature_id_mac_security_E,
        SYSCONFG_feature_id_i2c_syslog_E,
        SYSCONFG_feature_id_hw_interface_E,
        SYSCONFG_feature_id_auto_neg_preference_E,
        SYSCONFG_feature_id_components_versions_E,
        SYSCONFG_feature_id_lldp_snoop_E,
        SYSCONFG_feature_id_vlan_mac_base_vlan_E,
        SYSCONFG_feature_id_bridge_security_applications_E,
        SYSCONFG_feature_id_eee_E,
        SYSCONFG_feature_id_bluetooth_E,
        SYSCONFG_feature_id_l2_link_stability_E,
        SYSCONFG_feature_id_ipv6_prefix_list_E,
        SYSCONFG_feature_id_passwd_encrypt_E,
        SYSCONFG_feature_id_fiber_E,
        SYSCONFG_feature_id_vlan_mapping_E,
        SYSCONFG_feature_id_arp_inspection_E,
        SYSCONFG_feature_id_iscsi_qos_E,
        SYSCONFG_feature_id_ra_guard_E,
        SYSCONFG_feature_id_pe_E,
        SYSCONFG_feature_id_qos_E,
        SYSCONFG_feature_id_cpld_update_E,
        SYSCONFG_feature_id_scp_E,
        SYSCONFG_feature_id_sflow_E,
        SYSCONFG_feature_id_pbr_E,
        SYSCONFG_feature_id_tunnel_E,
        SYSCONFG_feature_id_snmp_traps_E,
        SYSCONFG_feature_id_source_guard_E,
        SYSCONFG_feature_id_ipv4_prefix_list_E,
        SYSCONFG_feature_id_green_E,
        SYSCONFG_feature_id_ddf_E,
        SYSCONFG_feature_id_tbi_E,
        SYSCONFG_feature_id_ssl_E,
        SYSCONFG_feature_id_unit_E,
        SYSCONFG_feature_id_flow_control_E,
        SYSCONFG_feature_id_images_E,
        SYSCONFG_feature_id_ip_standard_acl_E,
        SYSCONFG_feature_id_dce_E,
        SYSCONFG_feature_id_isatap_tunnel_E,
        SYSCONFG_feature_id_green_short_reach_E,
        SYSCONFG_feature_id_auto_config_E,
        SYSCONFG_feature_id_vlan_subnet_base_vlan_E,
        SYSCONFG_feature_id_errdisable_led_E,
        SYSCONFG_feature_id_storm_control_E,
        SYSCONFG_feature_id_dynamic_acl_E,
        SYSCONFG_feature_id_vrrp_E,
        SYSCONFG_feature_id_debug_logging_E,
        SYSCONFG_feature_id_aaa_E,
        SYSCONFG_feature_id_locate_port_E,
        SYSCONFG_feature_id_jumbo_frame_E,
        SYSCONFG_feature_id_ise_E,
        SYSCONFG_feature_id_sna_agent_E,
        SYSCONFG_feature_id_management_E,
        SYSCONFG_feature_id_vlan_surveillance_vlan_E,
        SYSCONFG_feature_id_loopback_detection_E,
        SYSCONFG_feature_id_syslog_E,
        SYSCONFG_feature_id_config_watchdog_E,
        SYSCONFG_feature_id_nbi_E,
        SYSCONFG_feature_id_rcli_E,
        SYSCONFG_feature_id_mtplap_health_check_E,
        SYSCONFG_feature_id_vlan_dot1x_extensions_E,
        SYSCONFG_feature_id_secure_boot_E,
        SYSCONFG_feature_id_bonjour_E,
        SYSCONFG_feature_id_ssh_server_E,
        SYSCONFG_feature_id_auto_upgrade_E,
        SYSCONFG_feature_id_fdb_E,
        SYSCONFG_feature_id_dhcp_snooping_E,
        SYSCONFG_feature_id_internal_port_E,
        SYSCONFG_feature_id_metaswitch_routing_protocols_suite_E,
        SYSCONFG_feature_id_dfs_E,
        SYSCONFG_feature_id_stp_E,
        SYSCONFG_feature_id_routemap_E,
        SYSCONFG_feature_id_ipv4_fft_E,
        SYSCONFG_feature_id_nd_inspection_E,
        SYSCONFG_feature_id_lldp_E,
        SYSCONFG_feature_id_green_energy_detect_E,
        SYSCONFG_feature_id_lcli_E,
        SYSCONFG_feature_id_snmp_transaction_E,
        SYSCONFG_feature_id_lmp_E,
        SYSCONFG_feature_id_radius_client_E,
        SYSCONFG_feature_id_unexpected_restart_alert_E,
        SYSCONFG_feature_id_snmp_E,
        SYSCONFG_feature_id_ipv6_fft_E,
        SYSCONFG_feature_id_link_stability_E,
        SYSCONFG_feature_id_six2four_tunnel_E,
        SYSCONFG_feature_id_vidx_E,
        SYSCONFG_feature_id_auto_save_E,
        SYSCONFG_feature_id_udld_E,
        SYSCONFG_feature_id_radius_coa_E,
        SYSCONFG_feature_id_span_E,
        SYSCONFG_feature_id_signal_stability_E,
        SYSCONFG_feature_id_snmp_user_E,
        SYSCONFG_feature_id_security_suite_E,
        SYSCONFG_feature_id_bridge_mc_E,
        SYSCONFG_feature_id_cloud_manager_E,
        SYSCONFG_feature_id_wba_E,
        SYSCONFG_feature_id_green_led_E,
        SYSCONFG_feature_id_locate_unit_E,
        SYSCONFG_feature_id_fhs_E,
        SYSCONFG_feature_id_dhcpv6_guard_E,
        SYSCONFG_feature_id_ptp_exception_workaround_E,
        SYSCONFG_feature_id_mirror_configuration_file_E,
        SYSCONFG_feature_id_dying_gasp_E,
        SYSCONFG_feature_id_time_logging_E,
        SYSCONFG_feature_id_radius_server_E,
        SYSCONFG_feature_id_port_statistics_E,
        SYSCONFG_feature_id_poe_E,
        SYSCONFG_feature_id_banner_E,
        SYSCONFG_feature_id_stack_E,
        SYSCONFG_feature_id_voip_E,
        SYSCONFG_feature_id_ssh_E,
        SYSCONFG_feature_id_snmp_events_log_E,
        SYSCONFG_feature_id_sntp_E,
        SYSCONFG_feature_id_cnc_E,
        SYSCONFG_feature_id_port_lock_E,
        SYSCONFG_feature_id_snmp_community_E,
        SYSCONFG_feature_id_dhcpv6_relay_E,
        SYSCONFG_feature_id_sla_E,
        SYSCONFG_feature_id_dns_client_E,
        SYSCONFG_feature_id_protected_ports_E,
        SYSCONFG_feature_id_vlan_multicast_tv_vlan_E,
        SYSCONFG_feature_id_security_management_E,
        SYSCONFG_feature_id_hal_os_E,
        SYSCONFG_feature_id_generic_debug_E,
        SYSCONFG_feature_id_gcli_E,
        SYSCONFG_feature_id_buffer_management_E,
        SYSCONFG_feature_id_management_acl_E,
        SYSCONFG_feature_id_ip_source_guard_E,
        SYSCONFG_feature_id_ap_E,
        SYSCONFG_feature_id_snmp_access_E,
        SYSCONFG_feature_id_cdp_E,
        SYSCONFG_feature_id_handle_private_mib_root_E,
        SYSCONFG_feature_id_traffic_to_cpu_E,
        SYSCONFG_feature_id_vlan_default_vlan_E,
        SYSCONFG_feature_id_port_E,
        SYSCONFG_feature_id_LAST_E
    } SYSCONFG_feature_id_ENT;
    /* FEATURES UNION DECLARTATION */
    typedef union {
        SYSCONFG_Configuration_file_header_params_STC Configuration_file_header;
        SYSCONFG_Web_params_STC Web;
        SYSCONFG_Inet_common_parameters_params_STC Inet_common_parameters;
        SYSCONFG_PNP_agent_params_STC PNP_agent;
        SYSCONFG_Rx_Training_params_STC Rx_Training;
        SYSCONFG_Security_sensitive_data_params_STC Security_sensitive_data;
        SYSCONFG_Component_mapper_params_STC Component_mapper;
        SYSCONFG_Vlan_params_STC Vlan;
        SYSCONFG_Port_Manager_params_STC Port_Manager;
        SYSCONFG_OSPFv3_params_STC OSPFv3;
        SYSCONFG_Debug_authentication_params_STC Debug_authentication;
        SYSCONFG_Unit_test_params_STC Unit_test;
        SYSCONFG_UDP_relay_params_STC UDP_relay;
        SYSCONFG_Special_Bpdu_params_STC Special_Bpdu;
        SYSCONFG_OSPF_params_STC OSPF;
        SYSCONFG_IPv4_stack_params_STC IPv4_stack;
        SYSCONFG_Protocol_Filtering_params_STC Protocol_Filtering;
        SYSCONFG_FIP_params_STC FIP;
        SYSCONFG_Delphi_script_params_STC Delphi_script;
        SYSCONFG_Auto_update_params_STC Auto_update;
        SYSCONFG_IPv6_stack_params_STC IPv6_stack;
        SYSCONFG_Vlan_Voice_Auto_Vlan_params_STC Vlan_Voice_Auto_Vlan;
        SYSCONFG_Env_poll_params_STC Env_poll;
        SYSCONFG_Dot1x_mac_authentication_params_STC Dot1x_mac_authentication;
        SYSCONFG_Dot1x_params_STC Dot1x;
        SYSCONFG_LAG_params_STC LAG;
        SYSCONFG_Port_event_params_STC Port_event;
        SYSCONFG_Vlan_Private_Vlan_params_STC Vlan_Private_Vlan;
        SYSCONFG_MTPLAP_params_STC MTPLAP;
        SYSCONFG_EnvMonitor_params_STC EnvMonitor;
        SYSCONFG_Arp_params_STC Arp;
        SYSCONFG_Environment_params_STC Environment;
        SYSCONFG_Copy_params_STC Copy;
        SYSCONFG_Vlan_Voice_Vlan_params_STC Vlan_Voice_Vlan;
        SYSCONFG_Embeded_Web_params_STC Embeded_Web;
        SYSCONFG_Link_Flapping_Prevention_params_STC Link_Flapping_Prevention;
        SYSCONFG_IPM_params_STC IPM;
        SYSCONFG_FindIT_params_STC FindIT;
        SYSCONFG_Open_flow_params_STC Open_flow;
        SYSCONFG_DHCPv6_client_params_STC DHCPv6_client;
        SYSCONFG_SNMP_client_params_STC SNMP_client;
        SYSCONFG_MAC_security_params_STC MAC_security;
        SYSCONFG_I2C_Syslog_params_STC I2C_Syslog;
        SYSCONFG_hw_interface_params_STC hw_interface;
        SYSCONFG_auto_neg_preference_params_STC auto_neg_preference;
        SYSCONFG_Components_versions_params_STC Components_versions;
        SYSCONFG_LLDP_Snoop_params_STC LLDP_Snoop;
        SYSCONFG_Vlan_Mac_Base_Vlan_params_STC Vlan_Mac_Base_Vlan;
        SYSCONFG_Bridge_security_applications_params_STC Bridge_security_applications;
        SYSCONFG_EEE_params_STC EEE;
        SYSCONFG_Bluetooth_params_STC Bluetooth;
        SYSCONFG_L2_Link_stability_params_STC L2_Link_stability;
        SYSCONFG_IPv6_prefix_list_params_STC IPv6_prefix_list;
        SYSCONFG_Passwd_Encrypt_params_STC Passwd_Encrypt;
        SYSCONFG_Fiber_params_STC Fiber;
        SYSCONFG_Vlan_Mapping_params_STC Vlan_Mapping;
        SYSCONFG_ARP_inspection_params_STC ARP_inspection;
        SYSCONFG_iSCSI_Qos_params_STC iSCSI_Qos;
        SYSCONFG_RA_guard_params_STC RA_guard;
        SYSCONFG_PE_params_STC PE;
        SYSCONFG_QOS_params_STC QOS;
        SYSCONFG_CPLD_Update_params_STC CPLD_Update;
        SYSCONFG_SCP_params_STC SCP;
        SYSCONFG_SFLOW_params_STC SFLOW;
        SYSCONFG_PBR_params_STC PBR;
        SYSCONFG_Tunnel_params_STC Tunnel;
        SYSCONFG_SNMP_traps_params_STC SNMP_traps;
        SYSCONFG_Source_guard_params_STC Source_guard;
        SYSCONFG_IPv4_prefix_list_params_STC IPv4_prefix_list;
        SYSCONFG_Green_params_STC Green;
        SYSCONFG_DDF_params_STC DDF;
        SYSCONFG_TBI_params_STC TBI;
        SYSCONFG_SSL_params_STC SSL;
        SYSCONFG_Unit_params_STC Unit;
        SYSCONFG_Flow_Control_params_STC Flow_Control;
        SYSCONFG_Images_params_STC Images;
        SYSCONFG_IP_standard_acl_params_STC IP_standard_acl;
        SYSCONFG_DCE_params_STC DCE;
        SYSCONFG_ISATAP_Tunnel_params_STC ISATAP_Tunnel;
        SYSCONFG_Green_Short_Reach_params_STC Green_Short_Reach;
        SYSCONFG_Auto_config_params_STC Auto_config;
        SYSCONFG_Vlan_Subnet_Base_Vlan_params_STC Vlan_Subnet_Base_Vlan;
        SYSCONFG_ErrDisable_led_params_STC ErrDisable_led;
        SYSCONFG_Storm_Control_params_STC Storm_Control;
        SYSCONFG_Dynamic_acl_params_STC Dynamic_acl;
        SYSCONFG_Vrrp_params_STC Vrrp;
        SYSCONFG_DEBUG_logging_params_STC DEBUG_logging;
        SYSCONFG_AAA_params_STC AAA;
        SYSCONFG_Locate_Port_params_STC Locate_Port;
        SYSCONFG_Jumbo_Frame_params_STC Jumbo_Frame;
        SYSCONFG_ISE_params_STC ISE;
        SYSCONFG_SNA_agent_params_STC SNA_agent;
        SYSCONFG_management_params_STC management;
        SYSCONFG_Vlan_Surveillance_Vlan_params_STC Vlan_Surveillance_Vlan;
        SYSCONFG_Loopback_Detection_params_STC Loopback_Detection;
        SYSCONFG_Syslog_params_STC Syslog;
        SYSCONFG_Config_Watchdog_params_STC Config_Watchdog;
        SYSCONFG_NBI_params_STC NBI;
        SYSCONFG_RCLI_params_STC RCLI;
        SYSCONFG_MTPLAP_health_check_params_STC MTPLAP_health_check;
        SYSCONFG_Vlan_Dot1x_Extensions_params_STC Vlan_Dot1x_Extensions;
        SYSCONFG_Secure_Boot_params_STC Secure_Boot;
        SYSCONFG_Bonjour_params_STC Bonjour;
        SYSCONFG_SSH_Server_params_STC SSH_Server;
        SYSCONFG_Auto_upgrade_params_STC Auto_upgrade;
        SYSCONFG_Fdb_params_STC Fdb;
        SYSCONFG_DHCP_snooping_params_STC DHCP_snooping;
        SYSCONFG_Internal_port_params_STC Internal_port;
        SYSCONFG_Metaswitch_Routing_Protocols_Suite_params_STC Metaswitch_Routing_Protocols_Suite;
        SYSCONFG_DFS_params_STC DFS;
        SYSCONFG_Stp_params_STC Stp;
        SYSCONFG_Routemap_params_STC Routemap;
        SYSCONFG_IPv4_fft_params_STC IPv4_fft;
        SYSCONFG_ND_inspection_params_STC ND_inspection;
        SYSCONFG_LLDP_params_STC LLDP;
        SYSCONFG_Green_Energy_Detect_params_STC Green_Energy_Detect;
        SYSCONFG_LCLI_params_STC LCLI;
        SYSCONFG_SNMP_transaction_params_STC SNMP_transaction;
        SYSCONFG_LMP_params_STC LMP;
        SYSCONFG_Radius_client_params_STC Radius_client;
        SYSCONFG_Unexpected_restart_alert_params_STC Unexpected_restart_alert;
        SYSCONFG_SNMP_params_STC SNMP;
        SYSCONFG_IPv6_fft_params_STC IPv6_fft;
        SYSCONFG_Link_stability_params_STC Link_stability;
        SYSCONFG_Six2four_Tunnel_params_STC Six2four_Tunnel;
        SYSCONFG_Vidx_params_STC Vidx;
        SYSCONFG_Auto_save_params_STC Auto_save;
        SYSCONFG_UDLD_params_STC UDLD;
        SYSCONFG_Radius_CoA_params_STC Radius_CoA;
        SYSCONFG_Span_params_STC Span;
        SYSCONFG_Signal_Stability_params_STC Signal_Stability;
        SYSCONFG_SNMP_user_params_STC SNMP_user;
        SYSCONFG_Security_suite_params_STC Security_suite;
        SYSCONFG_Bridge_MC_params_STC Bridge_MC;
        SYSCONFG_Cloud_Manager_params_STC Cloud_Manager;
        SYSCONFG_WBA_params_STC WBA;
        SYSCONFG_Green_LED_params_STC Green_LED;
        SYSCONFG_Locate_Unit_params_STC Locate_Unit;
        SYSCONFG_FHS_params_STC FHS;
        SYSCONFG_DHCPv6_guard_params_STC DHCPv6_guard;
        SYSCONFG_PTP_exception_workaround_params_STC PTP_exception_workaround;
        SYSCONFG_Mirror_Configuration_File_params_STC Mirror_Configuration_File;
        SYSCONFG_Dying_gasp_params_STC Dying_gasp;
        SYSCONFG_TIME_logging_params_STC TIME_logging;
        SYSCONFG_Radius_server_params_STC Radius_server;
        SYSCONFG_Port_Statistics_params_STC Port_Statistics;
        SYSCONFG_POE_params_STC POE;
        SYSCONFG_Banner_params_STC Banner;
        SYSCONFG_Stack_params_STC Stack;
        SYSCONFG_Voip_params_STC Voip;
        SYSCONFG_SSH_params_STC SSH;
        SYSCONFG_SNMP_events_log_params_STC SNMP_events_log;
        SYSCONFG_SNTP_params_STC SNTP;
        SYSCONFG_CNC_params_STC CNC;
        SYSCONFG_Port_Lock_params_STC Port_Lock;
        SYSCONFG_SNMP_Community_params_STC SNMP_Community;
        SYSCONFG_DHCPv6_relay_params_STC DHCPv6_relay;
        SYSCONFG_SLA_params_STC SLA;
        SYSCONFG_DNS_client_params_STC DNS_client;
        SYSCONFG_Protected_ports_params_STC Protected_ports;
        SYSCONFG_Vlan_Multicast_Tv_Vlan_params_STC Vlan_Multicast_Tv_Vlan;
        SYSCONFG_Security_management_params_STC Security_management;
        SYSCONFG_HAL_OS_params_STC HAL_OS;
        SYSCONFG_Generic_debug_params_STC Generic_debug;
        SYSCONFG_GCLI_params_STC GCLI;
        SYSCONFG_Buffer_management_params_STC Buffer_management;
        SYSCONFG_Management_ACL_params_STC Management_ACL;
        SYSCONFG_IP_source_guard_params_STC IP_source_guard;
        SYSCONFG_Ap_params_STC Ap;
        SYSCONFG_SNMP_access_params_STC SNMP_access;
        SYSCONFG_Cdp_params_STC Cdp;
        SYSCONFG_Handle_private_mib_root_params_STC Handle_private_mib_root;
        SYSCONFG_Traffic_To_CPU_params_STC Traffic_To_CPU;
        SYSCONFG_Vlan_Default_Vlan_params_STC Vlan_Default_Vlan;
        SYSCONFG_Port_params_STC Port;
    } SYSCONFG_feature_data_params_UNT;
    /* STRUCTURE FOR DATA MAPPING */
    typedef struct {
        SYSCONFG_feature_id_ENT feature_id;
        BOOLEAN is_supported;
        UINT_8 is_supported_mask;
        SYSCONFG_feature_data_params_UNT * data_PTR;
        UINT_32 data_size;
    } SYSCONFG_feature_data_STC;
#endif/* #ifndef __SYSCONFG_MTS_Project_AUTO_GENERATED_PARSER_HEADER_FILE__ */
