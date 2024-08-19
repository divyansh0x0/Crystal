#pragma once
#include "glad/glad.h"
#include "crystal/core/Color.h"
#include "crystal/layout/Size.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <string>
#include "crystal/graphics/ApiContextManager.h"
namespace crystal
{
    class Window : public crystal::graphics::ApiContextManager
    {
    private:
        std::string m_window_name;
        crystal::layout::Size m_frame_buffer_size;
        crystal::Color m_background_color;
        // crystal::graphics::Renderer m_renderer{};
        GLFWwindow *m_glfw_window;

        bool m_destroy_window_flag;
        void frameBufferResizedCallback(int new_width, int new_height);

    public:
        bool b_vsync_ = false;
        Window(std::string name, crystal::layout::Size size, crystal::Color background_color);
        void addComponent();
        void show();
        void destroyWindow();
        
        unsigned int getWidth() {return m_frame_buffer_size.width;}
        unsigned int getHeight() {return m_frame_buffer_size.height;}

        const crystal::layout::Size& getFrameBufferSize() override;
        void switchContextToCurrentThread()override;
        void detachContextFromCurrentThread()override;
        void swapBuffers()override;
        ~Window();
    };

}