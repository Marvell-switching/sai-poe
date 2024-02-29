#if !defined (__SAIPOE_H_)
#define __SAIPOE_H_

#include <saitypes.h>

typedef uint32_t  sai_poe_port_front_panel_id_t;

/** poe device power limit mode
 *  port limit - max power limit per port is configured by the user 
 *  class limit - max power is set automatically according the class of the connected device
 */
typedef enum _sai_poe_device_type_limit_mode_t
{
    SAI_POE_DEVICE_LIMIT_MODE_TYPE_PORT_LIMIT = 0,
    SAI_POE_DEVICE_LIMIT_MODE_TYPE_CLASS_LIMIT = 1
} sai_poe_device_limit_mode_t;

/* poe device pse (power sourcing  equipment) status */
typedef enum _sai_poe_device_pse_status_id_t
{
    SAI_POE_DEVICE_PSE_STATUS_TYPE_ACTIVE = 0,
    SAI_POE_DEVICE_PSE_STATUS_TYPE_FAIL = 1,
    SAI_POE_DEVICE_PSE_STATUS_TYPE_NOT_PRESENT = 2
} sai_poe_device_pse_status_id_t;

/* poe port power priority */
typedef enum _sai_poe_port_power_priority_t
{
    SAI_POE_PORT_POWER_PRIORITY_TYPE_LOW   = 0,
    SAI_POE_PORT_POWER_PRIORITY_TYPE_HIGH  = 1,
    SAI_POE_PORT_POWER_PRIORITY_TYPE_CRITICAL = 2
} sai_poe_port_power_priority_t;

/* poe port status */
typedef enum _sai_poe_port_status_t
{
    SAI_POE_PORT_STATUS_TYPE_OFF = 0,
    SAI_POE_PORT_STATUS_TYPE_SEARCHING = 1,
    SAI_POE_PORT_STATUS_TYPE_DELIVERING_POWER = 2,
    SAI_POE_PORT_STATUS_TYPE_FAULT = 3
} sai_poe_port_status_t;

/**
 * @brief poe device attributes
 */
typedef enum _sai_poe_device_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_POE_DEVICE_ATTR_START,

    /**
     * @brief Device Information for switch initialization.
     *
     * Hardware information format is based on SAI implementations by vendors.
     * String is NULL terminated. Format is vendor specific.
     * Example: Like PCI location, I2C address, MDIO address, MDIO bus SysFS information etc.
     * In case of NULL, use the default PoE associated switch id.
     *
     * @type sai_s8_list_t
     * @flags CREATE_ONLY
     * @default empty
     */
    SAI_ATTR_POE_HARDWARE_INFO = SAI_POE_DEVICE_ATTR_START,

    /**
     * @brief a list of all the PSE devices
     *
     * @type sai_object_list_t
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_POE_PSE_LIST,

    /**
     * @brief a list of all the poe ports
     *
     * @type sai_object_list_t
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_POE_PORT_LIST,

    /**
     * @brief the total power in the device
     *
     * @type sai_uint32_t
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_TOTAL_POWER,

    /**
     * @brief total power consumption
     *
     * @type sai_uint32_t
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_POWER_CONSUMPTION,

    /**
     * @brief poe device version and information (poe firmware version)
     *
     * @type char
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_VERSION,

    /**
     * @brief poe device PSE version and information
     *
     * @type sai_poe_device_pse_version_list_t
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_PSE_VERSION,

        /**
     * @brief list of temperature (in celsius) values for each PSE
     *
     * @type sai_poe_device_pse_temperature_list_t
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_TEMPERATURE_LIST,

    /**
     * @brief statuses for each PSEs
     *
     * @type sai_poe_device_pse_status_list_t
     * @flags READ_ONLY
     */
    SAI_POE_DEVICE_ATTR_PSE_STATUS_LIST,

    /**
     * @brief power limit mode
     *
     * @type sai_poe_device_limit_mode_t
     * @flags CREATE_AND_SET
     * @default SAI_POE_DEVICE_LIMIT_MODE_TYPE_CLASS_LIMIT
     */
    SAI_POE_DEVICE_ATTR_POWER_LIMIT_MODE,

    /**
     * @brief End of attributes
     */
    SAI_POE_DEVICE_ATTR_END,

    /** Custom range base value */
    SAI_POE_DEVICE_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_POE_DEVICE_ATTR_CUSTOM_RANGE_END

} sai_poe_device_attr_t;

