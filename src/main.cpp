#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#define width 800 
#define height 600

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)) {
        std::cerr << "SDL could not initialize! SDL_Error:" << SDL_GetError();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow( "RayTracing",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
        height, 0);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    std::vector<uint32_t> buffer(width * height);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
           }

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    uint8_t r = (x * 255) / width; // tang dan theo chieu ngang
                    uint8_t g = (y * 255) / height; // tang dan theo chieu doc
                    uint8_t b = 100; // xanh duong
                    uint8_t a = 255;

                    uint32_t color = (a << 24) | (r << 16) | (g << 8) | b; // dong goi 

                    buffer[y * width + x] = color;
                }
            }
            /*std::cout << sizeof(uint32_t);*/
            SDL_UpdateTexture(texture, NULL, buffer.data(), width * sizeof(uint32_t)); 
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}