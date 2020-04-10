#ifndef RF62X_CORE_H
#define RF62X_CORE_H

#include "platform_types.h"

#include "memory_platform.h"
#include "iostream_platform.h"
#include "netwok_platform.h"


#if (defined _WIN32 && defined RF627_LIBRARY)
    #define dllexport __declspec(dllexport)
#else
    #define dllexport
#endif

/*! Return rf627 sdk version
 */
dllexport rfChar* core_version();

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

#endif // RF62X_CORE_H
