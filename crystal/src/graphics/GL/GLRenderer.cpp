#include "crystal/graphics/GL/GLRenderer.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include <glad/glad.h>

#include <cassert>
#include <cstdint>

#define LENGTH_OF(x) (sizeof(x) / sizeof(x[0]))
unsigned int shaderID;

namespace crystal::graphics
{
struct a
{
        float x;
        float y;
};
void GLRenderer::init(WindowContext& window_context)
{

    m_window_context = &window_context;
    m_window_context->switchContextToCurrentThread();
    if (!gladLoadGLLoader((GLADloadproc) m_window_context->getGLLoadProc()))
    {
        logger::Error("GLAD", "Failed to initialize GLAD");
        return;
    }
    else
        logger::Success("GLAD", "GLAD Initialized");
    m_initialized_flag = true;
    m_destroyed_flag   = false;

    unsigned int array_buffer_id;
    unsigned int index_buffer_id;

    // float vertex_buffer_data[] = {-0.5f, -0.5f, 0.5f,  -0.5f,       0.5, 0.5,
    // 0.5,   0.5,   -0.5f, 0.5f, - 0.5f, -0.5f};
    float vertex_buffer_data[] = {
    -0.5f, -0.5f, // x1 y1
    0.5f,  -0.5f, // x2,y2
    0.5,   0.5,   // x3,y3
    -0.5f, 0.5f,  // x4,y4
    };
    unsigned int index_buffer_data[] = {0, 1, 2, 2, 3, 0};
    uint32_t     VAO;

    const char* frag = "#version 330 core\n"
                       "layout(location = 0) out vec4 color;\n"
                       "uniform vec4 u_Color;\n"
                       "void main(){\n"
                       "    color = u_Color;\n"
                       "}";
    const char* vert = "#version 330 core\n"
                       "layout(location = 0) in vec4 a_position;\n"

                       "void main() {\n"
                       "gl_Position = a_position;\n"
                       "}\n";
    crystal::graphics::GLShader my_shader(vert, frag);

    GL_CALL(glGenVertexArrays(1, &VAO));
    GL_CALL(glBindVertexArray(VAO));

    // Generate buffer and bind it to array buffer
    GL_CALL(glGenBuffers(1, &array_buffer_id));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, array_buffer_id));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, vertex_buffer_data, GL_STATIC_DRAW));
    // Bind position attribute
    GL_CALL(glEnableVertexAttribArray(0));

    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    // Generate and ind index buffer
    GL_CALL(glGenBuffers(1, &index_buffer_id));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id));

    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 4 * 2, index_buffer_data, GL_STATIC_DRAW));
    my_shader.activate();
    shaderID = my_shader.getID();
}
float r = 0;
float i = 0.1;

void GLRenderer::render()
{
    if (r > 1.0f) i = -0.1;
    if (r < 0.0f) i = 0.1;
    r += i;

    crystal::layout::Size framebuffer_size = m_window_context->getFrameBufferSize();
    GL_CALL(glViewport(0, 0, framebuffer_size.width, framebuffer_size.height));
    GL_CALL(glUniform4f(glGetUniformLocation(shaderID, "u_Color"), r, 0.3f, 0.8f, 1.0f));

    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    // GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void GLRenderer::destroy()
{
    if (m_destroyed_flag) return;

    m_destroyed_flag   = true;
    m_initialized_flag = false;
    if (m_window_context)
    {
        m_window_context->detachContextFromCurrentThread();
        m_window_context = nullptr;
    }

    logger::Info("Renderer", "Renderer destroyed");
}
GLRenderer::~GLRenderer()
{
    this->destroy();
}
} // namespace crystal::graphics