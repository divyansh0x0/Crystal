#include "crystal/graphics/GL/GLShader.hpp"
#include "crystal/core/Logger.hpp"
#include "crystal/graphics/GL/GLHelper.hpp"

#include "glad/glad.h"

// Helper function to compile OpenGL shader
static unsigned int CompileShader (unsigned int type, const char* src_code)
{
    unsigned int id = glCreateShader (type);
    GL_CALL (glShaderSource (id, 1, &src_code, nullptr));
    GL_CALL (glCompileShader (id));
    int result;
    glGetShaderiv (id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        // get error message
            int length;
            GL_CALL (glGetShaderiv (id, GL_INFO_LOG_LENGTH, &length));
            char* message = new char(length * sizeof (char));
            GL_CALL (glGetShaderInfoLog (id, length, &length, message));

            logger::Error ("OpenGL", (type == GL_VERTEX_SHADER ? std::string ("Vertex") : std::string ("Fragment"))
                                         + " shader compilation failed in following src code because of " + message);
            logger::Error ("OpenGL", src_code);

    }
    else
    {
        logger::Success ("OpenGL", (type == GL_VERTEX_SHADER ? std::string ("Vertex") : std::string ("Fragment"))
                                       + "shader compiled");
    }
    return id;
}

namespace crystal::graphics

{

    GLShader::GLShader (const char* vertex_shader_code, const char* fragment_shader_code)
    {
        unsigned int program = glCreateProgram ();
        unsigned int vs      = CompileShader (GL_VERTEX_SHADER, vertex_shader_code);
        unsigned int fs      = CompileShader (GL_FRAGMENT_SHADER, fragment_shader_code);
        GL_CALL (glAttachShader (program, vs));
        GL_CALL (glAttachShader (program, fs));
        GL_CALL (glLinkProgram (program));
        GL_CALL (glValidateProgram (program));
        GL_CALL (glDeleteShader (vs));
        GL_CALL (glDeleteShader (fs));
        m_ID = program;
    }

    void GLShader::activate ()
    {
        GL_CALL (glUseProgram (m_ID));
    };

    void GLShader::destroy ()
    {
        GL_CALL (glDeleteProgram (m_ID));
    };

} // namespace crystal::graphics