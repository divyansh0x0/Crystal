#include <gtest/gtest.h>
#include "crystal/core/Window.h"
#include "crystal/graphics/Color.h"
#include "crystal/graphics/Graphics.h"
#include "crystal/graphics/Renderer.h"
#include "crystal/layout/Size.h"


using namespace crystal;
int main (int argc, char** argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}

TEST (GUI, WindowCreation)
{
    graphics::Renderer* gl_rednerer = graphics::CreateRenderer (graphics::API::OpenGL);
    Window              window ("Test window", layout::Size (600, 420), Color (255, 255, 255), gl_rednerer);
    EXPECT_EQ (window.isVisible (), false) << "Expected window to be not visible before creation";
    window.show ();
    EXPECT_EQ (window.isVisible (), false) << "Expected window to be not visible after being destroyed ";
}