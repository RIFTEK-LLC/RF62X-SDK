#ifndef RF627_CORE_H
#define RF627_CORE_H

#include "rf627_config.h"
#include "rf627_devices.h"


#if (defined _WIN32 && defined RF627_LIBRARY)
    #define dllexport __declspec(dllexport)
#else
    #define dllexport
#endif

/*! Return rf627 sdk version
 */
dllexport rfUint32 core_version();

/**
 * @brief init_platform_dependent_methods - init platform dependent methods and settings
 * @param memory_methods
 * @param iostream_methods
 * @param network_methods
 * @param adapter_settings
 */
dllexport void init_platform_dependent_methods(
        memory_platform_dependent_methods_t* memory_methods,
        iostream_platform_dependent_methods_t* iostream_methods,
        network_platform_dependent_methods_t* network_methods,
        network_platform_dependent_settings_t* adapter_settings);

/**
 * @brief init_platform_dependent_methods - change adapter's settings
 * @param adapter_settings
 */
dllexport void change_platform_adapter_settings(
        network_platform_dependent_settings_t* adapter_settings);

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

/*! Return structure containing device information about scanner rf627(smart) version
 */
//dllexport device_info_t rf627_smart_get_info(rf627_smart_t* device);

#endif // RF627_CORE_H