/**
 * @brief poe device attributes
 */
typedef enum _sai_poe_pse_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_POE_PSE_ATTR_START,

    /**
     * @brief poe pse PSE software version
     *
     * @type char
     * @flags READ_ONLY
     */
    SAI_POE_PSE_ATTR_PSE_SOFTWARE_VERSION = SAI_POE_PSE_ATTR_START,

    /**
     * @brief poe pse PSE hardware version
     *
     * @type char
     * @flags READ_ONLY
     */
    SAI_POE_PSE_ATTR_PSE_HARDWARE_VERSION,

        /**
     * @brief temperature (in celsius) of the PSE
     *
     * @type int16_t
     * @flags READ_ONLY
     */
    SAI_POE_PSE_ATTR_TEMPERATURE,

    /**
     * @brief statuses for each PSEs
     *
     * @type sai_poe_device_pse_status_id_t
     * @flags READ_ONLY
     */
    SAI_POE_PSE_ATTR_PSE_STATUS,

    /**
     * @brief End of attributes
     */
    SAI_POE_PSE_ATTR_END,

    /** Custom range base value */
    SAI_POE_PSE_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_POE_PSE_ATTR_CUSTOM_RANGE_END

} sai_poe_pse_attr_t;


/**
 * @brief poe port attributes
 */
typedef enum _sai_poe_port_attr_t
{
    /**
     * @brief Start of attributes
     */
    SAI_POE_PORT_ATTR_START,

    /**
     * @brief PoE device ID
     *
     * @type sai_object_id_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY
     */
    SAI_POE_DEVICE_ID = SAI_POE_PORT_ATTR_START,

    /**
     * @brief PoE port front panel ID
     *
     * @type sai_poe_port_front_panel_id_t
     * @flags MANDATORY_ON_CREATE | CREATE ONLY
     */
    SAI_POE_PORT_ATTR_FRONT_PANEL_ID,

    /**
     * @brief PoE port enabled/disabled state, as set by the user
     *
     * @type bool
     * @flags CREATE_AND_SET
     * @default false
     */
    SAI_POE_PORT_ATTR_ADMIN_ENABLED_STATE,

    /**
     * @brief PoE port power limit mode
     *
     * @type sai_uint32_t
     * @flags CREATE_AND_SET
     * @default maximum value that the port can provide
     */
    SAI_POE_PORT_ATTR_POWER_LIMIT,

    /**
     * @brief PoE port priority
     *
     * @type sai_poe_port_power_priority_t
     * @flags CREATE_AND_SET
     * @default SAI_POE_PORT_POWER_PRIORITY_TYPE_HIGH
     */
    SAI_POE_PORT_ATTR_POWER_PRIORITY,

    /**
     * @brief PoE port consumption information
     *
     * @type sai_poe_port_power_consumption_t
     * @flags READ_ONLY
     */
    SAI_POE_PORT_ATTR_CONSUMPTION,

    /**
     * @brief PoE port status of the port status 
     *
     * @type sai_poe_port_status_t
     * @flags READ_ONLY
     */

    SAI_POE_PORT_ATTR_STATUS,

    /**
     * @brief PoE port detailed status of the port status (string)
     *
     * @type char
     * @flags READ_ONLY
     */

    SAI_POE_PORT_ATTR_DETAILED_STATUS,

    /**
     * @brief End of attributes
     */
    SAI_POE_PORT_ATTR_END,

    /** Custom range base value */
    SAI_POE_PORT_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    SAI_POE_PORT_ATTR_CUSTOM_RANGE_END

} sai_poe_port_attr_t;

/**
 * @brief Create a PoE device instance
 *
 * @param[out] poe_device_id PoE device ID
 * @param[in] switch_id switch_id Switch id
 * @param[in] attr_count count 
 * @param[in] attr_list Attribute list values
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_create_poe_device_fn)(
        _Out_ sai_object_id_t *poe_device_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove PoE device instance.
 *
 * @param[in] poe_device_id PoE device ID
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 * error code is returned.
 */
typedef sai_status_t  (*sai_remove_poe_device_fn)(
        _In_ sai_object_id_t poe_device_id);

