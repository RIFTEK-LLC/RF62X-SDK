#include <string>
#include <iostream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#          Frame Example v2.x.x         #"  << std::endl;
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
    // get a frame and print the main frame-info.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        // Print short information about the scanner
        std::cout << "\n\nID scanner's list: " << i              << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Device information: "                      << std::endl;
        std::cout << "* Name  \t: "   << info->device_name()     << std::endl;
        std::cout << "* Serial\t: "   << info->serial_number()   << std::endl;
        std::cout << "* IP Addr\t: "  << info->ip_address()      << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        bool is_connected = list[i]->connect();

        std::shared_ptr<frame> frame = nullptr;
        if (is_connected && ((frame = list[i]->get_frame()) != nullptr))
        {
            std::cout << "Frame information: "                          << std::endl;
            std::cout << "* Data Size\t: " << frame->getDataSize()      << std::endl;
            std::cout << "* Frame Height\t: " << frame->getFrameHeight()<< std::endl;
            std::cout << "* Frame Width\t: " << frame->getFrameWidth()  << std::endl;
            std::cout << "Frame was successfully received!"             << std::endl;
            std::cout << "-----------------------------------------"    << std::endl;
        }else
        {
            std::cout << "Frame was not received!"                      << std::endl;
            std::cout << "-----------------------------------------"    << std::endl;
        }

        // Disconnect from scanner.
        list[i]->disconnect();
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























