#ifndef RF627_SDK_H
#define RF627_SDK_H

#include "platform_types.h"
#include "custom_vector.h"
#include "rf627_devices.h"
#include "rf627_types.h"

#if (defined _WIN32 && defined RF627_LIBRARY)
    #define dllexport __declspec(dllexport)
#else
    #define dllexport
#endif

/**
 * @brief change_platform_adapter_settings - change adapter's settings
 * @param adapter_settings
 */
dllexport void change_platform_adapter_settings(
        rfUint32 host_mask, rfUint32 host_ip_addr);

/**
 * @brief search - Search for RF627 devices over network
 * @param list - ptr to list of rf627 objects. If not null list will be filled with found devices
 * @param model - scanner's type (RF627-old, RF627-smart)
 * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
dllexport rfUint8 search_scanners(
        vector_t *list, scanner_types_t model, protocol_types_t protocol);

/**
 * @brief connect - Establish connection to the RF627 device
 * @param device - prt to scanner
 * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
dllexport rfUint8 connect_to_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief disconnect_from_scanner - Close connection to the device
 * @param device - prt to scanner
 * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
dllexport rfUint8 disconnect_from_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief get_profile - Get measurement from scanner's data stream
 * @param device - ptr to scanner
 * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return ptr to rf627_profile_t structure
 */
dllexport rf627_profile_t* get_profile_from_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief read_params_from_scanner - Read parameters from device to rfInternal structure.
 * This structure is accessible via get_params() function
 * @param device - ptr to scanner
 * @param protocol -  protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
dllexport rfUint8 read_params_from_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief write_params_to_scanner - Write current parameters to device's memory
 * @param device - ptr to scanner
 * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
 * @return 0 on success
 */
dllexport rfUint8 write_params_to_scanner(
        scanner_base_t *device, protocol_types_t protocol);

/**
 * @brief get_parameter - Search parameters by his name
 * @param device - ptr to scanner
 * @param param_name - name of parameter
 * @return param on success, else - null
 */
dllexport parameter_t* get_parameter(
        scanner_base_t *device, const rfChar* param_name);

/*! Return structure containing device information about scanner rf627(smart) version
 */
//dllexport device_info_t rf627_smart_get_info(rf627_smart_t* device);

#endif // RF627_SDK_H
