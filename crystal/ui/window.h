#pragma once
#include <core/Core.h>
#include <GLFW/glfw3.h>
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
namespace quartz
{
    class Window
    {
    private:
        std::string window_name_;
        quartz::Size window_size_;
        quartz::Color background_color_;
        GLFWwindow* glfw_window_;
        uint32_t MAX_FPS = 60;
        uint32_t current_fps = 0;
        bool b_destroy_window_;
        void render();
    public:
        Window(std::string name, quartz::Size size, quartz::Color background_color);
        void addComponent();
        void loop();
        void destroyWindow();
        uint32_t getCurrentFPS();
        ~Window();
    };

}