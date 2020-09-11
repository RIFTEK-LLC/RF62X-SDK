from ctypes import *
from struct import unpack
from socket import inet_aton
from enum import IntEnum
import netifaces as ni #get all available network adapters

_profile_max_len=1296

rfInt16 = c_int16  # platform_types.h: 13
rfInt32 = c_int32  # platform_types.h: 14
rfUint8 = c_uint8  # platform_types.h: 16
rfUint16 = c_uint16  # platform_types.h: 17
rfUint32 = c_uint32  # platform_types.h: 18
rfChar = c_char  # platform_types.h: 20
rfBool = c_uint8  # platform_types.h: 22
rfSize = c_size_t  # platform_types.h: 23
rfFloat = c_float  # platform_types.h: 25
rfDouble = c_double  # platform_types.h: 26
rfInt64 = c_int64  # platform_types.h: 30
rfUint64 = c_uint64  # platform_types.h: 31

######################################
# enums
class CONST_rf627_old_data_type_t(IntEnum):
    DTY_PixelsNormal        = 0x10,
    DTY_ProfileNormal       = 0x11,
    DTY_PixelsInterpolated  = 0x12,
    DTY_ProfileInterpolated = 0x13

class CONST_paramValueType_t(IntEnum):
        PVT_UNKN        =0
        PVT_UINT        =1
        PVT_UINT64      =2
        PVT_INT =3
        PVT_INT64       =4
        PVT_FLOAT       =5
        PVT_DOUBLE      =6
        PVT_ARRAY_UINT32        =7
        PVT_ARRAY_UINT64        =8
        PVT_ARRAY_INT32 =9
        PVT_ARRAY_INT64 =10
        PVT_ARRAY_FLT   =11
        PVT_ARRAY_DBL   =12
        PVT_STRING      =13

class CONST_paramAccessType_t(IntEnum):	
        MAT_UNKN                =0
        MAT_FACTORY_ONLY        =1
        MAT_USER        =2

class CONST_parameter_name_keys_t(IntEnum):		
        FACT_GENERAL_PROTOCOLREV        =0
        FACT_GENERAL_DEVICETYPE =1
        FACT_GENERAL_SERIAL     =2
        FACT_GENERAL_PCBSERIAL  =3
        FACT_GENERAL_LIFETIME   =4
        FACT_GENERAL_WORKTIME   =5
        FACT_GENERAL_STARTSCOUNT        =6
        FACT_GENERAL_FIRMWAREREV        =7
        FACT_GENERAL_HARDWAREREV        =8
        FACT_GENERAL_FSBLREV    =9
        FACT_GENERAL_CUSTOMERID =10
        FACT_GENERAL_FPGAFREQ   =11
        FACT_GENERAL_SMR        =12
        FACT_GENERAL_MR =13
        FACT_GENERAL_XSMR       =14
        FACT_GENERAL_XEMR       =15
        FACT_GENERAL_PIXDIVIDER =16
        FACT_GENERAL_PROFDIVIDER        =17
        FACT_GENERAL_OEMDEVNAME =18
        FACT_GENERAL_AUTHSTATUS =19
        FACT_SENSOR_NAME        =20
        FACT_SENSOR_WIDTH       =21
        FACT_SENSOR_HEIGHT      =22
        FACT_SENSOR_PIXFREQ     =23
        FACT_SENSOR_FRMCONSTPART        =24
        FACT_SENSOR_FRMPERLINEPART      =25
        FACT_SENSOR_FPSOREXP    =26
        FACT_SENSOR_MINEXPOSURE =27
        FACT_SENSOR_MAXEXPOSURE =28
        FACT_SENSOR_IMGFLIP     =29
        FACT_NETWORK_MACADDR    =30
        FACT_NETWORK_FORCEAUTONEGTIME   =31
        FACT_NETWORK_WEBSOCKSERVICEPORT =32
        FACT_NETWORK_WEBSOCKDATAPORT    =33
        FACT_NETWORK_WEBSOCKMATHPORT    =34
        FACT_LASER_WAVELENGTH   =35
        FACT_LASER_KOEFF1       =36
        FACT_LASER_KOEFF2       =37
        FACT_LASER_MINVALUE     =38
        FACT_LASER_MAXVALUE     =39
        FACT_PROFILES_MAXDUMPSIZE       =40
        FACT_EIP_IDENTITY_VENDORID      =41
        FACT_EIP_IDENTITY_DEVICETYPE    =42
        FACT_EIP_IDENTITY_PRODUCTCODE   =43
        FACT_EIP_IDENTITY_REV   =44
        FACT_EIP_TCPINTRF_CAPABILITY    =45
        FACT_EIP_TCPINTRF_PHY_PATHSIZE  =46
        FACT_EIP_TCPINTRF_PHY_CLASSID   =47
        FACT_EIP_TCPINTRF_PHY_INSTNUMBER        =48
        FACT_EIP_TCPINTRF_PHY_ATTRNUMBER        =49
        FACT_EIP_INTRFTYPE      =50
        FACT_EIP_INTRFCAPABILITY_BITS   =51
        FACT_EIP_INTRFCAPABILITY_SPEEDDUPCOUNT  =52
        FACT_EIP_INTRFCAPABILITY_SPEEDDUPLEX_SPEED      =53
        FACT_EIP_INTRFCAPABILITY_SPEEDDUPLEX_DUPLEX     =54
        FACT_SENSOR_ANALOGGAIN  =55
        FACT_SENSOR_DIGITALGAIN =56
        FACT_SENSOR_BLACKODD    =57
        FACT_SENSOR_BLACKEVEN   =58
        FACT_SENSOR_HDRPIECEWISEDIV1    =59
        FACT_SENSOR_HDRPIECEWISEDIV2    =60
        FACT_SENSOR_INITREGS    =61
        USER_GENERAL_DEVICESTATE        =62
        USER_GENERAL_DEVICENAME =63
        USER_GENERAL_SAVELOG    =64
        USER_SYSMON_FPGATEMP    =65
        USER_SYSMON_PARAMSCHANGED       =66
        USER_SYSMON_TEMPSENS00  =67
        USER_SYSMON_TEMPSENS00MAX       =68
        USER_SYSMON_TEMPSENS00MIN       =69
        USER_SYSMON_TEMPSENS01  =70
        USER_SYSMON_TEMPSENS01MAX       =71
        USER_SYSMON_TEMPSENS01MIN       =72
        USER_SYSMON_TEMPSENS10  =73
        USER_SYSMON_TEMPSENS10MAX       =74
        USER_SYSMON_TEMPSENS10MIN       =75
        USER_SYSMON_TEMPSENS11  =76
        USER_SYSMON_TEMPSENS11MAX       =77
        USER_SYSMON_TEMPSENS11MIN       =78
        USER_SENSOR_SYNCSOURCE  =79
        USER_SENSOR_FRAMERATE   =80
        USER_SENSOR_MAXFRAMERATE        =81
        USER_SENSOR_EXPOSURECONTROL     =82
        USER_SENSOR_EXPOSURE1   =83
        USER_SENSOR_EXPOSURE2   =84
        USER_SENSOR_EXPOSURE3   =85
        USER_SENSOR_EXPOSURE4   =86
        USER_SENSOR_MAXEXPOSURE =87
        USER_ROI_ENABLED        =88
        USER_ROI_ACTIVE =89
        USER_ROI_POSMODE        =90
        USER_ROI_POS    =91
        USER_ROI_MAXPOS =92
        USER_ROI_REQPROFSIZE    =93
        USER_NETWORK_SPEED      =94
        USER_NETWORK_REQUIREDSPEED      =95
        USER_NETWORK_AUTONEG    =96
        USER_NETWORK_IP =97
        USER_NETWORK_MASK       =98
        USER_NETWORK_GATEWAY    =99
        USER_NETWORK_HOSTIP     =100
        USER_NETWORK_HOSTPORT   =101
        USER_NETWORK_WEBPORT    =102
        USER_NETWORK_SERVICEPORT        =103
        USER_STREAMS_UDPENABLED =104
        USER_STREAMS_FORMAT     =105
        USER_STREAMS_INCLUDEINTENSITY   =106
        USER_PROCESSING_THRESHOLD       =107
        USER_PROCESSING_PROFPERSEC      =108
        USER_PROCESSING_MEDIANMODE      =109
        USER_PROCESSING_BILATERALMODE   =110
        USER_PROCESSING_PEAKMODE        =111
        USER_PROCESSING_FLIP    =112
        USER_LASER_ENABLED      =113
        USER_LASER_VALUE        =114
        USER_TRIGGER_SYNC_SOURCE        =115
        USER_TRIGGER_SYNC_STRICTENABLED =116
        USER_TRIGGER_SYNC_DIVIDER       =117
        USER_TRIGGER_SYNC_DELAY =118
        USER_TRIGGER_COUNTER_TYPE       =119
        USER_TRIGGER_COUNTER_MAXVALUEENABLED    =120
        USER_TRIGGER_COUNTER_MAXVALUE   =121
        USER_TRIGGER_COUNTER_RESETTIMERENABLED  =122
        USER_TRIGGER_COUNTER_RESETTIMERVALUE    =123
        USER_TRIGGER_COUNTER_VALUE      =124
        USER_INPUT1_ENABLED     =125
        USER_INPUT1_MODE        =126
        USER_INPUT2_ENABLED     =127
        USER_INPUT2_MODE        =128
        USER_INPUT3_ENABLED     =129
        USER_INPUT3_MODE        =130
        USER_INPUT1_SAMPLES     =131
        USER_INPUT2_SAMPLES     =132
        USER_INPUT3_SAMPLES     =133
        USER_OUTPUT1_ENABLED    =134
        USER_OUTPUT1_MODE       =135
        USER_OUTPUT1_PULSEWIDTH =136
        USER_OUTPUT2_ENABLED    =137
        USER_OUTPUT2_MODE       =138
        USER_OUTPUT2_PULSEWIDTH =139
        USER_DUMP_ENABLED       =140
        USER_DUMP_CAPACITY      =141
        USER_DUMP_SIZE  =142
        USER_DUMP_TIMESTAMP     =143
        USER_DUMP_VIEW3D_MOTIONTYPE     =144
        USER_DUMP_VIEW3D_YSOURCE        =145
        USER_DUMP_VIEW3D_YSTEP  =146
        USER_DUMP_VIEW3D_PAINTMODE      =147
        USER_DUMP_VIEW3D_DECIMATION     =148
        USER_EIP_TCPPORT        =149
        USER_EIP_UDPPORT        =150
        USER_EIP_TCP_TTL        =151
        USER_EIP_TCP_TIMEOUT    =152
        USER_EIP_TCP_MULTICAST_ALLOC    =153
        USER_EIP_TCP_MULTICAST_NUM      =154
        USER_EIP_TCP_MULTICAST_ADDR     =155
        USER_COMPATIBILITY_RF625ENABLED =156
        USER_COMPATIBILITY_RF625TCPPORT =157
        USER_SENSOR_DOUBLESPEEDENABLED  =158
        USER_SENSOR_EDRTYPE     =159
        USER_SENSOR_EDRCOLUMNDIVIDER    =160
        USER_STREAMS_POINTSCOUNT        =161
        USER_ROI_SIZE   =162


