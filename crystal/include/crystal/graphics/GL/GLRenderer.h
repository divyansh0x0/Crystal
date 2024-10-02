#include "crystal/graphics/Renderer.h"

namespace crystal::graphics
{

class GLRenderer : public Renderer
{
    public:
        GLRenderer() {};
        void init(WindowContext& window_context) override;
        void destroy() override;
        void render() override;
        ~GLRenderer();

    private:
        const WindowContext* m_window_context = nullptr;

        bool m_initialized_flag = false;
        bool m_destroyed_flag   = false;
};
} // namespace crystal::graphics