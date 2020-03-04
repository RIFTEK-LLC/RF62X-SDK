#include <rf627sdk.h>
#include <rf627types.h>
#include <iostream>

using namespace SDK;
using namespace SCANNERS;
using namespace RF627;

int main()
{

    // Initialize sdk library
    sdk_init();

    // Print return rf627 sdk version
    std::cout << sdk_version() << std::endl;


    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE_PROTOKOL);


    //Print count of discovered rf627-old in network by Service Protocol
    std::cout << "Discovered " << list.size() << " rf627-old" << std::endl;

}


























