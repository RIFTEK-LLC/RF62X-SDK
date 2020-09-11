#include "rf62Xsdk.h"
#include "rf62Xtypes.h"
#include "rf62Xcore.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>

extern "C"{
#include <rf62X_sdk.h>
}


#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
typedef int BOOL;
#endif


extern BOOL EnumAdapterAddresses();
extern void FreeAdapterAddresses();
extern int GetAdaptersCount();
extern const char* GetAdapterAddress(int index);
/* windows sockets tweaks */
extern BOOL WinSockInit();
extern void WinSockDeinit();


std::string SDK::SCANNERS::RF62X::sdk_version()
{
    /*
     * Get rf627 core version
     */
    return SDK::CORES::RF62X::version();
}

bool SDK::SCANNERS::RF62X::sdk_init()
{   
    return SDK::CORES::RF62X::init();
}

namespace SDK {
namespace SCANNERS {
namespace RF62X {

class convert{
    public:
    static std::string to_hex(int to_convert, int precision_specifier, bool uppercase = false)
    {
        std::string hex_result = "";
        std::string value;
        std::stringstream ss;
        ss << std::hex <<to_convert;
        ss >> value;
        for (size_t i = 0; i < (precision_specifier - value.size()); i++)
            hex_result+="0";

        if (uppercase)
        {
            // convert string to upper case
            std::for_each(value.begin(), value.end(), [](char & c){
                c = ::toupper(c);
            });
        }

        hex_result += value;
        return hex_result;
    }


    static std::string to_oct(int to_convert){
        std::string result;
        std::stringstream ss;
        ss << std::oct << to_convert;
        ss >> result;
        return result;
    }

    static std::string to_bin(int to_convert){
        return int_to_bin(to_convert);
    }
    private:
          static std::string int_to_bin(int number){
              std::string result;
              int level = 0;
              level++;
              if (number > 0){
                  result += (number % 2 == 0) ? "0" : "1";
                  int_to_bin(number / 2);
                  level--;
              }
              if (level == 1) return reverse(result);
              return result;
          }

          static std::string reverse(std::string to_reverse){
              std::string result;
              for (int i = to_reverse.length()-1; i >=0 ; i--)
                  result += to_reverse[i];
              return result;
          }
};




//
// RF627
// old version (v1.x.x)
//


std::vector<rf627old*> rf627old::search(PROTOCOLS protocol)
{
    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
        /*
         * Create value for scanners vector's type
         */
        vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
        /*
         * Initialization vector
         */
        vector_init(&scanners);


        /*
         * Iterate over all available network adapters in the current operating
         * system to send "Hello" requests.
         */
        for (int i=0; i<GetAdaptersCount(); i++)
        {
            // get another IP Addr and set this changes in network adapter settings.
            uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
            uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
            // call the function to change adapter settings inside the library.
            set_platform_adapter_settings(host_mask, host_ip_addr);

            // Search for RF627-old devices over network by Service Protocol.
            search_scanners(scanners, kRF627_OLD, kSERVICE);
        }

        std::vector<rf627old*> result;

        /*
         * Iterate over all discovered rf627-old in network and push into list.
         */
        for(size_t i = 0; i < vector_count(scanners); i++)
        {
            result.push_back(new rf627old((void*)vector_get(scanners,i)));
            result[i]->current_protocol = PROTOCOLS::SERVICE;
        }
        return result;
        break;
    }
    default:
    {
        static std::vector<rf627old*> result;
        return result;
        break;
    }
    }

}

rf627old::hello_info rf627old::get_info(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        hello_information info = get_info_about_scanner(((scanner_base_t*)this->scanner_base), kSERVICE);

        hello_info _hello_info = hello_info(info.rf627old.hello_info_service_protocol, PROTOCOLS::SERVICE);

        return _hello_info;
        break;
    }
    default:
        break;
    }

    hello_info _hello_info = hello_info(nullptr, PROTOCOLS::CURRENT);
    return _hello_info;
}

rf627old::rf627old(void* base)
{
    this->scanner_base = base;
}

rf627old::~rf627old()
{

}

bool rf627old::connect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = connect_to_scanner(
                    ((scanner_base_t*)this->scanner_base), kSERVICE);

        return result;
        break;
    }
    default:
        break;
    }

    return false;

}

bool rf627old::disconnect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = disconnect_from_scanner(
                    (scanner_base_t*)scanner_base, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

profile2D_t* rf627old::get_profile2D(
        bool zero_points,
        PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Get profile from scanner's data stream by Service Protocol.
        rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                    (scanner_base_t*)scanner_base, zero_points, kSERVICE);

        profile2D_t* result = new profile2D_t;

        if(profile_from_scanner->rf627_profile2D != NULL)
        {
            result->header.data_type =
                    profile_from_scanner->rf627_profile2D->header.data_type;
            result->header.flags =
                    profile_from_scanner->rf627_profile2D->header.flags;
            result->header.device_type =
                    profile_from_scanner->rf627_profile2D->header.device_type;
            result->header.serial_number =
                    profile_from_scanner->rf627_profile2D->header.serial_number;
            result->header.system_time =
                    profile_from_scanner->rf627_profile2D->header.system_time;

            result->header.proto_version_major =
                    profile_from_scanner->rf627_profile2D->header.proto_version_major;
            result->header.proto_version_minor =
                    profile_from_scanner->rf627_profile2D->header.proto_version_minor;
            result->header.hardware_params_offset =
                    profile_from_scanner->rf627_profile2D->header.hardware_params_offset;
            result->header.data_offset =
                    profile_from_scanner->rf627_profile2D->header.data_offset;
            result->header.packet_count =
                    profile_from_scanner->rf627_profile2D->header.packet_count;
            result->header.measure_count =
                    profile_from_scanner->rf627_profile2D->header.measure_count;

            result->header.zmr =
                    profile_from_scanner->rf627_profile2D->header.zmr;
            result->header.xemr =
                    profile_from_scanner->rf627_profile2D->header.xemr;
            result->header.discrete_value =
                    profile_from_scanner->rf627_profile2D->header.discrete_value;

            result->header.exposure_time =
                    profile_from_scanner->rf627_profile2D->header.exposure_time;
            result->header.laser_value =
                    profile_from_scanner->rf627_profile2D->header.laser_value;
            result->header.step_count =
                    profile_from_scanner->rf627_profile2D->header.step_count;
            result->header.dir =
                    profile_from_scanner->rf627_profile2D->header.dir;

            switch (result->header.data_type) {
            case DTY_PixelsNormal:
            case DTY_PixelsInterpolated:
            {
                result->pixels.resize(profile_from_scanner->
                                      rf627_profile2D->pixels_format.pixels_count);

                for(size_t i = 0; i < result->pixels.size(); i++)
                {
                    result->pixels[i] = profile_from_scanner->
                            rf627_profile2D->pixels_format.pixels[i];
                }

                if(profile_from_scanner->rf627_profile2D->intensity_count > 0)
                {
                    result->intensity.resize(
                                profile_from_scanner->rf627_profile2D->intensity_count);
                    for (size_t i = 0; i < result->intensity.size(); i++)
                        result->intensity[i] =
                                profile_from_scanner->rf627_profile2D->intensity[i];
                }

                break;
            }
            case DTY_ProfileNormal:
            case DTY_ProfileInterpolated:
            {
                result->points.resize(profile_from_scanner->
                                      rf627_profile2D->profile_format.points_count);

                for(size_t i = 0; i < result->points.size(); i++)
                {
                    result->points[i].x = profile_from_scanner->rf627_profile2D->
                            profile_format.points[i].x;
                    result->points[i].z = profile_from_scanner->rf627_profile2D->
                            profile_format.points[i].z;
                }

                if(profile_from_scanner->rf627_profile2D->intensity_count > 0)
                {
                    result->intensity.resize(
                                profile_from_scanner->rf627_profile2D->intensity_count);
                    for (size_t i = 0; i < result->intensity.size(); i++)
                        result->intensity[i] =
                                profile_from_scanner->rf627_profile2D->intensity[i];
                }
                break;
            }
            default:
                break;
            }
            free(profile_from_scanner->rf627_profile2D->intensity);
            free(profile_from_scanner->rf627_profile2D->pixels_format.pixels);
            free(profile_from_scanner->rf627_profile2D);
            free(profile_from_scanner);
            return result;
        }

        free(profile_from_scanner->rf627_profile2D);
        free(profile_from_scanner);
        delete result;
    }
    default:
        break;
    }

    return NULL;

}

