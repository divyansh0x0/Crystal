#include "crystal/graphics/GL/GLShader.h"
#include "crystal/graphics/GL/GLHelper.h"
#include <stdexcept>

#include "glad/glad.h"

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GL_CALL(glShaderSource(id, 1, &src, nullptr));
    GL_CALL(glCompileShader(id));
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GL_CALL(glGetShaderInfoLog(id, length, &length, message));
        throw std::runtime_error((type == GL_VERTEX_SHADER ? std::string("Vertex") : std::string("Fragment")) + "Shader compilation failed " + std::string(message));
    }
    else
    {
        logger::success((type == GL_VERTEX_SHADER ? std::string("Vertex") : std::string("Fragment")) + "Shader compiled");
    }
    return id;
}
namespace crystal::graphics

{

    GLShader::GLShader(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader_code);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_code);
        GL_CALL(glAttachShader(program, vs));
        GL_CALL(glAttachShader(program, fs));
        GL_CALL(glLinkProgram(program));
        GL_CALL(glValidateProgram(program));
        GL_CALL(glDeleteShader(vs));
        GL_CALL(glDeleteShader(fs));
        this->m_ID = program;
    }
    void GLShader::activate()
    {
        GL_CALL(glUseProgram(this->m_ID));
    };
    void GLShader::destroy()
    {
        GL_CALL(glDeleteProgram(this->m_ID));
    };

}