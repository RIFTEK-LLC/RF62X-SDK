/**
 * @file
 * @brief Header file with a description of the basic functions
 *
 * This file contains definitions of the main
 * functions used for development.
 */


#ifndef RF62X_SDK_H
#define RF62X_SDK_H

#include "platform_types.h"
#include "custom_vector.h"
#include "rf62X_devices.h"
#include "rf62X_types.h"


#if (defined _WIN32 && defined RF62X_LIBRARY)
    #define API_EXPORT __declspec(dllexport)
#else
    #define API_EXPORT
#endif


/**
 * @brief change_platform_adapter_settings - change adapter's settings
 *
 * @param[in] subnet_mask Subnet mask on your local machine. A subnet mask is a
 *            number that defines a range of IP addresses that can be used in a
 *            network.
 * @param[in] host_ip_addr IP address of your network adapter(card)
 */
API_EXPORT void set_platform_adapter_settings(
        rfUint32 subnet_mask, rfUint32 host_ip_addr);


/**
 * @brief search - Search for RF62X devices over network
 *
 * @param[out] list Ptr to list of rf627 objects. If not null list will be
 *                  filled with found devices
 * @param[in] type Scanner's type (RF627-old, RF627-smart)
 * @param[in] timeout Time to search
 * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
 *
 * @return TRUE on success
 */
API_EXPORT rfUint8 search_scanners(
        vector_t *list, scanner_types_t type, uint32_t timeout, protocol_types_t protocol);

/**
 * @brief get_info_about_scanner - Get information about scanner from hello packet
 *
 * @param[in] device Ptr to scanner
 * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
 *
 * @return hello_information on success
 */
API_EXPORT hello_information get_info_about_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief connect_to_scanner - Establish connection to the RF62X device
 *
 * @param[in] device Ptr to scanner
 * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
 *
 * @return TRUE on success
 */
API_EXPORT rfUint8 connect_to_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief check_connection_to_scanner - Check connection to the RF62X device
 *
 * @param[in] device Ptr to scanner
 * @param[in] timeout Time to check connection
 * @param[in] protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
 *
 * @return TRUE on success
 */
API_EXPORT rfUint8 check_connection_to_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol);


/**
 * @brief disconnect_from_scanner - Close connection to the device
 *
 * @param[in] device Prt to scanner
 * @param[in] protocol Protocol's type (Service, ENIP, Modbus-TCP)
 *
 * @return TRUE on success
 */
API_EXPORT rfUint8 disconnect_from_scanner(
        scanner_base_t *device, protocol_types_t protocol);


/**
 * @brief free_scanner - Cleanup resources allocated by device
 *
 * @param[in] device Prt to scanner
 */
API_EXPORT void free_scanner(scanner_base_t *device);

/**
 * @brief get_profile - Get measurement from scanner's data stream
 * @param device - ptr to scanner
 * @param zero_points Enable zero points in return profile2D
 * @param realtime Enable getting profile in real time (buffering is disabled)
 * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return ptr to rf627_profile_t structure
 */
API_EXPORT rf627_profile2D_t* get_profile2D_from_scanner(
        scanner_base_t *device, rfBool zero_points, rfBool realtime, protocol_types_t protocol);


API_EXPORT rf627_profile3D_t* get_profile3D_from_scanner(
        scanner_base_t *device, rfFloat step_size, rfFloat k,
        count_types_t count_type,
        rfBool zero_points,
        protocol_types_t protocol);

API_EXPORT rf627_frame_t* get_frame_from_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief read_params_from_scanner - Read parameters from device to rfInternal structure.
 * This structure is accessible via get_params() function
 * @param device - ptr to scanner
 * @param protocol -  protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
API_EXPORT rfUint8 read_params_from_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol);

/**
 * @brief write_params_to_scanner - Write current parameters to device's memory
 * @param device - ptr to scanner
 * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
API_EXPORT rfUint8 write_params_to_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol);

/**
 * @brief get_parameter - Search parameters by his name
 * @param device - ptr to scanner
 * @param param_name - name of parameter
 * @return param on success, else - null
 */
API_EXPORT parameter_t* get_parameter(
        scanner_base_t *device, const rfChar* param_name);

/**
 * @brief set_parameter - Set parameter
 * @param device - ptr to scanner
 * @param param - setting parameter
 * @return 0 if success
 */
API_EXPORT rfUint8 set_parameter(
        scanner_base_t *device, parameter_t* param);

/**
 * @brief free_parameter - free parameter
 * @param param: ptr to parameter
 * @param type: scaner type
 */
API_EXPORT void free_parameter(
        parameter_t* param, scanner_types_t type);
/**
 * @brief set_parameter_by_name - Set parameters by his name
 * @param device - ptr to scanner
 * @param param_name - parameter name
 * @param value - value
 * @return 0 if success
 */
API_EXPORT rfUint8 set_parameter_by_name(
        scanner_base_t *device, const char* param_name, rfUint32 count, va_list value);

/**
 * @brief set_parameter - Search parameters by his name
 * @param device - ptr to scanner
 * @param param_name - name of parameter
 * @return param on success, else - null
 */
API_EXPORT rfUint8 send_command(
        scanner_base_t *device, command_t* command);

/**
 * @brief set_parameter - Search parameters by his name
 * @param device - ptr to scanner
 * @param param_name - name of parameter
 * @return param on success, else - null
 */
API_EXPORT rfUint8 send_command2(
        scanner_base_t *device, command2_t* command);

API_EXPORT rfUint8 get_authorization_token_from_scanner(
        scanner_base_t *device, char** token, uint32_t* token_size, uint32_t timeout, protocol_types_t protocol);

API_EXPORT rfUint8 set_authorization_key_to_scanner(
        scanner_base_t *device, char* key, uint32_t key_size, uint32_t timeout, protocol_types_t protocol);

API_EXPORT rfUint8 read_calibration_table_from_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol);
API_EXPORT rf627_calib_table_t* convert_calibration_table_from_bytes(char* bytes, uint32_t data_size);
API_EXPORT rfBool convert_calibration_table_to_bytes(rf627_calib_table_t* table, char** bytes, uint32_t* data_size);
API_EXPORT rfUint8 write_calibration_table_to_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol);

API_EXPORT rf627_calib_table_t* get_calibration_table_from_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol);
API_EXPORT rfUint8 set_calibration_table_to_scanner(
        scanner_base_t *device, rf627_calib_table_t* table, uint32_t timeout, protocol_types_t protocol);

API_EXPORT rfUint8 save_calibration_table_to_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol);


/*! Return structure containing device information about scanner rf627(smart) version
 */
//dllexport device_info_t rf627_smart_get_info(rf627_smart_t* device);

#endif // RF62X_SDK_H
