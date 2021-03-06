#include <string>
#include <iostream>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;


int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#         Search Example v2.x.x         #"  << std::endl;
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
    list = rf627smart::search(500);

    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Was found\t: " << list.size()<< " RF627 v2.x.x"<< std::endl;
    std::cout << "========================================="     << std::endl;


    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        std::cout << "\n\nID scanner's list: " << i               << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
        std::cout << "Device information: "                       << std::endl;
        std::cout << "* Name  \t: "   << info->device_name()      << std::endl;
        std::cout << "* Serial\t: "   << info->serial_number()    << std::endl;
        std::cout << "* IP Addr\t: "  << info->ip_address()       << std::endl;
        std::cout << "* MAC Addr\t: " << info->mac_address()      << std::endl;

        std::cout << "\nWorking ranges: "                         << std::endl;
        std::cout << "* Zsmr, mm\t: " << info->z_smr()            << std::endl;
        std::cout << "* Zmr , mm\t: " << info->z_mr()             << std::endl;
        std::cout << "* Xsmr, mm\t: " << info->x_smr()            << std::endl;
        std::cout << "* Xemr, mm\t: " << info->x_emr()            << std::endl;

        std::cout << "\nVersions: "                               << std::endl;
        std::cout << "* Firmware\t: " << info->firmware_version() << std::endl;
        std::cout << "* Hardware\t: " << info->hardware_version() << std::endl;
        std::cout << "-----------------------------------------"  << std::endl;
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