_CONST_parameter_names_array=[
  "fact_general_protocolRev",
    "fact_general_deviceType",
    "fact_general_serial",
    "fact_general_pcbSerial",
    "fact_general_lifeTime",
    "fact_general_workTime",
    "fact_general_startsCount",
    "fact_general_firmWareRev",
    "fact_general_hardWareRev",
    "fact_general_fsblRev",
    "fact_general_customerID",
    "fact_general_fpgaFreq",
    "fact_general_smr",
    "fact_general_mr",
    "fact_general_xsmr",
    "fact_general_xemr",
    "fact_general_pixDivider",
    "fact_general_profDivider",
    "fact_general_oemDevName",
    "fact_general_authStatus",
    "fact_sensor_name",
    "fact_sensor_width",
    "fact_sensor_height",
    "fact_sensor_pixFreq",
    "fact_sensor_frmConstPart",
    "fact_sensor_frmPerLinePart",
    "fact_sensor_fpsOrExp",
    "fact_sensor_minExposure",
    "fact_sensor_maxExposure",
    "fact_sensor_imgFlip",
    "fact_network_macAddr",
    "fact_network_forceAutoNegTime",
    "fact_network_webSockServicePort",
    "fact_network_webSockDataPort",
    "fact_network_webSockMathPort",
    "fact_laser_waveLength",
    "fact_laser_koeff1",
    "fact_laser_koeff2",
    "fact_laser_minValue",
    "fact_laser_maxValue",
    "fact_profiles_maxDumpSize",
    "fact_eip_identity_vendorID",
    "fact_eip_identity_deviceType",
    "fact_eip_identity_productCode",
    "fact_eip_identity_rev",
    "fact_eip_tcpIntrf_capability",
    "fact_eip_tcpIntrf_phy_pathSize",
    "fact_eip_tcpIntrf_phy_classId",
    "fact_eip_tcpIntrf_phy_instNumber",
    "fact_eip_tcpIntrf_phy_attrNumber",
    "fact_eip_intrfType",
    "fact_eip_intrfCapability_bits",
    "fact_eip_intrfCapability_speedDupCount",
    "fact_eip_intrfCapability_speedDuplex_speed",
    "fact_eip_intrfCapability_speedDuplex_duplex",
    "fact_sensor_analogGain",
    "fact_sensor_digitalGain",
    "fact_sensor_blackOdd",
    "fact_sensor_blackEven",
    "fact_sensor_hdrPiecewiseDiv1",
    "fact_sensor_hdrPiecewiseDiv2",
    "fact_sensor_initRegs",

    "user_general_deviceState",
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
    "user_sensor_syncSource",
    "user_sensor_framerate",
    "user_sensor_maxFramerate",
    "user_sensor_exposureControl",
    "user_sensor_exposure1",
    "user_sensor_exposure2",
    "user_sensor_exposure3",
    "user_sensor_exposure4",
    "user_sensor_maxExposure",
    "user_roi_enabled",
    "user_roi_active",
    "user_roi_posMode",
    "user_roi_pos",
    "user_roi_maxPos",
    "user_roi_reqProfSize",
    "user_network_speed",
    "user_network_requiredSpeed",
    "user_network_autoNeg",
    "user_network_ip",
    "user_network_mask",
    "user_network_gateway",
    "user_network_hostIP",
    "user_network_hostPort",
    "user_network_webPort",
    "user_network_servicePort",
    "user_streams_udpEnabled",
    "user_streams_format",
    "user_streams_includeIntensity",
    "user_processing_threshold",
    "user_processing_profPerSec",
    "user_processing_medianMode",
    "user_processing_bilateralMode",
    "user_processing_peakMode",
    "user_processing_flip",
    "user_laser_enabled",
    "user_laser_value",
    "user_trigger_sync_source",
    "user_trigger_sync_strictEnabled",
    "user_trigger_sync_divider",
    "user_trigger_sync_delay",
    "user_trigger_counter_type",
    "user_trigger_counter_maxValueEnabled",
    "user_trigger_counter_maxValue",
    "user_trigger_counter_resetTimerEnabled",
    "user_trigger_counter_resetTimerValue",
    "user_trigger_counter_value",
    "user_input1_enabled",
    "user_input1_mode",
    "user_input2_enabled",
    "user_input2_mode",
    "user_input3_enabled",
    "user_input3_mode",
    "user_input1_samples",
    "user_input2_samples",
    "user_input3_samples",
    "user_output1_enabled",
    "user_output1_mode",
    "user_output1_pulseWidth",
    "user_output2_enabled",
    "user_output2_mode",
    "user_output2_pulseWidth",
    "user_dump_enabled",
    "user_dump_capacity",
    "user_dump_size",
    "user_dump_timeStamp",
    "user_dump_view3d_motionType",
    "user_dump_view3d_ySource",
    "user_dump_view3d_yStep",
    "user_dump_view3d_paintMode",
    "user_dump_view3d_decimation",
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
    "user_sensor_edrType",
    "user_sensor_edrColumnDivider",
    "user_streams_pointsCount",
    "user_roi_size"
    ]

CONST_parameter_names_array=[x.encode('utf-8') for x in _CONST_parameter_names_array] #Encoded to UTF-8


CONST_pvtKey=[
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
    ]

CONST_patKey=[
       "unkn",
    "read_only",
    "write",
    "locked",
]

CONST_matKey=[
        "unkn",
    "factory_only",
    "user",
]

