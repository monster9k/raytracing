#include <SDL2/SDL.h>
#include <iostream>

#define w 800 
#define h 600

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)) {
        std::cerr << "SDL could not initialize! SDL_Error:" << SDL_GetError();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow( "RayTracing",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w,
         h, 0);
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
           }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}