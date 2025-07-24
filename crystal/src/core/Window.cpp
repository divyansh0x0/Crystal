#include "crystal/core/Window.hpp"
#include <GLFW/glfw3.h>
#include <basetsd.h>
#include <chrono>
#include <functional>
#include <thread>
#include "crystal/core/Core.hpp"
#include "crystal/core/Logger.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32

static void GlfwErrorCallback(int error, const char* description)
{
    logger::Error("GLFW (" + std::to_string(error) + ")", description);
}

namespace crystal
{
    Window::Window(const char*          name,
                   const geometry::Size size,
                   const Color          background_color,
                   const graphics::API  graphics_api)

        : m_window_name(name),
          m_frame_buffer_size(size),
          m_background_color(background_color),
          m_renderer(graphics::CreateRenderer(graphics_api)),

          m_is_renderer_attached(false),
          m_window_destroyed(false),
          m_is_window_visible(false)
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

    void Window::show()
    {
        m_is_window_visible = true;
        m_glfw_window = glfwCreateWindow(m_frame_buffer_size.getWidthAsInt(), m_frame_buffer_size.getHeightAsInt(),
                                         m_window_name.data(), nullptr, nullptr);

        auto callback = [](GLFWwindow* window, const int width, const int height)
        {
            if (auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
            {
                self->setFrameBufferSize(width, height);
            }
        };

        glfwSetWindowUserPointer(static_cast<GLFWwindow*>(m_glfw_window), this);
        glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(m_glfw_window), callback);

        if (!m_glfw_window)
        {
            logger::Error("Window", "Failed to create GLFW window");
            glfwTerminate();
            m_renderer.reset();
            return;
        }

        switchContextToCurrentThread();
        glfwSwapInterval(0);

        m_renderer->start(*this);
        while (!m_window_destroyed.load() && !glfwWindowShouldClose(static_cast<GLFWwindow*>(m_glfw_window)))
        {
            glfwWaitEvents();
        }
        // destroys the window once it has been exited
        destroyWindow();
    }

    void Window::setFrameBufferSize(int new_width, int new_height)
    {
        m_frame_buffer_size.changeTo(new_width, new_height);
    }

    void Window::swapBuffers() const
    {
        glfwSwapBuffers(static_cast<GLFWwindow*>(m_glfw_window));
    }

    /******************************************************************************************************************/
    /* ************************************* Overwrites ***************************************************************/
    /******************************************************************************************************************/
    void Window::switchContextToCurrentThread() const
    {
        const size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_glfw_window));
        if (m_glfw_window == glfwGetCurrentContext())
            logger::Info("Window", "Switched window context to thread " + std::to_string(thread_id));
        else
            logger::Error("Window", "Failed to switch window context to thread " + std::to_string(thread_id)
                                        + ". Make sure the other process has detached the context.");
    }

    void Window::detachContextFromCurrentThread() const
    {
        const size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
        if (m_glfw_window != glfwGetCurrentContext())
        {
            logger::Error("GLFW", "Detach window context failed. The window context does not belong to the thread you "
                                  "are trying to detach it from. Thread ID: "
                                      + std::to_string(thread_id));
            return;
        }
        glfwMakeContextCurrent(nullptr);
        logger::Info("Window", "Detached window context from thread " + std::to_string(thread_id));
    }

    const geometry::Size& Window::getFrameBufferSize() const
    {
        return m_frame_buffer_size;
    }

    GLLoadProc Window::getGLLoadProc() const
    {
        // there is no other way. glfwGetProcAddress returns a function pointer but glad requires a void* pointer
        return reinterpret_cast<GLLoadProc>(glfwGetProcAddress);
    }

    /******************************************************************************************************************/
    /* ************************************* DESTRUCTORS **************************************************************/
    /******************************************************************************************************************/
    void Window::destroyWindow()
    {
        if (m_window_destroyed.exchange(true)) return;

        m_window_destroyed = true;

        if (m_glfw_window)
        {
            glfwSetWindowShouldClose(static_cast<GLFWwindow*>(m_glfw_window), true);
            glfwDestroyWindow(static_cast<GLFWwindow*>(m_glfw_window));
            glfwTerminate();
            m_glfw_window = nullptr;
        }

        m_renderer->stop();
        m_renderer.reset();


        logger::Success("Window", "Window destroyed and terminated");
    }

    Window::~Window()
    {
        destroyWindow();
    }
} // namespace crystal
