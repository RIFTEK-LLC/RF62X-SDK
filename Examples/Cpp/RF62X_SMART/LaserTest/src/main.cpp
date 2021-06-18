#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;

void print_profile_info(std::shared_ptr<profile2D>& profile, bool isEnabled, int& count_ok, int& count_nok)
{
    if (isEnabled)
    {
        if (profile)
        {
            int current_size = 0;
            int max_size = 0;
            switch ((PROFILE_DATA_TYPES)profile->getHeader().data_type)
            {
            case PROFILE_DATA_TYPES::PIXELS:
                current_size = profile->getPixels().size();
                max_size = 648;
                break;
            case PROFILE_DATA_TYPES::PIXELS_INTRP:
                current_size = profile->getPixels().size();
                max_size = 648 * 2;
                break;
            case PROFILE_DATA_TYPES::PROFILE:
                current_size = profile->getPoints().size();
                max_size = 648;
                break;
            case PROFILE_DATA_TYPES::PROFILE_INTRP:
                current_size = profile->getPoints().size();
                max_size = 648 * 2;
                break;
            }
            if ((PROFILE_DATA_TYPES)profile->getHeader().data_type == PROFILE_DATA_TYPES::PROFILE ||
                    (PROFILE_DATA_TYPES)profile->getHeader().data_type == PROFILE_DATA_TYPES::PROFILE_INTRP)
            {
                if(current_size < max_size * 0.10)
                {
                    count_nok++;
                    std::cout << "Profile was received, but there are few points!!!!"<<std::endl;
                }else
                {
                    count_ok++;
                }
            }else
            {
                bool is_null = true;
                for (size_t i = 0; i < profile->getPixels().size()-10; i+=10)
                {
                    if (profile->getPixels()[i] != 0)
                    {
                        is_null = false;
                        break;
                    }
                }
                if(is_null)
                {
                    count_nok++;
                    std::cout << "Profile was received, but there are few points!!!!"<<std::endl;
                }else
                {
                    count_ok++;
                }
            }
        }else
        {
            count_nok++;
            std::cout << "Profile was not received!" <<std::endl;
        }
    }else
    {
        if (profile)
        {
            int current_size = 0;
            int max_size = 0;
            switch ((PROFILE_DATA_TYPES)profile->getHeader().data_type)
            {
            case PROFILE_DATA_TYPES::PIXELS:
                current_size = profile->getPixels().size();
                max_size = 648;
                break;
            case PROFILE_DATA_TYPES::PIXELS_INTRP:
                current_size = profile->getPixels().size();
                max_size = 648 * 2;
                break;
            case PROFILE_DATA_TYPES::PROFILE:
                current_size = profile->getPoints().size();
                max_size = 648;
                break;
            case PROFILE_DATA_TYPES::PROFILE_INTRP:
                current_size = profile->getPoints().size();
                max_size = 648 * 2;
                break;
            }
            if ((PROFILE_DATA_TYPES)profile->getHeader().data_type == PROFILE_DATA_TYPES::PROFILE ||
                    (PROFILE_DATA_TYPES)profile->getHeader().data_type == PROFILE_DATA_TYPES::PROFILE_INTRP)
            {
                if(current_size > max_size * 0.10)
                {
                    count_nok++;
                    std::cout << "When laser turned off, the profile was received!!!!"<<std::endl;
                }else
                {
                    count_ok++;
                }
            }else
            {
                bool is_null = true;
                for (size_t i = 0; i < profile->getPixels().size()-10; i+=10)
                {
                    if (profile->getPixels()[i] != 0)
                    {
                        is_null = false;
                        break;
                    }
                }
                if(!is_null)
                {
                    count_nok++;
                    std::cout << "When laser turned off, the profile was received!!!!"<<std::endl;
                }else
                {
                    count_ok++;
                }
            }
        }else
        {
            count_ok++;
        }
    }
}