class CONST_scanner_types_t(IntEnum):
    kRF627_OLD = 1,
    kRF627_SMART = 2	
	
class CONST_protocol_types_t(IntEnum):
    kSERVICE = 1,
    kETHERNET_IP = 2,
    kMODBUS_TCP = 3,
	
class CONST_count_types_t(IntEnum):
    kSTEP = 1,
    kMEASURE = 2,
    kPACKET = 3,

		
 ######################################


# custom_vector.h: 10
class struct_vector_(Structure):
    pass


struct_vector_.__slots__ = [
    'data',
    'size',
    'count',
]
struct_vector_._fields_ = [
    ('data', POINTER(POINTER(None))),
    ('size', rfSize),
    ('count', rfSize),
]

vector_t = struct_vector_  # custom_vector.h: 10

# rf62X_types.h: 15


class struct_anon_1(Structure):
    pass


struct_anon_1.__slots__ = [
    'version',
    'length',
    'validated',
    'reserved',
]
struct_anon_1._fields_ = [
    ('version', rfUint32),
    ('length', rfUint32),
    ('validated', rfUint8),
    ('reserved', rfUint8),
]

config_options_t = struct_anon_1  # rf62X_types.h: 15

# rf62X_types.h: 20


class struct_anon_2(Structure):
    pass


struct_anon_2.__slots__ = [
    'device_id',
    'serial',
    'serial_of_pcb',
    'operating_time_h',
    'operating_time_m',
    'operating_time_s',
    'runtime_h',
    'runtime_m',
    'runtime_s',
    'startup_counter',
    'firmware_ver',
    'hardware_ver',
    'customer_id',
    'fpga_freq',
    'base_z',
    'range_z',
    'range_x_start',
    'range_x_end',
    'pixels_divider',
    'profiles_divider',
    'fsbl_version',
    'oem_device_name',
    'reserved',
]
struct_anon_2._fields_ = [
    ('device_id', rfUint16),
    ('serial', rfUint32),
    ('serial_of_pcb', rfUint32),
    ('operating_time_h', rfUint32),
    ('operating_time_m', rfUint8),
    ('operating_time_s', rfUint8),
    ('runtime_h', rfUint32),
    ('runtime_m', rfUint8),
    ('runtime_s', rfUint8),
    ('startup_counter', rfUint32),
    ('firmware_ver', rfUint32),
    ('hardware_ver', rfUint32),
    ('customer_id', rfUint32),
    ('fpga_freq', rfUint32),
    ('base_z', rfUint32),
    ('range_z', rfUint32),
    ('range_x_start', rfUint32),
    ('range_x_end', rfUint32),
    ('pixels_divider', rfUint16),
    ('profiles_divider', rfUint16),
    ('fsbl_version', rfUint32),
    ('oem_device_name', rfChar * int(16)),
    ('reserved', rfUint8 * int(76)),
]

# rf62X_types.h: 66


class struct_anon_3(Structure):
    pass


struct_anon_3.__slots__ = [
    'addr',
    'value',
]
struct_anon_3._fields_ = [
    ('addr', rfUint16),
    ('value', rfUint16),
]

# rf62X_types.h: 47


class struct_anon_4(Structure):
    pass


struct_anon_4.__slots__ = [
    'name',
    'width',
    'height',
    'pixel_clock',
    'black_odd_lines',
    'black_even_lines',
    'frame_cycle_const_part',
    'frame_cycle_per_line_part',
    'frame_rate_or_exposure',
    'min_exposure',
    'image_flipping',
    'max_exposure',
    'edr_point1_value',
    'edr_point2_value',
    'edr_point1_pos',
    'edr_point2_pos',
    'reserved',
    'init_regs',
]
struct_anon_4._fields_ = [
    ('name', rfChar * int(32)),
    ('width', rfUint16),
    ('height', rfUint16),
    ('pixel_clock', rfUint32),
    ('black_odd_lines', rfUint16),
    ('black_even_lines', rfUint16),
    ('frame_cycle_const_part', rfUint32),
    ('frame_cycle_per_line_part', rfUint32),
    ('frame_rate_or_exposure', rfUint8),
    ('min_exposure', rfUint32),
    ('image_flipping', rfUint8),
    ('max_exposure', rfUint32),
    ('edr_point1_value', rfUint8),
    ('edr_point2_value', rfUint8),
    ('edr_point1_pos', rfUint16),
    ('edr_point2_pos', rfUint16),
    ('reserved', rfUint8 * int(113)),
    ('init_regs', struct_anon_3 * int(64)),
]

# rf62X_types.h: 73


class struct_anon_5(Structure):
    pass


struct_anon_5.__slots__ = [
    'mac',
    'eip_vendor_id',
    'eip_device_type',
    'force_autoneg_time',
    'reserved',
]
struct_anon_5._fields_ = [
    ('mac', rfUint8 * int(6)),
    ('eip_vendor_id', rfUint16),
    ('eip_device_type', rfUint16),
    ('force_autoneg_time', rfUint8),
    ('reserved', rfUint8 * int(31)),
]

# rf62X_types.h: 82


class struct_anon_6(Structure):
    pass


struct_anon_6.__slots__ = [
    'wave_length',
    'koeff1',
    'koeff2',
    'min_value',
    'max_value',
    'enable_mode_change',
    'reserved',
]
struct_anon_6._fields_ = [
    ('wave_length', rfUint16),
    ('koeff1', rfUint8),
    ('koeff2', rfUint8),
    ('min_value', rfUint32),
    ('max_value', rfUint32),
    ('enable_mode_change', rfUint8),
    ('reserved', rfUint8 * int(31)),
]

# rf62X_types.h: 93


class struct_anon_7(Structure):
    pass


struct_anon_7.__slots__ = [
    'in1_min_delay',
    'in1_max_delay',
    'max_divider_in1',
    'min_divider_in1',
    'reserved',
]
struct_anon_7._fields_ = [
    ('in1_min_delay', rfUint16),
    ('in1_max_delay', rfUint32),
    ('max_divider_in1', rfUint16),
    ('min_divider_in1', rfUint16),
    ('reserved', rfUint8 * int(62)),
]

# rf62X_types.h: 102


class struct_anon_8(Structure):
    pass


struct_anon_8.__slots__ = [
    'out1_min_delay',
    'out1_max_delay',
    'out1_min_pulse_width',
    'out1_max_pulse_width',
    'out2_min_delay',
    'out2_max_delay',
    'out2_min_pulse_width',
    'out2_max_pulse_width',
    'reserved',
]
struct_anon_8._fields_ = [
    ('out1_min_delay', rfUint16),
    ('out1_max_delay', rfUint32),
    ('out1_min_pulse_width', rfUint16),
    ('out1_max_pulse_width', rfUint32),
    ('out2_min_delay', rfUint16),
    ('out2_max_delay', rfUint32),
    ('out2_min_pulse_width', rfUint16),
    ('out2_max_pulse_width', rfUint32),
    ('reserved', rfUint8 * int(32)),
]

# rf62X_types.h: 115


class struct_anon_9(Structure):
    pass


struct_anon_9.__slots__ = [
    'max_dump_size',
    'reserved',
]
struct_anon_9._fields_ = [
    ('max_dump_size', rfUint32),
    ('reserved', rfUint8 * int(60)),
]

# rf62X_types.h: 128


class struct_anon_10(Structure):
    pass


struct_anon_10.__slots__ = [
    'major_rev',
    'minor_rev',
]
struct_anon_10._fields_ = [
    ('major_rev', c_uint8),
    ('minor_rev', rfUint8),
]

# rf62X_types.h: 123


class struct_anon_11(Structure):
    pass


struct_anon_11.__slots__ = [
    'vendor_iD',
    'device_type',
    'product_code',
    'revision',
]
struct_anon_11._fields_ = [
    ('vendor_iD', rfUint16),
    ('device_type', rfUint16),
    ('product_code', rfUint16),
    ('revision', struct_anon_10),
]

# rf62X_types.h: 137


class struct_anon_12(Structure):
    pass


struct_anon_12.__slots__ = [
    'path_size',
    'classId',
    'instance_number',
    'attribute_number',
]
struct_anon_12._fields_ = [
    ('path_size', c_uint16),
    ('classId', rfUint16),
    ('instance_number', rfUint16),
    ('attribute_number', rfUint16),
]

# rf62X_types.h: 134


class struct_anon_13(Structure):
    pass


