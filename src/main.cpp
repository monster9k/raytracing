#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../include/Vector3.h"
#include "../include/Ray.h"

#define width 800 
#define height 600

double  hit_sphere(const Point3& center, double radious, const Ray& r) {
    Vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radious * radious;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}


Color ray_color(const Ray& r) {
    auto t = hit_sphere(Point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        Vec3 N = unit_vector(r.at(t) - Vec3(0, 0, -1));
        return 0.5 * Color(N.x + 1, N.y + 1, N.z + 1);
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t2 = 0.5 * (unit_direction.y + 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blue(0.5, 0.7, 1.0);
    return (1.0 - t2) * white + t2 * blue; 
}

uint32_t to_argb(const Color& pixel_color) {
    uint8_t r = static_cast<uint8_t>(255.999 * pixel_color.x);
    uint8_t g = static_cast<uint8_t>(255.999 * pixel_color.y);
    uint8_t b = static_cast<uint8_t>(255.999 * pixel_color.z);
    uint8_t a = 255;
    return (a << 24) | (r << 16) | (g << 8) | b;
}



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL could not initialize! SDL_Error:" << SDL_GetError();
        return 1;
    }

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 800;


    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    SDL_Window* window = SDL_CreateWindow("RayTracing",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image_width,
        image_height, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, image_width, image_height
    );


    //camera
    // Viewport widths less than one are ok since they are real valued.
    auto focal_lenght = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = Vec3(0, 0, 0); // mat camera

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = Vec3(viewport_width, 0, 0 );
    auto viewport_v = Vec3(0, -viewport_height, 0);
    
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - viewport_u / 2 - viewport_v / 2 - Vec3(0, 0, focal_lenght);
    // TÍNH VỊ TRÍ PIXEL 0,0 (Quan trọng: Dời vào tâm pixel)
    auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);


    std::vector<uint32_t> buffer(image_width * image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

            auto ray_direction = pixel_center - camera_center;

            Ray r(camera_center, ray_direction);
            Color pixel_color = ray_color(r);

            buffer[j * image_width + i] = to_argb(pixel_color);
        }
    }
    /*std::cout << sizeof(uint32_t);*/
    SDL_UpdateTexture(texture, NULL, buffer.data(), image_width * sizeof(uint32_t));

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
           }

            
            
        }

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}