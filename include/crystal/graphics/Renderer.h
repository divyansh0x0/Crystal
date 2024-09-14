#include "crystal/core/Window.h"
#include "crystal/graphics/GraphicsAPI.h"
#include "crystal/graphics/WindowContext.h"
#include "crystal/layout/Size.h"

#include <atomic>
#include <thread>


namespace crystal::graphics
{
class Renderer
{
    private:
        const WindowContext *m_window_context;
        GraphicsContextType m_graphics_api = GraphicsContextType::OpenGL;
        GraphicsContext *m_graphics_context;
        std::thread *m_render_thread;
        unsigned int m_max_fps               = 120;
        unsigned int current_fps             = 0;
        std::atomic<bool> m_initialized_flag = false;
        std::atomic<bool> m_destroyed_flag   = false;
        Renderer();
        void renderingLoop();

    public:
        Renderer(const WindowContext *window_context, GraphicsContextType api)
            : m_graphics_api(api),
              m_graphics_context(GraphicsContext::create(api, window_context))
        {
            m_window_context = window_context;
        };
        ~Renderer();
        void init();
        void setMaxFps(unsigned int fps);
        void setAPI(GraphicsContextType api);
        void render();
};
} // namespace crystal::graphics