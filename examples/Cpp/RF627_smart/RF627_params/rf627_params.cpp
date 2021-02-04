#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>
#include <string>

using namespace SDK::SCANNERS::RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf62X sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<std::shared_ptr<rf627smart>> scanners;
    // Search for rf627smart devices over network
    scanners = rf627smart::search(500);


    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Discovered: " << scanners.size() << " rf627-smart"   << std::endl;


    // Iterate over all discovered rf627-old in network, connect to each of
    // them and get a profile.
    for (size_t i = 0; i < scanners.size(); i++)
    {
        rf627smart::hello_info info = scanners[i]->get_info();

        std::cout << "\n\n\nID scanner's list: " << i               << std::endl;
        std::cout << "-----------------------------------------"    << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        scanners[i]->connect();

        // read params from RF627 device by Service Protocol.
        scanners[i]->read_params();

        // Get parameter of Device Name
        std::shared_ptr<param> name = scanners[i]->get_param(PARAM_NAME_KEY::USER_GENERAL_DEVICENAME);
        if (name->getType() == param_value_types[(int)PARAM_VALUE_TYPE::STRING_PARAM_TYPE])
        {
            std::string str_name = name->getValue<std::string>();
            std::cout << "Current Device Name \t: " << str_name     << std::endl;

            // Add "_TEST" to the ending of the current name
            str_name += "_TEST";
            name->setValue<std::string>(str_name);
            std::cout << "New Device Name \t: " << str_name         << std::endl;
            std::cout << "-----------------------------------------"<< std::endl;

            scanners[i]->set_param(name);
        }

        // Get parameter of Device IP Addr
        std::shared_ptr<param> ip_addr = scanners[i]->get_param(PARAM_NAME_KEY::USER_NETWORK_IP);
        if (ip_addr->getType() == param_value_types[(int)PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE])
        {
            std::vector <uint32_t> ip = ip_addr->getValue<std::vector<uint32_t>>();
            std::cout << "Current Device IP\t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;

            // Change last digit of IP address (e.g. 192.168.1.30 -> 192.168.1.31)
            ip[3]++;
            ip_addr->setValue<std::vector<uint32_t>>(ip);
            std::cout << "New Device IP\t: ";
            for(auto i: ip) std::cout<<std::to_string(i)<<".";std::cout<<std::endl;
            std::cout << "-----------------------------------------"<< std::endl;

            scanners[i]->set_param(ip_addr);
        }

        // Get parameter of Laser Enabled
        std::shared_ptr<param> laser_enabled = scanners[i]->get_param(PARAM_NAME_KEY::USER_LASER_ENABLED);
        if (laser_enabled->getType() == param_value_types[(int)PARAM_VALUE_TYPE::UINT_PARAM_TYPE])
        {
            bool isEnabled = laser_enabled->getValue<uint32_t>();
            std::cout<<"Current Laser State\t: "<<(isEnabled?"ON":"OFF")<<std::endl;

            isEnabled = !isEnabled;
            // Change the current state to the opposite
            laser_enabled->setValue<uint32_t>(isEnabled);
            std::cout<<"New Laser State\t: "<<(isEnabled?"ON":"OFF")<< std::endl;
            std::cout << "-----------------------------------------"<< std::endl;

            scanners[i]->set_param(laser_enabled);
        }

        //  Write changes parameters to the device's memory
        scanners[i]->write_params();

        // Disconnect from scanner.
        scanners[i]->disconnect();

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();

}


























