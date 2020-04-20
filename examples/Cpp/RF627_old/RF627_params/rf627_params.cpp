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
        if (ip_addr->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
        {
            std::cout << ip_addr->get_value<value_uint32>();

            // The first way to set a new parameter and
            // write the changes to the scanner
            int param_id = (int)PARAM_NAME_KEY::USER_NETWORK_IP;
            scanners[i]->set_param(param_id, inet_addr("192.168.1.31"));
            scanners[i]->write_params();
        }

        // Get parameter by it's name from last read
        param_t* name = scanners[i]->get_param(PARAM_NAME_KEY::USER_GENERAL_DEVICENAME);
        if (name->type == param_value_types[(int)PARAM_VALUE_TYPE::STRING_PARAM_TYPE])
        {
            std::cout << name->get_value<value_str>() << std::endl;

            // The second way to set a new parameter and
            // write the changes to the scanner
            name->set_value<value_str>("RF627");
            scanners[i]->set_param(name);
            scanners[i]->write_params();
        }

    }

    system("pause");

}


























