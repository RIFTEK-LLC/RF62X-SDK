#include "rf62X_sdk.h"
#include <stdarg.h>
#include "custom_string.h"
#include "platform_types.h"
#include "netwok_platform.h"
#include "memory_platform.h"

#include <mpack/mpack.h>

#ifndef _WIN32
typedef int BOOL;
typedef int SOCKET;

#define INVALID_SOCKET          (-1)
#define SOCKET_ERROR            (-1)
#define TRUE 1
#define FALSE 0
#endif

void set_platform_adapter_settings(rfUint32 host_mask, rfUint32 host_ip_addr)
{
    set_adapter_settings(host_mask, host_ip_addr);
}

rfUint8 search_scanners(vector_t *list, scanner_types_t model, rfUint32 timeout, protocol_types_t protocol)
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
            rf627_smart_search_by_service_protocol(
                        list, network_platform.network_settings.host_ip_addr, timeout);
            break;
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
        {
            _hello_info.scanner_type = kRF627_SMART;
            _hello_info.protocol_type = kSERVICE;
            _hello_info.rf627smart.hello_info_service_protocol =
                    rf627_smart_get_scanner_info_by_service_protocol(device->rf627_smart);

            return _hello_info;
            break;
        }
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
        {
            rfBool result = FALSE;
            rfInt32 times = 3;
            for (rfInt32 i = 0; i < times; i++)
                if (rf627_smart_connect(device->rf627_smart))
                {
                    result = TRUE;
                    break;
                }
                else rf627_smart_disconnect(device->rf627_smart);
            return result;
        }
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
            return TRUE;
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
            rf627_smart_disconnect(device->rf627_smart);
            return TRUE;
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

extern uint8_t ip_string_to_uint32 (const char*  ip_string, uint32_t* ip_addr);

