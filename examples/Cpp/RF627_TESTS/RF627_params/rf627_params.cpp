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

        // Get parameter by it's name from last read
        param_t* param = scanners[i]->get_param(USER_GENERAL_DEVICENAME);
        if (param->type == param_value_types[STRING_PARAM_TYPE])
        {
            std::cout << param->get_value<value_str>() << std::endl;

            // set new scanner's name and write changed parameters to scanner
            param->set_value<value_str>("Test Name");
            scanners[i]->set_param(param);
            scanners[i]->write_params();
        }

        // Check that the parameter is set correctly
        // Read again all params from RF627 device by Service Protocol.
        scanners[i]->read_params();

        // Get device name
        param = scanners[i]->get_param(USER_GENERAL_DEVICENAME);
        if (param->get_value<value_str>() == "Test Name")
            std::cout << "Changed parameters write successfully" << std::endl;
        else std::cout << "Error changing parameters" << std::endl;


//           for(size_t j = 0; j < parameter_names->size(); j++)
//           {
//               // Get parameter by it's name from last read
//               a = list[i]->get_param(parameter_names[j]);
//               if (a->type == pvtKey[PVT_STRING])
//               {
//                   std::cout << a->get_value<value_str_t>() << std::endl;
//               a->set_value<value_str_t>("test");
//               list[i]->set_param(a);
//               a = list[i]->get_param(parameter_names[j]);
//               list[i]->write_params();
//               }


//               std::cout << parameter_names[j] << " ";
//               if(a != nullptr)
//               {
//                   if (a->type == pvtKey[PVT_STRING])
//                       std::cout << a->get_value<value_str_t>() << std::endl;
//                   else
//                       if (a->type == pvtKey[PVT_INT])
//                           std::cout << a->get_value<value_int32_t>() << std::endl;
//                       else
//                           if (a->type == pvtKey[PVT_INT64])
//                               std::cout << a->get_value<value_int64_t>() << std::endl;
//                           else
//                               if (a->type == pvtKey[PVT_UINT])
//                                   std::cout << a->get_value<value_uint32_t>() << std::endl;
//                               else
//                                   if (a->type == pvtKey[PVT_UINT64])
//                                       std::cout << a->get_value<value_uint64_t>() << std::endl;
//                                   else
//                                       if (a->type == pvtKey[PVT_FLOAT])
//                                           std::cout << a->get_value<value_flt_t>() << std::endl;
//                                       else
//                                           if (a->type == pvtKey[PVT_DOUBLE])
//                                               std::cout << a->get_value<value_dbl_t>() << std::endl;
//               }else
//               {
//                   std::cout << "null" << std::endl;
//               }
//           }
       }

}


























