#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

using namespace SDK;
using namespace SCANNERS;
using namespace RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf62X SDK version
    std::cout << "SDK version: " << sdk_version() << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> scanners;
    // Search for RF627old devices over network
    scanners = rf627old::search(PROTOCOLS::SERVICE);


    // Iterate over all discovered rf627-old in network, connect to each of
    // them and read/set parameters.
    for(size_t i = 0; i < scanners.size(); i++)
    {
        // Establish connection to the RF627 device by Service Protocol.
        scanners[i]->connect();

        // read params from RF627 device by Service Protocol.
        scanners[i]->read_params();

        // Get parameter by it's name from last read
        param_t* ip_addr = scanners[i]->get_param(PARAM_NAME_KEY::USER_NETWORK_IP);
        if (ip_addr->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE])
        {
            std::vector <uint32_t> ip = ip_addr->get_value<array_uint32>();
            for (auto i: ip)
                std::cout << std::to_string(i) << ".";

            // The first way to set a new parameter
            ip_addr->set_value<array_uint32>(std::vector<uint32_t> {192,168,1,32});
            scanners[i]->set_param(ip_addr);
        }

        // Get parameter by it's name from last read
        param_t* name = scanners[i]->get_param(PARAM_NAME_KEY::USER_GENERAL_DEVICENAME);
        if (name->type == param_value_types[(int)PARAM_VALUE_TYPE::STRING_PARAM_TYPE])
        {
            std::cout << name->get_value<value_str>() << std::endl;

            // The second way to set a new parameter
            name->set_value<value_str>("RF6271");
            scanners[i]->set_param(name);
        }

        // Get parameter by it's name from last read
        param_t* laser_enabled = scanners[i]->get_param(PARAM_NAME_KEY::USER_LASER_ENABLED);
        if (laser_enabled->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
        {
            std::cout << laser_enabled->get_value<value_uint32>() << std::endl;

            // The second way to set a new parameter
            laser_enabled->set_value<value_uint32>(false);
            scanners[i]->set_param(laser_enabled);
        }

        // Get parameter by it's name from last read
        param_t* sync_enabled = scanners[i]->get_param(PARAM_NAME_KEY::USER_TRIGGER_SYNC_SOURCE);
        if (laser_enabled->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
        {
            std::cout << sync_enabled->get_value<value_uint32>() << std::endl;

            // The second way to set a new parameter
            laser_enabled->set_value<value_uint32>(false);
            scanners[i]->set_param(laser_enabled);
        }

        //  Write changes parameters to the device's memory
        scanners[i]->write_params();

    }

    system("pause");

}


