/**
 * @brief Set the attribute of PoE instance.
 *
 * @param[in] poe_device_id PoE device ID
 * @param[in] attr Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_set_poe_device_attribute_fn)(
        _In_ sai_object_id_t poe_device_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get the attribute of PoE instance.
 *
 * @param[in] poe_device_id PoE device ID
 * @param[in] attr_count Number of the attribute
 * @param[inout] attr_list Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_get_poe_device_attribute_fn)(
        _In_ sai_object_id_t poe_device_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Create a PoE PSE instance
 *
 * @param[out] poe_pse_id PoE PSE ID
 * @param[in] switch_id  Switch id
 * @param[in] attr_count count 
 * @param[in] attr_list Attribute list values
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_create_poe_pse_fn)(
        _Out_ sai_object_id_t *poe_pse_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove PoE device PSE.
 *
 * @param[in] poe_pse_id PoE PSE ID
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 * error code is returned.
 */
typedef sai_status_t  (*sai_remove_poe_pse_fn)(
        _In_ sai_object_id_t poe_pse_id);

/**
 * @brief Set the attribute of PoE PSE.
 *
 * @param[in] poe_pse_id PoE PSE ID
 * @param[in] attr Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_set_poe_pse_attribute_fn)(
        _In_ sai_object_id_t poe_pse_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get the attribute of PoE PSE.
 *
 * @param[in] poe_pse_id PoE PSE ID
 * @param[in] attr_count Number of the attribute
 * @param[inout] attr_list Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_get_poe_pse_attribute_fn)(
        _In_ sai_object_id_t poe_pse_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);


 /**
 * @brief Create PoE port object
 *
 * @param[out] poe_port_id PoE port id
 * @param[in] switch_id switch ID
 * @param[in] attr_count Number of the attribute
 * @param[in] attr_list Value of attributes
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_create_poe_port_fn)(
        _Out_ sai_object_id_t *poe_port_id,
        _In_ sai_object_id_t switch_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

 /**
 * @brief Remove PoE port
 *
 * @param[in] poe_port_id PoE port id
 *
 * @return #SAI_STATUS_SUCCESS on success, failure status code on error
 */
typedef sai_status_t  (*sai_remove_poe_port_fn)(
        _In_ sai_object_id_t poe_port_id);

/**
 * @brief Set the attribute of PoE port.
 *
 * @param[in] poe_port_id Poe port id
 * @param[in] attr Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_set_poe_port_attribute_fn)(
        _In_ sai_object_id_t poe_port_id,
        _In_ sai_attribute_t *attr);

/**
 * @brief Get the attribute of PoE port.
 *
 * @param[in] poe_port_id Poe port id
 * @param[inout] attr_list Attribute value
 *
 * @return #SAI_STATUS_SUCCESS if operation is successful otherwise a different
 *    error code is returned.
 */
typedef sai_status_t  (*sai_get_poe_port_attribute_fn)(
        _In_ sai_object_id_t poe_port_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief PoE device method table retrieved with poe_api_query()
 */
typedef struct _sai_poe_device_api_t
{
    sai_create_poe_device_fn               create_poe_device;
    sai_remove_poe_device_fn               remove_poe_device;
    sai_set_poe_device_attribute_fn        set_poe_device_attribute;
    sai_get_poe_device_attribute_fn        get_poe_device_attribute;
} sai_poe_device_api_t;

/**
 * @brief PoE PSE method table retrieved with poe_api_query()
 */
typedef struct _sai_poe_port_api_t
{
    sai_create_poe_pse_fn                 create_poe_pse;
    sai_remove_poe_pse_fn                 remove_poe_pse;
    sai_set_poe_pse_attribute_fn          set_poe_pse_attribute;
    sai_get_poe_pse_attribute_fn          get_poe_pse_attribute;
} sai_poe_pse_api_t;

/**
 * @brief PoE port method table retrieved with poe_api_query()
 */
typedef struct _sai_poe_port_api_t
{
    sai_create_poe_port_fn                 create_poe_port;
    sai_remove_poe_port_fn                 remove_poe_port;
    sai_set_poe_port_attribute_fn          set_poe_port_attribute;
    sai_get_poe_port_attribute_fn          get_poe_port_attribute;
} sai_poe_port_api_t;


#endif /** __SAIPOE_H_ */

