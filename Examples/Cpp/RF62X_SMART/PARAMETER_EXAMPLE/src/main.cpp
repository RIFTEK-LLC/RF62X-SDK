#include <iostream>
#include <string>
#include <vector>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#       Parameter Example v2.x.x        #"  << std::endl;
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
    std::cout << "Was found\t: " << list.size()<< " RF627-Smart" << std::endl;
    std::cout << "========================================="     << std::endl;


    // Iterate over all discovered scanners in network, connect to each of them,
    // get parameters and set new values.
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
        if (!is_connected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
        }

        // read params from RF627 device by Service Protocol.
        bool is_read = scanner->read_params();
        if (!is_read){
            std::cout << "Failed to read scanner parameters!" << std::endl;
            continue;
        }


        //
        // Example of working with the parameter type:
        // std::string
        //
        // Get parameter of Device Name
        auto name = scanner->get_param("user_general_deviceName");
        if (name != nullptr)
        {
            std::string str_name = name->getValue<std::string>();
            std::cout << "Current Device Name \t: " << str_name << std::endl;

            // Add "_TEST" to the ending of the current name
            str_name += "_TEST";
            scanner->set_param("user_general_deviceName", str_name);
            std::cout << "New Device Name \t: " << str_name     << std::endl;
            std::cout << "-------------------------------------"<< std::endl;
        }

        //
        // Example of working with the parameter type:
        // uint32_t
        //
        // Get parameter of Sensor Framerate
        auto fps = scanner->get_param("user_sensor_framerate");
        if (fps != nullptr)
        {
            uint32_t value = fps->getValue<uint32_t>();
            std::cout<<"Current FPS\t\t: "<< value << std::endl;

            // Change the framerate to 100
            scanner->set_param("user_sensor_framerate", 100);
            std::cout<<"New FPS  \t\t: " << 100 << std::endl;
            std::cout << "-------------------------------------"<< std::endl;
        }

        //
        // Example of working with the parameter type:
        // std::vector<uint32_t>
        //
        // Get parameter of Device IP Addr
        auto ip_addr = scanner->get_param("user_network_ip");
        if (ip_addr != nullptr)
        {
            std::vector<uint32_t> ip =ip_addr->getValue<std::vector<uint32_t>>();
            std::cout << "Current Device IP\t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<< "\n";

            // Change last digit of IP address (e.g. 192.168.1.30->192.168.1.31)
            //ip[3]++;
            scanner->set_param("user_network_ip", ip);
            std::cout << "New Device IP    \t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<< "\n";
            std::cout << "-------------------------------------"       << "\n";
        }

        //
        // Example of working with using an Enum:
        // uint32_t
        //
        // Get parameter of Sync Source
        auto syncSource = scanner->get_param("user_sensor_syncSource");
        if (syncSource != nullptr)
        {
            uint32_t value = syncSource->getValue<uint32_t>();
            auto syncEnum = syncSource->getEnum<uint32_t>();
            std::cout << "Current Sync Source\t: "
                      << syncEnum.findLabel(value)
                      << std::endl;

            // Change the current state to SYNC_EXTERNAL (or SYNC_INTERNAL)
            if(value == syncEnum.getValue("SYNC_INTERNAL"))
            {
                scanner->set_param_by_key(
                             "user_sensor_syncSource", "SYNC_EXTERNAL");
                std::cout << "New Sync Source  \t: "
                          << syncEnum.getLabel("SYNC_EXTERNAL")
                          << std::endl;
            }else
            {
                scanner->set_param_by_key(
                             "user_sensor_syncSource", "SYNC_INTERNAL");
                std::cout << "New Sync Source  \t: "
                          << syncEnum.getLabel("SYNC_INTERNAL")
                          << std::endl;
            }
            std::cout << "-------------------------------------"<< std::endl;
        }

        //
        // Example of working with using an Enum:
        // uint32_t
        //
        // Get parameter of Laser Enabled
        std::shared_ptr<param> laser = scanner->get_param("user_laser_enabled");
        if (laser != nullptr)
        {
            uint32_t isEnabled = laser->getValue<uint32_t>();
            auto laserEnum = laser->getEnum<uint32_t>();
            std::cout << "Current Laser State\t: "
                      << laserEnum.findLabel(isEnabled)
                      << std::endl;


            // Change the current state to the opposite
            if(isEnabled == laser->getEnum<uint32_t>().getValue("FALSE"))
            {
                scanner->set_param_by_key("user_laser_enabled", "TRUE");
                std::cout << "New Laser State  \t: "
                          << laserEnum.getLabel("TRUE")
                          << std::endl;
            }else
            {
                scanner->set_param_by_key("user_laser_enabled", "FALSE");
                std::cout << "New Laser State  \t: "
                          << laserEnum.getLabel("FALSE")
                          << std::endl;
            }
            std::cout << "-------------------------------------"<< std::endl;
        }


        // Apply changed parameters to the device
        std::string answer = "n";
        std::cout << "Apply changed params to the device? (y/n): ";
        std::cin >> answer;
        if (answer == "y" || answer == "Y")
        {
            scanner->write_params();
            // Save changes to the device's memory
            std::cout<<std::endl<<"Save changes to device's memory? (y/n): ";
            std::cin >> answer;
            if (answer == "y" || answer == "Y")
                scanner->save_params();
        }

        // Disconnect from scanner.
        scanner->disconnect();
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























