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

#include <string.h>
#include <inttypes.h>
#include "assert.h"

#include <h/poe_v3.h>
#include <SAI/inc/sai.h>
#include <h/utils/dictionary.h>
#include <h/utils/lock.h>
#include <h/utils/log.h>

#define OID "oid:0x%" PRIx64

static sai_object_id_t g_switch_oid;

sai_status_t create_switch(
    _Out_ sai_object_id_t *switch_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list)
{
    poe_object_id_t *poe_object_id = (poe_object_id_t*)switch_id;

    /* TODO: add mutex */
    if (g_switch_oid)
    {
        LOG_ERROR("switch is already initialized");
        return SAI_STATUS_ITEM_ALREADY_EXISTS;
    }

    /* debug */
    LOG_PRINT("num attrs %u", attr_count);
    if (!attr_count)
    {
        LOG_ERROR("switch is missing mandatory attributes");
        return SAI_STATUS_INVALID_ATTRIBUTE_0;
    }
    for (int i = 0; i < attr_count; i++)
    {
        LOG_PRINT("[%d]: %u", attr_list[i].id, attr_list[i].value.u32);
    }

    /* parse attrs */
    for (int i = 0; i < attr_count; i++)
    {
        if (attr_list[i].id == SAI_SWITCH_ATTR_TYPE && attr_list[i].value.u32 != SAI_SWITCH_TYPE_POE)
        {
            LOG_ERROR("unsupported switch type %d", attr_list[i].value.u32);
            return SAI_STATUS_ATTR_NOT_SUPPORTED_0 + i;
        }
    }

    /* create object, use the given id and object type to create a unique sai object id */
    memset(poe_object_id, 0, sizeof(*poe_object_id));
    poe_object_id->id = 5;  /* FIXME: use something else */
    poe_object_id->object_type = SAI_OBJECT_TYPE_SWITCH;

    g_switch_oid = *switch_id;
    LOG_PRINT("created switch " OID, g_switch_oid);

    return SAI_STATUS_SUCCESS;
}

sai_status_t remove_switch(
    _In_ sai_object_id_t switch_id)
{
    if (switch_id != g_switch_oid)
    {
        LOG_ERROR("switch oid not found");
        return SAI_STATUS_FAILURE;
    }
    LOG_PRINT("removed switch " OID, g_switch_oid);
    g_switch_oid = SAI_NULL_OBJECT_ID;
    return SAI_STATUS_SUCCESS;
}

sai_status_t set_switch_attribute(
    _In_ sai_object_id_t switch_id,
    _In_ const sai_attribute_t *attr)
{
    return SAI_STATUS_NOT_IMPLEMENTED;
}

sai_status_t get_switch_attribute(
    _In_ sai_object_id_t switch_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
    for (int i = 0; i < attr_count; i++)
    {
        switch(attr_list[i].id)
        {
        case SAI_SWITCH_ATTR_TYPE:
            attr_list[i].value.u32 = SAI_SWITCH_TYPE_POE;
            break;
        case SAI_SWITCH_ATTR_SWITCH_HARDWARE_INFO:
            attr_list[i].value.s8list.count = 0;
            break;
        default:
            return SAI_STATUS_ATTR_NOT_IMPLEMENTED_0 + i;
        }
    }
    return SAI_STATUS_SUCCESS;
}

const sai_switch_api_t switch_api = {
    create_switch,
    remove_switch,
    set_switch_attribute,
    get_switch_attribute,
    NULL,  // sai_get_switch_stats_fn                get_switch_stats,
    NULL,  // sai_get_switch_stats_ext_fn            get_switch_stats_ext,
    NULL,  // sai_clear_switch_stats_fn              clear_switch_stats,
    NULL,  // sai_switch_mdio_read_fn                switch_mdio_read,
    NULL,  // sai_switch_mdio_write_fn               switch_mdio_write,
    NULL,  // sai_create_switch_tunnel_fn            create_switch_tunnel,
    NULL,  // sai_remove_switch_tunnel_fn            remove_switch_tunnel,
    NULL,  // sai_set_switch_tunnel_attribute_fn     set_switch_tunnel_attribute,
    NULL,  // sai_get_switch_tunnel_attribute_fn     get_switch_tunnel_attribute,
    NULL,  // sai_switch_mdio_cl22_read_fn           switch_mdio_cl22_read,
    NULL   // sai_switch_mdio_cl22_write_fn          switch_mdio_cl22_write,
};