struct_anon_13.__slots__ = [
    'config_capability',
    'phyLinkObject',
]
struct_anon_13._fields_ = [
    ('config_capability', rfUint32),
    ('phyLinkObject', struct_anon_12),
]

# rf62X_types.h: 149


class struct_anon_14(Structure):
    pass


struct_anon_14.__slots__ = [
    'speed',
    'duplex',
]
struct_anon_14._fields_ = [
    ('speed', rfUint16),
    ('duplex', rfUint8),
]

# rf62X_types.h: 146


class struct_anon_15(Structure):
    pass


struct_anon_15.__slots__ = [
    'capability_bits',
    'speed_dup_count',
    'speedDuplex',
]
struct_anon_15._fields_ = [
    ('capability_bits', c_uint16),
    ('speed_dup_count', rfUint8),
    ('speedDuplex', struct_anon_14 * int(4)),
]

# rf62X_types.h: 121


class struct_anon_16(Structure):
    pass


struct_anon_16.__slots__ = [
    'identity',
    'tcpInterface',
    'intrf_type',
    'intrfCapability',
    'reserved',
]
struct_anon_16._fields_ = [
    ('identity', struct_anon_11),
    ('tcpInterface', struct_anon_13),
    ('intrf_type', rfUint8),
    ('intrfCapability', struct_anon_15),
    ('reserved', rfUint8 * int(44)),
]

# rf62X_types.h: 161


class struct_anon_17(Structure):
    pass


struct_anon_17.__slots__ = [
    'general',
    'sensor',
    'network',
    'laser',
    'inputs',
    'outputs',
    'profiles',
    'eip',
    'reserved',
]
struct_anon_17._fields_ = [
    ('general', struct_anon_2),
    ('sensor', struct_anon_4),
    ('network', struct_anon_5),
    ('laser', struct_anon_6),
    ('inputs', struct_anon_7),
    ('outputs', struct_anon_8),
    ('profiles', struct_anon_9),
    ('eip', struct_anon_16),
    ('reserved', rfUint8 * int(167)),
]

rf627_old_factory_params_t = struct_anon_17  # rf62X_types.h: 161

# rf62X_types.h: 231


class struct_anon_26(Structure):
    pass


struct_anon_26.__slots__ = [
    'name',
    'save_log_to_spi',
    'reserved',
]
struct_anon_26._fields_ = [
    ('name', rfChar * int(64)),
    ('save_log_to_spi', rfUint8),
    ('reserved', rfUint8 * int(127)),
]

# rf62X_types.h: 238


class struct_anon_27(Structure):
    pass


struct_anon_27.__slots__ = [
    'fpga_temp',
    'params_changed',
    'sens00_temp',
    'sens00_max',
    'sens00_min',
    'sens01_temp',
    'sens01_max',
    'sens01_min',
    'sens10_temp',
    'sens10_max',
    'sens10_min',
    'sens11_temp',
    'sens11_max',
    'sens11_min',
    'reserved',
]
struct_anon_27._fields_ = [
    ('fpga_temp', rfInt16),
    ('params_changed', rfUint8),
    ('sens00_temp', rfInt16),
    ('sens00_max', rfInt16),
    ('sens00_min', rfInt16),
    ('sens01_temp', rfInt16),
    ('sens01_max', rfInt16),
    ('sens01_min', rfInt16),
    ('sens10_temp', rfInt16),
    ('sens10_max', rfInt16),
    ('sens10_min', rfInt16),
    ('sens11_temp', rfInt16),
    ('sens11_max', rfInt16),
    ('sens11_min', rfInt16),
    ('reserved', rfUint8 * int(55)),
]

# rf62X_types.h: 257


class struct_anon_28(Structure):
    pass


struct_anon_28.__slots__ = [
    'enable',
    'tcp_port',
    'reserved',
]
struct_anon_28._fields_ = [
    ('enable', rfUint8),
    ('tcp_port', rfUint16),
    ('reserved', rfUint8 * int(32)),
]

# rf62X_types.h: 264


class struct_anon_29(Structure):
    pass


struct_anon_29.__slots__ = [
    'dhs',
    'gain_analog',
    'gain_digital',
    'exposure',
    'max_exposure',
    'frame_rate',
    'max_frame_rate',
    'exposure_hdr_mode',
    'auto_exposure',
    'column_edr_mode',
    'column_exposure_div',
    'column_exposure_max_div',
    'reserved_1',
]
struct_anon_29._fields_ = [
    ('dhs', rfUint8),
    ('gain_analog', rfUint8),
    ('gain_digital', rfUint8),
    ('exposure', rfUint32),
    ('max_exposure', rfUint32),
    ('frame_rate', rfUint32),
    ('max_frame_rate', rfUint32),
    ('exposure_hdr_mode', rfUint8),
    ('auto_exposure', rfUint8),
    ('column_edr_mode', rfUint8),
    ('column_exposure_div', rfUint8),
    ('column_exposure_max_div', rfUint8),
    ('reserved_1', rfUint8 * int(59)),
]

# rf62X_types.h: 281


class struct_anon_30(Structure):
    pass


struct_anon_30.__slots__ = [
    'enable',
    'active',
    'size',
    'position_mode',
    'manual_position',
    'auto_position',
    'required_profile_size',
    'reserved',
]
struct_anon_30._fields_ = [
    ('enable', rfUint8),
    ('active', rfUint8),
    ('size', rfUint16),
    ('position_mode', rfUint8),
    ('manual_position', rfUint16),
    ('auto_position', rfUint16),
    ('required_profile_size', rfUint16),
    ('reserved', rfUint8 * int(80)),
]

# rf62X_types.h: 293


class struct_anon_31(Structure):
    pass


struct_anon_31.__slots__ = [
    'speed',
    'autonegotiation',
    'ip_address',
    'net_mask',
    'gateway_ip',
    'host_ip',
    'stream_port',
    'http_port',
    'service_port',
    'reserved',
]
struct_anon_31._fields_ = [
    ('speed', rfUint16),
    ('autonegotiation', rfUint8),
    ('ip_address', rfUint8 * int(4)),
    ('net_mask', rfUint8 * int(4)),
    ('gateway_ip', rfUint8 * int(4)),
    ('host_ip', rfUint8 * int(4)),
    ('stream_port', rfUint16),
    ('http_port', rfUint16),
    ('service_port', rfUint16),
    ('reserved', rfUint8 * int(68)),
]

# rf62X_types.h: 309


class struct_anon_32(Structure):
    pass


struct_anon_32.__slots__ = [
    'enable',
    'format',
    'ack',
    'include_intensivity',
    'reserved',
]
struct_anon_32._fields_ = [
    ('enable', rfUint8),
    ('format', rfUint8),
    ('ack', rfUint8),
    ('include_intensivity', rfUint8),
    ('reserved', rfUint8 * int(31)),
]

# rf62X_types.h: 318


class struct_anon_33(Structure):
    pass


struct_anon_33.__slots__ = [
    'brightness_threshold',
    'filter_width',
    'processing_mode',
    'reduce_noise',
    'frame_rate',
    'median_filter_mode',
    'bilateral_filter_mode',
    'peak_select_mode',
    'profile_flip',
    'reserved',
]
struct_anon_33._fields_ = [
    ('brightness_threshold', rfUint32),
    ('filter_width', rfUint8),
    ('processing_mode', rfUint8),
    ('reduce_noise', rfUint8),
    ('frame_rate', rfUint32),
    ('median_filter_mode', rfUint8),
    ('bilateral_filter_mode', rfUint8),
    ('peak_select_mode', rfUint8),
    ('profile_flip', rfUint8),
    ('reserved', rfUint8 * int(56)),
]

# rf62X_types.h: 332


class struct_anon_34(Structure):
    pass


struct_anon_34.__slots__ = [
    'enable',
    'level_mode',
    'level',
    'reserved',
]
struct_anon_34._fields_ = [
    ('enable', rfUint8),
    ('level_mode', rfUint8),
    ('level', rfUint16),
    ('reserved', rfUint8 * int(32)),
]

# rf62X_types.h: 343


class struct_anon_35(Structure):
    pass


