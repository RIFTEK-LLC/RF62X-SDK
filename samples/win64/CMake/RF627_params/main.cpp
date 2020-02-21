#include "rf627sdk.h"
#include "rf627types.h"
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF627;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf627 sdk version
    std::cout << sdk_version() << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE_PROTOKOL);


    //Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered " << list.size() << " rf627-old" << std::endl;

    /*
        * Iterate over all discovered rf627-old in network, connect to each of
        * them and get a profile.
        */
       for(size_t i = 0; i < list.size(); i++)
       {
           // Establish connection to the RF627 device by Service Protocol.
           list[i]->connect();

           // read params from RF627 device by Service Protocol.
           list[i]->read_params();
           param_t* a = NULL;

           for(size_t j = 0; j < sizeof(parameter_names)/sizeof(parameter_names[0]); j++)
           {
               // Get parameter by it's name from last read
               a = list[i]->get_param(parameter_names[j]);
               std::cout << parameter_names[j] << " ";
               if(a != nullptr)
               {
                   if (a->type == pvtKey[PVT_STRING])
                       std::cout << a->get_value<value_str_t>() << std::endl;
                   else
                       if (a->type == pvtKey[PVT_INT])
                           std::cout << a->get_value<value_int32_t>() << std::endl;
                       else
                           if (a->type == pvtKey[PVT_INT64])
                               std::cout << a->get_value<value_int64_t>() << std::endl;
                           else
                               if (a->type == pvtKey[PVT_UINT])
                                   std::cout << a->get_value<value_uint32_t>() << std::endl;
                               else
                                   if (a->type == pvtKey[PVT_UINT64])
                                       std::cout << a->get_value<value_uint64_t>() << std::endl;
                                   else
                                       if (a->type == pvtKey[PVT_FLOAT])
                                           std::cout << a->get_value<value_flt_t>() << std::endl;
                                       else
                                           if (a->type == pvtKey[PVT_DOUBLE])
                                               std::cout << a->get_value<value_dbl_t>() << std::endl;
               }else
               {
                   std::cout << "null" << std::endl;
               }
           }
       }

}


























