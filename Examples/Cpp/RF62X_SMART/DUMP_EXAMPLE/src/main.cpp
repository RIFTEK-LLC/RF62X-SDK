#include <string>
#include <iostream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#          Dump Example v2.x.x          #"  << std::endl;
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
    // get a frame and print the main frame-info.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<rf627smart> scanner = list[i];
        std::shared_ptr<hello_info> info = scanner->get_info();

        // Print short information about the scanner
        std::cout << "\n\nID scanner's list: " << i              << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Device information: "                      << std::endl;
        std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
        std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
        std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        bool is_connected = scanner->connect();
        if (!is_connected){
            std::cout << "Failed to connect to scanner!" << std::endl;
            continue;
        }

        uint32_t count_of_profiles = 1000;
        scanner->start_dump_recording(count_of_profiles);

        std::cout << "Start dump recording..."                   << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        uint32_t size = 0;
        do {
            scanner->read_params();
            size = scanner->get_param("user_dump_size")->getValue<uint32_t>();
            std::cout << "Current profiles in the dump: "<< size << std::endl;
        }while(size < count_of_profiles);
        std::cout << "-----------------------------------------" << std::endl;

        std::cout << "Start dump downloading..."                 << std::endl;
        std::vector<std::shared_ptr<profile2D>> dump =
                scanner->get_dumps_profiles(0, count_of_profiles);

        std::cout << dump.size() << " Profiles in dump were downloaded!\n";
        std::cout << "-----------------------------------------" << std::endl;

        // Disconnect from scanner.
        scanner->disconnect();
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























