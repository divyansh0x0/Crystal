#pragma once
#include "krystal/graphics/Shader.hpp"

namespace platform::gl
{
    class Shader final : public ktl::graphics::Shader
    {
        private:
            unsigned int m_ID;

        public:
            Shader(const char* vertex_shader_code, const char* fragment_shader_code);

            void bind() override;
            void unbind() override;
            ~Shader() override;
    };
} // namespace platform::gl