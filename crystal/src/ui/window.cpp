#include <ui/window.h>
#include <stdexcept>
#include <chrono>
#include <iostream>
double getCurrentTimeMs(){
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
/**
 * Constructs a Window object with the given name, size, and background color.
 *
 * @param name The name of the window.
 * @param size The size of the window.
 * @param background_color The background color of the window.
 *
 * @throws std::runtime_error If GLFW or GLAD initialization fails
 */
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
    glfwSwapInterval(this->b_vsync_ ? 1 : 0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
    glViewport(0, 0, this->window_size_.WIDTH, this->window_size_.HEIGHT);
}
void crystal::Window::loop()
{
    // Main loop
    typedef std::chrono::high_resolution_clock Clock;
    double min_frame_time_ms = 1000 / MAX_FPS;
    uint64_t timespent_ms = 0;
    uint64_t frames_rendered = 0;
    double time_accumulated = 0;
    double t1 = glfwGetTime();
    const double MIN_FRAME_DELAY = 1.0 / MAX_FPS;
    while (!b_destroy_window_ && !glfwWindowShouldClose(this->glfw_window_))
    {
        double t2 = glfwGetTime();
        double dt = t2 - t1;
     
        if (dt < MIN_FRAME_DELAY) continue;

        this->render();
        glfwSwapBuffers(this->glfw_window_);
        glfwPollEvents();

        time_accumulated += dt;
        ++frames_rendered;

        if(time_accumulated >= 1.0){
            this->current_fps = frames_rendered;
            logger::info(std::string("FPS: ") +std::to_string(this->current_fps) + "|Timespent" + std::to_string(time_accumulated));
            time_accumulated = 0;
            frames_rendered = 0;
        }
        t1= t2;
    }


    
}

void crystal::Window::addComponent()
{
}
uint32_t crystal::Window::getCurrentFPS()
{
    return this->current_fps;
}
uint8_t i = 0;
void crystal::Window::render()
{
    // RGBA background_color = background_color_.getRGBA();
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
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
