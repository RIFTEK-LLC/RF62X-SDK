#pragma once

#include <vector>
#include <memory>
#include <iostream>

namespace SDK {
namespace SCANNERS {
namespace RF62X {

enum class SCANNER_TYPES {
    RF627_OLD = 1,
    RF627_SMART = 2
};

enum class PROTOCOLS {
    CURRENT = 0,
    SERVICE = 1,
    ETHERNET_IP = 2,
    MODBUS_TCP = 3
};

enum class PROFILE_DATA_TYPES{
    PIXELS				= 0x10,
    PROFILE				= 0x11,
    PIXELS_INTRP		= 0x12,
    PROFILE_INTRP		= 0x13
};

enum class COUNT_TYPES {
    STEP = 1,
    MEASURE = 2,
    PACKET = 3
};


/*! Structure to store a 2D-point of profile
 */
typedef struct
{
    float x;
    float z;
}point2D_t;

/*! Structure to store a 3D-point of profile
 */
typedef struct
{
    float x;
    float y;
    float z;
}point3D_t;

/*! Structure to store a 3D-point of profile
 */
class frame
{
public:
    frame(void* frame_base);
    ~frame();


    std::vector<char> getData();
    uint32_t getDataSize();
    uint8_t getPixelSize();
    uint32_t getFrameWidth();
    uint32_t getFrameHeight();

    bool getRoiActive();
    bool getRoiEnabled();
    uint32_t getRoiPos();
    uint32_t getRoiSize();

private:
    void* m_FrameBase = nullptr;

    char* m_Data;
    uint32_t m_DataSize;
    uint8_t m_PixelSize;
    uint32_t m_FrameWidth;
    uint32_t m_FrameHeight;

    bool m_RoiActive;
    bool m_RoiEnabled;
    uint32_t m_RoiPos;
    uint32_t m_RoiSize;
};

class calib_table
{
public:
    calib_table(void* table_base);
    ~calib_table();

    static std::shared_ptr<calib_table> read_from_file(std::string file_name);
    static std::shared_ptr<calib_table> parse_from_bytes(std::vector<char> bytes);

    uint16_t getType();
    uint16_t getCRC16();
    uint32_t getSerial();
    uint32_t getDataRowLength();
    uint32_t getWidth();
    uint32_t getHeight();
    uint8_t getMultWidth();
    uint8_t getMultHeight();
    int getTimeStamp();

    std::vector<uint8_t> getData();

    bool setData(std::vector<uint8_t> data);
    bool setZ(std::vector<int16_t> Zd);
    bool setX(std::vector<int16_t> Xd);
    bool setZX(std::vector<int16_t> Zd, std::vector<int16_t> Xd);

    bool save_to_file(std::string file_name);
    bool convert_to_bytes(std::vector<char>& bytes);

private:
    void* m_CalibTableBase = nullptr;

    uint16_t m_Type;
    uint16_t m_CRC16;
    uint32_t m_Serial;
    uint32_t m_DataRowLength;
    uint32_t m_Width;
    uint32_t m_Height;
    uint8_t m_MultW;
    uint8_t m_MultH;
    int m_TimeStamp;

    std::vector<uint8_t> m_Data;

    std::vector<int16_t> m_Zd;
    std::vector<int16_t> m_Xd;
};



class version{
public:
    uint8_t major;
    uint8_t minor;
    uint8_t patch;

    std::string to_string();
    uint32_t to_uint();

    friend std::ostream& operator<<(std::ostream& out, const version &v);
    friend bool operator == (const version& v1, const version &v2);
    friend bool operator != (const version& v1, const version &v2);
    friend bool operator <= (const version& v1, const version &v2);
    friend bool operator >= (const version& v1, const version &v2);
    friend bool operator < (const version& v1, const version &v2);
    friend bool operator > (const version& v1, const version &v2);

    version();
    version(uint32_t value);
    version(std::string value);
    version(uint32_t* value);
    ~version();
private:
    uint32_t _value;
};

class hello_info
{
public:
    const std::string& device_name();
    const uint32_t& serial_number();
    const std::string& ip_address();
    const std::string& mac_address();
    const uint16_t& profile_port();
    const uint16_t& service_port();
    const version& firmware_version();
    const version& hardware_version();
    const uint32_t& z_smr();
    const uint32_t& z_mr();
    const uint32_t& x_smr();
    const uint32_t& x_emr();

