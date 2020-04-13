#include "gtest/gtest.h"
#include "rf62Xsdk.h"

using namespace SDK::SCANNERS::RF62X;

TEST(profile2D, must_be_returned_profile2D_from_scanners_by_service_protocol) {

    // ARRANGE =================================================================
    // Initialize sdk library
    sdk_init();


    // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    // ASSERT ==================================================================
    // Iterate over all discovered rf627-old in network, connect to each of
    // them and get a profile.
    for(size_t i = 0; i < list.size(); i++)
    {
        // Establish connection to the RF627 device by Service Protocol.
        list[i]->connect();
        // Get profile from scanner's data stream by Service Protocol.
        profile2D_t* profile = list[i]->get_profile2D();
        EXPECT_TRUE(profile != NULL);
    }
}

TEST(profile2D, must_be_returned_profile2D_without_zero_points_by_service_protocol) {

    // ARRANGE =================================================================
    // Initialize sdk library
    sdk_init();


    // ACT =====================================================================
    // Create value for scanners vector's type
    std::vector<rf627old*> list;
    // Search for RF627old devices over network
    list = rf627old::search(PROTOCOLS::SERVICE);


    // ASSERT ==================================================================
    // Iterate over all discovered rf627-old in network, connect to each of
    // them and get a profile.
    for(size_t i = 0; i < list.size(); i++)
    {
        // Establish connection to the RF627 device by Service Protocol.
        list[i]->connect();
        // Get profile from scanner's data stream by Service Protocol.
        profile2D_t* profile = list[i]->get_profile2D(false);

        bool zero_points = false;
        if (profile != nullptr)
            for(size_t i = 0; i < profile->points.size(); i++)
                if (profile->points[i].z == 0) zero_points = true;

        EXPECT_TRUE(profile != NULL);
        EXPECT_FALSE(zero_points);
    }
}

TEST(DISABLED_profile2D, must_be_returned_profile2D_from_scanners_by_modbus_tcp) {

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

TEST(DISABLED_profile2D, must_be_returned_profile2D_from_scanners_by_ethernet_ip) {

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
