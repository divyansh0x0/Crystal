#include "crystal/geometry/Matrix.h" // Include the appropriate header for the Matrix class
#include "crystal/geometry/Vector3.h"
#include <gtest/gtest.h>

using namespace crystal::geometry;

// Test the constructors
TEST(VectorTest, Vector_Test)
{
    Vector3 v1{1,2,3};
    ASSERT_EQ(v1[0], 1);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v1[2], 3);
}

