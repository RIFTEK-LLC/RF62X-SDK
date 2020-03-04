#pragma once

#include <vector>
#include <memory>

namespace SDK {
namespace SCANNERS {
namespace RF627 {

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

        uint32_t    exposure_time;
        uint32_t    laser_value;
        uint32_t    step_count;
        uint8_t     dir;
    }profile_header;

    union{
        std::vector<point_t> points;
        std::vector<uint16_t> pixels;
    };

    std::vector<uint8_t> intensity;
}profile_t;

//Типы значений параметров
typedef enum
{
    PVT_UNKN = 0,
    PVT_UINT,
    PVT_UINT64,
    PVT_INT,
    PVT_INT64,
    PVT_FLOAT,
    PVT_DOUBLE,
    PVT_ARRAY_UINT32,
    PVT_ARRAY_UINT64,
    PVT_ARRAY_INT32,
    PVT_ARRAY_INT64,
    PVT_ARRAY_FLT,
    PVT_ARRAY_DBL,
    PVT_STRING
}param_value_type_t;

const static std::string pvtKey[]	=
{
    "unkn_t",
    "uint32_t",
    "uint64_t",
    "int32_t",
    "int64_t",
    "float_t",
    "double_t",
    "u32_arr_t",
    "u64_arr_t",
    "i32_arr_t",
    "i64_arr_t",
    "flt_array_t",
    "dbl_array_t",
    "string_t"
};

//Поддерживаемый доступ к параметру
typedef enum
{
    PAT_UNKN				= 0,
    PAT_READ_ONLY,
    PAT_WRITE,
    PAT_RESTRICTED,
}param_access_type_t;

typedef enum {
    USER_GENERAL_DEVICE_NAME = 0,
    USER_GENERAL_SAVE_LOG,
    USER_SYSMON_FPGA_TEMP,
    USER_SYSMON_PARAMS_CHANGED,
    USER_SYSMON_TEMP_SENS_00,
    USER_SYSMON_TEMP_SENS_00_MAX,
    USER_SYSMON_TEMP_SENS_00_MIN,
    USER_SYSMON_TEMP_SENS_01,
    USER_SYSMON_TEMP_SENS_01_MAX,
    USER_SYSMON_TEMP_SENS_01_MIN,
    USER_SYSMON_TEMP_SENS_10,
    USER_SYSMON_TEMP_SENS_10_MAX,
    USER_SYSMON_TEMP_SENS_10_MIN,
    USER_SYSMON_TEMP_SENS_11,
    USER_SYSMON_TEMP_SENS_11_MAX,
    USER_SYSMON_TEMP_SENS_11_MIN,
    USER_SENSOR_EXPOSURE,
    USER_SENSOR_MAX_EXPOSURE,
    USER_SENSOR_AUTO_EXPOSURE_ENABLED,
    USER_SENSOR_FRAME_RATE,
    USER_SENSOR_MAX_FRAME_RATE,
    USER_ROI_ENABLED,
    USER_ROI_ACTIVE,
    USER_ROI_POS_MODE,
    USER_ROI_POS,
    USER_ROI_MAX_POS,
    USER_ROI_REQ_PROF_SIZE,
    USER_NETWORK_SPEED,
    USER_NETWORK_AUTO_NEG,
    USER_NETWORK_IP,
    USER_NETWORK_MASK,
    USER_NETWORK_GATEWAY,
    USER_NETWORK_HOST_IP,
    USER_NETWORK_HOST_PORT,
    USER_NETWORK_WEB_PORT,
    USER_NETWORK_SERVICE_PORT,
    USER_STREAMS_UDP_ENABLE,
    USER_STREAMS_FORMAT,
    USER_STREAMS_INCLUDE_INTENSITY,
    USER_PROCESSING_THRESHOLD,
    USER_PROCESSING_MODE,
    USER_PROCESSING_PROF_PER_SEC,
    USER_PROCESSING_MEDIAN_MODE,
    USER_PROCESSING_BILATERAL_MODE,
    USER_PROCESSING_PEAK_MODE,
    USER_PROCESSING_FLIP,
    USER_LASER_ENABLED,
    USER_LASER_MODE,
    USER_LASER_VALUE,
    USER_INPUTS_PRESET,
    USER_INPUTS_PARAMS_MASK,
    USER_INPUTS_1_ENABLED,
    USER_INPUTS_1_EVENT,
    USER_INPUTS_1_MODE,
    USER_INPUTS_1_DELAY,
    USER_INPUTS_1_DIVIDER,
    USER_INPUTS_2_ENABLED,
    USER_INPUTS_2_MODE,
    USER_INPUTS_2_INVERSE,
    USER_INPUTS_3_ENABLED,
    USER_INPUTS_3_MODE,
    USER_OUTPUTS_1_ENABLED,
    USER_OUTPUTS_1_MODE,
    USER_OUTPUTS_1_DELAY,
    USER_OUTPUTS_1_PULSE_WIDTH,
    USER_OUTPUTS_1_INVERSE,
    USER_OUTPUTS_2_ENABLED,
    USER_OUTPUTS_2_MODE,
    USER_OUTPUTS_2_DELAY,
    USER_OUTPUTS_2_PULSE_WIDTH,
    USER_OUTPUTS_2_INVERSE,
    USER_VIEW_3D_MOTION_TYPE,
    USER_VIEW_3D_Y_SOURCE,
    USER_VIEW_3D_Y_STEP,
    USER_VIEW_3D_PAINT_MODE,
    USER_VIEW_3D_DECIMATION,
    USER_EIP_TCP_PORT,
    USER_EIP_UDP_PORT,
    USER_EIP_TCP_TTL,
    USER_EIP_TCP_TIMEOUT,
    USER_EIP_TCP_MULTICAST_ALLOC,
    USER_EIP_TCP_MULTICAST_NUM,
    USER_EIP_TCP_MULTICAST_ADDR,
    USER_COMPATIBILITY_RF625_ENABLED,
    USER_COMPATIBILITY_RF625_TCP_PORT,
    USER_SENSOR_DOUBLE_SPEED_ENABLED,
    USER_SENSOR_EDR_TYPE_1_ENABLED,
    USER_SENSOR_EDRTYPE2_ENABLED,
    USER_SENSOR_EDR_TYPE_2_DIVIDER,
    USER_SENSOR_EDR_TYPE_2_MAX_DIVIDER,
    USER_ROI_SIZE
}parameter_name_keys_t;

const static std::string parameter_names[]	=
{
    "user_general_deviceName",
    "user_general_saveLog",
    "user_sysMon_fpgaTemp",
    "user_sysMon_paramsChanged",
    "user_sysMon_tempSens00",
    "user_sysMon_tempSens00Max",
    "user_sysMon_tempSens00Min",
    "user_sysMon_tempSens01",
    "user_sysMon_tempSens01Max",
    "user_sysMon_tempSens01Min",
    "user_sysMon_tempSens10",
    "user_sysMon_tempSens10Max",
    "user_sysMon_tempSens10Min",
    "user_sysMon_tempSens11",
    "user_sysMon_tempSens11Max",
    "user_sysMon_tempSens11Min",
    "user_sensor_exposure",
    "user_sensor_maxExposure",
    "user_sensor_autoExposureEnabled",
    "user_sensor_framerate",
    "user_sensor_maxFramerate",
    "user_roi_enable",
    "user_roi_active",
    "user_roi_posMode",
    "user_roi_pos",
    "user_roi_maxPos",
    "user_roi_reqProfSize",
    "user_network_speed",
    "user_network_autoNeg",
    "user_network_ip",
    "user_network_mask",
    "user_network_gateway",
    "user_network_hostIP",
    "user_network_hostPort",
    "user_network_webPort",
    "user_network_servicePort",
    "user_streams_udpEnable",
    "user_streams_format",
    "user_streams_includeIntensity",
    "user_processing_threshold",
    "user_processing_mode",
    "user_processing_profPerSec",
    "user_processing_medianMode",
    "user_processing_bilateralMode",
    "user_processing_peakMode",
    "user_processing_flip",
    "user_laser_enabled",
    "user_laser_mode",
    "user_laser_value",
    "user_laser_preset",
    "user_laser_params_mask",
    "user_inputs_1_enabled",
    "user_inputs_1_event",
    "user_inputs_1_mode",
    "user_inputs_1_delay",
    "user_inputs_1_divider",
    "user_inputs_2_enabled",
    "user_inputs_2_mode",
    "user_inputs_2_inverse",
    "user_inputs_3_enabled",
    "user_inputs_3_mode",
    "user_outputs_1_enabled",
    "user_outputs_1_mode",
    "user_outputs_1_delay",
    "user_outputs_1_pulseWidth",
    "user_outputs_1_inverse",
    "user_outputs_2_enabled",
    "user_outputs_2_mode",
    "user_outputs_2_delay",
    "user_outputs_2_pulseWidth",
    "user_outputs_2_inverse",
    "user_view_3D_motionType",
    "user_view_3D_ySource",
    "user_view_3D_yStep",
    "user_view_3D_paintMode",
    "user_view_3D_decimation",
    "user_eip_tcpPort",
    "user_eip_udpPort",
    "user_eip_tcp_ttl",
    "user_eip_tcp_timeout",
    "user_eip_tcp_multiCast_alloc",
    "user_eip_tcp_multiCast_num",
    "user_eip_tcp_multiCast_addr",
    "user_compatibility_rf625Enabled",
    "user_compatibility_rf625TCPPort",
    "user_sensor_doubleSpeedEnabled",
    "user_sensor_edrType1Enabled",
    "user_sensor_edrType2Enabled",
    "user_sensor_edrType2Divider",
    "user_sensor_edrType2MaxDivider",
    "user_roi_size"
};


typedef struct
{
  std::string  name;
  std::string  type;
  std::string  access;
  uint16_t     index;
  uint32_t	   offset;
  uint32_t	   size;
  std::string  units;
  template <typename T>
  auto get_value()->decltype( std::declval<T>().value )
  {
      return ((T*)this)->value;
  }
  template <typename T>
  void set_value(decltype( std::declval<T>().value) value)
  {
      ((T*)this)->value = value;
  }
  template <typename T>
  auto get_min()->decltype( std::declval<T>().min )
  {
      return ((T*)this)->min;
  }
  template <typename T>
  auto get_max()->decltype( std::declval<T>().max )
  {
      return ((T*)this)->max;
  }
  template <typename T>
  auto get_default_value()->decltype( std::declval<T>().defaultValue )
  {
      return ((T*)this)->defaultValue;
  }
  template <typename T>
  auto get_values_enum()->decltype( std::declval<T>().valuesEnum )
  {
      return ((T*)this)->valuesEnum;
  }
  template <typename T>
  auto get_units()->decltype( std::declval<T>().units )
  {
      return ((T*)this)->units;
  }
  template <typename T>
  auto get_count()->decltype( std::declval<T>().maxCount )
  {
      return ((T*)this)->maxCount;
  }
  template <typename T>
  auto get_default_count()->decltype( std::declval<T>().defCount )
  {
      return ((T*)this)->defCount;
  }
  template <typename T>
  auto get_max_length()->decltype( std::declval<T>().maxLen )
  {
      return ((T*)this)->maxLen;
  }
}param_t;

typedef struct value_uint32_t : param_t
{
  uint32_t    min;
  uint32_t    max;
  uint32_t    defaultValue;
  std::vector <std::pair<uint32_t, std::string>> valuesEnum;
  uint32_t    value;

}value_uint32_t;

typedef struct value_uint64_t : param_t
{
  uint64_t    min;
  uint64_t    max;
  uint64_t    defaultValue;
  std::vector <std::pair<uint64_t, std::string>> valuesEnum;
  uint64_t    value;
}value_uint64_t;

typedef struct value_int32_t : param_t
{
  int32_t     min;
  int32_t     max;
  int32_t     defaultValue;
  std::vector <std::pair<int32_t, std::string>> valuesEnum;
  int32_t     value;
}value_int32_t;

typedef struct value_int64_t : param_t
{
  int64_t     min;
  int64_t     max;
  int64_t     defaultValue;
  std::vector <std::pair<int64_t, std::string>> valuesEnum;
  int64_t     value;
}value_int64_t;

typedef struct value_flt_t : param_t
{
  float        min;
  float        max;
  float        defaultValue;
  float        value;
}value_flt_t;

typedef struct value_dbl_t : param_t
{
  double        min;
  double        max;
  double        defaultValue;
  double        value;
}value_dbl_t;

typedef struct array_uint_t : param_t
{
  uint32_t    min;
  uint32_t    max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <uint32_t> defaultValue;
  uint32_t    count;
  std::vector <uint32_t> value;
}array_uint_t;

typedef struct array_uint64_t : param_t
{
  uint64_t    min;
  uint64_t    max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <uint64_t>   defaultValue;
  uint32_t    count;
  std::vector <uint64_t>   value;
}array_uint64_t;

typedef struct array_int32_t : param_t
{
  int32_t     min;
  int32_t     max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <int32_t> defaultValue;
  uint32_t    count;
  std::vector <int32_t> value;
}array_int32_t;

typedef struct array_int64_t : param_t
{
  int64_t     min;
  int64_t     max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <int64_t> defaultValue;
  uint32_t    count;
  std::vector <int64_t> value;
}array_int64_t;

typedef struct array_flt_t : param_t
{
  float       min;
  float       max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <float> defaultValue;
  uint32_t    count;
  std::vector <float> value;
}array_flt_t;

typedef struct array_dbl_t : param_t
{
  double      min;
  double      max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <double> defaultValue;
  uint32_t    count;
  std::vector <double> value;
}array_dbl_t;

typedef struct value_str_t : param_t
{
  uint16_t      maxLen;
  std::string   defaultValue;
  std::string   value;
}value_str_t;

typedef struct value_raw_t : param_t
{
  void*         raw_data;
}value_raw_t;


}
}
}
