#pragma once

#include <vector>
#include <memory>

namespace SDK {
namespace RF_SCANNERS {


enum class PROTOCOLS {
    CURRENT = 0,
    SERVICE_PROTOKOL = 1,
    ETHERNET_IP = 2,
    MODBUS_TCP = 3
};

/*! Structure to store a point of profile
 */
typedef struct
{
    float x;
    float z;
}point_t;

/*! Structure to store a profile
 */
typedef struct
{
    struct
    {
        uint8_t     data_type;
        uint8_t     flags;
        uint16_t    device_type;
        uint32_t    serial_number;
        uint64_t    system_time;

        uint8_t     proto_version_major;
        uint8_t     proto_version_minor;
        uint8_t     hardware_params_offset;
        uint8_t     data_offset;
        uint32_t    packet_count;
        uint32_t    measure_count;

        uint16_t    zmr;
        uint16_t    xemr;
        uint16_t    discrete_value;
        uint8_t     reserved_0[14];

        uint32_t    exposure_time;
        uint32_t    laser_value;
        uint32_t    step_count;
        uint8_t     dir;
        uint8_t     reserved_1[3];
    }profile_header;

    union{
        std::vector<point_t> points;
        std::vector<uint16_t> pixels;
    };

    std::vector<uint8_t> intensity;
}profile_t;

}
}
