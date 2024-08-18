#pragma once
#include "glad/glad.h"
#include "crystal/core/Color.h"
#include "crystal/layout/Size.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <string>
// #include<SDL2/SDL.h>
// int main(int argv, char** args)
// {
//     if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
//         logger::Error("SDL INITIALIZATION FAILED");
//         return -1;
//     }
//     logger::Success("SDL INITIALIZED");
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
        // crystal::graphics::Renderer m_renderer{};
        GLFWwindow *m_glfw_window;

        bool m_destroy_window_flag;
        void frameBufferResizedCallback(int new_width, int new_height);

    public:
        bool b_vsync_ = false;
        Window(std::string name, crystal::Size size, crystal::Color background_color);
        void addComponent();
        void show();
        void destroyWindow();
        void swapBuffers();
        
        unsigned int getWidth() {return m_window_size.width;}
        unsigned int getHeight() {return m_window_size.height;}

        Size& getSize() {return m_window_size;};
        Size& getFrameBufferSize();
        void makeContextCurrent();
        void detachCurrentContext();

        ~Window();
    };

}