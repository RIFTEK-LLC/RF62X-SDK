#include <iostream>
#include <string>

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
    std::cout << "Total found: " << list.size() << " RF627-Smart" << std::endl;


    // Iterate over all discovered scanners in network, connect to each of them,
    // get parameters and set new values.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        std::cout << "\n\nID scanner's list: " << i                 << std::endl;
        std::cout << "-----------------------------------------"    << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        bool is_connected = list[i]->connect();

        // read params from RF627 device by Service Protocol.
        bool is_read = list[i]->read_params();

        if (is_connected && is_read)
        {
            //
            // Example of working with the parameter type:
            // std::string
            //
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

            //
            // Example of working with the parameter type:
            // uint32_t
            //
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

            //
            // Example of working with the parameter type:
            // std::vector<uint32_t>
            //
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

            //
            // Example of working with parameters using an Enum
            //
            // Get parameter of Streams Format
            std::shared_ptr<param> streams_format =
                    list[i]->get_param(PARAM_NAME_KEY::USER_STREAMS_FORMAT);
            if (streams_format != nullptr && streams_format->getType() ==
                    param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
            {
                uint32_t current_format = streams_format->getValue<uint32_t>();

                if (current_format == streams_format->
                        getEnum<uint32_t>().getValue("DATA_FORMAT_RAW_PROFILE"))
                {
                    std::string current_format_name = streams_format->
                            getEnum<uint32_t>().getLabel("DATA_FORMAT_RAW_PROFILE");
                    std::cout << "Current Streams Format\t: "
                              << current_format_name << std::endl;

                    // Change the current format to the opposite
                    streams_format->setValue<uint32_t>(
                                streams_format->getEnum<uint32_t>().
                                getValue("DATA_FORMAT_PROFILE"));

                    std::string new_format_name = streams_format->
                            getEnum<uint32_t>().getLabel("DATA_FORMAT_PROFILE");
                    std::cout <<"New Streams Format\t: "
                              << new_format_name << std::endl;
                }
                else if (current_format == streams_format->
                          getEnum<uint32_t>().getValue("DATA_FORMAT_PROFILE"))
                {
                    std::string current_format_name = streams_format->
                            getEnum<uint32_t>().getLabel("DATA_FORMAT_PROFILE");
                    std::cout << "Current Streams Format\t: "
                              << current_format_name << std::endl;

                    // Change the current format to the opposite
                    streams_format->setValue<uint32_t>(
                                streams_format->getEnum<uint32_t>().
                                getValue("DATA_FORMAT_RAW_PROFILE"));


                    std::string new_format_name = streams_format->
                            getEnum<uint32_t>().getLabel("DATA_FORMAT_RAW_PROFILE");
                    std::cout <<"New Streams Format\t: "
                              << new_format_name << std::endl;
                }

                std::cout << "-------------------------------------"<< std::endl;
                list[i]->set_param(streams_format);
            }

            std::string answer = "n";
            // Apply changed parameters to the device
            std::cout << "Apply changed params to the device? (y/n)"<< std::endl;
            std::cin >> answer;
            if (answer == "y" && answer == "Y")
                list[i]->write_params();

            // Save changes to the device's memory
            std::cout << "Save changes to the device's memory? (y/n)"<<std::endl;
            std::cin >> answer;
            if (answer == "y" && answer == "Y")
                list[i]->save_params();

            // Disconnect from scanner.
            list[i]->disconnect();
        }

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























