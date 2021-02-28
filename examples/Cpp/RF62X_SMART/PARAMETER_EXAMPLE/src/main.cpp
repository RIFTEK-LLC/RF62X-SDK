#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>
#include <string>

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
    std::cout << "Discovered: " << list.size() << " rf627-smart"   << std::endl;


    // Iterate over all discovered scanners in network, connect to each of them,
    // get parameters and set new values.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        std::cout << "\n\n\nID scanner's list: " << i               << std::endl;
        std::cout << "-----------------------------------------"    << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        bool is_connected = list[i]->connect();

        // read params from RF627 device by Service Protocol.
        bool is_read = list[i]->read_params();

        if (is_connected && is_read)
        {
            // Get parameter of Device Name (first way to get parameter by string name)
            std::shared_ptr<param> name = list[i]->get_param("user_general_deviceName");
            if (name->getType() == "string_t")
            {
                std::string str_name = name->getValue<std::string>();
                std::cout << "Current Device Name \t: " << str_name << std::endl;

                // Add "_TEST" to the ending of the current name
                str_name += "_TEST";
                name->setValue<std::string>(str_name);
                std::cout << "New Device Name \t: " << str_name     << std::endl;
                std::cout << "-------------------------------------"<< std::endl;

                list[i]->set_param(name);
            }

            // Get parameter of Device IP Addr (second way to get a parameter by keys)
            PARAM_NAME_KEY ip_addr_name_key = PARAM_NAME_KEY::USER_NETWORK_IP;
            PARAM_VALUE_TYPE ip_addr_type = PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE;
            std::shared_ptr<param> ip_addr = list[i]->get_param(ip_addr_name_key);
            if (ip_addr->getType() == param_value_types[(int)ip_addr_type])
            {
                std::vector<uint32_t> ip = ip_addr->getValue<std::vector<uint32_t>>();
                std::cout << "Current Device IP\t: ";
                for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;

                // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
                ip[3]++;
                ip_addr->setValue<std::vector<uint32_t>>(ip);
                std::cout << "New Device IP\t: ";
                for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;
                std::cout << "-------------------------------------"       <<std::endl;

                list[i]->set_param(ip_addr);
            }

            // Get parameter of Laser Enabled
            std::shared_ptr<param> laser_enabled =
                    list[i]->get_param(PARAM_NAME_KEY::USER_LASER_ENABLED);
            if (laser_enabled->getType() ==
                    param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
            {
                bool isEnabled = laser_enabled->getValue<uint32_t>();
                std::cout<<"Current Laser State\t: "<<(isEnabled?"ON\n":"OFF\n");

                // Change the current state to the opposite
                isEnabled = !isEnabled;
                laser_enabled->setValue<uint32_t>(isEnabled);
                std::cout<<"New Laser State\t: " << (isEnabled?"ON\n":"OFF\n");
                std::cout << "-------------------------------------"<< std::endl;

                list[i]->set_param(laser_enabled);
            }

            // Write changes parameters to the device's memory
            list[i]->write_params();

            // Disconnect from scanner.
            list[i]->disconnect();
        }

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























