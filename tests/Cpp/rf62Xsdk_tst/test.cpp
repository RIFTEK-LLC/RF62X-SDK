#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // Force printed tests times
    testing::GTEST_FLAG(print_time) = true;

    // Force colored tests console output
    ::testing::GTEST_FLAG(color) = "yes";

    return RUN_ALL_TESTS();
}
