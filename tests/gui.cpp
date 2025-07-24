#include <gtest/gtest.h>
#include "crystal/core/Window.hpp"
#include "crystal/graphics/Color.hpp"
#include "crystal/graphics/Graphics.hpp"
#include "../crystal/include/crystal/geometry/Size.hpp"


using namespace crystal;

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}

TEST (GUI, WindowCreation)
{
    Window window ("Test window", geometry::Size (600, 420), Color (22,22,22,1.0f), graphics::API::OpenGL);
    EXPECT_EQ (window.isVisible (), false) << "Expected window to be not visible before creation";
    window.show ();
    EXPECT_EQ (window.isVisible (), false) << "Expected window to be not visible after being destroyed ";
}