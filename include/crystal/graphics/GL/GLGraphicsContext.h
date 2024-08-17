#include "crystal/graphics/GraphicsAPI.h"
namespace crystal::graphics
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext();
        void begin() override;
        void end() override;
        void setVertexBuffer() override;
        void setIndexBuffer() override;
        ~OpenGLContext();

    };
}