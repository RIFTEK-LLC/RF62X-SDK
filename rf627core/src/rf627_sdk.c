#include "rf627_sdk.h"

void set_platform_adapter_settings(rfUint32 host_mask, rfUint32 host_ip_addr)
{
    set_adapter_settings(host_mask, host_ip_addr);
}

rfUint8 search_scanners(vector_t *list, scanner_types_t model, protocol_types_t protocol)
{
    switch (model) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            rf627_old_search_by_service_protocol(
                        list, network_platform.network_settings.host_ip_addr);
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return 1; // RF627-old doesn't support this protocol
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    default:
        return 2; // Unknown device type
        break;
    }
    return 0;
}


rfUint8 connect_to_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            return rf627_old_connect(device->rf627_old);
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return 1; // RF627-old doesn't support this protocol
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    default:
        return 2; // Unknown device type
        break;
    }
    return 0;
}

rfUint8 disconnect_from_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            rf627_old_disconnect(device->rf627_old);
            return 0;
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return 1; // RF627-old doesn't support this protocol
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    default:
        return 2; // Unknown device type
        break;
    }
    return 0;
}

rf627_profile_t* get_profile_from_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    rf627_profile_t* profile =
            memory_platform.rf_calloc(1 ,sizeof(rf627_profile_t));
    switch (device->type) {
    case kRF627_OLD:
        profile->type = kRF627_OLD;
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            profile->rf627_profile = rf627_old_get_profile(device->rf627_old);
            return profile;
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return NULL; // RF627-old doesn't support this protocol
            break;
        default:
            return NULL; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        profile->type = kRF627_SMART;
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
            return NULL; // Unknown protocol type
            break;
        }
        break;
    default:
        return NULL; // Unknown device type
        break;
    }
    return 0;
}

rfUint8 read_params_from_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            return rf627_old_read_params_from_scanner(device->rf627_old);
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return 1; // RF627-old doesn't support this protocol
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    default:
        return 2; // Unknown device type
        break;
    }
    return 0;
}

rfUint8 write_params_to_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            rf627_old_write_params_to_scanner(device->rf627_old);
            return 0;
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return 1; // RF627-old doesn't support this protocol
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE_PROTOKOL:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
            return 1; // Unknown protocol type
            break;
        }
        break;
    default:
        return 2; // Unknown device type
        break;
    }
    return 0;
}

parameter_t* get_parameter(scanner_base_t *device, const rfChar *param_name)
{
    switch (device->type) {
    case kRF627_OLD:
    {
        return rf627_old_get_parameter(device->rf627_old, param_name);
        break;
    }
    case kRF627_SMART:
        break;
    default:
        break;
    }
    return NULL;
}

rfUint8 set_parameter(scanner_base_t *device, parameter_t* param)
{
    switch (device->type) {
    case kRF627_OLD:
    {
        return rf627_old_set_parameter(device->rf627_old, param);
        break;
    }
    case kRF627_SMART:
        break;
    default:
        break;
    }
    return NULL;
}
