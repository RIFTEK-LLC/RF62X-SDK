#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;



/**
 * @brief Function to get profile
 * @param obj Ptr to std::shared_ptr<rf627smart>
 */
void get_profile_func(std::shared_ptr<rf627smart>& obj);

/**
 * @brief Function to get/set parameters
 * @param obj Ptr to std::shared_ptr<rf627smart>
 */
void laser_on_func(std::shared_ptr<rf627smart>& obj);
void laser_off_func(std::shared_ptr<rf627smart>& obj);

int main()
{
    std::cout << "#########################################"  << std::endl;
    std::cout << "#                                       #"  << std::endl;
    std::cout << "#      Multithread Example v2.x.x       #"  << std::endl;
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


    std::vector<std::thread*> thread_list;

    std::cout << "\nTEST 1: Get profiles in different threads" << std::endl;
    std::cout << "========================================="     << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // Iterate over all discovered scanners in network, connect to each of them,
    // get profiles in different threads.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::thread* profile_thread1 = new std::thread(get_profile_func, ref(list[i]));
        std::thread* profile_thread2 = new std::thread(get_profile_func, ref(list[i]));

        thread_list.push_back(profile_thread1);
        thread_list.push_back(profile_thread2);
    }

    for (size_t i = 0; i < thread_list.size(); i++)
    {
        if (thread_list[i]->joinable())
            thread_list[i]->join();
    }

    std::cout << "\nTEST 2: Get/Set parameters in different threads" << std::endl;
    std::cout << "========================================="     << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // Get the Laser Enabled parameter and turn it on in one thread, turn it off in the other
    for (size_t i = 0; i < list.size(); i++)
    {
        std::thread* param_thread1 = new std::thread(laser_on_func, ref(list[i]));
        std::thread* param_thread2 = new std::thread(laser_off_func, ref(list[i]));

        thread_list.push_back(param_thread1);
        thread_list.push_back(param_thread2);
    }

    for (size_t i = 0; i < thread_list.size(); i++)
    {
        if (thread_list[i]->joinable())
            thread_list[i]->join();
    }

    for (size_t i = 0; i < list.size(); i++)
    {
        // Disconnect from scanner.
        list[i]->disconnect();
    }

    // Cleanup resources allocated with sdk_init()
    sdk_cleanup();
}

std::mutex print_mutex;
void print_profile_info(std::shared_ptr<profile2D>& profile,
                        std::thread::id thread_id, int& count);

void get_profile_func(std::shared_ptr<rf627smart>& scanner)
{
    // Establish connection to the RF627 device by Service Protocol.
    bool is_connected = scanner->connect();

    // Get profile from scanner's data stream by Service Protocol.
    std::shared_ptr<profile2D> profile = nullptr;
    bool zero_points = true;
    bool realtime = true;

    int count = 0;
    while(count < 20)
    if (is_connected)
    {
        profile = scanner->get_profile2D(zero_points,realtime);
        print_profile_info(profile, std::this_thread::get_id(), count);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void print_profile_info(std::shared_ptr<profile2D>& profile,
                        std::thread::id thread_id, int& count)
{
    print_mutex.lock();
    if (profile)
    {
        std::cout << "Profile information from thread_id = " << thread_id <<": "<<std::endl;
        switch ((PROFILE_DATA_TYPES)profile->getHeader().data_type)
        {
        case PROFILE_DATA_TYPES::PIXELS:
            std::cout<<"* DataType\t: "<<"PIXELS"                <<std::endl;
            std::cout<<"* Count\t: "<<profile->getPixels().size()<<std::endl;
            break;
        case PROFILE_DATA_TYPES::PIXELS_INTRP:
            std::cout<<"* DataType\t: "<<"PIXELS_INTRP"          <<std::endl;
            std::cout<<"* Count\t: "<<profile->getPixels().size()<<std::endl;
            break;
        case PROFILE_DATA_TYPES::PROFILE:
            std::cout<<"* DataType\t: "<<"PROFILE"               <<std::endl;
            std::cout<<"* Size\t: "<<profile->getPoints().size() <<std::endl;
            break;
        case PROFILE_DATA_TYPES::PROFILE_INTRP:
            std::cout<<"* DataType\t: "<<"PROFILE_INTRP"         <<std::endl;
            std::cout<<"* Size\t: "<<profile->getPoints().size() <<std::endl;
            break;
        }
        count++;
        std::cout << "Profile was successfully received: "<<count<<std::endl;
        std::cout << "-----------------------------------------" <<std::endl;
    }else
    {
        std::cout << "Profile was not received!"                 <<std::endl;
        std::cout << "-----------------------------------------" <<std::endl;
    }
    print_mutex.unlock();
}

void print_laser_info(bool is_enable, std::thread::id thread_id, int& count);
void laser_on_func(std::shared_ptr<rf627smart>& obj)
{
    // Establish connection to the RF627 device by Service Protocol.
    bool is_connected = obj->connect();

    int count = 0;
    while(count < 20)
    {
        // read params from RF627 device by Service Protocol.
        bool is_read = obj->read_params();

        if (is_connected && is_read)
        {
            // Get parameter of Laser Enabled
            std::shared_ptr<param> laser_enabled = obj->get_param("user_laser_enabled");
            if (laser_enabled != nullptr)
            {
                bool isEnabled = laser_enabled->getValue<uint32_t>();
                if (isEnabled == false)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    laser_enabled->setValue<uint32_t>(true);
                    obj->set_param(laser_enabled);
                    obj->write_params();
                    print_laser_info(true, std::this_thread::get_id(), count);
                }else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    count++;
                }
            }
        }
    }
}

void laser_off_func(std::shared_ptr<rf627smart>& obj)
{
    // Establish connection to the RF627 device by Service Protocol.
    bool is_connected = obj->connect();


    int count = 0;
    while(count < 10)
    {
        // read params from RF627 device by Service Protocol.
        bool is_read = obj->read_params();

        if (is_connected && is_read)
        {
            // Get parameter of Laser Enabled
            std::shared_ptr<param> laser_enabled = obj->get_param("user_laser_enabled");
            if (laser_enabled != nullptr)
            {
                bool isEnabled = laser_enabled->getValue<uint32_t>();
                if (isEnabled == true)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    laser_enabled->setValue<uint32_t>(false);
                    obj->set_param(laser_enabled);
                    obj->write_params();
                    print_laser_info(false, std::this_thread::get_id(), count);
                }else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    count++;
                }
            }
        }
    }
}

void print_laser_info(bool is_enable, std::thread::id thread_id, int& count)
{
    print_mutex.lock();
    if (is_enable)
    {
        std::cout << "Laser switched OFF from thread_id = " << thread_id <<std::endl;
        count++;
    }else
    {
        std::cout << "Laser switched ON from thread_id = " << thread_id <<std::endl;
        count++;
    }
    print_mutex.unlock();
}




















