#pragma once
#include "crystal/graphics/WindowContext.h"

namespace crystal::graphics
{
class Renderer
{
    private:
        // GraphicsContext *m_graphics_context   = nullptr;
        // std::thread *m_render_thread          = nullptr;

    public:
        virtual void init(WindowContext& window_context) = 0;
        virtual void destroy()                           = 0;
        virtual void render()                            = 0;
        virtual ~Renderer()                              = default;
};

} // namespace crystal::graphics