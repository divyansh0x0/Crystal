#include "crystal/graphics/Renderer.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include <glad/glad.h>

#include <cassert>
#include <chrono>
#include <cstdint>

#define LENGTH_OF(x) (sizeof(x) / sizeof(x[0]))
unsigned int shaderID;
static inline uint64_t getCurrentTimeNanos()
{
    return std::chrono::steady_clock::now().time_since_epoch().count();
}
struct vertex
{
        float x;
        float y;
};

namespace crystal::graphics
{
void Renderer::renderingLoop()
{
    m_graphics_context->init();

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
    uint32_t VAO;

    const char *frag = "#version 330 core\n"
                       "layout(location = 0) out vec4 color;\n"
                       "uniform vec4 u_Color;\n"
                       "void main(){\n"
                       "    color = u_Color;\n"
                       "}";
    const char *vert = "#version 330 core\n"
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
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2,
                         vertex_buffer_data, GL_STATIC_DRAW));
    // Bind position attribute
    GL_CALL(glEnableVertexAttribArray(0));

    GL_CALL(
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    // Generate and ind index buffer
    GL_CALL(glGenBuffers(1, &index_buffer_id));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id));

    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 4 * 2,
                         index_buffer_data, GL_STATIC_DRAW));
    my_shader.activate();
    shaderID = my_shader.getID();

    uint64_t timespent_nanos     = 0;
    uint64_t frames_rendered     = 0;
    uint64_t one_second_in_nanos = 1000'000'000;

    uint64_t t1 = getCurrentTimeNanos();
    if (!m_initialized_flag.load())
    {
        logger::Error(
            "Renderer",
            "Renderer not initialized. Initialize the renderer first");
        return;
    }
    logger::Success("Renderer", "Begining rendering loop");

    while (!m_destroyed_flag.load())
    {
        uint64_t t2 = getCurrentTimeNanos();
        uint64_t dt = t2 - t1;

        if (dt < one_second_in_nanos / m_max_fps)
        {
            continue;
        }
        render();
        timespent_nanos += dt;
        ++frames_rendered;
        if (timespent_nanos >= one_second_in_nanos)
        {
            // logger::Info(std::string("FPS: ") +
            // std::to_string(frames_rendered)
            //              + " | Timespent: " + std::to_string(timespent_nanos)
            //              + "ns");
            current_fps     = frames_rendered;
            timespent_nanos = 0;
            frames_rendered = 0;
        }
        m_window_context->swapBuffers();
        t1 = t2;
    }
    logger::Info("Renderer", "rendering loop ended");

    m_graphics_context->dispose();
}

float r = 0;
float i = 0.1;

void Renderer::init()
{
    m_initialized_flag = true;

    m_render_thread = new std::thread(&Renderer::renderingLoop, this);
}
void Renderer::render()
{
    if (r > 1.0f) i = -0.1;
    if (r < 0.0f) i = 0.1;
    r += i;

    crystal::layout::Size framebuffer_size =
        m_window_context->getFrameBufferSize();
    GL_CALL(glViewport(0, 0, framebuffer_size.width, framebuffer_size.height));
    GL_CALL(glUniform4f(glGetUniformLocation(shaderID, "u_Color"), r, 0.3f,
                        0.8f, 1.0f));

    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    // GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
}

Renderer::~Renderer()
{
    logger::Warn("Renderer", "Destroying renderer");

    m_destroyed_flag = true;
    m_render_thread->join();
    delete m_render_thread;
    delete m_graphics_context;
    m_window_context = nullptr;
    m_render_thread  = nullptr;
    m_graphics_context= nullptr;
    logger::Info("Renderer", "Deleted rendering thread");

    logger::Info("Renderer", "Renderer destroyed");
}
} // namespace crystal::graphics