#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/core/Shader.h"
#include "crystal/graphics/GLHelper.h"
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


namespace crystal
{
    Window::Window(std::string name, Size size, Color background_color) : m_window_name(name), m_window_size(size), m_background_color(background_color), m_destroy_window_flag(false)
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

        glfwSetWindowUserPointer(m_glfw_window, this);
        glfwSetFramebufferSizeCallback(m_glfw_window, [](GLFWwindow *window, int width, int height)
                                       {
            Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (instance) {
                instance->windowResizedCallback(width, height);
            } });
        glfwSetWindowRefreshCallback(m_glfw_window,
                                     [](GLFWwindow *window)
                                     {
                                    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
                                    if (instance) {
                                        instance->render();

    } });
        // create context
        glfwMakeContextCurrent(this->m_glfw_window);
        // glfwSwapInterval(this->b_vsync_ ? 1 : 0);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");
        glViewport(0, 0, this->m_window_size.WIDTH, this->m_window_size.HEIGHT);
    }
    void Window::windowResizedCallback(int width, int height)
    {
        glViewport(0, 0, width, height);
        logger::success("Window resized " + std::to_string(width) + "x" + std::to_string(height) + "from" + std::to_string(this->m_window_size.WIDTH) + "x" + std::to_string(this->m_window_size.HEIGHT));
        this->m_window_size.changeTo(width, height);
        this->render();
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

        this->init();
        while (!m_destroy_window_flag && !glfwWindowShouldClose(this->m_glfw_window))
        {
            float t2 = glfwGetTime();
            float dt = t2 - t1;

            if (dt < MIN_FRAME_DELAY)
                continue;

            this->render();
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

    int u_Color = -1;
    void Window::init()
    {
        uint32_t VAO;
        Shader shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

        unsigned int buffer;
        float positions[6] = {
            -0.5f, -0.5,
            0.0f, 0.5f,
            0.5f, -0.5f};

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        shader.Activate();

        u_Color = glGetUniformLocation(shader.ID, "u_Color");
    }
    float r = 0;
    float i = 0.01;
    void Window::render()
    {
        if (u_Color != -1)
        {
            glUniform4f(u_Color, r, 0.3f, 0.8f, 1.0f);
        }
        if (r > 1)
        {
            i = -0.01;
        }
        else if (r < 0)
        {
            i = 0.01;
        }
        r += i;
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
        glFinish();
        glfwSwapBuffers(this->m_glfw_window);
    }

    void Window::addComponent()
    {
    }
    uint32_t Window::getCurrentFPS()
    {
        return this->current_fps;
    }

    /**
     * Destroys the window by setting the `m_destroy_window_flag` flag to true.
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