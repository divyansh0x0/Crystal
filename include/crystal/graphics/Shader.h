#pragma once
#include <string>
namespace crystal::graphics
{
    std::string GetShaderCode(const std::string &path);

    class Shader
    {
    public:
        virtual void activate() = 0;
        virtual void destroy() = 0;
    };

    class GLShader:public Shader{
        private:
        unsigned int m_ID;

    public:
        GLShader(const std::string& vertex_shader_code,const std::string& fragment_shader_code);

        void activate() override;
        void destroy() override;

        unsigned int getID(){return m_ID;}
    };

};