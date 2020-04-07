#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf627 sdk version
    std::cout << sdk_version() << std::endl;


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
        scanners[i]->read_params();
        scanners[i]->read_params();

        // Get parameter by it's name from last read
        param_t* ip_addr = scanners[i]->get_param(PARAM_NAME_KEY::USER_GENERAL_DEVICENAME);
        if (ip_addr->type == param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
        {
            std::cout << ip_addr->get_value<value_uint32>();
        }


        // Get parameter by it's name from last read
        param_t* name = scanners[i]->get_param(PARAM_NAME_KEY::USER_GENERAL_DEVICENAME);
        if (name->type == param_value_types[(int)PARAM_VALUE_TYPE::STRING_PARAM_TYPE])
        {
            std::cout << name->get_value<value_str>() << std::endl;

            // set new scanner's name and write changed parameters to scanner
            name->set_value<value_str>("Test Name");
            scanners[i]->set_param(name);
            scanners[i]->write_params();
        }

    }

}


























