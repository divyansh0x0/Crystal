#pragma once
#include <string>

namespace ktl::graphics
{
    std::string GetShaderCode(const char* path);

    class Shader
    {
        public:
            virtual void bind()   = 0;
            virtual void unbind() = 0;
            virtual ~Shader()     = default;
    };

}; // namespace ktl::graphics