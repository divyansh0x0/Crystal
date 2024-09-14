#include "crystal/graphics/GraphicsAPI.h"
#include "crystal/graphics/GL/GLGraphicsContext.h"
#include "crystal/graphics/WindowContext.h"

namespace crystal::graphics{

    GraphicsContext* GraphicsContext::create(GraphicsContextType api,const WindowContext* context){
        
        switch(api){
            case GraphicsContextType::OpenGL:
                return new OpenGLContext(context);
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