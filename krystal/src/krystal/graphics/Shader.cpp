#include "krystal/graphics/Shader.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include "krystal/core/Logger.hpp"

namespace ktl::graphics
{
    std::string GetShaderCode (const char* path)
    {
        if (!std::filesystem::exists (path))
        {
            logger::Error ("Shader not found:" + std::string (path));
            return "";
        }
        std::ifstream stream (path);
        std::string   line;
        std::string   code;
        while (std::getline (stream, line))
        {
            code += line + "\n";
        }
        return code;
    };
} // namespace ktl::graphics