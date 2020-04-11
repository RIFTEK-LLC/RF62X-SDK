#include "gtest/gtest.h"
#include "rf62Xsdk.h"

using namespace SDK::SCANNERS::RF62X;

TEST(connect, must_be_connected_to_scanners_by_service_protocol) {

    // ARRANGE =================================================================
    // Initialize sdk library
    sdk_init();


    // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    // ASSERT ==================================================================
    for (size_t i = 0; i < list.size(); i++)
        EXPECT_TRUE(list[i]->connect(PROTOCOLS::SERVICE));
}

TEST(DISABLED_connect, must_be_connected_to_scanners_by_modbus_tcp) {

    // ARRANGE =================================================================
    // Initialize sdk library
    sdk_init();


    // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::MODBUS_TCP);


    // ASSERT ==================================================================
    for (size_t i = 0; i < list.size(); i++)
        EXPECT_TRUE(list[i]->connect(PROTOCOLS::MODBUS_TCP));
}

TEST(DISABLED_connect, must_be_connected_to_scanners_by_ethernet_ip) {

    // ARRANGE =================================================================
    // Initialize sdk library
     sdk_init();


     // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::ETHERNET_IP);


    // ASSERT ==================================================================
    for (size_t i = 0; i < list.size(); i++)
        EXPECT_TRUE(list[i]->connect(PROTOCOLS::ETHERNET_IP));
}
