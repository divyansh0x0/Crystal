#include "crystal/graphics/GraphicsAPI.h"
#include "crystal/graphics/WindowContext.h"
namespace crystal::graphics
{
class OpenGLContext : public GraphicsContext
{

    private:
        const WindowContext *m_window_context;

    public:
        OpenGLContext(const WindowContext *window_context);
        void init() override;
        void begin() override;
        void end() override;
        void setVertexBuffer() override;
        void setIndexBuffer() override;
        void dispose() override;
        ~OpenGLContext();
};
} // namespace crystal::graphics