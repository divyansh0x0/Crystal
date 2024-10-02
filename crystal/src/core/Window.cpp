#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/GL/GLHelper.h"
#include "crystal/graphics/GL/GLShader.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

static inline uint64_t getCurrentTimeNanos()
{
    return std::chrono::steady_clock::now().time_since_epoch().count();
}

static void GlfwErrorCallback(int error, const char* description)
{
    logger::Error("GLFW", description);
}


namespace crystal
{
Window::Window(const char* name, crystal::layout::Size size, crystal::Color background_color, graphics::Renderer* renderer)

    : m_window_name(name), m_frame_buffer_size(size), m_background_color(background_color), m_renderer(renderer), m_renderer_attached_b(false), m_window_destroyed_b(false),
      m_window_visible_b(false), m_current_fps(0)
{

    glfwSetErrorCallback(GlfwErrorCallback);
    if (glfwInit() == GLFW_FALSE)
    {
        logger::Error("Window", "GLFW INITIALIZATION FAILED");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    logger::Success("Window", "GLFW Initialized");
}
void Window::attachRenderer(graphics::Renderer& renderer)
{
    if (m_window_destroyed_b)
    {
        logger::Error("Window", "Window already destroyed. Cannot attach renderer");
        return;
    }
    if (m_renderer_attached_b)
    {
        logger::Error("Window", "Renderer already attached");
        return;
    }
    m_renderer_attached_b = true;
    m_renderer            = &renderer;
    m_rendering_thread    = new std::thread(&Window::rendererLoop, this);
    logger::Info("Window", "Renderer attached");
}
void Window::dettachRenderer()
{
    if (!m_renderer_attached_b) return;

    m_renderer_attached_b = false;
    m_rendering_thread->join();
    delete m_rendering_thread;

    logger::Info("Window", "Rendering thread destroyed");
}
void Window::show()
{
    m_glfw_window      = glfwCreateWindow(m_frame_buffer_size.width, m_frame_buffer_size.height, m_window_name.data(), NULL, NULL);
    m_window_visible_b = true;
    glfwSetWindowUserPointer((GLFWwindow*) m_glfw_window, this);

    glfwSetFramebufferSizeCallback((GLFWwindow*) m_glfw_window,
                                   [](GLFWwindow* glfw_window, int width, int height)
                                   {
                                       Window* window = (Window*) glfwGetWindowUserPointer(glfw_window);
                                       window->frameBufferResizedCallback(width, height);
                                   });

    if (!m_glfw_window)
    {
        logger::Error("Window", "Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    switchContextToCurrentThread();
    glfwSwapInterval(0);
    detachContextFromCurrentThread();

    if (m_renderer != nullptr) attachRenderer(*m_renderer);

    while (!m_window_destroyed_b.load() && !glfwWindowShouldClose((GLFWwindow*) m_glfw_window))
    {
        glfwWaitEvents();
    }
    // destroys the window once it has been exited
    destroyWindow();
}
void Window::rendererLoop()
{
    m_renderer->init(*this);
    uint64_t timespent_nanos     = 0;
    uint64_t frames_rendered     = 0;
    uint64_t one_second_in_nanos = 1000'000'000;

    uint64_t t1 = getCurrentTimeNanos();

    logger::Info("Window", "Begining rendering loop");

    while (m_renderer_attached_b.load())
    {
        uint64_t t2 = getCurrentTimeNanos();
        uint64_t dt = t2 - t1;

        if (dt < one_second_in_nanos / m_max_fps) continue;

        m_renderer->render();

        timespent_nanos += dt;
        frames_rendered++;
        if (timespent_nanos >= one_second_in_nanos)
        {
            logger::Info(std::string("FPS: ") + std::to_string(frames_rendered) + " | Timespent: " + std::to_string(timespent_nanos) + "ns");
            m_current_fps   = frames_rendered;
            timespent_nanos = 0;
            frames_rendered = 0;
        }
        this->swapBuffers();
        t1 = t2;
    }

    logger::Info("Renderer", "rendering loop ended");

    if (m_renderer != nullptr) m_renderer->destroy();
}
void Window::frameBufferResizedCallback(int new_width, int new_height)
{
    m_frame_buffer_size.changeTo(new_width, new_height);
}

void Window::switchContextToCurrentThread() const
{
    size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    glfwMakeContextCurrent((GLFWwindow*) m_glfw_window);
    if ((GLFWwindow*) m_glfw_window == glfwGetCurrentContext())
        logger::Info("Window", "Switched window context to thread " + std::to_string(thread_id));
    else
        logger::Error("Window", "Failed to switch window context to thread " + std::to_string(thread_id));
}
void Window::detachContextFromCurrentThread() const
{
    size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    if ((GLFWwindow*) m_glfw_window != glfwGetCurrentContext())
    {
        logger::Error("GLFW", "Detach window context failed. The window context does not belong to this thread " + std::to_string(thread_id));
        return;
    }
    glfwMakeContextCurrent(NULL);
    logger::Info("Window", "Detached window context from thread " + std::to_string(thread_id));
}
void Window::swapBuffers() const
{
    // logger::Info("Swapping buffer");
    glfwSwapBuffers((GLFWwindow*) m_glfw_window);
}
const crystal::layout::Size& Window::getFrameBufferSize() const
{
    return m_frame_buffer_size;
}
typedef void (*API)(void);
void* Window::getGLLoadProc() const
{
    return (void*) glfwGetProcAddress;
}
void Window::addComponent() {}
/**
 * Destroys the window by setting the `b_destroy_window_` flag to true.
 *
 * @throws None
 */
void Window::destroyWindow()
{
    if (m_window_destroyed_b) return;
    m_window_destroyed_b = true;

    dettachRenderer();

    glfwSetWindowShouldClose((GLFWwindow*) m_glfw_window, true);
    glfwDestroyWindow((GLFWwindow*) m_glfw_window);
    glfwTerminate();
    m_glfw_window = nullptr;
    m_renderer    = nullptr;
    logger::Success("Window", "Window destroyed and terminated");
}
Window::~Window()
{
    destroyWindow();
}
} // namespace crystal