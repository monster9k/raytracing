# Nhật ký phát triển Raytracer

## [Giai đoạn 1] - Khởi tạo & "Hello World" Đồ họa
**Mục tiêu:** Thiết lập môi trường SDL2 và hiển thị khung hình đầu tiên.

### 1.1. Cấu hình Build System
- [x] Tạo file `CMakeLists.txt`.
- [x] Cấu hình `find_package(SDL2)` và link thư viện thành công.
- [x] Build thử project rỗng để kiểm tra liên kết thư viện.

### 1.2. Cửa sổ & Vòng lặp sự kiện (Đang thực hiện)
- [x] Sử dụng `SDL_Init` và `SDL_CreateWindow` để hiện cửa sổ.
- [ ] Viết vòng lặp `while` với `SDL_PollEvent` để giữ cửa sổ không bị đóng ngay lập tức.
- [ ] Xử lý sự kiện `SDL_QUIT` để thoát chương trình an toàn.

### 1.3. Pixel Buffer & Rendering (Đang thực hiện)
- [ ] Tạo `SDL_Renderer` và `SDL_Texture` với flag `STREAMING`.
- [ ] Tạo một mảng (buffer) trong C++ để chứa thông tin màu của từng pixel.
- [ ] Sử dụng `SDL_UpdateTexture` để copy mảng buffer lên texture.
- [ ] Gọi `SDL_RenderCopy` và `SDL_RenderPresent` để hiển thị ra màn hình.