struct_anon_35.__slots__ = [
    'params_mask',
    'in1_enable',
    'in1_mode',
    'in1_delay',
    'in1_decimation',
    'in2_enable',
    'in2_mode',
    'in2_invert',
    'in3_enable',
    'in3_mode',
    'reserved',
]
struct_anon_35._fields_ = [
    ('params_mask', rfUint16),
    ('in1_enable', rfUint8),
    ('in1_mode', rfUint8),
    ('in1_delay', rfUint32),
    ('in1_decimation', rfUint8),
    ('in2_enable', rfUint8),
    ('in2_mode', rfUint8),
    ('in2_invert', rfUint8),
    ('in3_enable', rfUint8),
    ('in3_mode', rfUint8),
    ('reserved', rfUint8 * int(12)),
]

# rf62X_types.h: 340


class struct_anon_36(Structure):
    pass


struct_anon_36.__slots__ = [
    'preset_index',
    'params',
    'reserved',
]
struct_anon_36._fields_ = [
    ('preset_index', rfUint8),
    ('params', struct_anon_35 * int(12)),
    ('reserved', rfUint8 * int(32)),
]

# rf62X_types.h: 360


class struct_anon_37(Structure):
    pass


struct_anon_37.__slots__ = [
    'out1_enable',
    'out1_mode',
    'out1_delay',
    'out1_pulse_width',
    'out1_invert',
    'out2_enable',
    'out2_mode',
    'out2_delay',
    'out2_pulse_width',
    'out2_invert',
    'reserved',
]
struct_anon_37._fields_ = [
    ('out1_enable', rfUint8),
    ('out1_mode', rfUint8),
    ('out1_delay', rfUint32),
    ('out1_pulse_width', rfUint32),
    ('out1_invert', rfUint8),
    ('out2_enable', rfUint8),
    ('out2_mode', rfUint8),
    ('out2_delay', rfUint32),
    ('out2_pulse_width', rfUint32),
    ('out2_invert', rfUint8),
    ('reserved', rfUint8 * int(32)),
]

# rf62X_types.h: 376


class struct_anon_38(Structure):
    pass


struct_anon_38.__slots__ = [
    'general',
    'sysmon',
    'rf625compat',
    'sensor',
    'roi',
    'network',
    'stream',
    'image_processing',
    'laser',
    'inputs',
    'outputs',
    'reserved',
]
struct_anon_38._fields_ = [
    ('general', struct_anon_26),
    ('sysmon', struct_anon_27),
    ('rf625compat', struct_anon_28),
    ('sensor', struct_anon_29),
    ('roi', struct_anon_30),
    ('network', struct_anon_31),
    ('stream', struct_anon_32),
    ('image_processing', struct_anon_33),
    ('laser', struct_anon_34),
    ('inputs', struct_anon_36),
    ('outputs', struct_anon_37),
    ('reserved', rfUint8 * int(283)),
]

rf627_old_user_params_t = struct_anon_38  # rf62X_types.h: 376

# rf62X_types.h: 404


class struct_anon_39(Structure):
    pass


struct_anon_39.__slots__ = [
    'data_type',
    'flags',
    'device_type',
    'serial_number',
    'system_time',
    'proto_version_major',
    'proto_version_minor',
    'hardware_params_offset',
    'data_offset',
    'packet_count',
    'measure_count',
    'zmr',
    'xemr',
    'discrete_value',
    'reserved_0',
    'exposure_time',
    'laser_value',
    'step_count',
    'dir',
    'reserved_1',
]
struct_anon_39._fields_ = [
    ('data_type', rfUint8),
    ('flags', rfUint8),
    ('device_type', rfUint16),
    ('serial_number', rfUint32),
    ('system_time', rfUint64),
    ('proto_version_major', rfUint8),
    ('proto_version_minor', rfUint8),
    ('hardware_params_offset', rfUint8),
    ('data_offset', rfUint8),
    ('packet_count', rfUint32),
    ('measure_count', rfUint32),
    ('zmr', rfUint16),
    ('xemr', rfUint16),
    ('discrete_value', rfUint16),
    ('reserved_0', rfUint8 * int(14)),
    ('exposure_time', rfUint32),
    ('laser_value', rfUint32),
    ('step_count', rfUint32),
    ('dir', rfUint8),
    ('reserved_1', rfUint8 * int(3)),
]

rf627_old_profile_header_t = struct_anon_39  # rf62X_types.h: 404

# rf62X_types.h: 431


class struct_anon_43(Structure):
    pass


struct_anon_43.__slots__ = [
    'x',
    'z',
]
struct_anon_43._fields_ = [
    ('x', rfFloat),
    ('z', rfFloat),
]

rf627_old_point2D_t = struct_anon_43  # rf62X_types.h: 431

# rf62X_types.h: 440


class struct_anon_44(Structure):
    pass


struct_anon_44.__slots__ = [
    'x',
    'y',
    'z',
]
struct_anon_44._fields_ = [
    ('x', rfFloat),
    ('y', rfFloat),
    ('z', rfFloat),
]

rf627_old_point3D_t = struct_anon_44  # rf62X_types.h: 440

# rf62X_types.h: 448


class struct_anon_45(Structure):
    pass


struct_anon_45.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_45._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

# rf62X_types.h: 452


class struct_anon_46(Structure):
    pass


struct_anon_46.__slots__ = [
    'points',
    'points_count',
]
struct_anon_46._fields_ = [
    ('points', POINTER(rf627_old_point2D_t)),
    ('points_count', rfUint32),
]

# rf62X_types.h: 447


class union_anon_47(Union):
    pass


union_anon_47.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_47._fields_ = [
    ('pixels_format', struct_anon_45),
    ('profile_format', struct_anon_46),
]

# rf62X_types.h: 459


class struct_anon_48(Structure):
    pass


struct_anon_48.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_48._anonymous_ = [
    'unnamed_1',
]
struct_anon_48._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_47),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_old_profile2D_t = struct_anon_48  # rf62X_types.h: 459

# rf62X_types.h: 467


class struct_anon_49(Structure):
    pass


struct_anon_49.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_49._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

# rf62X_types.h: 471


class struct_anon_50(Structure):
    pass


struct_anon_50.__slots__ = [
    'points',
    'points_count',
]
struct_anon_50._fields_ = [
    ('points', POINTER(rf627_old_point3D_t)),
    ('points_count', rfUint32),
]

# rf62X_types.h: 466


class union_anon_51(Union):
    pass


union_anon_51.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_51._fields_ = [
    ('pixels_format', struct_anon_49),
    ('profile_format', struct_anon_50),
]

# rf62X_types.h: 478


class struct_anon_52(Structure):
    pass


struct_anon_52.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_52._anonymous_ = [
    'unnamed_1',
]
struct_anon_52._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_51),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_old_profile3D_t = struct_anon_52  # rf62X_types.h: 478

# rf62X_types.h: 486


class struct_anon_53(Structure):
    pass


struct_anon_53.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_53._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

# rf62X_types.h: 490


class struct_anon_54(Structure):
    pass


struct_anon_54.__slots__ = [
    'points',
    'points_count',
]
struct_anon_54._fields_ = [
    ('points', POINTER(rf627_old_point2D_t)),
    ('points_count', rfUint32),
]

# rf62X_types.h: 485


class union_anon_55(Union):
    pass


union_anon_55.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_55._fields_ = [
    ('pixels_format', struct_anon_53),
    ('profile_format', struct_anon_54),
]

# rf62X_types.h: 497


class struct_anon_56(Structure):
    pass


struct_anon_56.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_56._anonymous_ = [
    'unnamed_1',
]
struct_anon_56._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_55),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_smart_profile2D_t = struct_anon_56  # rf62X_types.h: 497

# rf62X_types.h: 505


class struct_anon_57(Structure):
    pass


struct_anon_57.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_57._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

# rf62X_types.h: 509


class struct_anon_58(Structure):
    pass


struct_anon_58.__slots__ = [
    'points',
    'points_count',
]
struct_anon_58._fields_ = [
    ('points', POINTER(rf627_old_point3D_t)),
    ('points_count', rfUint32),
]

# rf62X_types.h: 504


class union_anon_59(Union):
    pass


union_anon_59.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_59._fields_ = [
    ('pixels_format', struct_anon_57),
    ('profile_format', struct_anon_58),
]

# rf62X_types.h: 516


class struct_anon_60(Structure):
    pass


struct_anon_60.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_60._anonymous_ = [
    'unnamed_1',
]
struct_anon_60._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_59),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_smart_profile3D_t = struct_anon_60  # rf62X_types.h: 516

# rf62X_types.h: 533


