#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

#include "json.hpp"

using namespace nlohmann;


using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#        Periphery Example v2.x.x       #"  << std::endl;
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

        // Establish connection to the RF627 device by Service Protocol.
        bool is_connected = scanner->connect();
        if (!is_connected)
            continue;

        // Send data to periphery
        std::vector<uint8_t> in {'H', 'E', 'L', 'L', 'O'};
        std::vector<uint8_t> out;
        bool status = scanner->send_to_periphery("usart0", in, out, 1000);
        if (status){
            std::cout << "The data was sent successfully." << std::endl;
            std::cout << "Size of received data: " << out.size() << std::endl;
        }
        // For a simple send data the following method can be used
        //scanner->send_to_periphery("usart0", in);

        // Receive data from periphery
        status = scanner->receive_from_periphery("usart0", 512, out, 1000);
        if (status){
            std::cout << "The request was sent successfully." << std::endl;
            std::cout << "Size of received data: " << out.size() << std::endl;
        }

        // Disconnect from scanner.
        scanner->disconnect();
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