profile3D_t* rf627old::get_profile3D(float step_size, float k,
                                     COUNT_TYPES count_type,
                                     bool zero_points,
                                     PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

//    switch (p) {
//    case PROTOCOLS::SERVICE:
//    {
//        // Get profile from scanner's data stream by Service Protocol.
//        rf627_profile3D_t* profile_from_scanner = get_profile3D_from_scanner(
//                    (scanner_base_t*)scanner_base, step_size, k, (count_types_t)count_type, zero_points, kSERVICE);

//        profile3D_t* result = new profile3D_t;

//        if(profile_from_scanner->rf627_profile3D != NULL)
//        {
//            result->header.data_type =
//                    profile_from_scanner->rf627_profile3D->header.data_type;
//            result->header.flags =
//                    profile_from_scanner->rf627_profile3D->header.flags;
//            result->header.device_type =
//                    profile_from_scanner->rf627_profile3D->header.device_type;
//            result->header.serial_number =
//                    profile_from_scanner->rf627_profile3D->header.serial_number;
//            result->header.system_time =
//                    profile_from_scanner->rf627_profile3D->header.system_time;

//            result->header.proto_version_major =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_major;
//            result->header.proto_version_minor =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_minor;
//            result->header.hardware_params_offset =
//                    profile_from_scanner->rf627_profile3D->header.hardware_params_offset;
//            result->header.data_offset =
//                    profile_from_scanner->rf627_profile3D->header.data_offset;
//            result->header.packet_count =
//                    profile_from_scanner->rf627_profile3D->header.packet_count;
//            result->header.measure_count =
//                    profile_from_scanner->rf627_profile3D->header.measure_count;

//            result->header.zmr =
//                    profile_from_scanner->rf627_profile3D->header.zmr;
//            result->header.xemr =
//                    profile_from_scanner->rf627_profile3D->header.xemr;
//            result->header.discrete_value =
//                    profile_from_scanner->rf627_profile3D->header.discrete_value;

//            result->header.exposure_time =
//                    profile_from_scanner->rf627_profile3D->header.exposure_time;
//            result->header.laser_value =
//                    profile_from_scanner->rf627_profile3D->header.laser_value;
//            result->header.step_count =
//                    profile_from_scanner->rf627_profile3D->header.step_count;
//            result->header.dir =
//                    profile_from_scanner->rf627_profile3D->header.dir;

//            switch (result->header.data_type) {
//            case DTY_PixelsNormal:
//            case DTY_PixelsInterpolated:
//            {
//                result->pixels.resize(profile_from_scanner->
//                                      rf627_profile3D->pixels_format.pixels_count);

//                for(size_t i = 0; i < result->pixels.size(); i++)
//                {
//                    result->pixels[i] = profile_from_scanner->
//                            rf627_profile3D->pixels_format.pixels[i];
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }

//                break;
//            }
//            case DTY_ProfileNormal:
//            case DTY_ProfileInterpolated:
//            {
//                result->points.resize(profile_from_scanner->
//                                      rf627_profile3D->profile_format.points_count);

//                for(size_t i = 0; i < result->points.size(); i++)
//                {
//                    result->points[i].x = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].x;
//                    result->points[i].y = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].y;
//                    result->points[i].z = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].z;
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }
//                break;
//            }
//            default:
//                break;
//            }
//            free(profile_from_scanner->rf627_profile3D->intensity);
//            free(profile_from_scanner->rf627_profile3D->pixels_format.pixels);
//            free(profile_from_scanner->rf627_profile3D);
//            free(profile_from_scanner);
//            return result;
//        }

//        free(profile_from_scanner->rf627_profile3D);
//        free(profile_from_scanner);
//        delete result;
//    }
//    default:
//        break;
//    }

    return NULL;

}

bool rf627old::read_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = read_params_from_scanner(
                    (scanner_base_t*)scanner_base, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

bool rf627old::write_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = write_params_to_scanner(
                    (scanner_base_t*)scanner_base, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

param_t* create_param_from_type(std::string type)
{
    param_t* p = nullptr;
    if(type == parameter_value_types[PVT_UINT])
    {
        p = new value_uint32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_UINT64])
    {
        p = new value_uint64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_INT])
    {
        p = new value_int32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_INT64])
    {
        p = new value_int64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_FLOAT])
    {
        p = new value_flt();
        p->type = type;
    }else if(type == parameter_value_types[PVT_DOUBLE])
    {
        p = new value_dbl();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_UINT32])
    {
        p = new array_uint32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_UINT64])
    {
        p = new array_uint64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_INT32])
    {
        p = new array_int32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_INT64])
    {
        p = new array_int64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_FLT])
    {
        p = new array_flt();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_DBL])
    {
        p = new array_dbl();
        p->type = type;
    }else if(type == parameter_value_types[PVT_STRING])
    {
        p = new value_str();
        p->type = type;
    }
    return p;
}

param_t *rf627old::get_param(PARAM_NAME_KEY param_name)
{
    return get_param(parameter_names[(uint8_t)param_name]);
}