rf627_profile2D_t* get_profile2D_from_scanner(
        scanner_base_t *device, rfBool zero_points, rfBool realtime, protocol_types_t protocol)
{
    rf627_profile2D_t* profile =
            memory_platform.rf_calloc(1 ,sizeof(rf627_profile2D_t));
    switch (device->type) {
    case kRF627_OLD:
        profile->type = kRF627_OLD;
        switch (protocol) {
        case kSERVICE:
            if (realtime)
            {
                if (((scanner_base_t*)device)->rf627_old->m_data_sock != NULL)
                {
                    if ((SOCKET)((scanner_base_t*)device)->rf627_old->m_data_sock != INVALID_SOCKET)
                    {
                        network_platform.network_methods.close_socket(
                                    ((scanner_base_t*)device)->rf627_old->m_data_sock);
                    }
                    ((scanner_base_t*)device)->rf627_old->m_data_sock = NULL;
                }

                rfUint32 recv_ip_addr;
                rfUint16 recv_port;
                rfInt nret;


                ((scanner_base_t*)device)->rf627_old->m_data_sock =
                        network_platform.network_methods.create_udp_socket();
                if (((scanner_base_t*)device)->rf627_old->m_data_sock != (void*)INVALID_SOCKET)
                {
                    nret = 1;
                    network_platform.network_methods.set_reuseaddr_socket_option(
                                ((scanner_base_t*)device)->rf627_old->m_data_sock);

                    network_platform.network_methods.set_socket_recv_timeout(
                                ((scanner_base_t*)device)->rf627_old->m_data_sock, 100);
                    //recv_addr.sin_family = RF_AF_INET;
                    recv_port = ((scanner_base_t*)device)->rf627_old->info_by_service_protocol.profile_port;

                    //recv_addr.sin_addr = RF_INADDR_ANY;
                    recv_ip_addr = ((scanner_base_t*)device)->rf627_old->host_ip;

                    nret = network_platform.network_methods.socket_bind(
                                ((scanner_base_t*)device)->rf627_old->m_data_sock, recv_ip_addr, recv_port);
                    if (nret == RF_SOCKET_ERROR)
                    {
                        network_platform.network_methods.close_socket(((scanner_base_t*)device)->rf627_old->m_data_sock);
                        ((scanner_base_t*)device)->rf627_old->m_data_sock = NULL;
                        return NULL;
                    }
                }
            }
            profile->rf627old_profile2D = rf627_old_get_profile2D(device->rf627_old, zero_points);
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
            if (realtime)
            {
                if (((scanner_base_t*)device)->rf627_smart->m_data_sock != NULL)
                {
                    if ((SOCKET)((scanner_base_t*)device)->rf627_smart->m_data_sock != INVALID_SOCKET)
                    {
                        network_platform.network_methods.close_socket(
                                    ((scanner_base_t*)device)->rf627_smart->m_data_sock);
                    }
                    ((scanner_base_t*)device)->rf627_smart->m_data_sock = NULL;
                }

                rfUint32 recv_ip_addr;
                rfUint16 recv_port;
                rfInt nret;


                ((scanner_base_t*)device)->rf627_smart->m_data_sock =
                        network_platform.network_methods.create_udp_socket();
                if (((scanner_base_t*)device)->rf627_smart->m_data_sock != (void*)INVALID_SOCKET)
                {
                    nret = 1;
                    network_platform.network_methods.set_reuseaddr_socket_option(
                                ((scanner_base_t*)device)->rf627_smart->m_data_sock);

                    network_platform.network_methods.set_socket_recv_timeout(
                                ((scanner_base_t*)device)->rf627_smart->m_data_sock, 100);
                    //recv_addr.sin_family = RF_AF_INET;
                    recv_port = ((scanner_base_t*)device)->rf627_smart->info_by_service_protocol.user_network_hostPort;

                    //recv_addr.sin_addr = RF_INADDR_ANY;
                    ip_string_to_uint32(((scanner_base_t*)device)->rf627_smart->
                                        info_by_service_protocol.user_network_hostIP, &recv_ip_addr);

                    nret = network_platform.network_methods.socket_bind(
                                ((scanner_base_t*)device)->rf627_smart->m_data_sock, recv_ip_addr, recv_port);
                    if (nret == RF_SOCKET_ERROR)
                    {
                        network_platform.network_methods.close_socket(((scanner_base_t*)device)->rf627_smart->m_data_sock);
                        ((scanner_base_t*)device)->rf627_smart->m_data_sock = NULL;
                        return NULL;
                    }
                }
            }
            profile->rf627smart_profile2D = rf627_smart_get_profile2D(device->rf627_smart, zero_points);
            return profile;
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

void free_smart_parameter(parameter_t* p)
{
    if (rf_strcmp(p->base.type, parameter_value_types[PVT_UINT]) == 0)
    {
        if(p->val_uint32->enumValues != NULL)
        {
            for(int i = 0; i < p->val_uint32->enumValues->recCount; i++)
            {
                free(p->val_uint32->enumValues->rec[i].key);
                p->val_uint32->enumValues->rec[i].key = NULL;
                free(p->val_uint32->enumValues->rec[i].label);
                p->val_uint32->enumValues->rec[i].label = NULL;
            }
            free(p->val_uint32->enumValues->rec); p->val_uint32->enumValues->rec = NULL;
            free(p->val_uint32->enumValues); p->val_uint32->enumValues = NULL;
        }
        memory_platform.rf_free(p->val_uint32); p->val_uint32 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }

        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_UINT64]) == 0)
    {
        memory_platform.rf_free(p->val_uint64); p->val_uint64 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_INT]) == 0)
    {
        memory_platform.rf_free(p->val_int32); p->val_int32 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_INT64]) == 0)
    {
        memory_platform.rf_free(p->val_int64); p->val_int64 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_FLOAT]) == 0)
    {
        memory_platform.rf_free(p->val_flt); p->val_flt = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_DOUBLE]) == 0)
    {
        memory_platform.rf_free(p->val_dbl); p->val_dbl = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_UINT32]) == 0)
    {
        memory_platform.rf_free(p->arr_uint32->value); p->arr_uint32->value = NULL;
        memory_platform.rf_free(p->arr_uint32->defValue); p->arr_uint32->defValue = NULL;
        memory_platform.rf_free(p->arr_uint32); p->arr_uint32 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_UINT64]) == 0)
    {
        memory_platform.rf_free(p->arr_uint64->value); p->arr_uint64->value = NULL;
        memory_platform.rf_free(p->arr_uint64->defValue); p->arr_uint64->defValue = NULL;
        memory_platform.rf_free(p->arr_uint64); p->arr_uint64 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_INT32]) == 0)
    {
        memory_platform.rf_free(p->arr_int32->value); p->arr_int32->value = NULL;
        memory_platform.rf_free(p->arr_int32->defValue); p->arr_int32->defValue = NULL;
        memory_platform.rf_free(p->arr_int32); p->arr_int32 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_INT64]) == 0)
    {
        memory_platform.rf_free(p->arr_int64->value); p->arr_int64->value = NULL;
        memory_platform.rf_free(p->arr_int64->defValue); p->arr_int64->defValue = NULL;
        memory_platform.rf_free(p->arr_int64); p->arr_int64 = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_FLT]) == 0)
    {
        memory_platform.rf_free(p->arr_flt->value); p->arr_flt->value = NULL;
        memory_platform.rf_free(p->arr_flt->defValue); p->arr_flt->defValue = NULL;
        memory_platform.rf_free(p->arr_flt); p->arr_flt = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_DBL]) == 0)
    {
        memory_platform.rf_free(p->arr_dbl->value); p->arr_dbl->value = NULL;
        memory_platform.rf_free(p->arr_dbl->defValue); p->arr_dbl->defValue = NULL;
        memory_platform.rf_free(p->arr_dbl); p->arr_dbl = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_STRING]) == 0)
    {
        memory_platform.rf_free(p->val_str->value); p->val_str->value = NULL;
        memory_platform.rf_free(p->val_str->defValue); p->val_str->defValue = NULL;
        memory_platform.rf_free(p->val_str); p->val_str = NULL;
        memory_platform.rf_free(p->base.name); p->base.name = NULL;
        memory_platform.rf_free(p->base.access); p->base.access = NULL;
        if (p->base.units != NULL && (rf_strcmp(p->base.units, "") != 0))
        {
            memory_platform.rf_free(p->base.units); p->base.units = NULL;
        }
    }
    memory_platform.rf_free(p);
    p = NULL;
}

