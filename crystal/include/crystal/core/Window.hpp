#pragma once
#include <atomic>
#include <string>
#include <thread>
#include "crystal/graphics/Color.hpp"
#include "crystal/graphics/Graphics.hpp"
#include "crystal/graphics/WindowContext.hpp"
#include "../geometry/Size.hpp"

#include "Core.hpp"

namespace crystal
{
    class Window : public WindowContext
    {
        public:
            bool b_vsync_ = false;
            Window(const char* name, geometry::Size size, Color background_color, graphics::API graphics_api);

            [[nodiscard]] unsigned int getWidth() const { return m_frame_buffer_size.width; }

            [[nodiscard]] unsigned int getHeight() const { return m_frame_buffer_size.height; }

            void addComponent();
            void show();
            void destroyWindow();

            bool isVisible() { return m_is_window_visible; };

            [[nodiscard]] const geometry::Size& getFrameBufferSize() const override;
            [[nodiscard]] GLLoadProc            getGLLoadProc() const override;

            [[nodiscard]] const Color& getFrameBufferBg() const override { return m_background_color; };

            void switchContextToCurrentThread() const override;
            void detachContextFromCurrentThread() const override;
            void swapBuffers() const override;


            ~Window() override;

        protected:
            void setFrameBufferSize(int new_width, int new_height);

        private:
            std::string    m_window_name;
            geometry::Size m_frame_buffer_size;
            Color          m_background_color;

            void*                     m_glfw_window{}; // pointer to GLFWWindow
            Owned<graphics::Renderer> m_renderer;

            std::atomic<bool>     m_is_renderer_attached;
            std::atomic<bool>     m_window_destroyed;
            std::atomic<bool>     m_is_window_visible;
    };

} // namespace crystal