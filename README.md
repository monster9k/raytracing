# SDL2 Raytracer

![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Library](https://img.shields.io/badge/library-SDL2-orange.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![Status](https://img.shields.io/badge/status-In%20Development-yellow.svg)

A C++ Raytracer built from scratch, using **SDL2** for window management and pixel rendering. This project aims to implement core ray tracing concepts (ray-sphere intersection, materials, lighting) without relying on external graphics APIs like OpenGL or DirectX for the rendering pipeline.

> **Note:** This project is currently **WIP (Work In Progress)**.

## 🖼️ Demo
*(Screenshot placeholder - To be updated once the first image is rendered)*
![Demo Image](https://via.placeholder.com/800x450?text=Raytracer+Demo+Image)

## 🚀 Features (Planned)
- [ ] **Basic Framework:** SDL2 window setup and pixel buffer management.
- [ ] **Math Library:** Custom Vector3 and Ray classes.
- [ ] **Primitives:** Sphere intersection logic.
- [ ] **Camera:** Positionable camera with antialiasing (MSAA).
- [ ] **Materials:**
    - [ ] Lambertian (Matte/Diffuse)
    - [ ] Metal (Reflective)
    - [ ] Dielectric (Glass/Refraction)
- [ ] **Scene:** Support for multiple objects handling.

## 🛠️ Prerequisites
Before building, ensure you have the following installed:
* **C++ Compiler** (GCC, Clang, or MSVC) supporting C++17.
* **CMake** (Version 3.10 or higher).
* **SDL2 Development Libraries**:
    * *Ubuntu/Debian:* `sudo apt-get install libsdl2-dev`
    * *Windows:* Install via vcpkg or download development binaries from libsdl.org.
    * *MacOS:* `brew install sdl2`

## 🔨 Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/YOUR_USERNAME/SDL2-Raytracer.git](https://github.com/YOUR_USERNAME/SDL2-Raytracer.git)
    cd SDL2-Raytracer
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure and Build with CMake:**
    ```bash
    cmake ..
    cmake --build .
    ```

4.  **Run the application:**
    * *Linux/Mac:* `./MyRayTracer`
    * *Windows:* `Debug\MyRayTracer.exe`

## 📂 Project Structure
```text
.
├── src/          # Source files (.cpp) - Main logic and implementation
├── include/      # Header files (.h) - Class declarations
├── docs/         # Documentation and Dev Journal (STEPS.md)
├── assets/       # Images or resources (if any)
└── CMakeLists.txt