#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include <stdexcept>
#include <chrono>
#include <fstream>
#include <iostream>
float getCurrentTimeMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

static void GlfwErrorCallback(int error, const char *description)
{
    logger::error(description);
}
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
namespace crystal{

Window::Window(std::string name, crystal::Size size, crystal::Color background_color) : m_window_name(name), m_window_size(size), m_background_color(background_color), m_destroy_window_flag(false)
{
    glfwSetErrorCallback(GlfwErrorCallback);
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("GLFW INITIALIZATION FAILED");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    logger::success("GLFW Initialized");

    logger::success("GLAD Initialized");

    this->m_glfw_window = glfwCreateWindow(this->m_window_size.WIDTH, this->m_window_size.HEIGHT, this->m_window_name.data(), NULL, NULL);

    if (!m_glfw_window)
    {
        throw std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(m_glfw_window, FramebufferSizeCallback);
    // create context
    glfwMakeContextCurrent(this->m_glfw_window);
    // glfwSwapInterval(this->b_vsync_ ? 1 : 0);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
    glViewport(0, 0, this->m_window_size.WIDTH, this->m_window_size.HEIGHT);
}
void Window::loop()
{
    // Main loop
    typedef std::chrono::high_resolution_clock Clock;
    float min_frame_time_ms = 1000 / MAX_FPS;
    uint64_t timespent_ms = 0;
    uint64_t frames_rendered = 0;
    float time_accumulated = 0;
    float t1 = glfwGetTime();
    const float MIN_FRAME_DELAY = 1.0 / MAX_FPS;

    this->m_renderer.init();

    while (!m_destroy_window_flag && !glfwWindowShouldClose(this->m_glfw_window))
    {
        float t2 = glfwGetTime();
        float dt = t2 - t1;

        if (dt < MIN_FRAME_DELAY)
            continue;

        // this->render();
       this->m_renderer.render();
        glfwSwapBuffers(this->m_glfw_window);
        glfwPollEvents();

        time_accumulated += dt;
        ++frames_rendered;

        if (time_accumulated >= 1.0)
        {
            this->current_fps = frames_rendered;
            logger::info(std::string("FPS: ") + std::to_string(this->current_fps) + "|Timespent" + std::to_string(time_accumulated));
            time_accumulated = 0;
            frames_rendered = 0;
        }
        t1 = t2;
    }
}


void Window::addComponent()
{
}
uint32_t Window::getCurrentFPS()
{
    return this->current_fps;
}

/**
 * Destroys the window by setting the `b_destroy_window_` flag to true.
 *
 * @throws None
 */
void Window::destroyWindow()
{
    m_destroy_window_flag = true;
}
Window::~Window()
{
    glfwDestroyWindow(this->m_glfw_window);
    glfwTerminate();
    logger::success("Window destroyed");
}
}