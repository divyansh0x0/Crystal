#include "platform/gl/Shader.hpp"
#include "krystal/core/Logger.hpp"
#include "platform/gl/Helper.hpp"

#include "glad/glad.h"

// Helper function to compile OpenGL shader
static unsigned int CompileShader(unsigned int type, const char* src_code)
{
    unsigned int id = glCreateShader(type);
    GL_CALL(glShaderSource(id, 1, &src_code, nullptr));
    GL_CALL(glCompileShader(id));
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        // get error message
        int length;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = new char(length * sizeof(char));
        GL_CALL(glGetShaderInfoLog(id, length, &length, message));

        logger::Error("OpenGL", (type == GL_VERTEX_SHADER ? std::string("Vertex") : std::string("Fragment"))
                                    + " shader compilation failed in following src code because of " + message);
        logger::Error("OpenGL", src_code);
        return -1;
    }
    logger::Success("OpenGL",
                    (type == GL_VERTEX_SHADER ? std::string("Vertex") : std::string("Fragment")) + "shader compiled");
    return id;
}

namespace platform::gl
{
    Shader::Shader(const char* vertex_shader_code, const char* fragment_shader_code)
    {
        const unsigned int program = glCreateProgram();
        const unsigned int vs      = CompileShader(GL_VERTEX_SHADER, vertex_shader_code);
        const unsigned int fs      = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_code);
        GL_CALL(glAttachShader(program, vs));
        GL_CALL(glAttachShader(program, fs));
        GL_CALL(glLinkProgram(program));
        GL_CALL(glValidateProgram(program));
        GL_CALL(glDeleteShader(vs));
        GL_CALL(glDeleteShader(fs));
        m_ID = program;
    }

    void Shader::bind()
    {
        GL_CALL(glUseProgram(m_ID));
    };

    void Shader::unbind()
    {
        GL_CALL(glUseProgram(0));
    };

    Shader::~Shader()
    {
        logger::Success("OpenGL", "Shader destroyed");
    };

} // namespace platform::gl