    hello_info(void* base_hello, SCANNER_TYPES type, PROTOCOLS protocol);
    ~hello_info();

private:
    std::string _device_name;
    uint32_t _serial_number;
    std::string _ip_address;
    std::string _mac_address;
    uint16_t _profile_port;
    uint16_t _service_port;
    version _firmware_version;
    version _hardware_version;
    uint32_t _z_smr;
    uint32_t _z_mr;
    uint32_t _x_smr;
    uint32_t _x_emr;
};

/*! Structure to store a profile
 */
class profile2D
{
public:
    profile2D(void* frame_base);
    ~profile2D();

    typedef struct
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
        uint16_t    payload_size;
        uint8_t     bytes_per_point;
    }header;

    header getHeader();

    const std::vector<point2D_t>& getPoints();
    const std::vector<uint16_t>& getPixels();
    const std::vector<uint8_t>& getIntensity();

private:
    void* m_ProfileBase;

    std::vector<point2D_t> m_Points;
    std::vector<uint16_t> m_Pixels;
    std::vector<uint8_t> m_Intensity;

    header m_Header;
};

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
    }header;


        std::vector<point3D_t> points;
        std::vector<uint16_t> pixels;


    std::vector<uint8_t> intensity;
}profile3D_t;

//Типы значений параметров
enum class PARAM_VALUE_TYPE
{
    UNKN_PARAM_TYPE         = 0,
    UINT_PARAM_TYPE         = 1,
    UINT64_PARAM_TYPE       = 2,
    INT_PARAM_TYPE          = 3,
    INT64_PARAM_TYPE        = 4,
    FLOAT_PARAM_TYPE        = 5,
    DOUBLE_PARAM_TYPE       = 6,
    UINT32_ARRAY_PARAM_TYPE = 7,
    UINT64_ARRAY_PARAM_TYPE = 8,
    INT32_ARRAY_PARAM_TYPE  = 9,
    INT64_ARRAY_PARAM_TYPE  = 10,
    FLT_ARRAY_PARAM_TYPE    = 11,
    DBL_ARRAY_PARAM_TYPE    = 12,
    STRING_PARAM_TYPE       = 13
};

static std::string param_value_types[]	=
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
enum class PARAM_ACCESS_TYPE
{
    PAT_UNKN		= 0,
    PAT_READ_ONLY   = 1,
    PAT_WRITE       = 2,
    PAT_RESTRICTED  = 3
};

