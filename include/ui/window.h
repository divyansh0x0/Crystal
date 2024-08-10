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
namespace crystal
{
    class Window
    {
    private:
        std::string window_name_;
        crystal::Size window_size_;
        crystal::Color background_color_;
        GLFWwindow* glfw_window_;
        const uint32_t MAX_FPS = 120;
        uint32_t current_fps = 0;
        bool b_destroy_window_;
    public:
        bool b_vsync_ = false;
        Window(std::string name, crystal::Size size, crystal::Color background_color);
        void addComponent();
        void loop();
        void destroyWindow();
        uint32_t getCurrentFPS();
        ~Window();
    protected:
        void render();
        void init();
    };

}