void free_old_parameter(parameter_t* p)
{
    if (rf_strcmp(p->base.type, parameter_value_types[PVT_UINT]) == 0)
    {
        memory_platform.rf_free(p->val_uint32);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_UINT64]) == 0)
    {
        memory_platform.rf_free(p->val_uint64);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_INT]) == 0)
    {
        memory_platform.rf_free(p->val_int32);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_INT64]) == 0)
    {
        memory_platform.rf_free(p->val_int64);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_FLOAT]) == 0)
    {
        memory_platform.rf_free(p->val_flt);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_DOUBLE]) == 0)
    {
        memory_platform.rf_free(p->val_dbl);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_UINT32]) == 0)
    {
        //memory_platform.rf_free(p->arr_uint32->value);
        //memory_platform.rf_free(p->arr_uint32->defValue);
        memory_platform.rf_free(p->arr_uint32);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_UINT64]) == 0)
    {
        memory_platform.rf_free(p->arr_uint64);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_INT32]) == 0)
    {
        memory_platform.rf_free(p->arr_int32);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_INT64]) == 0)
    {
        memory_platform.rf_free(p->arr_int64);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_FLT]) == 0)
    {
        memory_platform.rf_free(p->arr_flt);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_ARRAY_DBL]) == 0)
    {
        memory_platform.rf_free(p->arr_dbl);
        //memory_platform.rf_free(p);
    }else if (rf_strcmp(p->base.type, parameter_value_types[PVT_STRING]) == 0)
    {
        //memory_platform.rf_free(p->val_str->value);
        memory_platform.rf_free(p->val_str);
        //memory_platform.rf_free(p);
    }
    memory_platform.rf_free(p);
}

rfUint8 read_params_from_scanner(scanner_base_t *device, uint32_t timeout, protocol_types_t protocol)
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
                vector_delete(device->rf627_old->params_list, vector_count(device->rf627_old->params_list)-1);
                free_old_parameter(p);
                count++;
            }
            ret = rf627_old_read_user_params_from_scanner(device->rf627_old);
            ret = rf627_old_read_factory_params_from_scanner(device->rf627_old);
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
        {
            rfUint16 count = 0;
            rfBool ret = 0;
            while (vector_count(device->rf627_smart->params_list) > 0) {
                parameter_t* p = vector_get(device->rf627_smart->params_list, vector_count(device->rf627_smart->params_list)-1);
                vector_delete(device->rf627_smart->params_list, vector_count(device->rf627_smart->params_list)-1);
                free_smart_parameter(p);
                count++;
            }
            ret = rf627_smart_read_params_from_scanner(device->rf627_smart, timeout);
            return ret;
            break;
        }
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

