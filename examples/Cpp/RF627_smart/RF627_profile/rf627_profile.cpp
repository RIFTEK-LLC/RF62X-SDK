#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <string>
#include <iostream>

using namespace SDK::SCANNERS::RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf62X sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<std::shared_ptr<rf627smart>> list;
    // Search for rf627smart devices over network
    list = rf627smart::search(500);


    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Discovered: " << list.size() << " rf627-smart"   << std::endl;


    while (true) {


        // Iterate over all discovered rf627-old in network, connect to each of
        // them and get a profile.
        for (size_t i = 0; i < list.size(); i++)
        {
            rf627smart::hello_info info = list[i]->get_info();

            // Print information about the scanner to which the profile belongs.
            std::cout << "\n\n\nID scanner's list: " << i            << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << "Device information: "                      << std::endl;
            std::cout << "* Name\t: "     << info.device_name()      << std::endl;
            std::cout << "* Serial\t: "   << info.serial_number()    << std::endl;
            std::cout << "* IP Addr\t: "  << info.ip_address()       << std::endl;

            // Establish connection to the RF627 device by Service Protocol.
            bool is_connect = list[i]->connect();

            // Get profile from scanner's data stream by Service Protocol.
            std::shared_ptr<profile2D> profile = nullptr;
            if (is_connect && ((profile = list[i]->get_profile2D(true, true)) != nullptr))
            {
                std::cout << "Profile information: "                    << std::endl;
                switch (profile->getHeader().data_type) {
                case (int)PROFILE_DATA_TYPE::PIXELS:
                    std::cout << "* DataType\t: "<< "PIXELS"            << std::endl;
                    std::cout << "* Count\t: " << profile->getPixels().size()<< std::endl;
                    break;
                case (int)PROFILE_DATA_TYPE::PIXELS_INTRP:
                    std::cout << "* DataType\t: "<< "PIXELS_INTRP"      << std::endl;
                    std::cout << "* Count\t: " << profile->getPixels().size()<< std::endl;
                    break;
                case (int)PROFILE_DATA_TYPE::PROFILE:
                    std::cout << "* DataType\t: "<< "PROFILE"           << std::endl;
                    std::cout << "* Size\t: "  << profile->getPixels().size()<< std::endl;
                    break;
                case (int)PROFILE_DATA_TYPE::PROFILE_INTRP:
                    std::cout << "* DataType\t: "<< "PROFILE_INTRP"     << std::endl;
                    std::cout << "* Size\t: "  << profile->getPixels().size()<< std::endl;
                    break;
                }
                std::cout << "Profile was successfully received!"       << std::endl;
                std::cout << "-----------------------------------------"<< std::endl;
            }else
            {
                std::cout << "Profile was not received!"                << std::endl;
                std::cout << "-----------------------------------------"<< std::endl;
            }

            // Disconnect from scanner.
            list[i]->disconnect();
        }

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























