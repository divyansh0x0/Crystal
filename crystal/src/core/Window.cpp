#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include "crystal/graphics/GraphicsAPI.h"
#include "crystal/graphics/Renderer.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

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
    if (glfwInit() == GLFW_FALSE)
    {
        logger::Error("GLFW", "GLFW INITIALIZATION FAILED");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    logger::Success("GLFW", "GLFW Initialized");
}
void Window::show()
{
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
        logger::Error("GLFW", "Failed to create GLFW window");
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
    size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    glfwMakeContextCurrent((GLFWwindow *)m_glfw_window);
    if ((GLFWwindow *)m_glfw_window == glfwGetCurrentContext())
        logger::Info("GLFW",
                     "Switched window context to thread " + std::to_string(thread_id));
    else
        logger::Error("GLFW", "Failed to switch window context to thread "
                                  + std::to_string(thread_id));
}
void Window::detachContextFromCurrentThread() const
{
    size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    if ((GLFWwindow *)m_glfw_window != glfwGetCurrentContext())
    {
        logger::Error("GLFW", "Detach window context failed. The window context does not belong to this thread "
                                  + std::to_string(thread_id));
        return;
    }
    glfwMakeContextCurrent(NULL);
    logger::Info("GLFW",
                 "Detached window context from thread " + std::to_string(thread_id));
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
    m_glfw_window = nullptr;
    glfwDestroyWindow((GLFWwindow *)m_glfw_window);
    glfwTerminate();
    logger::Success("GLFW", "GLFW window destroyed and terminated");
}
} // namespace crystal