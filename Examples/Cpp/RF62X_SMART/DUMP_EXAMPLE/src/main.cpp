#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

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

    int index = -1;
    if (list.size() > 1)
    {
        std::cout << "Select scanner for test: " << std::endl;
        for (size_t i = 0; i < list.size(); i++)
            std::cout << i << ". Serial: "
                      << list[i]->get_info()->serial_number() << std::endl;
        std::cin >> index;
    }
    else if (list.size() == 1)
        index = 0;
    else
        return 0;


    std::shared_ptr<rf627smart> scanner = list[index];
    std::shared_ptr<hello_info> info = scanner->get_info();

    // Print short information about the scanner
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
        return 0;
    }

    uint32_t count = 1000;
    while(count > 0)
    {
        std::cout << "Enter the number of profiles in the dump: " << std::endl;
        std::cin >> count;
        scanner->start_dump_recording(count);

        std::cout << "Start dump recording..."                   << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        uint32_t size = 0;
        do {
            scanner->read_params();
            size = scanner->get_param("user_dump_size")->getValue<uint32_t>();
            std::cout << "Current profiles in the dump: "<< size << std::endl;
        }while(size < count);
        std::cout << "-----------------------------------------" << std::endl;

        std::cout << "Start dump downloading..."                 << std::endl;
        int waiting_timeout_ms = count * 10;
        std::vector<std::shared_ptr<profile2D>> dump =
            scanner->get_dumps_profiles(0,count,waiting_timeout_ms);

        // Create file name
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        std::stringstream date;
        date << std::put_time(localTime, "%Y.%m.%d_%H.%M.%S");
        std::string filename = "dump__"+date.str()+"__"+std::to_string(count)+".bin";

        for (auto& profile : dump) {
            profile->save_to_file(filename);
        }

        std::cout << dump.size() << " The dump has been downloaded!\n";
        std::cout << "-----------------------------------------" << std::endl;

        // Apply changed parameters to the device
        std::string answer = "n";
        std::cout << "Try again? (y/n): ";
        std::cin >> answer;
        if (!(answer == "y" || answer == "Y")){
            // Disconnect from scanner.
            scanner->disconnect();
            break;
        }
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























