#include <string>
#include <iostream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#         Profile Example v2.x.x        #"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#########################################\n"<< std::endl;

    // Initialize sdk library
    sdk_init();

    // Print return rf62X sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<std::shared_ptr<rf627smart>> list;
    // Search for rf627smart devices over network
    list = rf627smart::search();

    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Was found\t: " << list.size()<< " RF627 v2.x.x"<< std::endl;
    std::cout << "========================================="     << std::endl;


    // Iterate over all discovered scanners in network, connect to each of them,
    // get a profile and print the main profile-info.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<rf627smart> scanner = list[i];
        std::shared_ptr<hello_info> info = scanner->get_info();

        // Print information about the scanner to which the profile belongs.
        std::cout << "\n\nID scanner's list: " << i              << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Device information: "                      << std::endl;
        std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
        std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
        std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        bool is_connected = scanner->connect();
        if (!is_connected)
            continue;

        // Get profile from scanner's data stream by Service Protocol.
        std::shared_ptr<profile2D> profile = nullptr;
        bool zero_points = true;
        bool realtime = true;

        if ((profile=scanner->get_profile2D(zero_points,realtime)))
        {
            std::cout << "Profile information: "                     <<std::endl;
            switch ((PROFILE_DATA_TYPES)profile->getHeader().data_type)
            {
            case PROFILE_DATA_TYPES::PIXELS:
                std::cout<<"* DataType\t: "<<"PIXELS"                <<std::endl;
                std::cout<<"* Count\t: "<<profile->getPixels().size()<<std::endl;
                break;
            case PROFILE_DATA_TYPES::PIXELS_INTRP:
                std::cout<<"* DataType\t: "<<"PIXELS_INTRP"          <<std::endl;
                std::cout<<"* Count\t: "<<profile->getPixels().size()<<std::endl;
                break;
            case PROFILE_DATA_TYPES::PROFILE:
                std::cout<<"* DataType\t: "<<"PROFILE"               <<std::endl;
                std::cout<<"* Size\t: "<<profile->getPoints().size() <<std::endl;
                break;
            case PROFILE_DATA_TYPES::PROFILE_INTRP:
                std::cout<<"* DataType\t: "<<"PROFILE_INTRP"         <<std::endl;
                std::cout<<"* Size\t: "<<profile->getPoints().size() <<std::endl;
                break;
            }
            std::cout << "Profile was successfully received!"        <<std::endl;
            std::cout << "-----------------------------------------" <<std::endl;
        }else
        {
            std::cout << "Profile was not received!"                 <<std::endl;
            std::cout << "-----------------------------------------" <<std::endl;
        }

        // Disconnect from scanner.
        scanner->disconnect();
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























