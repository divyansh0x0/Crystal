#pragma once
#include "crystal/graphics/Color.h"
#include "crystal/graphics/Renderer.h"
#include "crystal/graphics/WindowContext.h"
#include "crystal/layout/Size.h"
#include <atomic>
#include <string>
#include <thread>

namespace crystal
{
typedef void* (*ProcAddress)(const char* name);
class Window : public crystal::WindowContext
{
    private:
        std::string           m_window_name;
        crystal::layout::Size m_frame_buffer_size;
        crystal::Color        m_background_color;

        void*               m_glfw_window; // pointer to GLFWWindow
        graphics::Renderer* m_renderer;
        std::thread*        m_rendering_thread;

        std::atomic<bool> m_renderer_attached_b;
        std::atomic<bool> m_window_destroyed_b;
        std::atomic<bool> m_window_visible_b;
        std::atomic<int>  m_current_fps;
        std::atomic<int>  m_max_fps = 120;

    protected:
        void frameBufferResizedCallback(const int new_width,
                                        const int new_height);
        void rendererLoop();

    public:
        bool b_vsync_ = false;
        Window(const char*           name,
               crystal::layout::Size size,
               crystal::Color        background_color,
               graphics::Renderer*   renderer = nullptr);

        unsigned int getWidth() { return m_frame_buffer_size.width; }
        unsigned int getHeight() { return m_frame_buffer_size.height; }

        void addComponent();
        void show();
        void destroyWindow();

        const crystal::layout::Size& getFrameBufferSize() const override;

        void attachRenderer(graphics::Renderer& renderer);
        void dettachRenderer();

        void  switchContextToCurrentThread() const override;
        void  detachContextFromCurrentThread() const override;
        void* getGLLoadProc() const override;
        void  swapBuffers() const override;
        ~Window();
};

} // namespace crystal