class struct_anon_61(Structure):
    pass


struct_anon_61.__slots__ = [
    'device_name',
    'serial_number',
    'ip_address',
    'mac_address',
    'profile_port',
    'service_port',
    'firmware_version',
    'hardware_version',
    'z_begin',
    'z_range',
    'x_begin',
    'x_end',
]
struct_anon_61._fields_ = [
    ('device_name', c_char_p),  # POINTER(rfChar)),
    ('serial_number', rfUint32),
    ('ip_address', rfUint8 * int(4)),
    ('mac_address', rfUint8 * int(6)),
    ('profile_port', rfUint16),
    ('service_port', rfUint16),
    ('firmware_version', rfUint32),
    ('hardware_version', rfUint32),
    ('z_begin', rfUint32),
    ('z_range', rfUint32),
    ('x_begin', rfUint32),
    ('x_end', rfUint32),
]

rf627_old_hello_info_by_service_protocol = struct_anon_61  # rf62X_types.h: 533

# rf62X_types.h: 946


class struct_anon_66(Structure):
    pass


struct_anon_66.__slots__ = [
    'value',
    'key',
]
struct_anon_66._fields_ = [
    ('value', rfInt32),
    ('key', c_char_p),  # POINTER(rfChar)
]

enumRec_t = struct_anon_66  # rf62X_types.h: 946

# rf62X_types.h: 952


class struct_anon_67(Structure):
    pass


struct_anon_67.__slots__ = [
    'recCount',
    'rec',
]
struct_anon_67._fields_ = [
    ('recCount', rfInt32),
    ('rec', enumRec_t),   
    # ('rec', POINTER(enumRec_t)),
]

valuesEnum_t = struct_anon_67  # rf62X_types.h: 952

# rf62X_types.h: 963


class struct_anon_68(Structure):
    pass


struct_anon_68.__slots__ = [
    'name',
    'type',
    'access',
    'index',
    'offset',
    'size',
    'units',
]
struct_anon_68._fields_ = [
    ('name', c_char_p),  # POINTER(rfChar)
    ('type', c_char_p),  # POINTER(rfChar)
    ('access', c_char_p),  # POINTER(rfChar)
    ('index', rfUint16),
    ('offset', rfUint32),
    ('size', rfUint32),
    ('units', c_char_p),  # POINTER(rfChar)
]

value_base_t = struct_anon_68  # rf62X_types.h: 963

# rf62X_types.h: 974


class struct_value_uint32_t(Structure):
    pass


struct_value_uint32_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_uint32_t._fields_ = [
    ('min', rfUint32),
    ('max', rfUint32),
    ('step', rfUint32),
    ('defValue', rfUint32),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfUint32),
]

value_uint32_t = struct_value_uint32_t  # rf62X_types.h: 974

# rf62X_types.h: 984


class struct_value_uint64_t(Structure):
    pass


struct_value_uint64_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_uint64_t._fields_ = [
    ('min', rfUint64),
    ('max', rfUint64),
    ('step', rfUint64),
    ('defValue', rfUint64),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfUint64),
]

value_uint64_t = struct_value_uint64_t  # rf62X_types.h: 984

# rf62X_types.h: 994


class struct_value_int32_t(Structure):
    pass


struct_value_int32_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_int32_t._fields_ = [
    ('min', rfInt32),
    ('max', rfInt32),
    ('step', rfInt32),
    ('defValue', rfInt32),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfInt32),
]

value_int32_t = struct_value_int32_t  # rf62X_types.h: 994

# rf62X_types.h: 1004


class struct_value_int64_t(Structure):
    pass


struct_value_int64_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_int64_t._fields_ = [
    ('min', rfInt64),
    ('max', rfInt64),
    ('step', rfInt64),
    ('defValue', rfInt64),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfInt64),
]

value_int64_t = struct_value_int64_t  # rf62X_types.h: 1004

# rf62X_types.h: 1013


class struct_value_flt_t(Structure):
    pass


struct_value_flt_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'value',
]
struct_value_flt_t._fields_ = [
    ('min', rfFloat),
    ('max', rfFloat),
    ('step', rfFloat),
    ('defValue', rfFloat),
    ('value', rfFloat),
]

value_flt_t = struct_value_flt_t  # rf62X_types.h: 1013

# rf62X_types.h: 1022


class struct_value_dbl_t(Structure):
    pass


struct_value_dbl_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'value',
]
struct_value_dbl_t._fields_ = [
    ('min', rfDouble),
    ('max', rfDouble),
    ('step', rfDouble),
    ('defValue', rfDouble),
    ('value', rfDouble),
]

value_dbl_t = struct_value_dbl_t  # rf62X_types.h: 1022

# rf62X_types.h: 1034


class struct_array_uint32_t(Structure):
    pass


struct_array_uint32_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_uint32_t._fields_ = [
    ('min', rfUint32),
    ('max', rfUint32),
    ('step', rfUint32),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfUint32)),
    ('count', rfUint32),
    ('value', POINTER(rfUint32)),
]

array_uint32_t = struct_array_uint32_t  # rf62X_types.h: 1034

# rf62X_types.h: 1046


class struct_array_uint64_t(Structure):
    pass


struct_array_uint64_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_uint64_t._fields_ = [
    ('min', rfUint64),
    ('max', rfUint64),
    ('step', rfUint64),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfUint64)),
    ('count', rfUint32),
    ('value', POINTER(rfUint64)),
]

array_uint64_t = struct_array_uint64_t  # rf62X_types.h: 1046

# rf62X_types.h: 1058


class struct_array_int32_t(Structure):
    pass


struct_array_int32_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_int32_t._fields_ = [
    ('min', rfInt32),
    ('max', rfInt32),
    ('step', rfInt32),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfInt32)),
    ('count', rfUint32),
    ('value', POINTER(rfInt32)),
]

array_int32_t = struct_array_int32_t  # rf62X_types.h: 1058

# rf62X_types.h: 1070


class struct_array_int64_t(Structure):
    pass


struct_array_int64_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_int64_t._fields_ = [
    ('min', rfInt64),
    ('max', rfInt64),
    ('step', rfInt64),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfInt64)),
    ('count', rfUint32),
    ('value', POINTER(rfInt64)),
]

array_int64_t = struct_array_int64_t  # rf62X_types.h: 1070

# rf62X_types.h: 1082


class struct_array_flt_t(Structure):
    pass


struct_array_flt_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_flt_t._fields_ = [
    ('min', rfFloat),
    ('max', rfFloat),
    ('step', rfFloat),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfFloat)),
    ('count', rfUint32),
    ('value', POINTER(rfFloat)),
]

array_flt_t = struct_array_flt_t  # rf62X_types.h: 1082

# rf62X_types.h: 1094


class struct_array_dbl_t(Structure):
    pass


struct_array_dbl_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_dbl_t._fields_ = [
    ('min', rfDouble),
    ('max', rfDouble),
    ('step', rfDouble),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfDouble)),
    ('count', rfUint32),
    ('value', POINTER(rfDouble)),
]

array_dbl_t = struct_array_dbl_t  # rf62X_types.h: 1094

# rf62X_types.h: 1101


class struct_value_str_t(Structure):
    pass


struct_value_str_t.__slots__ = [
    'maxLen',
    'defValue',
    'value',
]
struct_value_str_t._fields_ = [
    ('maxLen', rfUint16),
    ('defValue', c_char_p),  # POINTER(rfChar)
    ('value', c_char_p),  # POINTER(rfChar)
]

value_str_t = struct_value_str_t  # rf62X_types.h: 1101

# rf62X_types.h: 1107


class union_anon_69(Union):
    pass


union_anon_69.__slots__ = [
    'rawData',
    'val_uint32',
    'val_uint64',
    'val_int32',
    'val_int64',
    'val_flt',
    'val_dbl',
    'arr_uint32',
    'arr_uint64',
    'arr_int32',
    'arr_int64',
    'arr_flt',
    'arr_dbl',
    'val_str',
]
union_anon_69._fields_ = [
    ('rawData', POINTER(None)),
    ('val_uint32', POINTER(value_uint32_t)),
    ('val_uint64', POINTER(value_uint64_t)),
    ('val_int32', POINTER(value_int32_t)),
    ('val_int64', POINTER(value_int64_t)),
    ('val_flt', POINTER(value_flt_t)),
    ('val_dbl', POINTER(value_dbl_t)),
    ('arr_uint32', POINTER(array_uint32_t)),
    ('arr_uint64', POINTER(array_uint64_t)),
    ('arr_int32', POINTER(array_int32_t)),
    ('arr_int64', POINTER(array_int64_t)),
    ('arr_flt', POINTER(array_flt_t)),
    ('arr_dbl', POINTER(array_dbl_t)),
    ('val_str', POINTER(value_str_t)),
]

