#ifndef RF62X_DEVICES_H
#define RF62X_DEVICES_H

#include "rf62X_types.h"
#include "custom_vector.h"
#include "smartchannel.h"


//
// RF627
// old version (v1.x.x)
//

typedef struct
{
    config_options_t options;
    rf627_old_factory_params_t factory_params;
    rf627_old_user_params_t user_params;

    void* m_svc_sock;
    void* m_data_sock;
    rfUint16 msg_count;
    rfUint32 host_ip;

    vector_t *params_list;

    rf627_old_hello_info_by_service_protocol info_by_service_protocol;

}rf627_old_t;


/**
 * @brief rf627_old_search - Search for RF627-old devices over network
 * @param list - ptr to list of rf627-old objects. If not null list will be filled with found devices
 * @param ip_addr - the IP address of the adapter on which the connection should be established.
 * @return 0 on success
 */
uint8_t rf627_old_search_by_service_protocol(vector_t* list, rfUint32 ip_addr);


/**
 * @brief rf627_old_create_from_hello_msg
 * @param msg_info
 * @param init_msg_count
 * @return
 */
rf627_old_t* rf627_old_create_from_hello_msg(
        void* msg_info, rfUint16 init_msg_count);

/**
 * @brief get_hello_info_of_scanners - Get information about scanner from hello packet
 * @param device - prt to scanner
 * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
rf627_old_hello_info_by_service_protocol* rf627_old_get_info_about_scanner_by_service_protocol(rf627_old_t* scanner);

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
 * @param zero_points - include zero points in return profile2D
 * @return ptr to rf627_old_profile_t structure
 */
rf627_old_profile2D_t* rf627_old_get_profile2D(rf627_old_t* scanner, rfBool zero_points);

/**
 * @brief rf627_old_get_profile - Get measurement from scanner's data stream
 * @param scanner - ptr to device
 * @param zero_points - include zero points in return profile2D
 * @return ptr to rf627_old_profile_t structure
 */
rf627_old_profile3D_t* rf627_old_get_profile3D(
        rf627_old_t* scanner, rfFloat step_size, rfFloat k,
        count_types_t count_type,
        rfBool zero_points,
        protocol_types_t protocol);

/**
 * @brief read_params_from_scanner - Read parameters from device to rfInternal structure.
 * This structure is accessible via get_params() function
 * @param scanner - ptr to scanner
 * @return 0 on success
 */
rfBool rf627_old_read_user_params_from_scanner(rf627_old_t* scanner);

/**
 * @brief read_params_from_scanner - Read parameters from device to rfInternal structure.
 * This structure is accessible via get_params() function
 * @param scanner - ptr to scanner
 * @return 0 on success
 */
rfBool rf627_old_read_factory_params_from_scanner(rf627_old_t* scanner);

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
 * @brief rf627_old_set_parameter - set parameters
 * @param scanner - ptr to scanner
 * @param param - ptr to parameter
 * @return 0 on success
 */
rfUint8 rf627_old_set_parameter(
        rf627_old_t* scanner, parameter_t* param);

/**
 * @brief rf627_old_set_parameter_by_name - set parameter by his name
 * @param scanner - ptr to scanner
 * @param param_name - param name
 * @param value - setting value
 * @return 0 on success
 */
rfUint8 rf627_old_set_parameter_by_name(
        rf627_old_t* scanner, const rfChar* param_name, rfUint32 count, va_list value);

/**
 * @brief rf627_old_command_set_counters
 * @param scanner
 * @param profile_counter
 * @param packet_counter
 * @return 0 on success
 */
rfUint8 rf627_old_command_set_counters(
        rf627_old_t* scanner, rfUint32 profile_counter, rfUint32 packet_counter);

/**
 * @brief rf627_old_command_set_counters
 * @param scanner
 * @param profile_counter
 * @param packet_counter
 * @return 0 on success
 */
rfUint8 rf627_old_command_periphery_send(
        rf627_old_t* scanner,
        rfUint16 input_size, void* input_data,
        rfUint16* output_size, void** output_data);


//
// RF627
// smart version (v2.x.x)
//

typedef struct
{
    smart_channel* channel;

    vector_t *params_list;
}rf627_smart_t;

/**
 * @brief rf627_old_search - Search for RF627-old devices over network
 * @param list - ptr to list of rf627-old objects. If not null list will be filled with found devices
 * @param ip_addr - the IP address of the adapter on which the connection should be established.
 * @return 0 on success
 */
uint8_t rf627_smart_search_by_service_protocol(vector_t* list, rfUint32 ip_addr);



typedef struct
{
    scanner_types_t type;
    union{
        rf627_old_t* rf627_old;
        rf627_smart_t* rf627_smart;
    };
}scanner_base_t;



#endif // RF62X_DEVICES_H
