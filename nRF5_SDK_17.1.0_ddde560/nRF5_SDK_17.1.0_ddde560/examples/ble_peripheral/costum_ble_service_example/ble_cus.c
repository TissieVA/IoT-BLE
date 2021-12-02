#include "sdk_common.h"
#include "ble_srv_common.h"
#include "ble_cus.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"

/**@brief Function for adding the Custom Value characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t custom_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;        // sets the properties that will be displayed to the central during service discovery.
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value; //sets the UUID, points to the attribute metadata and sets the size of the characteristic
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;        // sets the properties( i.e. accessability of the attribute).

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;   //choosing the properties for the characteristics
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 0; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL; 
    char_md.p_sccd_md         = NULL;

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_cus_init->custom_value_char_attr_md.read_perm;
    attr_md.write_perm = p_cus_init->custom_value_char_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;  //Characteristic stored in the SoftDevice RAM section and not in the Application RAM section.
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CUSTOM_VALUE_CHAR_UUID;
    
    //populate the attr_char_value struct, which sets the UUID, points to the attribute metadata and sets the size of the characteristic, in our case a single byte(uint8_t).
    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(uint8_t);

    //we can add our characteristic by calling sd_ble_gatts_characteristic_add() with the structs as arguments.
    err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_cus->custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}

uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
    if (p_cus == NULL || p_cus_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_cus->conn_handle               = BLE_CONN_HANDLE_INVALID;

    // Add Custom Service UUID
    ble_uuid128_t base_uuid = {CUSTOM_SERVICE_UUID_BASE};
    err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_cus->uuid_type);
    VERIFY_SUCCESS(err_code);
    
    ble_uuid.type = p_cus->uuid_type;
    ble_uuid.uuid = CUSTOM_SERVICE_UUID;

    // Add the Custom Service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_cus->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    return err_code;

    // Add Custom Value characteristic
    return custom_value_char_add(p_cus, p_cus_init);
}


// void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
// {
//     ble_cus_t * p_cus = (ble_cus_t *) p_context;
    
//     if (p_cus == NULL || p_ble_evt == NULL) // its considered good practice to check that none of the pointers that we provided as arguments are NULL.
//     {
//         return;
//     }
    
//     switch (p_ble_evt->header.evt_id)   // add a switch-case to check which event that has been propagated to the application by the SoftDevice.
//     {
//         case BLE_GAP_EVT_CONNECTED:
//             on_connect(p_cus, p_ble_evt);
//             break;

//         case BLE_GAP_EVT_DISCONNECTED:
//             on_disconnect(p_cus, p_ble_evt);
//             break;

//         default:
//             // No implementation needed.
//             break;
//     }
// }

// /**@brief Function for handling the Connect event.
//  *
//  * @param[in]   p_cus       Custom Service structure.
//  * @param[in]   p_ble_evt   Event received from the BLE stack.
//  */
//  //when we get the Connect event assign the connection handle in the Custom Service structure to the connection handle that is passed with the event.
// static void on_connect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
// {
//     p_cus->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;   
// }

// /**@brief Function for handling the Disconnect event.
//  *
//  * @param[in]   p_cus       Custom Service structure.
//  * @param[in]   p_ble_evt   Event received from the BLE stack.
//  */
 
//  //when we get the Disconnect event, the only thing we need to do is invalidate the connection handle in the Custom Service structure since the connection is now dead.
// static void on_disconnect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
// {
//     UNUSED_PARAMETER(p_ble_evt);
//     p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;
// }

