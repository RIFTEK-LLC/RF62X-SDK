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
    [PVT_UNKN]			= "unkn_t",
    [PVT_UINT]			= "uint32_t",
    [PVT_UINT64]		= "uint64_t",
    [PVT_INT]			= "int32_t",
    [PVT_INT64]			= "int64_t",
    [PVT_FLOAT]			= "float_t",
    [PVT_DOUBLE]		= "double_t",
    [PVT_ARRAY_UINT32]	= "u32_arr_t",
    [PVT_ARRAY_UINT64]	= "u64_arr_t",
    [PVT_ARRAY_INT32]	= "i32_arr_t",
    [PVT_ARRAY_INT64]	= "i64_arr_t",
    [PVT_ARRAY_FLT]		= "flt_array_t",
    [PVT_ARRAY_DBL]		= "dbl_array_t",
    [PVT_STRING]		= "string_t"
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
    [USER_GENERAL_DEVICE_NAME] 			= "user_general_deviceName",
    [USER_GENERAL_SAVE_LOG]			    = "user_general_saveLog",
    [USER_SYSMON_FPGA_TEMP]             = "user_sysMon_fpgaTemp",
    [USER_SYSMON_PARAMS_CHANGED]		= "user_sysMon_paramsChanged",
    [USER_SYSMON_TEMP_SENS_00]			= "user_sysMon_tempSens00",
    [USER_SYSMON_TEMP_SENS_00_MAX]		= "user_sysMon_tempSens00Max",
    [USER_SYSMON_TEMP_SENS_00_MIN]		= "user_sysMon_tempSens00Min",
    [USER_SYSMON_TEMP_SENS_01]          = "user_sysMon_tempSens01",
    [USER_SYSMON_TEMP_SENS_01_MAX]      = "user_sysMon_tempSens01Max",
    [USER_SYSMON_TEMP_SENS_01_MIN]		= "user_sysMon_tempSens01Min",
    [USER_SYSMON_TEMP_SENS_10]          = "user_sysMon_tempSens10",
    [USER_SYSMON_TEMP_SENS_10_MAX]		= "user_sysMon_tempSens10Max",
    [USER_SYSMON_TEMP_SENS_10_MIN]		= "user_sysMon_tempSens10Min",
    [USER_SYSMON_TEMP_SENS_11]          = "user_sysMon_tempSens11",
    [USER_SYSMON_TEMP_SENS_11_MAX]		= "user_sysMon_tempSens11Max",
    [USER_SYSMON_TEMP_SENS_11_MIN]		= "user_sysMon_tempSens11Min",
    [USER_SENSOR_EXPOSURE]              = "user_sensor_exposure",
    [USER_SENSOR_MAX_EXPOSURE]			= "user_sensor_maxExposure",
    [USER_SENSOR_AUTO_EXPOSURE_ENABLED] = "user_sensor_autoExposureEnabled",
    [USER_SENSOR_FRAME_RATE]			= "user_sensor_framerate",
    [USER_SENSOR_MAX_FRAME_RATE]		= "user_sensor_maxFramerate",
    [USER_ROI_ENABLED]                  = "user_roi_enable",
    [USER_ROI_ACTIVE]                   = "user_roi_active",
    [USER_ROI_POS_MODE]                 = "user_roi_posMode",
    [USER_ROI_POS]                      = "user_roi_pos",
    [USER_ROI_MAX_POS]          		= "user_roi_maxPos",
    [USER_ROI_REQ_PROF_SIZE]    		= "user_roi_reqProfSize",
    [USER_NETWORK_SPEED]            	= "user_network_speed",
    [USER_NETWORK_AUTO_NEG]         	= "user_network_autoNeg",
    [USER_NETWORK_IP]               	= "user_network_ip",
    [USER_NETWORK_MASK]                 = "user_network_mask",
    [USER_NETWORK_GATEWAY]          	= "user_network_gateway",
    [USER_NETWORK_HOST_IP]      		= "user_network_hostIP",
    [USER_NETWORK_HOST_PORT]			= "user_network_hostPort",
    [USER_NETWORK_WEB_PORT]         	= "user_network_webPort",
    [USER_NETWORK_SERVICE_PORT]     	= "user_network_servicePort",
    [USER_STREAMS_UDP_ENABLE]         	= "user_streams_udpEnable",
    [USER_STREAMS_FORMAT]               = "user_streams_format",
    [USER_STREAMS_INCLUDE_INTENSITY]    = "user_streams_includeIntensity",
    [USER_PROCESSING_THRESHOLD]         = "user_processing_threshold",
    [USER_PROCESSING_MODE]          	= "user_processing_mode",
    [USER_PROCESSING_PROF_PER_SEC]		= "user_processing_profPerSec",
    [USER_PROCESSING_MEDIAN_MODE]		= "user_processing_medianMode",
    [USER_PROCESSING_BILATERAL_MODE]	= "user_processing_bilateralMode",
    [USER_PROCESSING_PEAK_MODE]			= "user_processing_peakMode",
    [USER_PROCESSING_FLIP]              = "user_processing_flip",
    [USER_LASER_ENABLED]            	= "user_laser_enabled",
    [USER_LASER_MODE]           		= "user_laser_mode",
    [USER_LASER_VALUE]          		= "user_laser_value",
    [USER_INPUTS_PRESET]                = "user_laser_preset",
    [USER_INPUTS_PARAMS_MASK]           = "user_laser_params_mask",
    [USER_INPUTS_1_ENABLED]   			= "user_inputs_1_enabled",
    [USER_INPUTS_1_EVENT]   			= "user_inputs_1_event",
    [USER_INPUTS_1_MODE]        		= "user_inputs_1_mode",
    [USER_INPUTS_1_DELAY]               = "user_inputs_1_delay",
    [USER_INPUTS_1_DIVIDER]         	= "user_inputs_1_divider",
    [USER_INPUTS_2_ENABLED]         	= "user_inputs_2_enabled",
    [USER_INPUTS_2_MODE]                = "user_inputs_2_mode",
    [USER_INPUTS_2_INVERSE]         	= "user_inputs_2_inverse",
    [USER_INPUTS_3_ENABLED]         	= "user_inputs_3_enabled",
    [USER_INPUTS_3_MODE]            	= "user_inputs_3_mode",
    [USER_OUTPUTS_1_ENABLED]    		= "user_outputs_1_enabled",
    [USER_OUTPUTS_1_MODE]       		= "user_outputs_1_mode",
    [USER_OUTPUTS_1_DELAY]      		= "user_outputs_1_delay",
    [USER_OUTPUTS_1_PULSE_WIDTH]		= "user_outputs_1_pulseWidth",
    [USER_OUTPUTS_1_INVERSE]			= "user_outputs_1_inverse",
    [USER_OUTPUTS_2_ENABLED]			= "user_outputs_2_enabled",
    [USER_OUTPUTS_2_MODE]       		= "user_outputs_2_mode",
    [USER_OUTPUTS_2_DELAY]          	= "user_outputs_2_delay",
    [USER_OUTPUTS_2_PULSE_WIDTH]    	= "user_outputs_2_pulseWidth",
    [USER_OUTPUTS_2_INVERSE]        	= "user_outputs_2_inverse",
    [USER_VIEW_3D_MOTION_TYPE]  		= "user_view_3D_motionType",
    [USER_VIEW_3D_Y_SOURCE]             = "user_view_3D_ySource",
    [USER_VIEW_3D_Y_STEP]               = "user_view_3D_yStep",
    [USER_VIEW_3D_PAINT_MODE]       	= "user_view_3D_paintMode",
    [USER_VIEW_3D_DECIMATION]       	= "user_view_3D_decimation",
    [USER_EIP_TCP_PORT]                 = "user_eip_tcpPort",
    [USER_EIP_UDP_PORT]             	= "user_eip_udpPort",
    [USER_EIP_TCP_TTL]              	= "user_eip_tcp_ttl",
    [USER_EIP_TCP_TIMEOUT]          	= "user_eip_tcp_timeout",
    [USER_EIP_TCP_MULTICAST_ALLOC]  	= "user_eip_tcp_multiCast_alloc",
    [USER_EIP_TCP_MULTICAST_NUM]        = "user_eip_tcp_multiCast_num",
    [USER_EIP_TCP_MULTICAST_ADDR]   	= "user_eip_tcp_multiCast_addr",
    [USER_COMPATIBILITY_RF625_ENABLED]	= "user_compatibility_rf625Enabled",
    [USER_COMPATIBILITY_RF625_TCP_PORT]	= "user_compatibility_rf625TCPPort",
    [USER_SENSOR_DOUBLE_SPEED_ENABLED]	= "user_sensor_doubleSpeedEnabled",
    [USER_SENSOR_EDR_TYPE_1_ENABLED]	= "user_sensor_edrType1Enabled",
    [USER_SENSOR_EDRTYPE2_ENABLED]      = "user_sensor_edrType2Enabled",
    [USER_SENSOR_EDR_TYPE_2_DIVIDER]	= "user_sensor_edrType2Divider",
    [USER_SENSOR_EDR_TYPE_2_MAX_DIVIDER]= "user_sensor_edrType2MaxDivider",
    [USER_ROI_SIZE]                     = "user_roi_size"
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