# rf62X_types.h: 1123


class struct_anon_70(Structure):
    pass


struct_anon_70.__slots__ = [
    'base',
    'unnamed_1',
]
struct_anon_70._anonymous_ = [
    'unnamed_1',
]
struct_anon_70._fields_ = [
    ('base', value_base_t),
    ('unnamed_1', union_anon_69),
]

parameter_t = struct_anon_70  # rf62X_types.h: 1123

# rf62X_types.h: 1130


class struct_anon_71(Structure):
    pass


struct_anon_71.__slots__ = [
    'name',
    'arg_list',
]
struct_anon_71._fields_ = [
    ('name', c_char_p),  # POINTER(rfChar)
    ('arg_list', c_void_p),
]

command_t = struct_anon_71  # rf62X_types.h: 1130

enum_anon_72 = c_int  # rf62X_types.h: 1140

scanner_types_t = enum_anon_72  # rf62X_types.h: 1140

enum_anon_73 = c_int  # rf62X_types.h: 1146

protocol_types_t = enum_anon_73  # rf62X_types.h: 1146

enum_anon_74 = c_int  # rf62X_types.h: 1152

count_types_t = enum_anon_74  # rf62X_types.h: 1152


# rf62X_types.h: 1159
class union_anon_75(Union):
    pass


union_anon_75.__slots__ = [
    'rf627_profile2D',
    'rf627smart_profile2D',
]
union_anon_75._fields_ = [
    ('rf627_profile2D', POINTER(rf627_old_profile2D_t)),
    ('rf627smart_profile2D', POINTER(rf627_smart_profile2D_t)),
]

# rf62X_types.h: 1163


class struct_anon_76(Structure):
    pass


struct_anon_76.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_76._anonymous_ = [
    'unnamed_1',
]
struct_anon_76._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_75),
]

rf627_profile2D_t = struct_anon_76  # rf62X_types.h: 1163

# rf62X_types.h: 1170


class union_anon_77(Union):
    pass


union_anon_77.__slots__ = [
    'rf627_profile3D',
    'rf627smart_profile3D',
]
union_anon_77._fields_ = [
    ('rf627_profile3D', POINTER(rf627_old_profile3D_t)),
    ('rf627smart_profile3D', POINTER(rf627_smart_profile3D_t)),
]

# rf62X_types.h: 1174


class struct_anon_78(Structure):
    pass


struct_anon_78.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_78._anonymous_ = [
    'unnamed_1',
]
struct_anon_78._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_77),
]

rf627_profile3D_t = struct_anon_78  # rf62X_types.h: 1174

# rf62X_types.h: 1183


class union_anon_79(Union):
    pass


union_anon_79.__slots__ = [
    'hello_info_service_protocol',
]
union_anon_79._fields_ = [
    ('hello_info_service_protocol', POINTER(
        rf627_old_hello_info_by_service_protocol)),
]

# rf62X_types.h: 1186


class union_anon_80(Union):
    pass


union_anon_80.__slots__ = [
    'hello_info_service_protocol',
]
union_anon_80._fields_ = [
    ('hello_info_service_protocol', POINTER(
        rf627_old_hello_info_by_service_protocol)),
]

# rf62X_types.h: 1182


class union_anon_81(Union):
    pass


union_anon_81.__slots__ = [
    'rf627old',
    'rf627smart',
]
union_anon_81._fields_ = [
    ('rf627old', union_anon_79),
    ('rf627smart', union_anon_80),
]

# rf62X_types.h: 1190


class struct_anon_82(Structure):
    pass


struct_anon_82.__slots__ = [
    'scanner_type',
    'protocol_type',
    'unnamed_1',
]
struct_anon_82._anonymous_ = [
    'unnamed_1',
]
struct_anon_82._fields_ = [
    ('scanner_type', scanner_types_t),
    ('protocol_type', protocol_types_t),
    ('unnamed_1', union_anon_81),
]

hello_information = struct_anon_82  # rf62X_types.h: 1190

# rf62X_devices.h: 22


class struct_anon_83(Structure):
    pass


struct_anon_83.__slots__ = [
    'options',
    'factory_params',
    'user_params',
    'm_svc_sock',
    'm_data_sock',
    'msg_count',
    'host_ip',
    'params_list',
    'info_by_service_protocol',
]
struct_anon_83._fields_ = [
    ('options', config_options_t),
    ('factory_params', rf627_old_factory_params_t),
    ('user_params', rf627_old_user_params_t),
    ('m_svc_sock', POINTER(None)),
    ('m_data_sock', POINTER(None)),
    ('msg_count', rfUint16),
    ('host_ip', rfUint32),
    ('params_list', POINTER(vector_t)),
    ('info_by_service_protocol', rf627_old_hello_info_by_service_protocol),
]

rf627_old_t = struct_anon_83  # rf62X_devices.h: 22

# rf62X_devices.h: 175


class struct_anon_84(Structure):
    pass


struct_anon_84.__slots__ = [
    'm_svc_sock',
    'm_data_sock',
    'msg_count',
    'params_list',
]
struct_anon_84._fields_ = [
    ('m_svc_sock', POINTER(None)),
    ('m_data_sock', POINTER(None)),
    ('msg_count', rfUint16),
    ('params_list', POINTER(vector_t)),
]

rf627_smart_t = struct_anon_84  # rf62X_devices.h: 175

# rf62X_devices.h: 182


class union_anon_85(Union):
    pass


union_anon_85.__slots__ = [
    'rf627_old',
    'rf627_smart',
]
union_anon_85._fields_ = [
    ('rf627_old', POINTER(rf627_old_t)),
    ('rf627_smart', POINTER(rf627_smart_t)),
]

# rf62X_devices.h: 186


class struct_anon_86(Structure):
    pass


struct_anon_86.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_86._anonymous_ = [
    'unnamed_1',
]
struct_anon_86._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_85),
]

scanner_base_t = struct_anon_86  # rf62X_devices.h: 186

lib = cdll.LoadLibrary("./rf62Xsdk.dll")

# C functions in DLL to be called from Python (interface)

lib.core_init.restype = c_bool
lib.core_init.argtypes = None

lib.core_version.restype = c_char_p
lib.core_version.argtypes = None


lib.set_platform_adapter_settings.argtypes = [rfUint32, rfUint32]
lib.set_platform_adapter_settings.restype = None

lib.search_scanners.argtypes = [ POINTER(vector_t), scanner_types_t, protocol_types_t]
lib.search_scanners.restype = rfUint8

lib.get_info_about_scanner.argtypes = [ POINTER(scanner_base_t), protocol_types_t]
lib.get_info_about_scanner.restype = hello_information

lib.connect_to_scanner.argtypes = [ POINTER(scanner_base_t), protocol_types_t]
lib.connect_to_scanner.restype = rfUint8

lib.disconnect_from_scanner.argtypes = [ POINTER(scanner_base_t), protocol_types_t]
lib.disconnect_from_scanner.restype = rfUint8

lib.get_profile2D_from_scanner.argtypes = [ POINTER(scanner_base_t), rfBool, protocol_types_t]
lib.get_profile2D_from_scanner.restype = POINTER(rf627_profile2D_t)


lib.get_profile3D_from_scanner.argtypes = [POINTER(scanner_base_t), rfFloat, rfFloat, count_types_t, rfBool, protocol_types_t]
lib.get_profile3D_from_scanner.restype = POINTER(rf627_profile3D_t)

lib.read_params_from_scanner.argtypes = [ POINTER(scanner_base_t), protocol_types_t]
lib.read_params_from_scanner.restype = rfUint8

lib.write_params_to_scanner.argtypes = [POINTER(scanner_base_t), protocol_types_t]
lib.write_params_to_scanner.restype = rfUint8

lib.get_parameter.argtypes = [ POINTER(scanner_base_t), c_char_p]  
lib.get_parameter.restype = POINTER(parameter_t)


lib.set_parameter.argtypes = [POINTER(scanner_base_t), POINTER(parameter_t)]
lib.set_parameter.restype = rfUint8

