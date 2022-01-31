#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "rf62Xsdk.h"
#include "rf62Xtypes.h"

using namespace SDK::SCANNERS::RF62X;

void read_params_func(std::shared_ptr<rf627smart>& obj);
void get_profile_func(std::shared_ptr<rf627smart>& obj);

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

    std::cout << "\nTEST 1: Read params in different threads" << std::endl;
    std::cout << "========================================="     << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // Iterate over all discovered scanners in network, connect to each of them,
    // read params in different threads.
    for (size_t i = 0; i < list.size(); i++)
    {
        std::thread* profile_thread1 = new std::thread(read_params_func, ref(list[i]));
        thread_list.push_back(profile_thread1);
    }

    for (size_t i = 0; i < thread_list.size(); i++)
    {
        if (thread_list[i]->joinable())
            thread_list[i]->join();
    }
    thread_list.clear();

    std::cout << "\nTEST 2: Get profiles in different threads" << std::endl;
    std::cout << "========================================="     << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    for (size_t i = 0; i < list.size(); i++)
    {
        std::thread* profile_thread1 = new std::thread(get_profile_func, ref(list[i]));
        thread_list.push_back(profile_thread1);
    }

    for (size_t i = 0; i < thread_list.size(); i++)
    {
        if (thread_list[i]->joinable())
            thread_list[i]->join();
    }
    thread_list.clear();

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

void print_read_params_info(bool is_read, std::thread::id thread_id, int& count)
{
    print_mutex.lock();
    if (is_read)
    {
        std::cout << "Params read from thread_id = " << thread_id <<std::endl;
        count++;
    }else
    {
        std::cout << "Params not read from thread_id = " << thread_id <<std::endl;
        count++;
    }
    print_mutex.unlock();
}

void read_params_func(std::shared_ptr<rf627smart>& obj)
{
    // Establish connection to the RF627 device by Service Protocol.
    bool is_connected = obj->connect();

    int count = 0;
    if (is_connected)
    while(count < 10)
    {
        // read params from RF627 device by Service Protocol.
        print_read_params_info(obj->read_params(), std::this_thread::get_id(), count);
    }
}



















