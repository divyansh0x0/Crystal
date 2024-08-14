#include "crystal/core/Shader.h"
#include "glad/glad.h"
#include "crystal/core/Logger.h"
#include <string>

static std::string GetShaderCode(const char *path)
{
    std::ifstream stream(path);
    std::string line;
    std::string code;
    while (std::getline(stream, line))
    {
        code += line + "\n";
    }
    logger::success(code);
    return code;
}
static unsigned int CompileShader(unsigned int type, const char *path)
{
    std::string source = GetShaderCode(path);
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    // TODO error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        throw std::runtime_error((type == GL_VERTEX_SHADER ? std::string("Vertex") : std::string("Fragment")) + "Shader compilation failed " + std::string(message));
    }
    return id;
}
namespace crystal
{
    Shader::Shader(const char *vertex_file, const char *fragment_file)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_file);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_file);
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);
        this->ID = program;
    }
    void Shader::Activate()
    {
        glUseProgram(this->ID);
    }
    void Shader::Delete()
    {
        glDeleteProgram(this->ID);
    }
}