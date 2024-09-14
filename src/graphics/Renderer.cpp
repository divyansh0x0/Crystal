#include <glad/glad.h>
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include "crystal/graphics/Renderer.h"

#include <cassert>
#include <chrono>
#include <cstdint>

#define LENGTH_OF(x) (sizeof(x) / sizeof(x[0]))
unsigned int shaderID;
struct vertex
{
    float x;
    float y;
};
static uint64_t getCurrentTimeMicros()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
}
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

    std::string vert_shader = crystal::graphics::GetShaderCode(
        "assets/shaders/vertex.glsl");
    std::string frag_shader = crystal::graphics::GetShaderCode(
        "assets/shaders/fragment.glsl");

    crystal::graphics::GLShader Shader(vert_shader.c_str(),
                                       frag_shader.c_str());

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
    Shader.activate();
    shaderID = Shader.getID();

    uint64_t timespent_micros     = 0;
    uint64_t frames_rendered      = 0;
    uint64_t one_second_in_micros = 1000'000;

    uint64_t time_accumulated_micros = 0;
    uint64_t t1                      = getCurrentTimeMicros();
    if (!m_initialized_flag.load())
    {
        logger::Error("Renderer not initialized");
        return;
    }
    logger::Success("rendering loop started");

    while (!m_destroyed_flag.load())
    {
        uint64_t t2 = getCurrentTimeMicros();
        uint64_t dt = t2 - t1;

        if (dt < one_second_in_micros / m_max_fps)
        {
            continue;
        }
        render();
        timespent_micros += dt;
        ++frames_rendered;
        if (timespent_micros >= one_second_in_micros)
        {
            logger::Info(std::string("FPS: ") + std::to_string(frames_rendered)
                         + " | Timespent: " + std::to_string(timespent_micros)
                         + "microsecond");
            current_fps      = frames_rendered;
            timespent_micros = 0;
            frames_rendered  = 0;
        }
        m_window_context->swapBuffers();
        t1 = t2;
    }
    logger::Info("Destroying Renderer", "rendering loop ended");
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
    logger::Warn("Destroying Renderer", "Destroying renderer");

    m_destroyed_flag = true;
    m_render_thread->join();
    delete m_render_thread;
    logger::Success("Destroying Renderer", "Deleted rendering thread");
    delete m_graphics_context;
    logger::Success("Destroying Renderer", "Deleted graphics context");

    logger::Success("Destroying Renderer", "Renderer destroyed");
}
} // namespace crystal::graphics