#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/Shader.h"
#include <stdexcept>
#include <chrono>
#include <fstream>
#include <iostream>
float getCurrentTimeMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

// static unsigned int CompileShader(unsigned int type, const std::string file)
// {
//     std::string source = GetShaderCode(file);
//     unsigned int id = glCreateShader(type);
//     const char *src = source.c_str();
//     glShaderSource(id, 1, &src, nullptr);
//     glCompileShader(id);
//     // TODO error handling
//     int result;
//     glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//     if (!result)
//     {
//         int length;
//         glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//         char *message = (char *)alloca(length * sizeof(char));
//         glGetShaderInfoLog(id, length, &length, message);
//         throw std::runtime_error((type == GL_VERTEX_SHADER ? std::string("Vertex") : std::string("Fragment")) + "Shader compilation failed " + std::string(message));
//     }
//     return id;
// // }
// static unsigned int CreateShader(const std::string vert_shader, const std::string frag_shader)
// {
//     unsigned int program = glCreateProgram();
//     unsigned int vs = CompileShader(GL_VERTEX_SHADER, vert_shader);
//     unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, frag_shader);
//     glAttachShader(program, vs);
//     glAttachShader(program, fs);
//     glLinkProgram(program);
//     glValidateProgram(program);
//     glDeleteShader(vs);
//     glDeleteShader(fs);
//     return program;
// }
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

    this->init();
    while (!m_destroy_window_flag && !glfwWindowShouldClose(this->m_glfw_window))
    {
        float t2 = glfwGetTime();
        float dt = t2 - t1;

        if (dt < MIN_FRAME_DELAY)
            continue;

        this->render();
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
int shaderID = 0;
void Window::init()
{
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
}

float r = 0;
float i = 0.1;
void Window::render()
{
    if(r >  1.0f)
        i = -0.1;
    if(r < 0.0f)
        i = 0.1;
    r += i;
    glUniform4f(glGetUniformLocation(shaderID, "u_Color"),r, 0.3f, 0.8f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
   GL_CALL( glDrawArrays(GL_TRIANGLES, 0, 3));
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