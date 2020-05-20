/**
 * @file
 * @brief Header file with a description of the functions to run the core
 *
 * This file contains definitions of the main
 * functions used to initialize the core.
 */

#ifndef RF62X_CORE_H
#define RF62X_CORE_H

#include "platform_types.h"

#include "memory_platform.h"
#include "iostream_platform.h"
#include "netwok_platform.h"


#if (defined _WIN32 && defined RF627_LIBRARY)
    #define API_EXPORT __declspec(dllexport)
#else
    #define API_EXPORT
#endif

/**
 * @brief core_version - Return rf627 sdk version.
 * @return ptr to rfChar
 */
API_EXPORT rfChar* core_version();


/*!
 * @brief init_platform_dependent_methods - Init platform dependent methods and settings
 * @param memory_methods Structure with platform-specific methods for work with memory
 * @param iostream_methods Structure with platform-specific methods for work with iostream
 * @param network_methods Structure with platform-specific methods for work with network
 * @param adapter_settings Structure with platform-specific settings
 */
API_EXPORT void init_platform_dependent_methods(
        memory_platform_dependent_methods_t* memory_methods,
        iostream_platform_dependent_methods_t* iostream_methods,
        network_platform_dependent_methods_t* network_methods,
        network_platform_dependent_settings_t* adapter_settings);

#endif // RF62X_CORE_H
