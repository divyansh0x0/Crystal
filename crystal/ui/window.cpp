#include<ui/window.h>
#include<stdexcept>
#include<chrono>
static void GlfwErrorCallback(int error, const char* description) {
    logger::error(description);
}
static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
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
quartz::Window::Window(std::string name, quartz::Size size, quartz::Color background_color) : window_name_(name), window_size_(size),  background_color_(background_color), b_destroy_window_(false){
    glfwSetErrorCallback(GlfwErrorCallback);
    if(glfwInit() == GLFW_FALSE)
        throw std::runtime_error("GLFW INITIALIZATION FAILED");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    logger::success("GLFW Initialized");



    logger::success("GLAD Initialized");

    this->glfw_window_ = glfwCreateWindow(this->window_size_.WIDTH, this->window_size_.HEIGHT, this->window_name_.data(), NULL, NULL);
    
    
    if (!glfw_window_) {
        throw std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(glfw_window_, FramebufferSizeCallback); 
    //create context
    glfwMakeContextCurrent(this->glfw_window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error( "Failed to initialize GLAD" );
    glViewport(0, 0, this->window_size_.WIDTH, this->window_size_.HEIGHT);


}
void quartz::Window::loop(){
    // Main loop
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point t1 = Clock::now();
    uint32_t min_frame_time_ms = 1000/ MAX_FPS;
    uint64_t timespent_ms = 0;
    uint32_t frames_rendered = 0;
    while (!b_destroy_window_ && !glfwWindowShouldClose(this->glfw_window_)) {
       // Poll for and process events
    
        Clock::time_point t2 = std::chrono::high_resolution_clock::now();
        uint32_t dt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        if(dt_ms < min_frame_time_ms){
            continue;
        }
        timespent_ms += dt_ms;
        this->render();
        glfwSwapBuffers(this->glfw_window_);
        frames_rendered += 1;
        // logger::info(std::string("dt: ") +std::to_string(dt_ms));
        glfwPollEvents();

        if(timespent_ms >= 1000){
            this->current_fps = frames_rendered;
            logger::info(std::string("FPS: ") +std::to_string(this->current_fps));
            frames_rendered = 0;
            timespent_ms = 0;
        }
        t1 = t2;
    }
}

void quartz::Window::addComponent(){
    
}
uint32_t quartz::Window::getCurrentFPS(){
    return this->current_fps;
}
uint8_t i = 0;
void quartz::Window::render(){
    RGBA background_color = background_color_.getRGBA();
    glClearColor( background_color.r/ 255.0f, background_color.g / 255.0f, background_color.b / 255.0f, background_color.a/ 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
/**
 * Destroys the window by setting the `b_destroy_window_` flag to true.
 *
 * @throws None
 */
void quartz::Window::destroyWindow(){
    b_destroy_window_ = true;
}
quartz::Window::~Window(){
    glfwDestroyWindow(this->glfw_window_);
    glfwTerminate();
    logger::success("Window destroyed");
}