enum class PARAM_NAME_KEY {
    FACT_GENERAL_PROTOCOLREV = 0,
    FACT_GENERAL_DEVICETYPE,
    FACT_GENERAL_SERIAL,
    FACT_GENERAL_PCBSERIAL,
    FACT_GENERAL_LIFETIME,
    FACT_GENERAL_WORKTIME,
    FACT_GENERAL_STARTSCOUNT,
    FACT_GENERAL_FIRMWAREREV,
    FACT_GENERAL_HARDWAREREV,
    FACT_GENERAL_FSBLREV,
    FACT_GENERAL_CUSTOMERID,
    FACT_GENERAL_FPGAFREQ,
    FACT_GENERAL_SMR,
    FACT_GENERAL_MR,
    FACT_GENERAL_XSMR,
    FACT_GENERAL_XEMR,
    FACT_GENERAL_PIXDIVIDER,
    FACT_GENERAL_PROFDIVIDER,
    FACT_GENERAL_OEMDEVNAME,
    FACT_GENERAL_AUTHSTATUS,
    FACT_SENSOR_NAME,
    FACT_SENSOR_WIDTH,
    FACT_SENSOR_HEIGHT,
    FACT_SENSOR_PIXFREQ,
    FACT_SENSOR_FRMCONSTPART,
    FACT_SENSOR_FRMPERLINEPART,
    FACT_SENSOR_FPSOREXP,
    FACT_SENSOR_MINEXPOSURE,
    FACT_SENSOR_MAXEXPOSURE,
    FACT_SENSOR_IMGFLIP,
    FACT_NETWORK_MACADDR,
    FACT_NETWORK_FORCEAUTONEGTIME,
    FACT_NETWORK_WEBSOCKSERVICEPORT,
    FACT_NETWORK_WEBSOCKDATAPORT,
    FACT_NETWORK_WEBSOCKMATHPORT,
    FACT_LASER_WAVELENGTH,
    FACT_LASER_KOEFF1,
    FACT_LASER_KOEFF2,
    FACT_LASER_MINVALUE,
    FACT_LASER_MAXVALUE,
    FACT_PROFILES_MAXDUMPSIZE,
    FACT_EIP_IDENTITY_VENDORID,
    FACT_EIP_IDENTITY_DEVICETYPE,
    FACT_EIP_IDENTITY_PRODUCTCODE,
    FACT_EIP_IDENTITY_REV,
    FACT_EIP_TCPINTRF_CAPABILITY,
    FACT_EIP_TCPINTRF_PHY_PATHSIZE,
    FACT_EIP_TCPINTRF_PHY_CLASSID,
    FACT_EIP_TCPINTRF_PHY_INSTNUMBER,
    FACT_EIP_TCPINTRF_PHY_ATTRNUMBER,
    FACT_EIP_INTRFTYPE,
    FACT_EIP_INTRFCAPABILITY_BITS,
    FACT_EIP_INTRFCAPABILITY_SPEEDDUPCOUNT,
    FACT_EIP_INTRFCAPABILITY_SPEEDDUPLEX_SPEED,
    FACT_EIP_INTRFCAPABILITY_SPEEDDUPLEX_DUPLEX,
    FACT_SENSOR_ANALOGGAIN,
    FACT_SENSOR_DIGITALGAIN,
    FACT_SENSOR_BLACKODD,
    FACT_SENSOR_BLACKEVEN,
    FACT_SENSOR_HDRPIECEWISEDIV1,
    FACT_SENSOR_HDRPIECEWISEDIV2,
    FACT_SENSOR_INITREGS,

