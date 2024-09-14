#include "crystal/core/Window.h"
#include "crystal/graphics/GraphicsAPI.h"
#include "crystal/layout/Size.h"
#include "crystal/graphics/ApiContextManager.h"
#include <thread>
#include <atomic>

namespace crystal::graphics
{
    class Renderer
    {
    private:
        ApiContextManager* m_context_manager;
        GraphicsContextType m_graphics_api = GraphicsContextType::OpenGL;
        GraphicsContext* m_graphics_context;
        std::thread* m_render_thread;
        unsigned int m_max_fps = 120;
        unsigned int current_fps = 0;
        std::atomic<bool> m_initialized_flag = false;
        std::atomic<bool> m_destroyed_flag = false;
        Renderer();
        void renderingLoop();
    public:
        Renderer(ApiContextManager* context_manager, GraphicsContextType api = GraphicsContextType::OpenGL):m_context_manager(context_manager), m_graphics_api(api), m_graphics_context(GraphicsContext::create(api)){};
        ~Renderer();
        void init();
        void setMaxFps(unsigned int fps);
        void setAPI(GraphicsContextType api);
        void render();
    };
}