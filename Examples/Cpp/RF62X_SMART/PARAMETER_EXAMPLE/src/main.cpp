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

        std::cout << "\n\nID scanner's list: " << i                 << std::endl;
        std::cout << "-----------------------------------------"    << std::endl;

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
        std::shared_ptr<param> name = scanner->get_param("user_general_deviceName");
        if (name != nullptr && name->getType() == "string_t")
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
        std::shared_ptr<param> framerate = scanner->get_param("user_sensor_framerate");
        if (framerate != nullptr)
        {
            uint32_t fps = framerate->getValue<uint32_t>();
            std::cout<<"Current FPS\t\t: "<< fps << std::endl;

            // Change the framerate to 100
            scanner->set_param("user_sensor_framerate", 100);
            std::cout<<"New FPS  \t\t: " << 100 << std::endl;
            std::cout << "-------------------------------------"<< std::endl;
        }

        //
        // Example of working with the parameter type:
        // std::vector<uint32_t>
        //
        // Get parameter of Device IP Addr (second way to get a parameter by keys)
        std::shared_ptr<param> ip_addr = scanner->get_param("user_network_ip");
        if (ip_addr != nullptr)
        {
            std::vector<uint32_t> ip = ip_addr->getValue<std::vector<uint32_t>>();
            std::cout << "Current Device IP\t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;

            // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
            //ip[3]++;
            scanner->set_param("user_network_ip", ip);
            std::cout << "New Device IP    \t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;
            std::cout << "-------------------------------------"       <<std::endl;
        }

        //
        // Example of working with using an Enum:
        // uint32_t
        //
        // Get parameter of Laser Enabled
        std::shared_ptr<param> laser_enabled = scanner->get_param("user_laser_enabled");
        if (laser_enabled != nullptr)
        {
            uint32_t isEnabled = laser_enabled->getValue<uint32_t>();
            auto t = laser_enabled->getEnum<uint32_t>();
            std::cout << "Current Laser State\t: "
                      << laser_enabled->getEnum<uint32_t>().findLabel(isEnabled)
                      << std::endl;


            // Change the current state to the opposite
            if(isEnabled == laser_enabled->getEnum<uint32_t>().getValue("FALSE"))
            {
                scanner->set_param_by_key("user_laser_enabled", "TRUE");
                std::cout << "New Laser State  \t: "
                          << laser_enabled->getEnum<uint32_t>().getLabel("TRUE")
                          << std::endl;
            }else
            {
                scanner->set_param_by_key("user_laser_enabled", "FALSE");
                std::cout << "New Laser State  \t: "
                          << laser_enabled->getEnum<uint32_t>().getLabel("FALSE")
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


























