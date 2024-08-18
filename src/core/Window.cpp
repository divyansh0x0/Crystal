#include "crystal/core/Window.h"
#include "crystal/core/Logger.h"
#include "crystal/graphics/Renderer.h"

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
    logger::Error(description);
}
static void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    
}
namespace crystal
{

    Window::Window(std::string name, crystal::Size size, crystal::Color background_color) : m_window_name(name), m_window_size(size), m_background_color(background_color), m_destroy_window_flag(false)
    {
        glfwSetErrorCallback(GlfwErrorCallback);
        if (glfwInit() == GLFW_FALSE)
            throw std::runtime_error("GLFW INITIALIZATION FAILED");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        logger::Success("GLFW Initialized");
    }
    void Window::show()
    {
        this->m_glfw_window = glfwCreateWindow(this->m_window_size.width, this->m_window_size.height, this->m_window_name.data(), NULL, NULL);
        glfwSetWindowUserPointer(this->m_glfw_window, this);
        
        glfwSetFramebufferSizeCallback(this->m_glfw_window, [](GLFWwindow *glfw_window, int width, int height){
            Window* window = (Window*)  glfwGetWindowUserPointer(glfw_window);
            window->frameBufferResizedCallback(width, height);
        });

        if (!m_glfw_window)
        {
            throw std::runtime_error("Failed to create GLFW window");
            glfwTerminate();
        }

        this->makeContextCurrent();
        glfwSwapInterval(0);
        this->detachCurrentContext();



        crystal::graphics::Renderer renderer = crystal::graphics::Renderer(this);
        renderer.init();


        while (!m_destroy_window_flag && !glfwWindowShouldClose(this->m_glfw_window))
        {
            glfwWaitEvents();
        }

    }
    void Window::frameBufferResizedCallback(int new_width, int new_height){
        this->m_window_size.changeTo(new_width, new_height);
        logger::Success("Window resized to " + std::to_string(new_width) + "x" + std::to_string(new_height));
    }

    void Window::makeContextCurrent(){
        glfwMakeContextCurrent(this->m_glfw_window);
    }
    void Window::detachCurrentContext(){
        glfwMakeContextCurrent(NULL);
    }
    void Window::swapBuffers()
    {
        // logger::Info("Swapping buffer");
        glfwSwapBuffers(this->m_glfw_window);
    }

    void Window::addComponent()
    {
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
        logger::Success(logger::LogType::DESTRUCTION,"Window destroyed");
    }
}