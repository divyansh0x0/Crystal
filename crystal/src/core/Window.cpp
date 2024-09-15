#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include "crystal/graphics/GraphicsAPI.h"
#include "crystal/graphics/Renderer.h"

#include <GLFW/glfw3.h>
#include <chrono>

float getCurrentTimeMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

static void GlfwErrorCallback(int error, const char *description)
{
    logger::Error("GLFW ERROR", description);
}

namespace crystal
{

Window::Window(const char *name,
               crystal::layout::Size size,
               crystal::Color background_color)
    : m_window_name(name), m_frame_buffer_size(size),
      m_background_color(background_color), m_destroy_window_flag(false)
{

    glfwSetErrorCallback(GlfwErrorCallback);
    if (glfwInit() == GLFW_FALSE) logger::Error("GLFW INITIALIZATION FAILED");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    logger::Success("GLFW Initialized");
}
void Window::show()
{
    //TODO: Memory skyrockets here
    m_glfw_window = glfwCreateWindow(m_frame_buffer_size.width,
                                     m_frame_buffer_size.height,
                                     m_window_name.data(), NULL, NULL);
    glfwSetWindowUserPointer((GLFWwindow *)m_glfw_window, this);

    glfwSetFramebufferSizeCallback(
        (GLFWwindow *)m_glfw_window,
        [](GLFWwindow *glfw_window, int width, int height)
        {
            Window *window = (Window *)glfwGetWindowUserPointer(glfw_window);
            window->frameBufferResizedCallback(width, height);
        });

    if (!m_glfw_window)
    {
        logger::Error("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    switchContextToCurrentThread();
    glfwSwapInterval(0);
    detachContextFromCurrentThread();

    // renderer has its own separate thread
    crystal::graphics::Renderer renderer = crystal::graphics::Renderer(
        this, graphics::GraphicsContextType::OpenGL);
    renderer.init();

    while (!m_destroy_window_flag
           && !glfwWindowShouldClose((GLFWwindow *)m_glfw_window))
    {
        glfwWaitEvents();
    }
}
void Window::frameBufferResizedCallback(int new_width, int new_height)
{
    m_frame_buffer_size.changeTo(new_width, new_height);
}

void Window::switchContextToCurrentThread() const
{
    glfwMakeContextCurrent((GLFWwindow *)m_glfw_window);
    if ((GLFWwindow *)m_glfw_window == glfwGetCurrentContext())
        logger::Success("Switched context to current thread");
    else
        logger::Error("Failed to switch context to current thread");
}
void Window::detachContextFromCurrentThread() const
{
    glfwMakeContextCurrent(NULL);
}
void Window::swapBuffers() const
{
    // logger::Info("Swapping buffer");
    glfwSwapBuffers((GLFWwindow *)m_glfw_window);
}
const crystal::layout::Size &Window::getFrameBufferSize() const
{
    return m_frame_buffer_size;
}
typedef void (*API)(void);
void *Window::getGLLoadProc() const
{
    return (void *)glfwGetProcAddress;
}
void Window::addComponent() {}
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
    glfwDestroyWindow((GLFWwindow *)m_glfw_window);
    glfwTerminate();
    logger::Success("Destroyed", "Window destroyed");
}
} // namespace crystal