rfUint8 write_params_to_scanner(scanner_base_t *device, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
            rf627_old_write_params_to_scanner(device->rf627_old);
            return TRUE;
            break;
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
            rf627_smart_write_params_to_scanner(device->rf627_smart, timeout);
            return TRUE;
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
    {
        return rf627_smart_get_parameter(device->rf627_smart, param_name);
        break;
    }
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
    {
        return rf627_smart_set_parameter(device->rf627_smart, param);
        break;
    }
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


rfUint8 send_command2(
        scanner_base_t *device, command2_t* command)
{
    switch (device->type) {
    case kRF627_OLD:
    {
        if(rf_strcmp("CID_PERIPHERY_SEND", command->name) == 0)
        {
            return rf627_old_command_periphery_send(
                        device->rf627_old,
                        command->input.size, command->input.payload,
                        &command->output.size, &command->output.payload);
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

void free_parameter(parameter_t *param, scanner_types_t type)
{
    switch (type) {
    case kRF627_OLD:
    {
        free_old_parameter(param);
        break;
    }
    case kRF627_SMART:
        free_smart_parameter(param);
        break;
    default:
        break;
    }
}

rf627_frame_t* get_frame_from_scanner(scanner_base_t* device, protocol_types_t protocol)
{
    rf627_frame_t* frame =
            memory_platform.rf_calloc(1 ,sizeof(rf627_frame_t));
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
            //char* frame = rf627_old_get_profile2D(device->rf627_old, zero_points);
            //return frame;
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
        switch (protocol) {
        case kSERVICE:
            frame->type = kRF627_SMART;
            frame->rf627smart_frame = rf627_smart_get_frame(device->rf627_smart, 200);
            return frame;
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

rfUint8 check_connection_to_scanner(scanner_base_t *device, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            return FALSE;
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
        {
            rfBool result = FALSE;
            result = rf627_smart_check_connection_by_service_protocol(device->rf627_smart, timeout);
            return result;
        }
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

rfUint8 get_authorization_token_from_scanner(scanner_base_t *device, char **token, uint32_t* token_size, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            return FALSE;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
        {
            rfBool result = FALSE;
            result = rf627_smart_get_authorization_token_by_service_protocol(device->rf627_smart, token, token_size, timeout);
            return result;
        }
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

rfUint8 set_authorization_key_to_scanner(scanner_base_t *device, char *key, uint32_t key_size, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            return FALSE;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
        {
            rfBool result = FALSE;
            result = rf627_smart_set_authorization_key_by_service_protocol(device->rf627_smart, key, key_size, timeout);
            return result;
        }
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

rfBool read_calibration_table_from_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            return FALSE;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
        {
            rfBool status = FALSE;
            status = rf627_smart_read_calibration_table_by_service_protocol(device->rf627_smart, timeout);         
            return status;
        }
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
rf627_calib_table_t* get_calibration_table_from_scanner(
        scanner_base_t *device, uint32_t timeout, protocol_types_t protocol)
{
    rf627_calib_table_t* _table = calloc(1, sizeof(rf627_calib_table_t));
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            _table->type = kRF627_OLD;
            _table->rf627old_calib_table = NULL;
            return _table;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
        {
            _table->type = kRF627_SMART;
            _table->rf627smart_calib_table = rf627_smart_get_calibration_table(device->rf627_smart);
            return _table;
        }
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
rfUint8 set_calibration_table_to_scanner(scanner_base_t *device, rf627_calib_table_t* table, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            return FALSE;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
        {
            rfBool result = FALSE;
            result = rf627_smart_set_calibration_table(device->rf627_smart, table->rf627smart_calib_table);
            return result;
        }
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

rfUint8 write_calibration_table_to_scanner(scanner_base_t *device, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            return FALSE;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
        {
            rfBool result = FALSE;
            result = rf627_smart_write_calibration_data_by_service_protocol(device->rf627_smart, timeout);
            return result;
        }
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

rfUint8 save_calibration_table_to_scanner(scanner_base_t *device, uint32_t timeout, protocol_types_t protocol)
{
    switch (device->type) {
    case kRF627_OLD:
        switch (protocol) {
        case kSERVICE:
        {
            return FALSE;
        }
        case kETHERNET_IP:
        case kMODBUS_TCP:
            return FALSE; // RF627-old doesn't support this protocol
            break;
        default:
            return FALSE; // Unknown protocol type
            break;
        }
        break;
    case kRF627_SMART:
        switch (protocol) {
        case kSERVICE:
        {
            rfBool result = FALSE;
            result = rf627_smart_save_calibration_data_by_service_protocol(device->rf627_smart, timeout);
            return result;
        }
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

rfBool convert_calibration_table_to_bytes(rf627_calib_table_t* table, char** bytes, uint32_t* data_size)
{
    // Create calib_file
    mpack_writer_t writer;
    char* calib_file = NULL;
    size_t calib_file_size = 0;
    mpack_writer_init_growable(&writer, &calib_file, &calib_file_size);

    // Идентификатор сообщения для подтверждения
    mpack_start_map(&writer, 10);
    {
        mpack_write_cstr(&writer, "type");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_Type);

        mpack_write_cstr(&writer, "crc");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_CRC16);

        mpack_write_cstr(&writer, "serial");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_Serial);

        mpack_write_cstr(&writer, "data_row_length");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_DataRowLength);

        mpack_write_cstr(&writer, "width");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_Width);

        mpack_write_cstr(&writer, "height");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_Height);

        mpack_write_cstr(&writer, "mult_w");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_MultW);

        mpack_write_cstr(&writer, "mult_h");
        mpack_write_uint(&writer, table->rf627smart_calib_table->m_MultH);

        mpack_write_cstr(&writer, "time_stamp");
        mpack_write_int(&writer, table->rf627smart_calib_table->m_TimeStamp);

        mpack_write_cstr(&writer, "data");
        mpack_write_bin(&writer, (char*)table->rf627smart_calib_table->m_Data,
                        table->rf627smart_calib_table->m_DataSize);
    }mpack_finish_map(&writer);

    // finish writing
    if (mpack_writer_destroy(&writer) != mpack_ok) {
        fprintf(stderr, "An error occurred encoding the data!\n");
        return FALSE;
    }

    *data_size = calib_file_size;
    *bytes = calloc(calib_file_size, sizeof (char));
    memcpy(*bytes, calib_file, calib_file_size);
    free(calib_file);
    return TRUE;
}

rf627_calib_table_t *convert_calibration_table_from_bytes(char *bytes, uint32_t data_size)
{
    mpack_tree_t tree;
    mpack_tree_init_data(&tree, (const char*)bytes, data_size);
    mpack_tree_parse(&tree);
    if (mpack_tree_error(&tree) != mpack_ok)
    {
        mpack_tree_destroy(&tree);
        return NULL;
    }
    mpack_node_t root = mpack_tree_root(&tree);

    rf627_calib_table_t* _table =
            (rf627_calib_table_t*)calloc(1, sizeof (rf627_calib_table_t));

    _table->type = kRF627_SMART;
    _table->rf627smart_calib_table =
            (rf627_smart_calib_table_t*)calloc(1, sizeof(rf627_smart_calib_table_t));

    _table->rf627smart_calib_table->m_Type =
            mpack_node_uint(mpack_node_map_cstr(root, "type"));

    _table->rf627smart_calib_table->m_CRC16 =
            mpack_node_uint(mpack_node_map_cstr(root, "crc"));

    _table->rf627smart_calib_table->m_Serial =
            mpack_node_uint(mpack_node_map_cstr(root, "serial"));

    _table->rf627smart_calib_table->m_DataRowLength =
            mpack_node_uint(mpack_node_map_cstr(root, "data_row_length"));

    _table->rf627smart_calib_table->m_Width =
            mpack_node_uint(mpack_node_map_cstr(root, "width"));

    _table->rf627smart_calib_table->m_Height =
            mpack_node_uint(mpack_node_map_cstr(root, "height"));

    _table->rf627smart_calib_table->m_MultW =
            mpack_node_float(mpack_node_map_cstr(root, "mult_w"));

    _table->rf627smart_calib_table->m_MultH =
            mpack_node_float(mpack_node_map_cstr(root, "mult_h"));

    _table->rf627smart_calib_table->m_TimeStamp =
            mpack_node_int(mpack_node_map_cstr(root, "time_stamp"));

    _table->rf627smart_calib_table->m_DataSize =
            mpack_node_bin_size(mpack_node_map_cstr(root, "data"));

    _table->rf627smart_calib_table->m_Data =
            (unsigned char*)mpack_node_data_alloc(
                mpack_node_map_cstr(root, "data"),
                _table->rf627smart_calib_table->m_DataSize);

    return _table;
}

void free_scanner(scanner_base_t *device)
{
    switch (device->type)
    {
    case kRF627_OLD:
    {
        rf627_old_free(device->rf627_old);
        break;
    }
    case kRF627_SMART:
    {
        rf627_smart_free(device->rf627_smart);
        break;
    }
    default:
        break;
    }
}
