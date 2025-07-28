#include "krystal/graphics/Graphics.hpp"
#include "platform/gl/Renderer.hpp"

namespace ktl::graphics
{
    Renderer* CreateRenderer( WindowContext* window_context,const API api)
    {
        switch (api)
        {

            case API::OpenGL:
                return new platform::gl::Renderer(window_context);
            case API::Vulkan:
            case API::DirectX:
            default:
                return nullptr;
        }
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
} // namespace ktl::graphics