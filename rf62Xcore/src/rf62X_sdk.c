#include "rf62X_sdk.h"
#include <stdarg.h>
#include "custom_string.h"
#include "platform_types.h"
#include "netwok_platform.h"
#include "memory_platform.h"

void set_platform_adapter_settings(rfUint32 host_mask, rfUint32 host_ip_addr)
{
    set_adapter_settings(host_mask, host_ip_addr);
}

rfUint8 search_scanners(vector_t *list, scanner_types_t model, protocol_types_t protocol)
{
    switch (model) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
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
        case kSERVICE:
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


hello_information get_info_about_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    hello_information _hello_info = {0};
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            _hello_info.scanner_type = kRF627_OLD;
            _hello_info.protocol_type = kSERVICE;
            _hello_info.rf627old.hello_info_service_protocol = rf627_old_get_info_about_scanner_by_service_protocol(device->rf627_old);

            return _hello_info;
            break;
        }

        case kETHERNET_IP:
        case kMODBUS_TCP:
        {
            return _hello_info; // RF627-old doesn't support this protocol
            break;
        }

        default:
        {
            return _hello_info; // RF627-old doesn't support this protocol
            break;
        }
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
        {
            return _hello_info; // RF627-old doesn't support this protocol
            break;
        }
        }
        break;
    default:
    {
        return _hello_info; // RF627-old doesn't support this protocol
        break;
    }
    }
    return _hello_info; // RF627-old doesn't support this protocol
}


rfUint8 connect_to_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            rfBool result = FALSE;
            rfInt32 times = 3;
            for (rfInt32 i = 0; i < times; i++)
                if (rf627_old_connect(device->rf627_old))
                {
                    result = TRUE;
                    break;
                }
                else rf627_old_disconnect(device->rf627_old);
            return result;
        }
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
        case kSERVICE:
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
        case kSERVICE:
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
        case kSERVICE:
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

rf627_profile2D_t* get_profile2D_from_scanner(
        scanner_base_t *device, rfBool zero_points,  protocol_types_t protocol)
{
    rf627_profile2D_t* profile =
            memory_platform.rf_calloc(1 ,sizeof(rf627_profile2D_t));
    switch (device->type) {
    case kRF627_OLD:
        profile->type = kRF627_OLD;
        switch (protocol) {
        case kSERVICE:
            profile->rf627_profile2D = rf627_old_get_profile2D(device->rf627_old, zero_points);
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
        case kSERVICE:
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

rf627_profile3D_t* get_profile3D_from_scanner(
        scanner_base_t *device, rfFloat step_size, rfFloat k,
        count_types_t count_type,
        rfBool zero_points,
        protocol_types_t protocol)
{
    rf627_profile3D_t* profile =
            memory_platform.rf_calloc(1 ,sizeof(rf627_profile3D_t));
    switch (device->type) {
    case kRF627_OLD:
        profile->type = kRF627_OLD;
        switch (protocol) {
        case kSERVICE:
            profile->rf627_profile3D = rf627_old_get_profile3D(
                        device->rf627_old, step_size, k, count_type, zero_points, protocol);
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
        case kSERVICE:
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
        case kSERVICE:
        {
            rfUint16 count = 0;
            rfBool ret = 0;
            while (vector_count(device->rf627_old->params_list) > 0) {
                parameter_t* p = vector_get(device->rf627_old->params_list, vector_count(device->rf627_old->params_list)-1);

                if (rf_strcmp(p->base.type, pvtKey[PVT_UINT]) == 0)
                {
                    memory_platform.rf_free(p->val_uint32);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_UINT64]) == 0)
                {
                    memory_platform.rf_free(p->val_uint64);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_INT]) == 0)
                {
                    memory_platform.rf_free(p->val_int32);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_INT64]) == 0)
                {
                    memory_platform.rf_free(p->val_int64);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_FLOAT]) == 0)
                {
                    memory_platform.rf_free(p->val_flt);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_DOUBLE]) == 0)
                {
                    memory_platform.rf_free(p->val_dbl);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_ARRAY_UINT32]) == 0)
                {
                    //memory_platform.rf_free(p->arr_uint32->value);
                    //memory_platform.rf_free(p->arr_uint32->defValue);
                    memory_platform.rf_free(p->arr_uint32);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_ARRAY_UINT64]) == 0)
                {
                    memory_platform.rf_free(p->arr_uint64);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_ARRAY_INT32]) == 0)
                {
                    memory_platform.rf_free(p->arr_int32);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_ARRAY_INT64]) == 0)
                {
                    memory_platform.rf_free(p->arr_int64);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_ARRAY_FLT]) == 0)
                {
                    memory_platform.rf_free(p->arr_flt);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_ARRAY_DBL]) == 0)
                {
                    memory_platform.rf_free(p->arr_dbl);
                    //memory_platform.rf_free(p);
                }else if (rf_strcmp(p->base.type, pvtKey[PVT_STRING]) == 0)
                {
                    //memory_platform.rf_free(p->val_str->value);
                    memory_platform.rf_free(p->val_str);
                    //memory_platform.rf_free(p);
                }
                vector_delete(device->rf627_old->params_list, vector_count(device->rf627_old->params_list)-1);
                memory_platform.rf_free(p);
                count++;
            }
            ret = rf627_old_read_user_params_from_scanner(device->rf627_old);
            //ret = rf627_old_read_factory_params_from_scanner(device->rf627_old);
            return ret;
            break;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return 0; // RF627-old doesn't support this protocol
            break;
        default:
            return 0; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
            break;
        case kETHERNET_IP:
            break;
        case kMODBUS_TCP:
            break;
        default:
            return 0; // Unknown protocol type
            break;
        }
        break;
    default:
        return 0; // Unknown device type
        break;
    }
    return 0;
}

rfUint8 write_params_to_scanner(scanner_base_t *device, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
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
        case kSERVICE:
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
    return 1;
}

rfUint8 set_parameter_by_name(scanner_base_t *device, const char* param_name, rfUint32 count, va_list value)
{
    switch (device->type) {
    case kRF627_OLD:
    {
        return rf627_old_set_parameter_by_name(device->rf627_old, param_name, count, value);
        break;
    }
    case kRF627_SMART:
        break;
    default:
        break;
    }
    return 1;
}

rfUint8 send_command(
        scanner_base_t *device, command_t* command)
{
    switch (device->type) {
    case kRF627_OLD:
    {
        if(rf_strcmp("CID_PROFILE_SET_COUNTERS", command->name) == 0)
        {
            rfUint32 profile_counter = va_arg(command->arg_list, rfUint32);
            rfUint32 packet_counter = va_arg(command->arg_list, rfUint32);
            return rf627_old_command_set_counters(device->rf627_old, profile_counter, packet_counter);
        }
        break;
    }
    case kRF627_SMART:
        break;
    default:
        break;
    }
    return 1;
}

