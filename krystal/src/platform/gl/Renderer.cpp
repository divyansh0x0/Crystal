#include "platform/gl/Renderer.hpp"
#include <glad/glad.h>
#include "krystal/core/Logger.hpp"
#include "platform/gl/Helper.hpp"
#include "platform/gl/Shader.hpp"


#include <cassert>
#include <cstdint>

#include "krystal/graphics/GraphicsFactory.hpp"

#include "platform/gl/Buffer.hpp"

#define LENGTH_OF(x)            (sizeof(x) / sizeof(x[0]))
#define REQUIRES_INITIALIZATION assert(m_initialized_flag && "Renderer not initialized")
        uint32_t VAO_ID;

unsigned int shaderID;

namespace platform::gl
{
    void Renderer::init()
    {
        if (!gladLoadGLLoader(this->m_window_context->getGLLoadProc()))
        {
            logger::Error("GLAD", "Failed to initialize GLAD");
            return;
        }
        logger::Success("GLAD", "GLAD Initialized");
        m_initialized_flag = true;
        m_destroyed_flag   = false;

        GLfloat vertex_buffer_data[] = {
            -0.5f, -0.5f, // Bottom left
            0.5f,  -0.5f, // Bottom right
            0.5f,  0.5f,  // Top right
            -0.5f, 0.5f   // Top left
        };

        const GLuint index_buffer_data[] = {0, 1, 2, 2, 3, 0};

        const auto frag = "#version 330 core\n"
                          "layout(location = 0) out vec4 color;\n"
                          "void main() { color = vec4(1.0, 0.0, 0.0, 1.0); }";

        const auto vert = "#version 330 core\n"
                          "layout(location = 0) in vec4 a_position;\n"
                          "void main() { gl_Position = a_position; }";

        // Create and bind VAO
        GL_CALL(glGenVertexArrays(1, &VAO_ID));
        GL_CALL(glBindVertexArray(VAO_ID));

        // Now create and bind vertex buffer BEFORE setting vertex attributes
        m_vertex_buffer = std::make_unique<VertexBuffer>(vertex_buffer_data, sizeof(vertex_buffer_data));

        // Set vertex attribute pointer
        constexpr int position_attrib_index = 0;
        constexpr int vertex_size           = 2; // x and y only
        GL_CALL(glEnableVertexAttribArray(position_attrib_index));
        GL_CALL(glVertexAttribPointer(position_attrib_index, vertex_size, GL_FLOAT, GL_FALSE,
                                      vertex_size * sizeof(float), nullptr));

        // Create and bind index buffer
        m_index_buffer = std::make_unique<IndexBuffer>(index_buffer_data, std::size(index_buffer_data));
        // Create and store the shader
        m_shader = std::make_unique<Shader>(vert, frag);
        m_shader->bind();
    }

    void Renderer::render()
    {
        ktl::geometry::Size framebuffer_size = m_window_context->getFrameBufferSize();
        GL_CALL(glViewport(0, 0, framebuffer_size.width, framebuffer_size.height));
        auto bg = m_window_context->getFrameBufferBg().getRGBA();
        GL_CALL(glClearColor(bg.r, bg.g, bg.b, bg.a));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        GL_CALL(glBindVertexArray(VAO_ID));
        GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        // GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
    }

    void Renderer::destroy()
    {
        if (m_destroyed_flag) return;

        m_vertex_buffer.reset();
        m_index_buffer.reset();
        m_shader.reset();


        m_destroyed_flag   = true;
        m_initialized_flag = false;
    }

    Renderer::~Renderer()
    {
        this->Renderer::destroy();
        logger::Info("Renderer", "Renderer destroyed");
    }
} // namespace platform::gl