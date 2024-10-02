#pragma once
#include "crystal/graphics/Renderer.h"
namespace crystal::graphics
{
enum class API
{
    OpenGL  = 0,
    Vulkan  = 1,
    DirectX = 2
};
Renderer *CreateRenderer(API api);

// class GraphicsContext
// {
//     public:
//         virtual void init()            = 0;
//         virtual void begin()           = 0;
//         virtual void end()             = 0;
//         virtual void setVertexBuffer() = 0;
//         virtual void setIndexBuffer()  = 0;
//         virtual void dispose()         = 0;
//         virtual ~GraphicsContext()     = default;
//         static GraphicsContext *create(API api,
//                                        const WindowContext *window_context);

//     protected:
//         GraphicsContext()                             = default;
//         GraphicsContext(const GraphicsContext &other) = default;
// };
/**Returns a renderer based on the API used. Must be deleted after use */

// class DirectXContext : public GraphicsContext
// {
//     void begin() override;
//     void end() override;
//     void setVertexBuffer() override;
//     void setIndexBuffer() override;
// };
// class VulkanContext : public GraphicsContext
// {
//     void begin() override;
//     void end() override;
//     void setVertexBuffer() override;
//     void setIndexBuffer() override;
// };
} // namespace crystal::graphics
