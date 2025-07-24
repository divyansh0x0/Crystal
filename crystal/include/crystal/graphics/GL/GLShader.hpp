#include "crystal/graphics/Shader.hpp"

namespace crystal::graphics
{
    class GLShader final : public Shader
    {
        private:
            unsigned int m_ID;

        public:
            GLShader (const char* vertex_shader_code, const char* fragment_shader_code);

            void activate () override;
            void destroy () override;

            [[nodiscard]] unsigned int getID () const { return m_ID; }
    };
} // namespace crystal::graphics