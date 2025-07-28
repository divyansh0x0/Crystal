#pragma once
#include <string>
#include "krystal/graphics/Color.hpp"
#include "krystal/graphics/Graphics.hpp"
#include "krystal/graphics/WindowContext.hpp"
#include "../geometry/Size.hpp"

#include "Core.hpp"

namespace ktl
{
    class Window : public WindowContext
    {
        public:
            bool b_vsync_ = false;
            Window(const char* name, geometry::Size size, Color background_color, ktl::graphics::API graphics_api);

            [[nodiscard]] unsigned int getWidth() const { return m_frame_buffer_size.width; }

            [[nodiscard]] unsigned int getHeight() const { return m_frame_buffer_size.height; }

            void addComponent();
            void show();
            void destroyWindow();

            [[nodiscard]] bool isVisible() const { return m_is_window_visible; };

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

            void*                      m_glfw_window{}; // pointer to GLFWWindow
            Shared<graphics::Renderer> m_renderer;

            bool m_is_renderer_attached;
            bool m_window_destroyed;
            bool m_is_window_visible;
    };

} // namespace ktl