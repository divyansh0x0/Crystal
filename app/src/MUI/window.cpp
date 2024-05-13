#include<MUI/window.h>
// #include<log.h>
SDL_Window* initAndGetWindow(char* window_name){
        /* Initialises data */
    SDL_Window *window = NULL;
    int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);

    /*
     * Initialises the SDL video subsystem (as well as the events subsystem).
     * Returns 0 on success or a negative error code on failure using SDL_GetError().
     */
    // SDL_Vulkan_LoadLibrary(nullotr)
    window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (sdlInit != 0)
    {
        // fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return NULL;
    }

    /* Checks if window has been created; if not, exits program */
    if (window == NULL)
    {
        // fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return NULL;
    }
    const char* errors = SDL_GetError();
    if(errors)
        SDL_Log("cleaned up with errors: %s");
    return window;
}
