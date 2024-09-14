#pragma once
#include "crystal/core/Color.h"
#include "crystal/graphics/WindowContext.h"
#include "crystal/layout/Size.h"

#include <string>
#include <thread>


namespace crystal
{
typedef void* (*ProcAddress)(const char *name);
class Window : public crystal::WindowContext
{
    private:
        std::string m_window_name;
        crystal::layout::Size m_frame_buffer_size;
        crystal::Color m_background_color;
        // crystal::graphics::Renderer m_renderer{};
        void *m_glfw_window;

        bool m_destroy_window_flag;
        void frameBufferResizedCallback(int new_width, int new_height);

    public:
        bool b_vsync_ = false;
        Window(const char *name,
               crystal::layout::Size size,
               crystal::Color background_color);
        void addComponent();
        void show();
        void destroyWindow();

        unsigned int getWidth() { return m_frame_buffer_size.width; }
        unsigned int getHeight() { return m_frame_buffer_size.height; }

        const crystal::layout::Size &getFrameBufferSize() const override;
        void  switchContextToCurrentThread() const override;
        void detachContextFromCurrentThread() const override;
        void* getGLLoadProc() const override;
        void swapBuffers() const override;
        ~Window();
};

} // namespace crystal