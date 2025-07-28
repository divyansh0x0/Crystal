#pragma once
#include <thread>


#include "krystal/core/Core.hpp"
#include "krystal/graphics/WindowContext.hpp"

namespace ktl::graphics
{
    class  Renderer
    {
        public:
            Renderer() = delete;
            explicit Renderer(WindowContext* window_context);
            virtual void init()    = 0;
            virtual void destroy() = 0;
            virtual void render()  = 0;
            virtual ~Renderer();
            void start();
            void loop();
            void stop();

        protected:
            WindowContext* m_window_context = nullptr;

        private:
            std::atomic<bool> m_running = false;
            int  m_max_fps      = 60;
            int  m_current_fps  = 0;

            Owned<std::thread> m_rendering_thread;
    };

} // namespace ktl::graphics