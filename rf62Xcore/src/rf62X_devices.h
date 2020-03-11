#ifndef RF62X_DEVICES_H
#define RF62X_DEVICES_H

#include "rf62X_types.h"
#include "custom_vector.h"

typedef struct
{
    config_options_t options;
    factory_params_t factory_params;
    rf627_old_user_params_t user_params;

    void* m_svc_sock;
    void* m_data_sock;
    rfUint16 msg_count;

    vector_t *params_list;

}rf627_old_t;



/*! Return rf627-old api version
 */
rfUint32 rf627_old_api_version();

/**
 * @brief rf627_old_search - Search for RF627-old devices over network
 * @param list - ptr to list of rf627-old objects. If not null list will be filled with found devices
 * @param ip_addr - the IP address of the adapter on which the connection should be established.
 * @return 0 on success
 */
uint8_t rf627_old_search_by_service_protocol(vector_t* list, rfUint32 ip_addr);

/**
 * @brief rf627_old_mutex_lock
 * @return
 */
int rf627_old_mutex_lock();

/**
 * @brief rf627_old_mutex_trylock
 * @return
 */
int rf627_old_mutex_trylock();

/**
 * @brief rf627_old_mutex_unlock
 * @return
 */
int rf627_old_mutex_unlock();

/**
 * @brief rf627_old_create_from_hello_msg
 * @param msg_info
 * @param init_msg_count
 * @return
 */
rf627_old_t* rf627_old_create_from_hello_msg(
        void* msg_info, rfUint16 init_msg_count);

/**
 * @brief rf627_old_connect - Establish connection to the device
 * @param scanner - ptr to device
 * @return true on success
 */
rfBool rf627_old_connect(rf627_old_t* scanner);

/**
 * @brief rf627_old_disconnect - Close connection to the device
 * @param scanner - ptr to device
 */
void rf627_old_disconnect(rf627_old_t* scanner);

/**
 * @brief rf627_old_get_profile - Get measurement from scanner's data stream
 * @param scanner - ptr to device
 * @return ptr to rf627_old_profile_t structure
 */
rf627_old_profile_t* rf627_old_get_profile(rf627_old_t* scanner);

/**
 * @brief read_params_from_scanner - Read parameters from device to rfInternal structure.
 * This structure is accessible via get_params() function
 * @param scanner - ptr to scanner
 * @return 0 on success
 */
rfBool rf627_old_read_params_from_scanner(rf627_old_t* scanner);

/**
 * @brief rf627_old_write_params_to_scanner - Write current parameters to device.
 * @param scanner - ptr to scanner
 * @return 0 on success
 */
rfBool rf627_old_write_params_to_scanner(rf627_old_t* scanner);

/**
 * @brief rf627_old_get_parameter - Search parameters by his name
 * @param scanner - ptr to scanner
 * @param param_name - name of parameter
 * @return param on success, else - null
 */
parameter_t* rf627_old_get_parameter(
        rf627_old_t* scanner, const rfChar* param_name);

/**
 * @brief rf627_old_set_parameter - Search parameters by his name
 * @param scanner - ptr to scanner
 * @param param - ptr to parameter
 * @return 0 on success
 */
rfUint8 rf627_old_set_parameter(
        rf627_old_t* scanner, parameter_t* param);

/**
 * @brief rf627_old_command_set_counters
 * @param scanner
 * @param profile_counter
 * @param packet_counter
 * @return 0 on success
 */
rfUint8 rf627_old_command_set_counters(
        rf627_old_t* scanner, rfUint32 profile_counter, rfUint32 packet_counter);


typedef struct
{
    void* m_svc_sock;
    void* m_data_sock;
    rfUint16 msg_count;

    vector_t *params_list;
}rf627_smart_t;



typedef struct
{
    scanner_types_t type;
    union{
        rf627_old_t* rf627_old;
        rf627_smart_t* rf627_smart;
    };
}scanner_base_t;



#endif // RF62X_DEVICES_H
