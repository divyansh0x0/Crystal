#include <gtest/gtest.h>
#include "krystal/core/Window.hpp"
#include "krystal/graphics/Color.hpp"
#include "krystal/graphics/Graphics.hpp"
#include "../krystal/include/krystal/geometry/Size.hpp"


using namespace ktl;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(GUI, WindowCreation)
{
    Window window("Test window", geometry::Size(600, 420), Color(22, 22, 22, 1.0f), ktl::graphics::API::OpenGL);
    EXPECT_EQ(window.isVisible(), false) << "Expected window to be not visible before creation";
    window.show();
    EXPECT_EQ(window.isVisible(), false) << "Expected window to be not visible after being destroyed ";
}