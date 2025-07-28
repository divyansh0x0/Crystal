#include <gtest/gtest.h>
#include "krystal/geometry/Vector3.hpp"


using namespace ktl::geometry;

// Test the constructors
TEST (VectorTest, Vector_Test)
{
    Vector3 v1{1, 2, 3};
    ASSERT_EQ (v1[0], 1);
    ASSERT_EQ (v1[1], 2);
    ASSERT_EQ (v1[2], 3);
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}