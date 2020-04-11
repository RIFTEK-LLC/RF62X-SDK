#include "gtest/gtest.h"
#include "rf62Xsdk.h"

TEST(sdk_init, must_be_returned_true) {
    // ARRANGE =================================================================
    // ACT =====================================================================
    // ASSERT ==================================================================
    EXPECT_TRUE (SDK::SCANNERS::RF62X::sdk_init());
}
