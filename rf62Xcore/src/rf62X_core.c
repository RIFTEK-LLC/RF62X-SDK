#include "rf62X_core.h"
#include "endian_conv.h"

#define CORE_VERSION "1.3.0"

rfChar* core_version()
{
    return CORE_VERSION;
}

void init_platform_dependent_methods(
        memory_platform_dependent_methods_t* memory_methods,
        iostream_platform_dependent_methods_t* iostream_methods,
        network_platform_dependent_methods_t* network_methods,
        network_platform_dependent_settings_t* adapter_settings)
{
    init_memory_platform(memory_methods);
    init_iostream_platform(iostream_methods);
    init_network_platform(network_methods);
    set_adapter_settings(adapter_settings->host_mask, adapter_settings->host_ip_addr);
    determine_endianess();
}