param_t *rf627old::get_param(std::string param_name)
{
    parameter_t* p = get_parameter(
                (scanner_base_t*)this->scanner_base, param_name.c_str());
    if (p != NULL)
    {
        param_t* result = create_param_from_type(std::string(p->base.type));


        if (result->type == parameter_value_types[PVT_UINT])
        {
            result->set_value<value_uint32_t>(p->val_uint32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_uint32*)result)->defaultValue = p->val_uint32->defValue;
            ((value_uint32*)result)->value = p->val_uint32->value;
            ((value_uint32*)result)->min = p->val_uint32->min;
            ((value_uint32*)result)->max = p->val_uint32->max;

            if(p->val_uint32->enumValues != NULL)
            for(int i = 0; i < p->val_uint32->enumValues->recCount; i++)
                ((value_uint32*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_uint32->enumValues->rec[i].value,
                            p->val_uint32->enumValues->rec[i].key));
        }
        else if (result->type == parameter_value_types[PVT_UINT64])
        {
            result->set_value<value_uint64_t>(p->val_uint64->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_uint64*)result)->defaultValue = p->val_uint64->defValue;
            ((value_uint64*)result)->value = p->val_uint64->value;
            ((value_uint64*)result)->min = p->val_uint64->min;
            ((value_uint64*)result)->max = p->val_uint64->max;

            if(p->val_uint64->enumValues != NULL)
            for(int i = 0; i < p->val_uint64->enumValues->recCount; i++)
                ((value_uint64*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_uint64->enumValues->rec[i].value,
                            p->val_uint64->enumValues->rec[i].key));
        }
        else if (result->type == parameter_value_types[PVT_INT])
        {
            result->set_value<value_int32_t>(p->val_int32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_int32*)result)->defaultValue = p->val_int32->defValue;
            ((value_int32*)result)->value = p->val_int32->value;
            ((value_int32*)result)->min = p->val_int32->min;
            ((value_int32*)result)->max = p->val_int32->max;

            if(p->val_int32->enumValues != NULL)
            for(int i = 0; i < p->val_int32->enumValues->recCount; i++)
                ((value_int32*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_int32->enumValues->rec[i].value,
                            p->val_int32->enumValues->rec[i].key));

        }
        else if (result->type == parameter_value_types[PVT_INT64])
        {
            result->set_value<value_int64_t>(p->val_int64->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_int64*)result)->defaultValue = p->val_int64->defValue;
            ((value_int64*)result)->value = p->val_int64->value;
            ((value_int64*)result)->min = p->val_int64->min;
            ((value_int64*)result)->max = p->val_int64->max;

            if(p->val_int64->enumValues != NULL)
            for(int i = 0; i < p->val_int64->enumValues->recCount; i++)
                ((value_int64*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_int64->enumValues->rec[i].value,
                            p->val_int64->enumValues->rec[i].key));

        }
        else if (result->type == parameter_value_types[PVT_FLOAT])
        {
            result->set_value<value_flt_t>(p->val_flt->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_flt*)result)->defaultValue = p->val_flt->defValue;
            ((value_flt*)result)->value = p->val_flt->value;
            ((value_flt*)result)->min = p->val_flt->min;
            ((value_flt*)result)->max = p->val_flt->max;
        }
        else if (result->type == parameter_value_types[PVT_DOUBLE])
        {
            result->set_value<value_dbl_t>(p->val_dbl->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_dbl*)result)->defaultValue = p->val_dbl->defValue;
            ((value_dbl*)result)->value = p->val_dbl->value;
            ((value_dbl*)result)->min = p->val_dbl->min;
            ((value_dbl*)result)->max = p->val_dbl->max;
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_UINT32])
        {
            //result->set_value<array_uint32_t>(p->arr_uint32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            for(size_t i = 0; i < p->arr_uint32->defCount; i++)
                ((array_uint32*)result)->defaultValue.push_back(p->arr_uint32->defValue[i]);
            for(size_t i = 0; i < p->arr_uint32->count; i++)
                ((array_uint32*)result)->value.push_back(p->arr_uint32->value[i]);
            ((array_uint32*)result)->min = p->arr_uint32->min;
            ((array_uint32*)result)->max = p->arr_uint32->max;
            ((array_uint32*)result)->maxCount = p->arr_uint32->maxCount;
            ((array_uint32*)result)->defCount = p->arr_uint32->defCount;
            ((array_uint32*)result)->count = p->arr_uint32->count;
//            parse_string_param(p, array_uint_t, name);
//            parse_string_param(p, array_uint_t, type);
//            parse_string_param(p, array_uint_t, access);
//            parse_uint16_param(p, array_uint_t, index);
//            parse_uint32_param(p, array_uint_t, offset);
//            parse_uint32_param(p, array_uint_t, size);
//            parse_string_param(p, array_uint_t, units);

//            parse_uint32_param(p, array_uint_t, maxCount);
//            parse_uint32_param(p, array_uint_t, defCount);
//            parse_uint32_param(p, array_uint_t, count);

//            parse_arr_param(p, array_uint_t, defaultValue, uint32_t);
//            parse_arr_param(p, array_uint_t, value, uint32_t);

//            parse_uint32_param(p, array_uint_t, min);
//            parse_uint32_param(p, array_uint_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_UINT64])
        {
//            parse_string_param(p, array_uint64_t, name);
//            parse_string_param(p, array_uint64_t, type);
//            parse_string_param(p, array_uint64_t, access);
//            parse_uint16_param(p, array_uint64_t, index);
//            parse_uint32_param(p, array_uint64_t, offset);
//            parse_uint32_param(p, array_uint64_t, size);
//            parse_string_param(p, array_uint64_t, units);

//            parse_uint32_param(p, array_uint64_t, maxCount);
//            parse_uint32_param(p, array_uint64_t, defCount);
//            parse_uint32_param(p, array_uint64_t, count);

//            parse_arr_param(p, array_uint64_t, defaultValue, uint64_t);
//            parse_arr_param(p, array_uint64_t, value, uint64_t);

//            parse_uint64_param(p, array_uint64_t, min);
//            parse_uint64_param(p, array_uint64_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_INT32])
        {
//            parse_string_param(p, array_int32_t, name);
//            parse_string_param(p, array_int32_t, type);
//            parse_string_param(p, array_int32_t, access);
//            parse_uint16_param(p, array_int32_t, index);
//            parse_uint32_param(p, array_int32_t, offset);
//            parse_uint32_param(p, array_int32_t, size);
//            parse_string_param(p, array_int32_t, units);

//            parse_uint32_param(p, array_int32_t, maxCount);
//            parse_uint32_param(p, array_int32_t, defCount);
//            parse_uint32_param(p, array_int32_t, count);

//            parse_arr_param(p, array_int32_t, defaultValue, int32_t);
//            parse_arr_param(p, array_int32_t, value, int32_t);

//            parse_int32_param(p, array_int32_t, min);
//            parse_int32_param(p, array_int32_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_INT64])
        {
//            parse_string_param(p, array_int64_t, name);
//            parse_string_param(p, array_int64_t, type);
//            parse_string_param(p, array_int64_t, access);
//            parse_uint16_param(p, array_int64_t, index);
//            parse_uint32_param(p, array_int64_t, offset);
//            parse_uint32_param(p, array_int64_t, size);
//            parse_string_param(p, array_int64_t, units);

//            parse_uint32_param(p, array_int64_t, maxCount);
//            parse_uint32_param(p, array_int64_t, defCount);
//            parse_uint32_param(p, array_int64_t, count);

//            parse_arr_param(p, array_int64_t, defaultValue, int64_t);
//            parse_arr_param(p, array_int64_t, value, int64_t);

//            parse_int64_param(p, array_int64_t, min);
//            parse_int64_param(p, array_int64_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_FLT])
        {
//            parse_string_param(p, array_flt_t, name);
//            parse_string_param(p, array_flt_t, type);
//            parse_string_param(p, array_flt_t, access);
//            parse_uint16_param(p, array_flt_t, index);
//            parse_uint32_param(p, array_flt_t, offset);
//            parse_uint32_param(p, array_flt_t, size);
//            parse_string_param(p, array_flt_t, units);

//            parse_uint32_param(p, array_flt_t, maxCount);
//            parse_uint32_param(p, array_flt_t, defCount);
//            parse_uint32_param(p, array_flt_t, count);

//            parse_arr_param(p, array_flt_t, defaultValue, float);
//            parse_arr_param(p, array_flt_t, value, float);

//            parse_float_param(p, array_flt_t, min);
//            parse_float_param(p, array_flt_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_DBL])
        {
//            parse_string_param(p, array_dbl_t, name);
//            parse_string_param(p, array_dbl_t, type);
//            parse_string_param(p, array_dbl_t, access);
//            parse_uint16_param(p, array_dbl_t, index);
//            parse_uint32_param(p, array_dbl_t, offset);
//            parse_uint32_param(p, array_dbl_t, size);
//            parse_string_param(p, array_dbl_t, units);

//            parse_uint32_param(p, array_dbl_t, maxCount);
//            parse_uint32_param(p, array_dbl_t, defCount);
//            parse_uint32_param(p, array_dbl_t, count);

//            parse_arr_param(p, array_dbl_t, defaultValue, double);
//            parse_arr_param(p, array_dbl_t, value, double);

//            parse_double_param(p, array_dbl_t, min);
//            parse_double_param(p, array_dbl_t, max);
        }
        else if (result->type == parameter_value_types[PVT_STRING])
        {
            result->set_value<value_str_t>(p->val_str->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_str*)result)->defaultValue = p->val_str->defValue;
            ((value_str*)result)->value = p->val_str->value;
            ((value_str*)result)->maxLen = p->val_str->maxLen;

//            parse_string_param(p, value_str_t, defaultValue);
//            parse_string_param(p, value_str_t, value);
//            parse_uint16_param(p, value_str_t, maxLen);

        }else if (result->type == parameter_value_types[PVT_UNKN])
        {
//            parse_string_param(p, value_raw_t, name);
//            parse_string_param(p, value_raw_t, type);
//            parse_string_param(p, value_raw_t, access);
//            parse_uint16_param(p, value_raw_t, index);
//            parse_uint32_param(p, value_raw_t, offset);
//            parse_uint32_param(p, value_raw_t, size);

//            parse_raw_param(p, value_raw_t);


        }

        return result;
    }
    return nullptr;
}

parameter_t* create_parameter_from_type(std::string type)
{
    parameter_t* p = NULL;
    if (type == parameter_value_types[PVT_UINT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_uint32 = (value_uint32_t*)calloc(1, sizeof (value_uint32_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT_PARAM_TYPE].c_str();
    }else if (type == parameter_value_types[PVT_UINT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_uint64 = (value_uint64_t*)calloc(1, sizeof (value_uint64_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT64_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_INT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_int32 = (value_int32_t*)calloc(1, sizeof (value_int32_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_INT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_int64 = (value_int64_t*)calloc(1, sizeof (value_int64_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT64_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_FLOAT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_flt = (value_flt_t*)calloc(1, sizeof (value_flt_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::FLOAT_PARAM_TYPE].c_str();
    }else if(type ==  parameter_value_types[PVT_DOUBLE])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_dbl = (value_dbl_t*)calloc(1, sizeof (value_dbl_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::DOUBLE_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_UINT32])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_uint32 = (array_uint32_t*)calloc(1, sizeof (array_uint32_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_UINT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_uint64 = (array_uint64_t*)calloc(1, sizeof (array_uint64_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT64_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_INT32])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_int32 = (array_int32_t*)calloc(1, sizeof (array_int32_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT32_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_INT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_int64 = (array_int64_t*)calloc(1, sizeof (array_int64_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT64_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_FLT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_flt = (array_flt_t*)calloc(1, sizeof (array_flt_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::FLT_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_DBL])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_dbl = (array_dbl_t*)calloc(1, sizeof (array_dbl_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::DBL_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_STRING])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_str = (value_str_t*)calloc(1, sizeof (value_str_t));
        p->base.type = param_value_types[(uint8_t)PARAM_VALUE_TYPE::STRING_PARAM_TYPE].c_str();
    }
    return p;
}

bool rf627old::set_param(param_t* param)
{
    parameter_t* p = create_parameter_from_type(param->type.c_str());
    if (p != NULL)
    {
        p->base.name = param->name.c_str();
        p->base.type = param->type.c_str();
        p->base.access = param->access.c_str();
        p->base.units = param->units.c_str();
        if (param->type == parameter_value_types[PVT_STRING])
        {
            std::string new_value = param->get_value<value_str>();
            delete[] p->val_str->value;
            p->val_str->value = new char[new_value.length() + 1];
            strcpy(p->val_str->value, new_value.c_str());
            p->base.size = new_value.length() + 1;
        }
        else if (param->type == parameter_value_types[PVT_INT])
        {
            p->val_int32->value = param->get_value<value_int32>();
        }
        else if (param->type == parameter_value_types[PVT_INT64])
        {
            p->val_int64->value = param->get_value<value_int64>();
        }
        else if (param->type == parameter_value_types[PVT_UINT])
        {
            p->val_uint32->value = param->get_value<value_uint32>();
        }
        else if (param->type == parameter_value_types[PVT_UINT64])
        {
            p->val_uint64->value = param->get_value<value_uint64>();
        }
        else if (param->type == parameter_value_types[PVT_FLOAT])
        {
            p->val_flt->value = param->get_value<value_flt>();
        }
        else if (param->type ==  parameter_value_types[PVT_DOUBLE])
        {
            p->val_dbl->value = param->get_value<value_dbl>();
        }
        else if (param->type ==  parameter_value_types[PVT_ARRAY_UINT32])
        {
            std::vector<uint32_t> v = param->get_value<array_uint32>();
            p->arr_uint32->value = (rfUint32*)calloc(v.size(), sizeof (rfUint32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint32);
        }
        set_parameter((scanner_base_t*)this->scanner_base, p);
        return true;
    }
    return false;
}
bool rf627old::set_param(const char* param_name, int arg_count, ...)
{
    va_list valist;
    va_start(valist, arg_count);

    bool result = set_parameter_by_name(
                (scanner_base_t*)this->scanner_base, param_name, arg_count, valist);

    va_end(valist);

    return result;
}
bool rf627old::set_param(int param_id, int arg_count, ...)
{
    va_list valist;
    va_start(valist, arg_count);

    bool result = set_parameter_by_name(
                (scanner_base_t*)this->scanner_base, parameter_names[param_id].c_str(), arg_count, valist);

    va_end(valist);

    return result;
}

bool rf627old::send_cmd(const char* command_name, int arg_count, ...)
{
    va_list valist;
    va_start(valist, arg_count);

    //int arg1 = va_arg(valist, int);
    //int arg2 = va_arg(valist, int);

    command_t cmd = {0};
    cmd.name = command_name;
    va_copy (cmd.arg_list, valist);

    bool result = send_command((scanner_base_t*)this->scanner_base, &cmd);

    va_end(valist);

    return result;
}

bool rf627old::send_cmd(const char* command_name,
                        std::vector<uint8_t>* input, std::vector<uint8_t>* output)
{


    command2_t cmd = {0};
    cmd.name = command_name;
    cmd.input.size = input->size();
    cmd.input.payload = (rfUint8*)input->data();
    bool result = send_command2((scanner_base_t*)this->scanner_base, &cmd);

    for (int i = 0; i < cmd.output.size; i++)
        output->push_back(((uint8_t*)cmd.output.payload)[i]);

    free(cmd.output.payload);

    return result;
}

const std::string& rf627old::hello_info::device_name()
{
    return _device_name;
}

const uint32_t& rf627old::hello_info::serial_number()
{
    return _serial_number;
}

const std::string& rf627old::hello_info::ip_address()
{
    return _ip_address;
}

const std::string& rf627old::hello_info::mac_address()
{
    return _mac_address;
}

const uint16_t& rf627old::hello_info::profile_port()
{
    return _profile_port;
}

const uint16_t& rf627old::hello_info::service_port()
{
    return _service_port;
}

const rf627old::hello_info::version& rf627old::hello_info::firmware_version()
{
    return _firmware_version;
}

const rf627old::hello_info::version& rf627old::hello_info::hardware_version()
{
    return _hardware_version;
}

const uint32_t& rf627old::hello_info::z_smr()
{
    return _z_smr;
}

const uint32_t& rf627old::hello_info::z_mr()
{
    return _z_mr;
}

const uint32_t& rf627old::hello_info::x_smr()
{
    return _x_smr;
}

const uint32_t& rf627old::hello_info::x_emr()
{
    return _x_emr;
}


rf627old::hello_info::hello_info(void* info, PROTOCOLS protocol)
{
    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
        _device_name = ((rf627_old_hello_info_by_service_protocol*)info)->device_name;
        _serial_number = ((rf627_old_hello_info_by_service_protocol*)info)->serial_number;

        in_addr addr = {0};
        uint32_t ip = ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[0] << 24 |
                      ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[1] << 16 |
                      ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[2] << 8 |
                      ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[3];
        addr.s_addr = htonl(ip);
        _ip_address = inet_ntoa(addr);
        _mac_address = "";

        for (int i = 0; i < 6; i++)
        {
            if (i != 0)
                _mac_address += ":";
            _mac_address += convert::to_hex(((rf627_old_hello_info_by_service_protocol*)info)->mac_address[i], 2);
        }

        _profile_port = ((rf627_old_hello_info_by_service_protocol*)info)->profile_port;
        _service_port = ((rf627_old_hello_info_by_service_protocol*)info)->service_port;

        _firmware_version = hello_info::version(((rf627_old_hello_info_by_service_protocol*)info)->firmware_version);
        _hardware_version = hello_info::version(((rf627_old_hello_info_by_service_protocol*)info)->hardware_version);

        _z_smr = ((rf627_old_hello_info_by_service_protocol*)info)->z_begin;
        _z_mr = ((rf627_old_hello_info_by_service_protocol*)info)->z_range;
        _x_smr = ((rf627_old_hello_info_by_service_protocol*)info)->x_begin;
        _x_emr = ((rf627_old_hello_info_by_service_protocol*)info)->x_end;
        break;
    }
    default:
        break;
    }

}

rf627old::hello_info::~hello_info()
{

}

std::ostream &operator<<(std::ostream &out, rf627old::hello_info::version const &v)
{
    out << std::to_string(v.major) << "."
        << std::to_string(v.minor) << "."
        << std::to_string(v.patch);
    return out;
}

bool operator ==(const rf627old::hello_info::version &v1, const rf627old::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) ==
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator !=(const rf627old::hello_info::version &v1,const  rf627old::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) ==
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator <=(const rf627old::hello_info::version &v1, const rf627old::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) <=
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator >=(const rf627old::hello_info::version &v1, const rf627old::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) >=
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator <(const rf627old::hello_info::version &v1, const rf627old::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) <
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator >(const rf627old::hello_info::version &v1, const rf627old::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) >
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}

std::string rf627old::hello_info::version::to_string()
{
    std::string s;
    s = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    return s;
}

uint32_t rf627old::hello_info::version::to_uint()
{
    return _value;
}

rf627old::hello_info::version::version()
{
    version(0);
}

rf627old::hello_info::version::version(uint32_t value)
{
    major = (((uint8_t*)(void*)(&value))[3]);
    minor = (((uint8_t*)(void*)(&value))[2]);
    patch = (((uint8_t*)(void*)(&value))[1]);
    _value = value;
}

rf627old::hello_info::version::~version()
{

}


//
// RF627
// smart version (v2.x.x)
//


std::vector<rf627smart*> rf627smart::search(PROTOCOLS protocol)
{
    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
        /*
         * Create value for scanners vector's type
         */
        vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
        /*
         * Initialization vector
         */
        vector_init(&scanners);


        /*
         * Iterate over all available network adapters in the current operating
         * system to send "Hello" requests.
         */
        for (int i=0; i<GetAdaptersCount(); i++)
        {
            // get another IP Addr and set this changes in network adapter settings.
            uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
            uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
            // call the function to change adapter settings inside the library.
            set_platform_adapter_settings(host_mask, host_ip_addr);

            // Search for RF627-old devices over network by Service Protocol.
            search_scanners(scanners, kRF627_SMART, kSERVICE);
        }

        std::vector<rf627smart*> result;

        /*
         * Iterate over all discovered rf627-old in network and push into list.
         */
        for(size_t i = 0; i < vector_count(scanners); i++)
        {
            result.push_back(new rf627smart((void*)vector_get(scanners,i)));
            result[i]->current_protocol = PROTOCOLS::SERVICE;
        }
        return result;
        break;
    }
    default:
    {
        static std::vector<rf627smart*> result;
        return result;
        break;
    }
    }

}

rf627smart::hello_info rf627smart::get_info(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        hello_information info = get_info_about_scanner(((scanner_base_t*)this->scanner_base), kSERVICE);

        hello_info _hello_info = hello_info(info.rf627smart.hello_info_service_protocol, PROTOCOLS::SERVICE);

        return _hello_info;
        break;
    }
    default:
        break;
    }

    hello_info _hello_info = hello_info(nullptr, PROTOCOLS::CURRENT);
    return _hello_info;
}

rf627smart::rf627smart(void* base)
{
    this->scanner_base = base;
}

rf627smart::~rf627smart()
{

}

bool rf627smart::connect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = connect_to_scanner(
                    ((scanner_base_t*)this->scanner_base), kSERVICE);

        return result;
        break;
    }
    default:
        break;
    }

    return false;

}

bool rf627smart::disconnect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = disconnect_from_scanner(
                    (scanner_base_t*)scanner_base, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

profile2D_t* rf627smart::get_profile2D(
        bool zero_points,
        PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Get profile from scanner's data stream by Service Protocol.
        rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                    (scanner_base_t*)scanner_base, zero_points, kSERVICE);

        profile2D_t* result = new profile2D_t;

        if(profile_from_scanner->rf627_profile2D != NULL)
        {
            result->header.data_type =
                    profile_from_scanner->rf627_profile2D->header.data_type;
            result->header.flags =
                    profile_from_scanner->rf627_profile2D->header.flags;
            result->header.device_type =
                    profile_from_scanner->rf627_profile2D->header.device_type;
            result->header.serial_number =
                    profile_from_scanner->rf627_profile2D->header.serial_number;
            result->header.system_time =
                    profile_from_scanner->rf627_profile2D->header.system_time;

            result->header.proto_version_major =
                    profile_from_scanner->rf627_profile2D->header.proto_version_major;
            result->header.proto_version_minor =
                    profile_from_scanner->rf627_profile2D->header.proto_version_minor;
            result->header.hardware_params_offset =
                    profile_from_scanner->rf627_profile2D->header.hardware_params_offset;
            result->header.data_offset =
                    profile_from_scanner->rf627_profile2D->header.data_offset;
            result->header.packet_count =
                    profile_from_scanner->rf627_profile2D->header.packet_count;
            result->header.measure_count =
                    profile_from_scanner->rf627_profile2D->header.measure_count;

            result->header.zmr =
                    profile_from_scanner->rf627_profile2D->header.zmr;
            result->header.xemr =
                    profile_from_scanner->rf627_profile2D->header.xemr;
            result->header.discrete_value =
                    profile_from_scanner->rf627_profile2D->header.discrete_value;

            result->header.exposure_time =
                    profile_from_scanner->rf627_profile2D->header.exposure_time;
            result->header.laser_value =
                    profile_from_scanner->rf627_profile2D->header.laser_value;
            result->header.step_count =
                    profile_from_scanner->rf627_profile2D->header.step_count;
            result->header.dir =
                    profile_from_scanner->rf627_profile2D->header.dir;

            switch (result->header.data_type) {
            case DTY_PixelsNormal:
            case DTY_PixelsInterpolated:
            {
                result->pixels.resize(profile_from_scanner->
                                      rf627_profile2D->pixels_format.pixels_count);

                for(size_t i = 0; i < result->pixels.size(); i++)
                {
                    result->pixels[i] = profile_from_scanner->
                            rf627_profile2D->pixels_format.pixels[i];
                }

                if(profile_from_scanner->rf627_profile2D->intensity_count > 0)
                {
                    result->intensity.resize(
                                profile_from_scanner->rf627_profile2D->intensity_count);
                    for (size_t i = 0; i < result->intensity.size(); i++)
                        result->intensity[i] =
                                profile_from_scanner->rf627_profile2D->intensity[i];
                }

                break;
            }
            case DTY_ProfileNormal:
            case DTY_ProfileInterpolated:
            {
                result->points.resize(profile_from_scanner->
                                      rf627_profile2D->profile_format.points_count);

                for(size_t i = 0; i < result->points.size(); i++)
                {
                    result->points[i].x = profile_from_scanner->rf627_profile2D->
                            profile_format.points[i].x;
                    result->points[i].z = profile_from_scanner->rf627_profile2D->
                            profile_format.points[i].z;
                }

                if(profile_from_scanner->rf627_profile2D->intensity_count > 0)
                {
                    result->intensity.resize(
                                profile_from_scanner->rf627_profile2D->intensity_count);
                    for (size_t i = 0; i < result->intensity.size(); i++)
                        result->intensity[i] =
                                profile_from_scanner->rf627_profile2D->intensity[i];
                }
                break;
            }
            default:
                break;
            }
            free(profile_from_scanner->rf627_profile2D->intensity);
            free(profile_from_scanner->rf627_profile2D->pixels_format.pixels);
            free(profile_from_scanner->rf627_profile2D);
            free(profile_from_scanner);
            return result;
        }

        free(profile_from_scanner->rf627_profile2D);
        free(profile_from_scanner);
        delete result;
    }
    default:
        break;
    }

    return NULL;

}

profile3D_t* rf627smart::get_profile3D(float step_size, float k,
                                     COUNT_TYPES count_type,
                                     bool zero_points,
                                     PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

//    switch (p) {
//    case PROTOCOLS::SERVICE:
//    {
//        // Get profile from scanner's data stream by Service Protocol.
//        rf627_profile3D_t* profile_from_scanner = get_profile3D_from_scanner(
//                    (scanner_base_t*)scanner_base, step_size, k, (count_types_t)count_type, zero_points, kSERVICE);

//        profile3D_t* result = new profile3D_t;

//        if(profile_from_scanner->rf627_profile3D != NULL)
//        {
//            result->header.data_type =
//                    profile_from_scanner->rf627_profile3D->header.data_type;
//            result->header.flags =
//                    profile_from_scanner->rf627_profile3D->header.flags;
//            result->header.device_type =
//                    profile_from_scanner->rf627_profile3D->header.device_type;
//            result->header.serial_number =
//                    profile_from_scanner->rf627_profile3D->header.serial_number;
//            result->header.system_time =
//                    profile_from_scanner->rf627_profile3D->header.system_time;

//            result->header.proto_version_major =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_major;
//            result->header.proto_version_minor =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_minor;
//            result->header.hardware_params_offset =
//                    profile_from_scanner->rf627_profile3D->header.hardware_params_offset;
//            result->header.data_offset =
//                    profile_from_scanner->rf627_profile3D->header.data_offset;
//            result->header.packet_count =
//                    profile_from_scanner->rf627_profile3D->header.packet_count;
//            result->header.measure_count =
//                    profile_from_scanner->rf627_profile3D->header.measure_count;

//            result->header.zmr =
//                    profile_from_scanner->rf627_profile3D->header.zmr;
//            result->header.xemr =
//                    profile_from_scanner->rf627_profile3D->header.xemr;
//            result->header.discrete_value =
//                    profile_from_scanner->rf627_profile3D->header.discrete_value;

//            result->header.exposure_time =
//                    profile_from_scanner->rf627_profile3D->header.exposure_time;
//            result->header.laser_value =
//                    profile_from_scanner->rf627_profile3D->header.laser_value;
//            result->header.step_count =
//                    profile_from_scanner->rf627_profile3D->header.step_count;
//            result->header.dir =
//                    profile_from_scanner->rf627_profile3D->header.dir;

//            switch (result->header.data_type) {
//            case DTY_PixelsNormal:
//            case DTY_PixelsInterpolated:
//            {
//                result->pixels.resize(profile_from_scanner->
//                                      rf627_profile3D->pixels_format.pixels_count);

//                for(size_t i = 0; i < result->pixels.size(); i++)
//                {
//                    result->pixels[i] = profile_from_scanner->
//                            rf627_profile3D->pixels_format.pixels[i];
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }

//                break;
//            }
//            case DTY_ProfileNormal:
//            case DTY_ProfileInterpolated:
//            {
//                result->points.resize(profile_from_scanner->
//                                      rf627_profile3D->profile_format.points_count);

//                for(size_t i = 0; i < result->points.size(); i++)
//                {
//                    result->points[i].x = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].x;
//                    result->points[i].y = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].y;
//                    result->points[i].z = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].z;
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }
//                break;
//            }
//            default:
//                break;
//            }
//            free(profile_from_scanner->rf627_profile3D->intensity);
//            free(profile_from_scanner->rf627_profile3D->pixels_format.pixels);
//            free(profile_from_scanner->rf627_profile3D);
//            free(profile_from_scanner);
//            return result;
//        }

//        free(profile_from_scanner->rf627_profile3D);
//        free(profile_from_scanner);
//        delete result;
//    }
//    default:
//        break;
//    }

    return NULL;

}

bool rf627smart::read_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = read_params_from_scanner(
                    (scanner_base_t*)scanner_base, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

bool rf627smart::write_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = write_params_to_scanner(
                    (scanner_base_t*)scanner_base, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

param_t *rf627smart::get_param(PARAM_NAME_KEY param_name)
{
    return get_param(parameter_names[(uint8_t)param_name]);
}

param_t *rf627smart::get_param(std::string param_name)
{
    parameter_t* p = get_parameter(
                (scanner_base_t*)this->scanner_base, param_name.c_str());
    if (p != NULL)
    {
        param_t* result = create_param_from_type(std::string(p->base.type));


        if (result->type == parameter_value_types[PVT_UINT])
        {
            result->set_value<value_uint32_t>(p->val_uint32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_uint32*)result)->defaultValue = p->val_uint32->defValue;
            ((value_uint32*)result)->value = p->val_uint32->value;
            ((value_uint32*)result)->min = p->val_uint32->min;
            ((value_uint32*)result)->max = p->val_uint32->max;

            if(p->val_uint32->enumValues != NULL)
            for(int i = 0; i < p->val_uint32->enumValues->recCount; i++)
                ((value_uint32*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_uint32->enumValues->rec[i].value,
                            p->val_uint32->enumValues->rec[i].key));
        }
        else if (result->type == parameter_value_types[PVT_UINT64])
        {
            result->set_value<value_uint64_t>(p->val_uint64->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_uint64*)result)->defaultValue = p->val_uint64->defValue;
            ((value_uint64*)result)->value = p->val_uint64->value;
            ((value_uint64*)result)->min = p->val_uint64->min;
            ((value_uint64*)result)->max = p->val_uint64->max;

            if(p->val_uint64->enumValues != NULL)
            for(int i = 0; i < p->val_uint64->enumValues->recCount; i++)
                ((value_uint64*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_uint64->enumValues->rec[i].value,
                            p->val_uint64->enumValues->rec[i].key));
        }
        else if (result->type == parameter_value_types[PVT_INT])
        {
            result->set_value<value_int32_t>(p->val_int32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_int32*)result)->defaultValue = p->val_int32->defValue;
            ((value_int32*)result)->value = p->val_int32->value;
            ((value_int32*)result)->min = p->val_int32->min;
            ((value_int32*)result)->max = p->val_int32->max;

            if(p->val_int32->enumValues != NULL)
            for(int i = 0; i < p->val_int32->enumValues->recCount; i++)
                ((value_int32*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_int32->enumValues->rec[i].value,
                            p->val_int32->enumValues->rec[i].key));

        }
        else if (result->type == parameter_value_types[PVT_INT64])
        {
            result->set_value<value_int64_t>(p->val_int64->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_int64*)result)->defaultValue = p->val_int64->defValue;
            ((value_int64*)result)->value = p->val_int64->value;
            ((value_int64*)result)->min = p->val_int64->min;
            ((value_int64*)result)->max = p->val_int64->max;

            if(p->val_int64->enumValues != NULL)
            for(int i = 0; i < p->val_int64->enumValues->recCount; i++)
                ((value_int64*)result)->valuesEnum.push_back(std::make_pair(
                            p->val_int64->enumValues->rec[i].value,
                            p->val_int64->enumValues->rec[i].key));

        }
        else if (result->type == parameter_value_types[PVT_FLOAT])
        {
            result->set_value<value_flt_t>(p->val_flt->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_flt*)result)->defaultValue = p->val_flt->defValue;
            ((value_flt*)result)->value = p->val_flt->value;
            ((value_flt*)result)->min = p->val_flt->min;
            ((value_flt*)result)->max = p->val_flt->max;
        }
        else if (result->type == parameter_value_types[PVT_DOUBLE])
        {
            result->set_value<value_dbl_t>(p->val_dbl->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_dbl*)result)->defaultValue = p->val_dbl->defValue;
            ((value_dbl*)result)->value = p->val_dbl->value;
            ((value_dbl*)result)->min = p->val_dbl->min;
            ((value_dbl*)result)->max = p->val_dbl->max;
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_UINT32])
        {
            //result->set_value<array_uint32_t>(p->arr_uint32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            for(size_t i = 0; i < p->arr_uint32->defCount; i++)
                ((array_uint32*)result)->defaultValue.push_back(p->arr_uint32->defValue[i]);
            for(size_t i = 0; i < p->arr_uint32->count; i++)
                ((array_uint32*)result)->value.push_back(p->arr_uint32->value[i]);
            ((array_uint32*)result)->min = p->arr_uint32->min;
            ((array_uint32*)result)->max = p->arr_uint32->max;
            ((array_uint32*)result)->maxCount = p->arr_uint32->maxCount;
            ((array_uint32*)result)->defCount = p->arr_uint32->defCount;
            ((array_uint32*)result)->count = p->arr_uint32->count;
//            parse_string_param(p, array_uint_t, name);
//            parse_string_param(p, array_uint_t, type);
//            parse_string_param(p, array_uint_t, access);
//            parse_uint16_param(p, array_uint_t, index);
//            parse_uint32_param(p, array_uint_t, offset);
//            parse_uint32_param(p, array_uint_t, size);
//            parse_string_param(p, array_uint_t, units);

//            parse_uint32_param(p, array_uint_t, maxCount);
//            parse_uint32_param(p, array_uint_t, defCount);
//            parse_uint32_param(p, array_uint_t, count);

//            parse_arr_param(p, array_uint_t, defaultValue, uint32_t);
//            parse_arr_param(p, array_uint_t, value, uint32_t);

//            parse_uint32_param(p, array_uint_t, min);
//            parse_uint32_param(p, array_uint_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_UINT64])
        {
//            parse_string_param(p, array_uint64_t, name);
//            parse_string_param(p, array_uint64_t, type);
//            parse_string_param(p, array_uint64_t, access);
//            parse_uint16_param(p, array_uint64_t, index);
//            parse_uint32_param(p, array_uint64_t, offset);
//            parse_uint32_param(p, array_uint64_t, size);
//            parse_string_param(p, array_uint64_t, units);

//            parse_uint32_param(p, array_uint64_t, maxCount);
//            parse_uint32_param(p, array_uint64_t, defCount);
//            parse_uint32_param(p, array_uint64_t, count);

//            parse_arr_param(p, array_uint64_t, defaultValue, uint64_t);
//            parse_arr_param(p, array_uint64_t, value, uint64_t);

//            parse_uint64_param(p, array_uint64_t, min);
//            parse_uint64_param(p, array_uint64_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_INT32])
        {
//            parse_string_param(p, array_int32_t, name);
//            parse_string_param(p, array_int32_t, type);
//            parse_string_param(p, array_int32_t, access);
//            parse_uint16_param(p, array_int32_t, index);
//            parse_uint32_param(p, array_int32_t, offset);
//            parse_uint32_param(p, array_int32_t, size);
//            parse_string_param(p, array_int32_t, units);

//            parse_uint32_param(p, array_int32_t, maxCount);
//            parse_uint32_param(p, array_int32_t, defCount);
//            parse_uint32_param(p, array_int32_t, count);

//            parse_arr_param(p, array_int32_t, defaultValue, int32_t);
//            parse_arr_param(p, array_int32_t, value, int32_t);

//            parse_int32_param(p, array_int32_t, min);
//            parse_int32_param(p, array_int32_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_INT64])
        {
//            parse_string_param(p, array_int64_t, name);
//            parse_string_param(p, array_int64_t, type);
//            parse_string_param(p, array_int64_t, access);
//            parse_uint16_param(p, array_int64_t, index);
//            parse_uint32_param(p, array_int64_t, offset);
//            parse_uint32_param(p, array_int64_t, size);
//            parse_string_param(p, array_int64_t, units);

//            parse_uint32_param(p, array_int64_t, maxCount);
//            parse_uint32_param(p, array_int64_t, defCount);
//            parse_uint32_param(p, array_int64_t, count);

//            parse_arr_param(p, array_int64_t, defaultValue, int64_t);
//            parse_arr_param(p, array_int64_t, value, int64_t);

//            parse_int64_param(p, array_int64_t, min);
//            parse_int64_param(p, array_int64_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_FLT])
        {
//            parse_string_param(p, array_flt_t, name);
//            parse_string_param(p, array_flt_t, type);
//            parse_string_param(p, array_flt_t, access);
//            parse_uint16_param(p, array_flt_t, index);
//            parse_uint32_param(p, array_flt_t, offset);
//            parse_uint32_param(p, array_flt_t, size);
//            parse_string_param(p, array_flt_t, units);

//            parse_uint32_param(p, array_flt_t, maxCount);
//            parse_uint32_param(p, array_flt_t, defCount);
//            parse_uint32_param(p, array_flt_t, count);

//            parse_arr_param(p, array_flt_t, defaultValue, float);
//            parse_arr_param(p, array_flt_t, value, float);

//            parse_float_param(p, array_flt_t, min);
//            parse_float_param(p, array_flt_t, max);
        }
        else if (result->type == parameter_value_types[PVT_ARRAY_DBL])
        {
//            parse_string_param(p, array_dbl_t, name);
//            parse_string_param(p, array_dbl_t, type);
//            parse_string_param(p, array_dbl_t, access);
//            parse_uint16_param(p, array_dbl_t, index);
//            parse_uint32_param(p, array_dbl_t, offset);
//            parse_uint32_param(p, array_dbl_t, size);
//            parse_string_param(p, array_dbl_t, units);

//            parse_uint32_param(p, array_dbl_t, maxCount);
//            parse_uint32_param(p, array_dbl_t, defCount);
//            parse_uint32_param(p, array_dbl_t, count);

//            parse_arr_param(p, array_dbl_t, defaultValue, double);
//            parse_arr_param(p, array_dbl_t, value, double);

//            parse_double_param(p, array_dbl_t, min);
//            parse_double_param(p, array_dbl_t, max);
        }
        else if (result->type == parameter_value_types[PVT_STRING])
        {
            result->set_value<value_str_t>(p->val_str->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            result->units = p->base.units;

            ((value_str*)result)->defaultValue = p->val_str->defValue;
            ((value_str*)result)->value = p->val_str->value;
            ((value_str*)result)->maxLen = p->val_str->maxLen;

//            parse_string_param(p, value_str_t, defaultValue);
//            parse_string_param(p, value_str_t, value);
//            parse_uint16_param(p, value_str_t, maxLen);

        }else if (result->type == parameter_value_types[PVT_UNKN])
        {
//            parse_string_param(p, value_raw_t, name);
//            parse_string_param(p, value_raw_t, type);
//            parse_string_param(p, value_raw_t, access);
//            parse_uint16_param(p, value_raw_t, index);
//            parse_uint32_param(p, value_raw_t, offset);
//            parse_uint32_param(p, value_raw_t, size);

//            parse_raw_param(p, value_raw_t);


        }

        return result;
    }
    return nullptr;
}

bool rf627smart::set_param(param_t* param)
{
    parameter_t* p = create_parameter_from_type(param->type.c_str());
    if (p != NULL)
    {
        p->base.name = param->name.c_str();
        p->base.type = param->type.c_str();
        p->base.access = param->access.c_str();
        p->base.units = param->units.c_str();
        if (param->type == parameter_value_types[PVT_STRING])
        {
            std::string new_value = param->get_value<value_str>();
            delete[] p->val_str->value;
            p->val_str->value = new char[new_value.length() + 1];
            strcpy(p->val_str->value, new_value.c_str());
            p->base.size = new_value.length() + 1;
        }
        else if (param->type == parameter_value_types[PVT_INT])
        {
            p->val_int32->value = param->get_value<value_int32>();
        }
        else if (param->type == parameter_value_types[PVT_INT64])
        {
            p->val_int64->value = param->get_value<value_int64>();
        }
        else if (param->type == parameter_value_types[PVT_UINT])
        {
            p->val_uint32->value = param->get_value<value_uint32>();
        }
        else if (param->type == parameter_value_types[PVT_UINT64])
        {
            p->val_uint64->value = param->get_value<value_uint64>();
        }
        else if (param->type == parameter_value_types[PVT_FLOAT])
        {
            p->val_flt->value = param->get_value<value_flt>();
        }
        else if (param->type ==  parameter_value_types[PVT_DOUBLE])
        {
            p->val_dbl->value = param->get_value<value_dbl>();
        }
        else if (param->type ==  parameter_value_types[PVT_ARRAY_UINT32])
        {
            std::vector<uint32_t> v = param->get_value<array_uint32>();
            p->arr_uint32->value = (rfUint32*)calloc(v.size(), sizeof (rfUint32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint32);
        }
        set_parameter((scanner_base_t*)this->scanner_base, p);
        return true;
    }
    return false;
}
bool rf627smart::set_param(const char* param_name, int arg_count, ...)
{
    va_list valist;
    va_start(valist, arg_count);

    bool result = set_parameter_by_name(
                (scanner_base_t*)this->scanner_base, param_name, arg_count, valist);

    va_end(valist);

    return result;
}
bool rf627smart::set_param(int param_id, int arg_count, ...)
{
    va_list valist;
    va_start(valist, arg_count);

    bool result = set_parameter_by_name(
                (scanner_base_t*)this->scanner_base, parameter_names[param_id].c_str(), arg_count, valist);

    va_end(valist);

    return result;
}

bool rf627smart::send_cmd(const char* command_name, int arg_count, ...)
{
    va_list valist;
    va_start(valist, arg_count);

    //int arg1 = va_arg(valist, int);
    //int arg2 = va_arg(valist, int);

    command_t cmd = {0};
    cmd.name = command_name;
    va_copy (cmd.arg_list, valist);

    bool result = send_command((scanner_base_t*)this->scanner_base, &cmd);

    va_end(valist);

    return result;
}

bool rf627smart::send_cmd(const char* command_name,
                        std::vector<uint8_t>* input, std::vector<uint8_t>* output)
{


    command2_t cmd = {0};
    cmd.name = command_name;
    cmd.input.size = input->size();
    cmd.input.payload = (rfUint8*)input->data();
    bool result = send_command2((scanner_base_t*)this->scanner_base, &cmd);

    for (int i = 0; i < cmd.output.size; i++)
        output->push_back(((uint8_t*)cmd.output.payload)[i]);

    free(cmd.output.payload);

    return result;
}

const std::string& rf627smart::hello_info::device_name()
{
    return _device_name;
}

const uint32_t& rf627smart::hello_info::serial_number()
{
    return _serial_number;
}

const std::string& rf627smart::hello_info::ip_address()
{
    return _ip_address;
}

const std::string& rf627smart::hello_info::mac_address()
{
    return _mac_address;
}

const uint16_t& rf627smart::hello_info::profile_port()
{
    return _profile_port;
}

const uint16_t& rf627smart::hello_info::service_port()
{
    return _service_port;
}

const rf627smart::hello_info::version& rf627smart::hello_info::firmware_version()
{
    return _firmware_version;
}

const rf627smart::hello_info::version& rf627smart::hello_info::hardware_version()
{
    return _hardware_version;
}

const uint32_t& rf627smart::hello_info::z_smr()
{
    return _z_smr;
}

const uint32_t& rf627smart::hello_info::z_mr()
{
    return _z_mr;
}

const uint32_t& rf627smart::hello_info::x_smr()
{
    return _x_smr;
}

const uint32_t& rf627smart::hello_info::x_emr()
{
    return _x_emr;
}


rf627smart::hello_info::hello_info(void* info, PROTOCOLS protocol)
{
    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
        _device_name = ((rf627_smart_hello_info_by_service_protocol*)info)->user_general_deviceName;
        _serial_number = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_serial;
        _ip_address = ((rf627_smart_hello_info_by_service_protocol*)info)->user_network_ip;
        _mac_address = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_network_macAddr;

        _profile_port = ((rf627_smart_hello_info_by_service_protocol*)info)->user_network_hostPort;
        _service_port = ((rf627_smart_hello_info_by_service_protocol*)info)->user_network_servicePort;

        _firmware_version = hello_info::version(((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_firmwareVer);
        _hardware_version = hello_info::version(((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_hardwareVer);

        _z_smr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_smr;
        _z_mr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_mr;
        _x_smr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_xsmr;
        //_x_emr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_xsmr + ;
        break;
    }
    default:
        break;
    }

}

rf627smart::hello_info::~hello_info()
{

}

std::ostream &operator<<(std::ostream &out, rf627smart::hello_info::version const &v)
{
    out << std::to_string(v.major) << "."
        << std::to_string(v.minor) << "."
        << std::to_string(v.patch);
    return out;
}

bool operator ==(const rf627smart::hello_info::version &v1, const rf627smart::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) ==
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator !=(const rf627smart::hello_info::version &v1,const  rf627smart::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) ==
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator <=(const rf627smart::hello_info::version &v1, const rf627smart::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) <=
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator >=(const rf627smart::hello_info::version &v1, const rf627smart::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) >=
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator <(const rf627smart::hello_info::version &v1, const rf627smart::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) <
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator >(const rf627smart::hello_info::version &v1, const rf627smart::hello_info::version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) >
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}

std::string rf627smart::hello_info::version::to_string()
{
    std::string s;
    s = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    return s;
}

uint32_t rf627smart::hello_info::version::to_uint()
{
    return _value;
}

rf627smart::hello_info::version::version()
{
    version((uint32_t)0);
}

rf627smart::hello_info::version::version(uint32_t value)
{
    major = (((uint8_t*)(void*)(&value))[3]);
    minor = (((uint8_t*)(void*)(&value))[2]);
    patch = (((uint8_t*)(void*)(&value))[1]);
    _value = value;
}

rf627smart::hello_info::version::version(std::string value)
{
    std::string s = value;
    std::string delimiter = ".";

    size_t pos = 0;
    std::string token;

    token = s.substr(0, pos);
    major =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

    token = s.substr(0, pos);
    minor =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

    token = s.substr(0, pos);
    patch =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

    _value = (major << 3) + (minor << 2) + (patch << 1);
}

rf627smart::hello_info::version::version(uint32_t *value)
{
    major = value[0];
    minor = value[1];
    patch = value[2];
    _value = (major << 3) + (minor << 2) + (patch << 1);
}

rf627smart::hello_info::version::~version()
{

}



void sdk_cleanup()
{
#if (defined _WIN32)
    FreeAdapterAddresses();
    WinSockDeinit();
#endif
}


}
}
}

