#include "crystal/graphics/GraphicsAPI.h"
#include "crystal/graphics/GL/GLGraphicsContext.h"

namespace crystal::graphics{

    GraphicsContext* GraphicsContext::create(GraphicsContextType api){
        
        switch(api){
            case GraphicsContextType::OpenGL:
                return new OpenGLContext();
            // case GraphicsContextType::DirectX:
            //     return new DirectXContext();
            // case GraphicsContextType::Vulkan:
            //     return new VulkanContext();
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
}