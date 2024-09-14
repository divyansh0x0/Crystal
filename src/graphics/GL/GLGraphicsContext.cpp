#include <glad/glad.h>
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLGraphicsContext.h"
#include "crystal/graphics/GL/GLShader.h"

namespace crystal::graphics
{

    /*****************************************************************************/
    // OPENGL CONTEXT
    /*****************************************************************************/
    OpenGLContext::OpenGLContext()
    {
        logger::Success("OpenGL graphics context created");
        
    }
    void OpenGLContext::begin()
    {
    }
    void OpenGLContext::end()
    {
    }
    void OpenGLContext::setVertexBuffer()
    {

    }
    void OpenGLContext::setIndexBuffer()
    {
    }
    OpenGLContext::~OpenGLContext()
    {
        
    }
}