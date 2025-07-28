#include "platform/gl/Helper.hpp"

#include "krystal/core/Logger.hpp"

#include "glad/glad.h"

static std::string DecodeGLError(const GLenum error)
{
    switch (error)
    {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        default:
            return "UNKNOWN ERROR " + std::to_string(error);
    }
}

namespace platform::gl
{


    void CheckGLError(const char* file, int line, const char* expr)
    {
        if (const GLenum error = glGetError(); error != GL_NO_ERROR)
        {
            logger::Error("[OpenGL Error] (" + DecodeGLError(error) + ") " + "at " + file + ":" + std::to_string(line)
                          + " -> " + expr + "\n");
        }
    }


} // namespace platform::gl
