#pragma once

#include"rf627types.h"

#include <vector>
#include <memory>

#if (defined _WIN32 && defined RF627_LIBRARY)
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif

namespace SDK {
namespace RF_SCANNERS {

/**
 * @brief sdk_version - Return info about SDK version
 * @return SDK version
 */
API_EXPORT int sdk_version();

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

class rf627old;
typedef std::vector<rf627old*> rf627_list;

class API_EXPORT rf627old
{

public:
    /**
     * @brief search - Search for RF627old devices over network
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return vector of rf627old devices
     */
    static rf627_list search(PROTOCOLS protocol);

    /**
     * @brief connect - Establish connection to the RF627old device
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool connect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief disconnect_from_scanner - Close connection to the device
     * @param device - prt to scanner
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return true on success
     */
    bool disconnect(PROTOCOLS protocol = PROTOCOLS::CURRENT);

    /**
     * @brief get_profile - Get measurement from scanner's data stream
     * @param device - ptr to scanner
     * @param protocol - protocol's type (Service Protocol, ENIP, Modbus-TCP)
     * @return ptr to rf627_profile_t structure
     */
    profile_t* get_profile(PROTOCOLS protocol = PROTOCOLS::CURRENT);



    rf627old(void* scanner_base);
    ~rf627old();

private:
    void* scanner_base = NULL;
    PROTOCOLS current_protocol;

};

}
}