int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#       RF627(v2.x.x) Laser Test        #"  << std::endl;
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
    list = rf627smart::search(300);

    // Print count of discovered rf627smart in network by Service Protocol
    std::cout << "Was found\t: " << list.size()<< " RF627-Smart" << std::endl;
    std::cout << "========================================="     << std::endl;

    std::string answer = "n";
    std::cout << "Enable profile checking? (y/n): ";
    std::cin >> answer;
    bool is_check = false;
    bool is_auto_check = false;
    if (answer == "y" || answer == "Y")
    {
        is_check = true;
        answer = "n";
        std::cout << "Enable auto-detection of laser on/off duration? (y/n): ";
        std::cin >> answer;
        if (answer == "y" || answer == "Y")
            is_auto_check = true;
    }

    uint32_t delay_ms = 150;
    if (!is_auto_check)
    {
        std::cout << "Enter the delay between packets, ms: ";
        std::cin >> delay_ms;
    }

    std::cin.ignore(256, '\n');

    // Iterate over all discovered scanners in network, connect to each of them,
    // get parameters and set new values.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::shared_ptr<hello_info> info = list[i]->get_info();

        std::cout << "\n\nID scanner's list: " << i                 << std::endl;
        std::cout << "-----------------------------------------"    << std::endl;

        // Establish connection to the RF627 device by Service Protocol.
        bool is_connected = list[i]->connect();

        int count_ok = 0;
        int count_nok = 0;
        int current_nok = 0;
        int is_ok1 = false;
        int is_ok2 = false;
        while (is_connected)
        {
            // read params from RF627 device by Service Protocol.
            bool is_read = list[i]->read_params();

            if (is_read)
            {
                // Get parameter of Laser Enabled
                std::shared_ptr<param> laser_enabled =
                        list[i]->get_param("user_laser_enabled");
                if (laser_enabled != nullptr)
                {
                    bool isEnabled = laser_enabled->getValue<uint32_t>();
                    std::cout<<"Current Laser State\t: "<<(isEnabled?"ON\n":"OFF\n");

                    // Change the current state to the opposite
                    isEnabled = !isEnabled;
                    laser_enabled->setValue<uint32_t>(isEnabled);
                    std::cout<<"New Laser State  \t: " << (isEnabled?"ON\n":"OFF\n");

                    list[i]->set_param(laser_enabled);

                    bool is_write = list[i]->write_params();

                    if (is_write && is_check)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
                        bool zero_points = false;
                        bool realtime = true;
                        std::shared_ptr<profile2D> profile =
                                list[i]->get_profile2D(zero_points,realtime);
                        print_profile_info(profile, isEnabled, count_ok, count_nok);
                        if (isEnabled)
                        {
                            if (current_nok != count_nok)
                            {
                                current_nok = count_nok;
                                if (!is_auto_check)
                                {
                                    std::cout << "Press Enter to Continue...";
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }else
                                {
                                    //delay_ms+=1;
                                    is_ok1 = false;
                                }
                            }else
                                if (is_auto_check)
                                {
                                    //if (delay_ms > 0)
                                    //    delay_ms--;
                                    is_ok1 = true;
                                }
                        }else
                        {
                            if (current_nok != count_nok)
                            {
                                current_nok = count_nok;
                                if (!is_auto_check)
                                {
                                    std::cout << "Press Enter to Continue...";
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }else
                                {
                                    //delay_ms+=1;
                                    is_ok2 = false;
                                }
                            }else
                                if (is_auto_check)
                                {
                                    //if (delay_ms > 0)
                                    //    delay_ms--;
                                    is_ok2 = true;
                                }
                        }
                    }else
                        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
                    if (is_auto_check)
                    {
                        if (is_ok1 && is_ok2 && delay_ms > 0)
                            delay_ms--;
                        else
                            delay_ms++;
                        std::cout << "Current delay, ms: " << delay_ms << std::endl;
                    }
                    std::cout << "-------------------------------------"<< std::endl;
                }


            }

        }

    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}


























