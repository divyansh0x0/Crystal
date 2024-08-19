#include "crystal/graphics/Renderer.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include <chrono>
#include <glad/glad.h>
unsigned int shaderID;

static uint64_t getCurrentTimeMicros()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
namespace crystal::graphics
{
    void Renderer::renderingLoop()
    {
        m_context_manager->switchContextToCurrentThread();
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            logger::Error("Failed to initialize GLAD");
        else
            logger::Success("GLAD Initialized");

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
        uint64_t timespent_micros = 0;
        uint64_t frames_rendered = 0;
        uint64_t one_second_in_micros = 1000'000;
        // double min_frame_time_micros =  one_second_in_micros / m_max_fps;
       
        uint64_t time_accumulated_micros = 0;
        uint64_t t1 = getCurrentTimeMicros();
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
                continue;
            render();
            timespent_micros += dt;
            ++frames_rendered;
            if (timespent_micros >= one_second_in_micros)
            {
                logger::Info(std::string("FPS: ") + std::to_string(frames_rendered) + " | Timespent: " + std::to_string(timespent_micros) + "microsecond");
                current_fps = frames_rendered;
                timespent_micros = 0;
                frames_rendered = 0;
            }
            m_context_manager->swapBuffers();
            t1 = t2;
        }
        logger::Info(logger::LogType::DESTRUCTION,"rendering loop ended");
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
        if (r > 1.0f)
            i = -0.1;
        if (r < 0.0f)
            i = 0.1;
        r += i;
        crystal::layout::Size framebuffer_size = m_context_manager->getFrameBufferSize();
        GL_CALL(glViewport(0, 0, framebuffer_size.width, framebuffer_size.height));
        GL_CALL(glUniform4f(glGetUniformLocation(shaderID, "u_Color"), r, 0.3f, 0.8f, 1.0f));

        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    }


    Renderer::~Renderer()
    {
        logger::Warn(logger::LogType::DESTRUCTION, "Destroying renderer");

        m_destroyed_flag = true;
        m_render_thread->join();
        delete m_render_thread;
        logger::Success(logger::LogType::DESTRUCTION, "Deleted rendering thread");
        delete m_graphics_context;
        logger::Success(logger::LogType::DESTRUCTION, "Deleted graphics context");

        logger::Success(logger::LogType::DESTRUCTION, "Renderer destroyed");
    }
}