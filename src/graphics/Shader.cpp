#include "crystal/graphics/Shader.h"
#include "crystal/core/Logger.h"
#include <fstream>
#include <filesystem>
#include <string>

namespace crystal::graphics
{
    std::string GetShaderCode(const char* path)
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Shader not found:" + std::string(path));
        }
        std::ifstream stream(path);
        std::string line;
        std::string code;
        while (std::getline(stream, line))
        {
            code += line + "\n";
        }
        logger::Success(code);
        return code;
    };
}