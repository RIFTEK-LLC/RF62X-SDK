#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <mutex>

#include "rf62Xtypes.h"

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
 * @details Must be called once before further calls to any library functions
 * @return true if success.
 */
API_EXPORT bool sdk_init();

/**
 * @brief sdk_cleanup - Cleanup resources allocated with sdk_init() function
 */
API_EXPORT void sdk_cleanup();


/**
 * @brief rf627smart - This class is the main interface
 * for working with RF627-smart series scanners.
 */
class API_EXPORT rf627smart
{

public:
    /**
     * @brief search - Search for RF627smart devices over network
     * @param timeout Search timeout for each Ethernet interface
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return vector of rf627smart devices
     */
    static std::vector<std::shared_ptr<rf627smart>> search(
            uint32_t timeout = 1000, PROTOCOLS protocol = PROTOCOLS::SERVICE);
    /**
     * @brief get_info - Get information about scanner from hello packet
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return hello_info on success, else - null
     */
    std::shared_ptr<hello_info> get_info(PROTOCOLS protocol = PROTOCOLS::CURRENT);



    /**
     * @brief connect - Establish connection to the RF627old device
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool connect(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief disconnect_from_scanner - Close connection to the device
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool disconnect(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief check_connection - Сheck the connection with the RF627smart device
     * @param timeout Connection check timeout
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool check_connection(
            uint32_t timeout = 3000, PROTOCOLS protocol = PROTOCOLS::CURRENT);



    /**
     * @brief get_profile2D - Get 2D measurement from scanner's data stream
     * @param zero_points Enable zero points in return profile2D
     * @param realtime Enable getting profile in real time (buffering is disabled)
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return profile2D if success, else - null
     */
    std::shared_ptr<profile2D> get_profile2D(
            bool zero_points = true, bool realtime = true,
            PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief get_frame - Get RAW frame from scanner
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return frame if success, else - null
     */
    std::shared_ptr<frame> get_frame(PROTOCOLS protocol = PROTOCOLS::CURRENT);



    /**
     * @brief read_params - Read parameters from device to internal SDK memory
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool read_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief write_params - Send current parameters to device
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool write_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief save_params - Save changes to device's memory
     * @details The saved parameters will also be used if the device
     * is restarted or even if the firmware is updated.
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool save_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief load_recovery_params - Loading parameters from recovery area
     * @details The device will automatically reboot.
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool load_recovery_params(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_param - Get parameter by his name
     * Before using read_params() method should be called
     * @param param_name Name of parameter
     * @return param on success, else - null
     */
    std::shared_ptr<param> get_param(std::string param_name);
    std::shared_ptr<param> get_param(PARAM_NAME_KEY param_key);
    /**
     * @brief set_param - Set parameter
     * @param param Parameter to set
     * @return true on success, else - false
     */
    bool set_param(std::shared_ptr<param> param);



    /**
     * @brief start_dump_recording - enabling profile recording to the internal
     * memory of the device - generating a dump.
     * @details Recording will stop when the number of recorded profiles exceeds
     * the maximum allowed dump size, or when the count_of_profiles number is
     * exceeded, or when the stop_dump_recording method is called
     * @param count_of_profiles The number of profiles to record the dump:
     *      count_of_profiles == 0 - Recording will continue until the maximum
     * dump size is reached, or until recording is stopped by calling
     * the stop_dump_recording method;
     *      count_of_profiles > 0  - Recording will continue until the number
     * of recorded profiles exceeds the specified number.
     * @return true if recording started successfully, else - false
     */
    bool start_dump_recording(uint32_t count_of_profiles = 0);

    /**
     * @brief stop_dump_recording - disabling profile recording to the internal
     * memory of the device.
     * @param count_of_profiles The number of recorded profiles
     * @return true if recording was stopped successfully, else - false
     */
    bool stop_dump_recording(uint32_t& count_of_profiles);

    /**
     * @brief get_dumps_profiles - getting the content of the profile dump
     * @param index Start number of the requested profile from memory
     * @param count The count of requested profiles
     * @param proto Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return Vector profiles
     */
    std::vector<std::shared_ptr<profile2D>> get_dumps_profiles(
            uint32_t index,uint32_t count,PROTOCOLS proto = PROTOCOLS::CURRENT);



    /**
     * @brief start_profile_capturing - Command to start profiles measuring.
     * @details This command is used only in the "software measurement" mode:
     * when parameter "user_sensor_syncSource" == "SYNC_SOFTWARE"
     * or "SYNC_SOFTWARE_EXT". Device starts a measurement cycle immediately
     * after receiving this command.
     * ! In "software measurement" mode the get_profile2D method must be used
     * with the realtime == false argument to avoid loss of requested profiles.
     * @param count_of_profiles The count of measurements
     * @return true if measuring was started successfully, else - false
     */
    bool start_profile_capturing(uint32_t count_of_profiles = 0);



    /**
     * @brief get_authorization_token - Get authorization token from scanner
     * @param[out] token Return value.
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool get_authorization_token(
            std::string& token, PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief set_authorization_key - Set authorization key to scanner
     * @param key Authorization key.
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool set_authorization_key(
            std::string key, PROTOCOLS protocol = PROTOCOLS::CURRENT);



    /**
     * @brief read_calibration_table - Read calibration table from scanner
     * @return true on success, else - false
     */
    bool read_calibration_table(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief write_calibration_table - Write calibration table to scanner
     * @return true on success, else - false
     */
    bool write_calibration_table(PROTOCOLS protocol = PROTOCOLS::CURRENT);
    /**
     * @brief save_calibration_table - Save calibration table to device's memory
     * @return true on success, else - false
     */
    bool save_calibration_table(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_calibration_table - Get calibration table from internal SDK memory
     * Before using read_calibration_table() method should be called
     * @return calib_table on success, else - null
     */
    std::shared_ptr<calib_table> get_calibration_table();
    /**
     * @brief set_calibration_table - Set calibration table to internal SDK memory
     * @return true on success, else - false
     */
    bool set_calibration_table(std::shared_ptr<calib_table> table);


    /**
     * @brief reboot_device - The scanner will restart
     * @param protocol Protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success, else - false
     */
    bool reboot_device(PROTOCOLS protocol = PROTOCOLS::CURRENT);


    /**
     * @brief rf627smart - Class constructor.
     * @param scanner_base Passing a ptr to a basic scanner (cannot be nullptr)
     */
    rf627smart(void* scanner_base);
    /**
    * @brief ~rf627smart - Class destructor.
    */
    ~rf627smart();

private:
    void* scanner_base = NULL;
    bool is_connected;
    PROTOCOLS current_protocol;
    std::mutex param_mutex;
    std::mutex profile_mutex;
};




/**
 * @brief rf627old - This class is the main interface
 * for working with RF627-old series scanners.
 */
class API_EXPORT rf627old
{
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
    std::shared_ptr<hello_info> get_info(PROTOCOLS protocol = PROTOCOLS::CURRENT);
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
     * @param realtime Enable getting profile in real time (buffering is disabled)
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return ptr to profile2D_t structure if success, else - null
     */
    std::shared_ptr<profile2D> get_profile2D(
            bool zero_points = true, bool realtime = true,
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
     * @param param - parameter
     * @return true on success, else - false
     */
    bool set_param(std::shared_ptr<param> param);

    /**
     * @brief send_cmd - Send command to parameter
     * @param command_name Name of command
     * @param[in] input Data to send in command payload
     * @param[out] output Data to receive from command payload
     * @return true on success, else - false
     */
    bool send_cmd(std::string command_name,
                  std::vector<uint8_t> input, std::vector<uint8_t>& output);

    rf627old(void* scanner_base);
    ~rf627old();

private:
    void* scanner_base = NULL;
    bool is_connected;
    PROTOCOLS current_protocol;
    std::mutex param_mutex;
    std::mutex profile_mutex;
};



}
}
}


