#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLGraphicsContext.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include "crystal/graphics/WindowContext.h"

#include <glad/glad.h>

namespace crystal::graphics
{

/*****************************************************************************/
// OPENGL CONTEXT
/*****************************************************************************/
OpenGLContext::OpenGLContext(const WindowContext *window_context)
{
    if (window_context == nullptr)
    {
        logger::Error("Window context cannot be null");
        return;
    }
    m_window_context = window_context;

}
void OpenGLContext::init()
{
    logger::Success("OpenGL graphics context initialized");
    m_window_context->switchContextToCurrentThread();
    if (!gladLoadGLLoader((GLADloadproc)m_window_context->getGLLoadProc()))
    {
        logger::Error("Failed to initialize GLAD");
        return;
    }
    else
        logger::Success("GLAD Initialized");

    std::string vert_shader = crystal::graphics::GetShaderCode(
        "assets/shaders/vertex.glsl");
    std::string frag_shader = crystal::graphics::GetShaderCode(
        "assets/shaders/fragment.glsl");

    crystal::graphics::GLShader Shader(vert_shader.c_str(),
                                       frag_shader.c_str());
    Shader.activate();
    logger::Success("shader activated");
}
void OpenGLContext::begin() {}
void OpenGLContext::end() {}
void OpenGLContext::setVertexBuffer() {}
void OpenGLContext::setIndexBuffer() {}
void OpenGLContext::dispose()
{
    m_window_context->detachContextFromCurrentThread();
    m_window_context = nullptr;
    logger::Success("OpenGL graphics context destroyed");
}
OpenGLContext::~OpenGLContext()
{
    dispose();
}
} // namespace crystal::graphics