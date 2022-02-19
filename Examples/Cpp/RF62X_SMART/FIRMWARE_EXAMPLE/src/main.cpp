#include <string>
#include <iostream>
#include <fstream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#     RF62X(v2.x.x) Firmware Example    #"  << std::endl;
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

    int index = -1;
    if (list.size() > 1) {
        std::cout << "Select scanner for test: " << std::endl;
        for (size_t i = 0; i < list.size(); i++)
            std::cout << i << ". Serial: "
                      << list[i]->get_info()->serial_number() << std::endl;
        std::cin >> index;
    }
    else if (list.size() == 1) {
        index = 0;
    }
    else {
        return 0;
    }

    std::shared_ptr<rf627smart> scanner = list[index];
    std::shared_ptr<hello_info> info = scanner->get_info();

    // Print information about the scanner to which the profile belongs.
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Device information: "                      << std::endl;
    std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
    std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
    std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    // Establish connection to the RF627 device by Service Protocol.
    bool is_connected = scanner->connect();

    if (is_connected)
    {
        std::vector<uint8_t> firmware;
        bool status = scanner->get_firmware(firmware);
        if (status){
            std::cout << "The firmware was receive successfully." << std::endl;
            std::cout << "Size of firmware: " << firmware.size() << std::endl;
            std::ofstream file("file.2fw", std::ios::out | std::ios::binary);
            file.write(reinterpret_cast<const char*>(firmware.data()), firmware.size());
            file.close();
        }
    }else
    {
        std::cout << "Failed to connect scanner..." << std::endl;
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























