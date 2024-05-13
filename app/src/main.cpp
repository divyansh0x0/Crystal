// for initializing and shutdown functions
#define SDL_MAIN_HANDLED
// #include <stdio.h> /* printf and fprintf */
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_vulkan.h>
// #include <stdint.h>
// #include <vulkan/vulkan.h>
// #include <MUI/include/window.h>

/* Sets constants */
// #define WIDTH 800
// #define HEIGHT 600
// #define DELAY 3000
// SDL_Window *window;
// uint8_t isRunning = 0;
// char *window_name = "example SDL2 VULKAN APP";
// int KEYS[322];
#include <log.h>
#include <MUI/window.h>
bool isRunning = false;
char *window_name = "crystal";

void handleEvent(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    SDL_Window *window = initAndGetWindow(window_name);
    log::info("Hello world");
    log::warn("Hello world");

    log::error("Hello world");
    log::success("Hello world");

    isRunning = true;
    while (isRunning)
    {
        SDL_Event window_event;
        while (SDL_PollEvent(&window_event))
        {
            handleEvent(window_event);
        }
    }
    return 0;
    // while (isRunning != 0)
    // {
    //     SDL_Event windowEvent;
    //     while (SDL_PollEvent(&windowEvent))
    //     {
    //         if (windowEvent.type == SDL_QUIT)
    //         {
    //             isRunning = 0;
    //             break;
    //         }
    //     }
    // }
}
