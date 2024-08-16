#include "crystal/graphics/Shader.h"
#include "crystal/core/Logger.h"
#include <fstream>
#include <filesystem>

namespace crystal::graphics
{
    std::string GetShaderCode(const std::string &path)
    {
        if (!std::filesystem::exists(path))
        {
            throw std::runtime_error("Shader not found:" + path);
        }
        std::ifstream stream(path);
        std::string line;
        std::string code;
        while (std::getline(stream, line))
        {
            code += line + "\n";
        }
        logger::success(code);
        return code;
    };
}