#include "crystal/graphics/GL/GLRenderer.hpp"
#include <glad/glad.h>
#include "crystal/core/Logger.hpp"
#include "crystal/graphics/GL/GLHelper.hpp"
#include "crystal/graphics/GL/GLShader.hpp"


#include <cassert>
#include <cstdint>

#define LENGTH_OF(x) (sizeof(x) / sizeof(x[0]))
unsigned int shaderID;
        uint32_t VAO_ID; // Once it is created and contains all the data, we can bind it to the context anytime we want
                         // to draw something with this configuration;

namespace crystal::graphics
{
    struct a
    {
            float x;
            float y;
    };

    void GLRenderer::init()
    {
        if (!gladLoadGLLoader(m_window_context->getGLLoadProc()))
        {
            logger::Error("GLAD", "Failed to initialize GLAD");
            return;
        }
        else
            logger::Success("GLAD", "GLAD Initialized");
        m_initialized_flag = true;
        m_destroyed_flag   = false;

        uint32_t VBO_ID;          // vertex buffer object is a buffer containing all the vertices
        uint32_t index_buffer_id; // A buffer containing the instructions on which corners connect to make triangles.


        // A VAO is like a container that "remembers" all the state settings related to your vertex data.
        //  This includes which VBOs are bound, how the vertex attributes (like position, color, texture coordinates)
        //  are configured (using glVertexAttribPointer),
        // and which index buffer is bound.
        //  By binding a VAO, you can restore a whole set of vertex data configurations with a single command.


        // float vertex_buffer_data[] = {-0.5f, -0.5f, 0.5f,  -0.5f,       0.5, 0.5,
        // 0.5,   0.5,   -0.5f, 0.5f, - 0.5f, -0.5f};
        float vertex_buffer_data[] = {
            -0.5f,
            -0.5f, // x1 y1 (bottom left)
            0.5f,
            -0.5f, // x2,y2 (top left)
            0.5,
            0.5,   // x3,y3 (top right)
            -0.5f,
            0.5f,  // x4,y4 (bottom right)

        };
        const uint32_t index_buffer_data[] = {0, 1, 2, 2, 3, 0};

        const auto                  frag = "#version 330 core\n"
                                           "layout(location = 0) out vec4 color;\n"
                                           "uniform vec4 u_Color;\n"
                                           "void main(){\n"
                                           "    color = u_Color;\n"
                                           "}";
        const auto                  vert = "#version 330 core\n"
                                           "layout(location = 0) in vec4 a_position;\n"
                                           "uniform mat4 u_Transform;\n"
                                           "void main() {\n"
                                           "gl_Position = u_Transform * a_position;\n"
                                           "}\n";
        crystal::graphics::GLShader my_shader(vert, frag);

        GL_CALL(glGenVertexArrays(1, &VAO_ID));
        glBindVertexArray(VAO_ID);

        // Generate a bufferto store vertices
        GL_CALL(glGenBuffers(1, &VBO_ID));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO_ID));

        // Copy vertex data to buffer, the original data is not needed anymore
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, vertex_buffer_data, GL_STATIC_DRAW));

        // Bind position attribute
        GL_CALL(glEnableVertexAttribArray(0)); // By default it is disabled so we enable it
        // because position has location 0 thats why index is 0
        const int position_attrib_index = 0;
        const int vertex_size           = 2; // only x and y coordinates
        GL_CALL(glVertexAttribPointer(position_attrib_index, vertex_size, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        // Generate and bind index buffer
        GL_CALL(glGenBuffers(1, &index_buffer_id));
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id));

        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW));
        my_shader.activate();
        shaderID = my_shader.getID();
    }

    float r = 0;
    float i = 0.1;

    void GLRenderer::render()
    {
       // glBindVertexArray(VAO_ID);
        if (r > 1.0f) i = -0.01;
        if (r < -1.0f) i = 0.01;
        r += i;

        crystal::geometry::Size framebuffer_size = m_window_context->getFrameBufferSize();
        GL_CALL(glViewport(0, 0, framebuffer_size.width, framebuffer_size.height));
        const auto color_attr = glGetUniformLocation(shaderID, "u_Color");
        if (color_attr == -1) {
            logger::Error("Shader", "u_Color uniform not found");
        }
        GL_CALL(glUniform4f(color_attr, r, 0.3f, 0.8f, 0.5f));
        float transform[16] = {
            1.0f, 0.0f, 0.0f, 0.0f, // column 1
            0.0f, 1.0f, 0.0f, 0.0f, // column 2
            0.0f, 0.0f, 1.0f, 0.0f, // column 3
            r,    0.0f, 0.0f, 1.0f  // column 4: translation
        };
        auto transform_location = glGetUniformLocation(shaderID, "u_Transform");
        GL_CALL(glUniformMatrix4fv(transform_location, 1, GL_FALSE, transform));
        auto bg = m_window_context->getFrameBufferBg().getRGBA();
        GL_CALL(glClearColor(bg.r, bg.g, bg.b, bg.a));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        // GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
    }

    void GLRenderer::destroy()
    {
        if (m_destroyed_flag) return;

        m_destroyed_flag   = true;
        m_initialized_flag = false;
        logger::Info("Renderer", "Renderer destroyed");
    }

    GLRenderer::~GLRenderer()
    {
        this->GLRenderer::destroy();
    }
} // namespace crystal::graphics