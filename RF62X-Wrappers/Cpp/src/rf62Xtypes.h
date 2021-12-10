#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <string>

#if (defined _WIN32 && defined RF62X_LIBRARY)
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif

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
    uint32_t getSensorWidth();
    uint32_t getSensorHeight();

    frame(const frame&) = delete;
    frame& operator=(const frame&) = delete;
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
    uint32_t m_SensorWidth;
    uint32_t m_SensorHeight;
};
using frame_ptr = std::shared_ptr<SDK::SCANNERS::RF62X::frame>;

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
    bool updateTimeStamp();

    bool setTimeStamp(int);

    bool save_to_file(std::string file_name);
    bool convert_to_bytes(std::vector<char>& bytes);

    calib_table(const calib_table&) = delete;
    calib_table& operator=(const calib_table&) = delete;

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

    std::string to_string() const;
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
    const uint32_t& product_code();

    hello_info(void* base_hello, SCANNER_TYPES type, PROTOCOLS protocol);
    ~hello_info();

    hello_info(const hello_info&) = delete;
    hello_info& operator=(const hello_info&) = delete;

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
    uint32_t _product_code;
};

/*! Structure to store a profile
 */
class profile2D
{
    explicit profile2D(void* frame_base);
    friend class rf627old;
    friend class rf627smart;
public:
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
        uint32_t    license_hash;

        uint32_t    exposure_time;
        uint32_t    laser_value;
        uint32_t    step_count;
        uint8_t     dir;
        uint16_t    payload_size;
        uint8_t     bytes_per_point;
    }header;

    const header& getHeader() const noexcept;

    const std::vector<point2D_t>& getPoints() const noexcept;
    const std::vector<uint16_t>& getPixels() const noexcept;
    const std::vector<uint8_t>& getIntensity() const noexcept;

    profile2D(const profile2D&) = delete;
    profile2D& operator=(const profile2D&) = delete;
private:
    void* m_ProfileBase;

    std::vector<point2D_t> m_Points;
    std::vector<uint16_t> m_Pixels;
    std::vector<uint8_t> m_Intensity;

    header m_Header;
};
using profile_ptr = std::shared_ptr<SDK::SCANNERS::RF62X::profile2D>;

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

template <typename T>
class ValueEnum
{
public:
    ValueEnum(std::vector <std::tuple<T, std::string, std::string>> enum_base);
    ~ValueEnum();

    T getValue(std::string key) const;
    std::string getLabel(std::string key) const;

    std::string findLabel(T value) const;
    std::string findKey(T value) const;

    std::vector<T> getValueList() const;
    std::vector<std::string> getKeyList() const;
    std::vector<std::string> getLabelList() const;

    std::tuple<T, std::string, std::string> getItem(uint32_t index) const;
    std::vector<std::tuple<T, std::string, std::string>> getItemList() const;

private:
    std::vector <std::tuple<T, std::string, std::string>> _enum_base;
};


class API_EXPORT param
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
    ValueEnum<T> getEnum() const;

    param(const param&) = delete;
    param& operator=(const param&) = delete;
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

