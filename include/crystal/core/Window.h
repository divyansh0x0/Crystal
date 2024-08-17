#pragma once
#include "glad/glad.h"
#include "crystal/core/Color.h"
#include "crystal/layout/Size.h"
#include "crystal/graphics/Renderer.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <string>
// #include<SDL2/SDL.h>
// int main(int argv, char** args)
// {
//     if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
//         logger::error("SDL INITIALIZATION FAILED");
//         return -1;
//     }
//     logger::success("SDL INITIALIZED");
//     SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_VULKAN| SDL_WINDOW_SHOWN);
//     return 0;
// }
namespace crystal
{
    class Window
    {
    private:
        std::string m_window_name;
        crystal::Size m_window_size;
        crystal::Color m_background_color;
        crystal::graphics::Renderer m_renderer{};
        GLFWwindow *m_glfw_window;

        const uint32_t MAX_FPS = 120;
        uint32_t current_fps = 0;
        bool m_destroy_window_flag;
        void windowResizedCallback(int new_width, int new_height);

    public:
        bool b_vsync_ = false;
        Window(std::string name, crystal::Size size, crystal::Color background_color);
        void addComponent();
        void loop();
        void destroyWindow();
        void swapBuffers();
        uint32_t getCurrentFPS();
        ~Window();
    };

}