#include "crystal/graphics/GraphicsAPI.h"

namespace crystal::graphics
{
    class Renderer
    {
    private:
        GraphicsAPI api = GraphicsAPI::OpenGL;

    public:
        void Init();
    };
}