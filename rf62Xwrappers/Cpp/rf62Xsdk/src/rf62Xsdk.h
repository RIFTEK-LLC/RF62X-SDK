#pragma once

#include"rf62Xtypes.h"

#include <vector>
#include <memory>
#include <iostream>

#if (defined _WIN32 && defined RF627_LIBRARY)
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif

namespace SDK {
namespace SCANNERS {
namespace RF62X {

/**
 * @brief sdk_version - Return info about SDK version
 * @return SDK version
 */
API_EXPORT std::string sdk_version();

/**
 * @brief sdk_init - Initialize sdk library
 * Must be called once before further calls to any library functions
 * @return true if success.
 */
API_EXPORT bool sdk_init();

/**
 * @brief sdk_cleanup - Cleanup resources allocated with sdk_init() function
 */
API_EXPORT void sdk_cleanup();

/**
 * @brief rf627old - This class is the main interface
 * for working with RF627-old series scanners.
 */
class API_EXPORT rf627old
{

public:
    class hello_info
    {
    public:
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
            ~version();
        private:
            uint32_t _value;
        };
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

        hello_info(void* base_hello, PROTOCOLS protocol);
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

public:
    /**
     * @brief search - Search for RF627old devices over network
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return vector of rf627old devices
     */
    static std::vector<rf627old*> search(PROTOCOLS protocol);

    /**
     * @brief get_info - Get information about scanner from hello packet
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return hello_info on success
     */
    hello_info get_info(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief connect - Establish connection to the RF627old device
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool connect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief check_connection - Сheck the connection with the RF627old device
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool check_connection(PROTOCOLS protocol = PROTOCOLS::CURRENT);


    /**
     * @brief disconnect_from_scanner - Close connection to the device
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool disconnect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_profile2D  - Get 2D measurement from scanner's data stream
     * @param zero_points - include zero points in return profile2D
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return ptr to profile2D_t structure if success, else - null
     */
    std::shared_ptr<profile2D> get_profile2D(
            bool zero_points = true,
            PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_profile3D - Get 3D measurement from scanner's data stream
     * where y is calculated based on the next equation: y = k * x + b
     * where b - y-intercept of the line, calculates by the next equation: b = step_size * count_value
     * @param step_size - step size in real units (mm, sm, etc.)
     * @param k - slope or gradient of the line , where
     * @param count_type - type of counter (STEP, MEASURE, PACKET)
     * @param zero_points - include zero points in return profile2D
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return ptr to profile3D_t structure if success, else - null
     */
    profile3D_t* get_profile3D(
            float step_size, float k = 0,
            COUNT_TYPES count_type = COUNT_TYPES::MEASURE,
            bool zero_points = true,
            PROTOCOLS protocol = PROTOCOLS::CURRENT);

    char* get_frame(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief read_params - Read parameters from device to internal structure.
     * This structure is accessible via get_params() function
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool read_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief write_params - Write current parameters to device's memory
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool write_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_param - Search parameters by his name
     * @param param_name - name of parameter
     * @return param on success, else - null
     */
    std::shared_ptr<param> get_param(std::string param_name);

    /**
     * @brief get_param - Search parameters by his name's key
     * @param param_name - name's key of parameter
     * @return param on success, else - null
     */
    std::shared_ptr<param> get_param(PARAM_NAME_KEY param_key);
    /**
     * @brief set_param - set parameter
     * @param param - prt to parameter
     * @return true on success, else - false
     */
    bool set_param(std::shared_ptr<param>& param);
    bool set_param(const char* param_name, int arg_count, ...);
    bool set_param(int param_id, int arg_count, ...);

    bool send_cmd(const char* command_name, int arg_count, ...);

    bool send_cmd(const char* command_name,
                  std::vector<uint8_t>* input, std::vector<uint8_t>* output);

    rf627old(void* scanner_base);
    ~rf627old();

private:
    void* scanner_base = NULL;
    bool is_connected;
    PROTOCOLS current_protocol;
};

/**
 * @brief rf627smart - This class is the main interface
 * for working with RF627-smart series scanners.
 */
class API_EXPORT rf627smart
{

public:
    class hello_info
    {
    public:
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

        hello_info(void* base_hello, PROTOCOLS protocol);
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

public:
    /**
     * @brief search - Search for RF627smart devices over network
     * @param timeout - search timeout
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return vector of rf627smart devices
     */
    static std::vector<std::shared_ptr<rf627smart>> search(
            uint32_t timeout = 1000, PROTOCOLS protocol = PROTOCOLS::SERVICE);

    /**
     * @brief get_info - Get information about scanner from hello packet
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return hello_info on success
     */
    hello_info get_info(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief connect - Establish connection to the RF627old device
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool connect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief check_connection - Сheck the connection with the RF627smart device
     * @param timeout - connection check timeout
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool check_connection(
            uint32_t timeout = 3000, PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief disconnect_from_scanner - Close connection to the device
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool disconnect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_profile2D  - Get 2D measurement from scanner's data stream
     * @param zero_points - include zero points in return profile2D
     * @param realtime - getting a profile in real time (buffering is disabled)
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return ptr to profile2D_t structure if success, else - null
     */
    std::shared_ptr<profile2D> get_profile2D(
            bool zero_points = true, bool realtime = true,
            PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_profile3D - Get 3D measurement from scanner's data stream
     * where y is calculated based on the next equation: y = k * x + b
     * where b - y-intercept of the line, calculates by the next equation:
     * b = step_size * count_value
     * @param step_size - step size in real units (mm, sm, etc.)
     * @param k - slope or gradient of the line , where
     * @param count_type - type of counter (STEP, MEASURE, PACKET)
     * @param zero_points - include zero points in return profile2D
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return ptr to profile3D_t structure if success, else - null
     */
    profile3D_t* get_profile3D(
            float step_size, float k = 0,
            COUNT_TYPES count_type = COUNT_TYPES::MEASURE,
            bool zero_points = true,
            PROTOCOLS protocol = PROTOCOLS::CURRENT);

    std::shared_ptr<frame> get_frame(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief read_params - Read parameters from device to internal structure.
     * This structure is accessible via get_params() function
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool read_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief write_params - Write current parameters to device's memory
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool write_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_param - Search parameters by his name
     * @param param_name - name of parameter
     * @return param on success, else - null
     */
    std::shared_ptr<param> get_param(std::string param_name);

    /**
     * @brief get_param - Search parameters by his name's key
     * @param param_name - name's key of parameter
     * @return param on success, else - null
     */
    std::shared_ptr<param> get_param(PARAM_NAME_KEY param_key);

    /**
     * @brief set_param - set parameter
     * @param param - prt to parameter
     * @return true on success, else - false
     */
    bool set_param(std::shared_ptr<param>& param);
    bool set_param(const char* param_name, int arg_count, ...);
    bool set_param(int param_id, int arg_count, ...);

    bool send_cmd(const char* command_name, int arg_count, ...);

    bool send_cmd(const char* command_name,
                  std::vector<uint8_t>* input, std::vector<uint8_t>* output);


    bool get_authorization_token(
            std::string& token, PROTOCOLS protocol = PROTOCOLS::CURRENT);
    bool set_authorization_key(
            std::string key, PROTOCOLS protocol = PROTOCOLS::CURRENT);


    rf627smart(void* scanner_base);
    ~rf627smart();

private:
    void* scanner_base = NULL;
    bool is_connected;
    PROTOCOLS current_protocol;
};


}
}
}


