#include <rf62Xsdk.h>
#include <rf62Xtypes.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF62X;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf627 sdk version
    std::cout << sdk_version() << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    //Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered " << list.size() << " rf627-old" << std::endl;

    list[0]->connect();
    list[0]->send_cmd("CID_PROFILE_SET_COUNTERS", 5000, 1000);
    list[0]->read_params();
    list[0]->set_param(USER_GENERAL_DEVICENAME, "test name");
    profile2D_t* test = list[0]->get_profile2D(false);
    std::cout << test->intensity.size() << std::endl;
}


























