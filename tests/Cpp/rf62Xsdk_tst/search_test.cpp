#include "gtest/gtest.h"
#include "rf62Xsdk.h"

using namespace SDK::SCANNERS::RF62X;

TEST(search, must_be_found_more_than_one_scanner_by_service_protocol) {

    // ARRANGE =================================================================
    // Initialize sdk library
    sdk_init();


    // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    // ASSERT ==================================================================
    EXPECT_GT(list.size(), 0);
}

TEST(DISABLED_search, must_be_found_more_than_one_scanner_by_modbus_tcp) {

    // ARRANGE =================================================================
    // Initialize sdk library
    sdk_init();


    // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::MODBUS_TCP);


    // ASSERT ==================================================================
    EXPECT_GT(list.size(), 0);
}

TEST(DISABLED_search, must_be_found_more_than_one_scanner_by_ethernet_ip) {

    // ARRANGE =================================================================
    // Initialize sdk library
    sdk_init();


    // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::ETHERNET_IP);


    // ASSERT ==================================================================
    EXPECT_GT(list.size(), 0);
}