    USER_GENERAL_DEVICESTATE,
    USER_GENERAL_DEVICENAME,
    USER_GENERAL_SAVELOG,
    USER_SYSMON_FPGATEMP,
    USER_SYSMON_PARAMSCHANGED,
    USER_SYSMON_TEMPSENS00,
    USER_SYSMON_TEMPSENS00MAX,
    USER_SYSMON_TEMPSENS00MIN,
    USER_SYSMON_TEMPSENS01,
    USER_SYSMON_TEMPSENS01MAX,
    USER_SYSMON_TEMPSENS01MIN,
    USER_SYSMON_TEMPSENS10,
    USER_SYSMON_TEMPSENS10MAX,
    USER_SYSMON_TEMPSENS10MIN,
    USER_SYSMON_TEMPSENS11,
    USER_SYSMON_TEMPSENS11MAX,
    USER_SYSMON_TEMPSENS11MIN,
    USER_SENSOR_SYNCSOURCE,
    USER_SENSOR_FRAMERATE,
    USER_SENSOR_MAXFRAMERATE,
    USER_SENSOR_EXPOSURECONTROL,
    USER_SENSOR_EXPOSURE1,
    USER_SENSOR_EXPOSURE2,
    USER_SENSOR_EXPOSURE3,
    USER_SENSOR_EXPOSURE4,
    USER_SENSOR_MAXEXPOSURE,
    USER_ROI_ENABLED,
    USER_ROI_ACTIVE,
    USER_ROI_POSMODE,
    USER_ROI_POS,
    USER_ROI_MAXPOS,
    USER_ROI_REQPROFSIZE,
    USER_NETWORK_SPEED,
    USER_NETWORK_REQUIREDSPEED,
    USER_NETWORK_AUTONEG,
    USER_NETWORK_IP,
    USER_NETWORK_MASK,
    USER_NETWORK_GATEWAY,
    USER_NETWORK_HOSTIP,
    USER_NETWORK_HOSTPORT,
    USER_NETWORK_WEBPORT,
    USER_NETWORK_SERVICEPORT,
    USER_STREAMS_UDPENABLED,
    USER_STREAMS_FORMAT,
    USER_STREAMS_INCLUDEINTENSITY,
    USER_PROCESSING_THRESHOLD,
    USER_PROCESSING_PROFPERSEC,
    USER_PROCESSING_MEDIANMODE,
    USER_PROCESSING_BILATERALMODE,
    USER_PROCESSING_PEAKMODE,
    USER_PROCESSING_FLIP,
    USER_LASER_ENABLED,
    USER_LASER_VALUE,
    USER_TRIGGER_SYNC_SOURCE,
    USER_TRIGGER_SYNC_STRICTENABLED,
    USER_TRIGGER_SYNC_DIVIDER,
    USER_TRIGGER_SYNC_DELAY,
    USER_TRIGGER_COUNTER_TYPE,
    USER_TRIGGER_COUNTER_MAXVALUEENABLED,
    USER_TRIGGER_COUNTER_MAXVALUE,
    USER_TRIGGER_COUNTER_RESETTIMERENABLED,
    USER_TRIGGER_COUNTER_RESETTIMERVALUE,
    USER_TRIGGER_COUNTER_VALUE,
    USER_INPUT1_ENABLED,
    USER_INPUT1_MODE,
    USER_INPUT2_ENABLED,
    USER_INPUT2_MODE,
    USER_INPUT3_ENABLED,
    USER_INPUT3_MODE,
    USER_INPUT1_SAMPLES,
    USER_INPUT2_SAMPLES,
    USER_INPUT3_SAMPLES,
    USER_OUTPUT1_ENABLED,
    USER_OUTPUT1_MODE,
    USER_OUTPUT1_PULSEWIDTH,
    USER_OUTPUT2_ENABLED,
    USER_OUTPUT2_MODE,
    USER_OUTPUT2_PULSEWIDTH,
    USER_DUMP_ENABLED,
    USER_DUMP_CAPACITY,
    USER_DUMP_SIZE,
    USER_DUMP_TIMESTAMP,
    USER_DUMP_VIEW3D_MOTIONTYPE,
    USER_DUMP_VIEW3D_YSOURCE,
    USER_DUMP_VIEW3D_YSTEP,
    USER_DUMP_VIEW3D_PAINTMODE,
    USER_DUMP_VIEW3D_DECIMATION,
    USER_EIP_TCPPORT,
    USER_EIP_UDPPORT,
    USER_EIP_TCP_TTL,
    USER_EIP_TCP_TIMEOUT,
    USER_EIP_TCP_MULTICAST_ALLOC,
    USER_EIP_TCP_MULTICAST_NUM,
    USER_EIP_TCP_MULTICAST_ADDR,
    USER_COMPATIBILITY_RF625ENABLED,
    USER_COMPATIBILITY_RF625TCPPORT,
    USER_SENSOR_DOUBLESPEEDENABLED,
    USER_SENSOR_EDRTYPE,
    USER_SENSOR_EDRCOLUMNDIVIDER,
    USER_STREAMS_POINTSCOUNT,
    USER_ROI_SIZE
};

const static std::string parameter_names[]	=
{
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
};

template <typename T>
class ValueEnum
{
public:
    ValueEnum(std::vector <std::tuple<T, std::string, std::string>> enum_base);
    ~ValueEnum();

    T getValue(std::string key) const;
    T getValue(uint32_t index) const;

    std::string getLabel(std::string key) const;
    std::string getLabel(uint32_t index) const;

    std::string getKey(uint32_t index) const;

    std::vector<T> getValueList() const;
    std::vector<std::string> getKeyList() const;
    std::vector<std::string> getLabelList() const;

    std::tuple<T, std::string, std::string> getItem(uint32_t index) const;
    std::vector<std::tuple<T, std::string, std::string>> getItemList() const;

private:
    std::vector <std::tuple<T, std::string, std::string>> _enum_base;
};


class param
{
public:
    param(void* param_base);
    ~param();

    std::string getName();
    std::string getType();
    std::string getAccess();
    std::string getUnits();

    uint16_t getIndex();
    uint32_t getOffset();
    uint32_t getSize();

    template <typename T>
    T getValue() const;
    template <typename T>
    bool setValue(T) const;
    template <typename T>
    T getMin() const;
    template <typename T>
    T getMax() const;
    template <typename T>
    T getStep() const;

    template <typename T>
    T getDefValue() const;
    template <typename T>
    T getValuesEnum() const;

    template <typename T>
    ValueEnum<T> getEnum() const;
private:
    void* param_base;

};

typedef struct {
    int ID;
    std::vector<param> args;
}cmd_t;



}
}
}

