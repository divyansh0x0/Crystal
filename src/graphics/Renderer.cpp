#include "crystal/graphics/Renderer.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include <glad/glad.h>
    unsigned int shaderID;

namespace crystal::graphics
{
    Renderer::Renderer()
    {
       
    }
    float r = 0;
    float i = 0.1;
    void Renderer::init(){
         m_graphics_context = GraphicsContext::create(m_graphics_api);

        uint32_t VAO;
        std::string vert_shader = crystal::graphics::GetShaderCode("assets/shaders/vertex.glsl");
        std::string frag_shader = crystal::graphics::GetShaderCode("assets/shaders/fragment.glsl");


        crystal::graphics::GLShader Shader(vert_shader, frag_shader);
        GL_CALL(glGenVertexArrays(1, &VAO));
        GL_CALL(glBindVertexArray(VAO));
        unsigned int buffer;
        float positions[6] = {
            -0.5f, -0.5,
            0.0f, 0.5f,
            0.5f, -0.5f};
        GL_CALL(glGenBuffers(1, &buffer));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW));
        GL_CALL(glEnableVertexAttribArray(0));
        Shader.activate();
        shaderID = Shader.getID();
        GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
        m_initialized_flag = true;
    }
    void Renderer::render()
    {
        if (!m_initialized_flag)
        {
            logger::error("Renderer not initialized");
            return;
        }
        if (r > 1.0f)
            i = -0.1;
        if (r < 0.0f)
            i = 0.1;
        r += i;
        GL_CALL(glUniform4f(glGetUniformLocation(shaderID, "u_Color"), r, 0.3f, 0.8f, 1.0f));

        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    }
    void Renderer::setAPI(GraphicsContextType api)
    {
    }

    Renderer::~Renderer(){

    }
}