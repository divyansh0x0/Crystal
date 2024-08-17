#include "crystal/graphics/GraphicsAPI.h"

namespace crystal::graphics
{
    class Renderer
    {
    private:
        GraphicsContextType m_graphics_api = GraphicsContextType::OpenGL;
        GraphicsContext* m_graphics_context;
        bool m_initialized_flag;
    public:
        Renderer();
        ~Renderer();
        void init();
        void setAPI(GraphicsContextType api);
        void render();
    };
}