#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/core/Shader.h"

#include <stdexcept>
#include <chrono>
#include <fstream>
#include <iostream>
float getCurrentTimeMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

static std::string DecodeGLError(GLint error)
{
    switch (error)
    {
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    default:
        return "UNKNOWN ERROR";
    }
}
static void CheckGLError(){
    uint32_t result;
    while ((result = glGetError()) != GL_NO_ERROR)
        logger::error("[OPENGL ERROR]" + DecodeGLError(result) + " in " + __FILE__ + ":" + std::to_string(__LINE__));
}

static void GlfwErrorCallback(int error, const char *description)
{
    logger::error(description);
}
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
crystal::Window::Window(std::string name, crystal::Size size, crystal::Color background_color) : window_name_(name), window_size_(size), background_color_(background_color), b_destroy_window_(false)
{
    glfwSetErrorCallback(GlfwErrorCallback);
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("GLFW INITIALIZATION FAILED");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    logger::success("GLFW Initialized");

    logger::success("GLAD Initialized");

    this->glfw_window_ = glfwCreateWindow(this->window_size_.WIDTH, this->window_size_.HEIGHT, this->window_name_.data(), NULL, NULL);

    if (!glfw_window_)
    {
        throw std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(glfw_window_, FramebufferSizeCallback);
    // create context
    glfwMakeContextCurrent(this->glfw_window_);
    // glfwSwapInterval(this->b_vsync_ ? 1 : 0);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
    glViewport(0, 0, this->window_size_.WIDTH, this->window_size_.HEIGHT);
}
void crystal::Window::loop()
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
    while (!b_destroy_window_ && !glfwWindowShouldClose(this->glfw_window_))
    {
        float t2 = glfwGetTime();
        float dt = t2 - t1;

        if (dt < MIN_FRAME_DELAY)
            continue;

        this->render();
        glfwSwapBuffers(this->glfw_window_);
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

void crystal::Window::init()
{
    uint32_t VAO;
    Shader shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int buffer;
    float positions[6] = {
        -0.5f, -0.5,
        0.0f, 0.5f,
        0.5f, -0.5f};
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    shader.Activate();
}
void crystal::Window::render()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    CheckGLError();
}

void crystal::Window::addComponent()
{
}
uint32_t crystal::Window::getCurrentFPS()
{
    return this->current_fps;
}

/**
 * Destroys the window by setting the `b_destroy_window_` flag to true.
 *
 * @throws None
 */
void crystal::Window::destroyWindow()
{
    b_destroy_window_ = true;
}
crystal::Window::~Window()
{
    glfwDestroyWindow(this->glfw_window_);
    glfwTerminate();
    logger::success("Window destroyed");
}
