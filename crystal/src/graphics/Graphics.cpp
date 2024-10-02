#include "crystal/graphics/Graphics.h"
#include "crystal/graphics/GL/GLRenderer.h"
namespace crystal::graphics
{
Renderer* CreateRenderer(API api)
{
    switch (api)
    {

    case API::OpenGL:   
    case API::Vulkan:
    case API::DirectX:
        return new GLRenderer();
    }
    return nullptr;
}

// /*****************************************************************************/
//                             // DIRECTX CONTEXT
// /*****************************************************************************/
// DirectXContext::DirectXContext(){
// }
// void DirectXContext::begin(){

// }
// void DirectXContext::end(){

// }
// void DirectXContext::setVertexBuffer(){

// }
// void DirectXContext::setIndexBuffer(){

// }
// /*****************************************************************************/
//                             // VULKAN CONTEXT
// /*****************************************************************************/
// VulkanContext::VulkanContext(){
// }
// void DirectXContext::begin(){

// }
// void VulkanContext::end(){

// }
// void VulkanContext::setVertexBuffer(){

// }
// void VulkanContext::setIndexBuffer(){

// }
} // namespace crystal::graphics