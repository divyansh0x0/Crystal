#pragma once
#include <string>
namespace crystal::graphics
{
    std::string GetShaderCode(const char* path);

    class Shader
    {
    public:
        virtual void activate() = 0;
        virtual void destroy() = 0;
    };


};