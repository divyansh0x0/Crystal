#include "crystal/graphics/Shader.h"

namespace crystal::graphics{
    class GLShader:public Shader{
        private:
        unsigned int m_ID;

    public:
        GLShader(const std::string& vertex_shader_code,const std::string& fragment_shader_code);

        void activate() override;
        void destroy() override;

        unsigned int getID(){return m_ID;}
    };
}