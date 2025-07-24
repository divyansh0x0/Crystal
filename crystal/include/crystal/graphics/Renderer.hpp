#pragma once
#include <thread>


#include "crystal/core/Core.hpp"
#include "crystal/graphics/WindowContext.hpp"

namespace crystal::graphics
{
    class Renderer
    {
        public:
            virtual void init()    = 0;
            virtual void destroy() = 0;
            virtual void render()  = 0;
            virtual ~Renderer();
            void start(WindowContext& window_context_ptr);
            void loop();
            void stop();

        protected:
            WindowContext* m_window_context = nullptr;

        private:
            std::atomic<bool> m_is_rendering = false;
            int  m_max_fps      = 60;
            int  m_current_fps  = 0;

            Owned<std::thread> m_rendering_thread;
    };

} // namespace crystal::graphics