lib.set_parameter_by_name.argtypes = [ POINTER(scanner_base_t),  c_char_p, rfUint32, c_void_p]  
lib.set_parameter_by_name.restype = rfUint8


lib.platform_free.argtypes = [c_void_p]  
lib.platform_free.restype = None

######################################
# helper functions

def inet_addr(addr):
    return unpack("!I", inet_aton(addr))[0]

def num_to_ip(num):
    return '.'.join(str(x) for x in num)

def num_to_mac(num):
    return ':'.join(format(x, '02x') for x in num)    

def parse_version(version_as_int32):
    num = version_as_int32
    major = (num >> (8 * 3)) & 0xFF
    minor = (num >> (8 * 2)) & 0xFF
    patch = (num >> (8 * 1)) & 0xFF
    return str(major)+"."+str(minor)+"."+str(patch)

def getdict(struct):
    ''' struct to dict'''
    ret={}
    for field, type in struct._fields_:
        ret [field]= getattr(struct, field)
        if ("_Array_") in str(type):
            val= ret [field]
            ret [field]=[val[i] for i in range(len(val))]
        elif ("c_char_p") in str(type):
            ret[field]=ret[field].decode('utf-8')
    return ret

def parse_py_get_info_about_scanner(p):
    ret={}
    ret=getdict(p.rf627old.hello_info_service_protocol.contents)
    ret['scanner_type']=p.scanner_type
    ret['protocol_type']=p.protocol_type
    ret['ip_address']=num_to_ip(ret['ip_address'])
    ret['mac_address']=num_to_mac(ret['mac_address'])
    ret['firmware_version']=parse_version(ret['firmware_version'])
    ret['hardware_version']=parse_version(ret['hardware_version'])
    return ret


_buffer_tmp=(c_char*_profile_max_len*sizeof(rf627_old_point2D_t))() #buffer for profile

def py_get_profile2D_from_scanner(p,dummy1,dummy2):
    ret=None
    if (p.contents.rf627_profile2D):
        ret={}
        ret['header']=getdict(p.contents.rf627_profile2D.contents.header)
        
        datatype = ret['header']['data_type']
        
        if (datatype == CONST_rf627_old_data_type_t.DTY_PixelsNormal) or (datatype == CONST_rf627_old_data_type_t.DTY_PixelsInterpolated):
            # pixels_format
            c=p.contents.rf627_profile2D.contents.pixels_format.pixels_count
            v=p.contents.rf627_profile2D.contents.pixels_format.pixels
            ret['pixels_count']=c
            memmove(_buffer_tmp, v, c*sizeof(rfUint16)) #copy ctypes object to buffer
            ret['pixels']=(c*rfUint16).from_buffer_copy(_buffer_tmp)
            lib.platform_free(v) #free ctypes object 

        if (datatype == CONST_rf627_old_data_type_t.DTY_ProfileNormal) or (datatype == CONST_rf627_old_data_type_t.DTY_ProfileInterpolated):
            # profile_format
            c=p.contents.rf627_profile2D.contents.profile_format.points_count
            v=p.contents.rf627_profile2D.contents.profile_format.points
            ret['points_count']=c
            memmove(_buffer_tmp, v, c*sizeof(rf627_old_point2D_t))
            ret['points']=(c*rf627_old_point2D_t).from_buffer_copy(_buffer_tmp)
            lib.platform_free(v)#free ctypes object 

        if (p.contents.rf627_profile2D.contents.intensity_count>0):
            #intensity
            c=p.contents.rf627_profile2D.contents.intensity_count
            v=p.contents.rf627_profile2D.contents.intensity
            ret['intensity_count']=c
            memmove(_buffer_tmp, v, c*sizeof(rfUint8)) 
            ret['intensity']=(c*rfUint8).from_buffer_copy(_buffer_tmp)
            lib.platform_free(v)#free ctypes object 

        lib.platform_free(p.contents.rf627_profile2D)#free ctypes object 
        lib.platform_free(p)#free ctypes object 
    
    return ret


def get_base_by_type(p, type):
    struct_type=None
    base=None
    arr_el_type=None
 
    #   "unkn_t",
    # "uint32_t",
    if (type==CONST_pvtKey[CONST_paramValueType_t.PVT_UINT]):
        struct_type=struct_value_uint32_t
        base=p.contents.val_uint32

    # "uint64_t",
    elif  (type==CONST_pvtKey[CONST_paramValueType_t.PVT_UINT64]):
        struct_type=struct_value_uint64_t
        base=p.contents.val_uint64
    # "int32_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_INT]):
        struct_type=struct_value_int32_t
        base=p.contents.val_int32
    # "int64_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_INT64]):
        struct_type=struct_value_int64_t
        base=p.contents.val_int64
    # "float_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_FLOAT]):
        struct_type=struct_value_flt_t
        base=p.contents.val_flt
    # "double_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_FLOAT]):
        struct_type=struct_value_flt_t
        base=p.contents.val_flt
    # "u32_arr_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_UINT32]):
        struct_type=struct_array_uint32_t
        base=p.contents.arr_uint32
        arr_el_type=c_uint32
    # "u64_arr_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_UINT64]):
        struct_type=struct_array_uint64_t
        base=p.contents.arr_uint64
        arr_el_type=c_uint64
    # "i32_arr_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_INT32]):
        struct_type=struct_array_int32_t
        base=p.contents.arr_int32
        arr_el_type=c_int32
    # "i64_arr_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_INT64]):
        struct_type=struct_array_int64_t
        base=p.contents.arr_int64
        arr_el_type=c_int64
    # "flt_array_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_FLT]):
        struct_type=struct_array_flt_t
        base=p.contents.arr_flt
        arr_el_type=c_float
    # "dbl_array_t",
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_DBL]):
        struct_type=struct_array_dbl_t
        base=p.contents.arr_dbl
        arr_el_type=c_double
    # "string_t"
    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_STRING]):
         struct_type=struct_value_str_t
         base=p.contents.val_str 

    if struct_type:
        return struct_type, base, arr_el_type
    else:
        return None

def struct_to_str(p):
    pass

def parse_py_get_parameter(p):
    if p:
        ret=getdict(p.contents.base)
        struct_type, base,arr_el_type=get_base_by_type(p, ret['type'])
        if struct_type:
            base=base.contents
            ret.update(getdict(base))   #the rest of rest keys-values
            ret['ctypes']= (c_char *  sizeof(parameter_t) )()
            memmove(ret['ctypes'], p, sizeof(parameter_t)) #copy ctypes object 
            ret['ctypes']=cast(ret['ctypes'], POINTER(parameter_t))
            
            #parse value
            if ('_arr_' in ret['type']): #arrays
                val= ret['value']
                val= cast(val, POINTER(ret['count']*arr_el_type)).contents 
                ret['value']=[val[i] for i in range(len(val))]
            #parse default values of ctypes array
            for key, value in ret.items():
                if ('ctypes.' in str(value)):
                    val= cast(value, POINTER(ret['defCount']*arr_el_type)).contents 
                    ret[key]=[val[i] for i in range(len(val))]
            # enumValues
            if 'enumValues' in ret:
                if ret['enumValues']:
                    c=ret['enumValues'].contents.recCount
                    r=ret['enumValues'].contents.rec
                    #only the first value
                    if c>0:
                        ret['enumValues']=r.key.decode('utf-8')+'='+str(r.value)+', ...'
                    else:
                        ret['enumValues']=None
                else:
                    ret['enumValues']=None
            
            return ret

    return None

def set_parameter_value(p):
    # p['value'] is a new value
    type=p['type']
    struct_type, base,arr_el_type=get_base_by_type(cast(p['ctypes'], POINTER(parameter_t))  , type)
 
    if struct_type:
        if ('string' in type): #string
            base.contents.value=p['value'].encode('utf-8')
            p['size']=len(p['value'])+1
            p['ctypes'].contents.base.size=p['size']
        elif ('arr_' in type): #arrays
            base.contents.value = (arr_el_type* len(p['value']) )(*p['value'])
            p['size']=sizeof(arr_el_type) * len(p['value'])
            p['ctypes'].contents.base.size=p['size']
        else:
            base.contents.value=p['value']
        return p
    else:
        return None

########################################################
lib.get_profile2D_from_scanner.errcheck = py_get_profile2D_from_scanner


