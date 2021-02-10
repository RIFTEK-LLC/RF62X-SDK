#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <string>
#include <iostream>

#include <chrono>
#include <thread>
#include <cstdlib>

using namespace SDK::SCANNERS::RF62X;


int main(int argc, char *argv[])
{

    int count = 30;
    int timeout = 1000;
    if(argc>=3)
    {
        count = atoi(argv[1]);
        timeout = atoi(argv[2]);
    }
    // Initialize sdk library
    sdk_init();

    // Print return rf62X sdk version
    std::cout << "SDK version: " << sdk_version()                << std::endl;
    std::cout << "========================================="     << std::endl;


    // Create value for scanners vector's type
    std::vector<std::shared_ptr<rf627smart>> list;
    // Search for rf627smart devices over network
    list = rf627smart::search(timeout);


    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Discovered: " << list.size() << " rf627-smart"   << std::endl;


    while (true) {
        // Iterate over all discovered rf627-old in network, connect to each of
        // them and get a profile.
        for (size_t i = 0; i < list.size(); i++)
        {
            rf627smart::hello_info info = list[i]->get_info();

            // Print information about the scanner to which the profile belongs.
            std::cout << "\n\n\nID scanner's list: " << i            << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
            std::cout << "Device information: "                      << std::endl;
            std::cout << "* Name\t: "     << info.device_name()      << std::endl;
            std::cout << "* Serial\t: "   << info.serial_number()    << std::endl;
            std::cout << "* IP Addr\t: "  << info.ip_address()       << std::endl;

            // Establish connection to the RF627 device by Service Protocol.
            bool is_connect = list[i]->connect();

            for (int j = 0; j < count; j++)
            {
                // Get profile from scanner's data stream by Service Protocol.
                std::shared_ptr<frame> frame = nullptr;
                if (is_connect && ((frame = list[i]->get_frame()) != nullptr))
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

                std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
            }

            // Disconnect from scanner.
            list[i]->disconnect();
        }

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























