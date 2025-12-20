# Nhật ký phát triển Raytracer

## [Giai đoạn 1] - Khởi tạo & "Hello World" Đồ họa
**Mục tiêu:** Thiết lập môi trường SDL2 và hiển thị khung hình đầu tiên.

### 1.1. Cấu hình Build System
- [x] Tạo file `CMakeLists.txt`.
- [x] Cấu hình `find_package(SDL2)` và link thư viện thành công.
- [x] Build thử project rỗng để kiểm tra liên kết thư viện.

### 1.2. Cửa sổ & Vòng lặp sự kiện (Đang thực hiện)
- [x] Sử dụng `SDL_Init` và `SDL_CreateWindow` để hiện cửa sổ.
- [x] Viết vòng lặp `while` với `SDL_PollEvent` để giữ cửa sổ không bị đóng ngay lập tức.
- [x] Xử lý sự kiện `SDL_QUIT` để thoát chương trình an toàn.

### 1.3. Pixel Buffer & Rendering (Phương pháp Real-time Buffer)

Đây là bước quan trọng nhất để chuẩn bị cho Raytracing. Thay vì vẽ hình, ta sẽ thao tác trực tiếp trên bộ nhớ.

**Kiến thức cần tìm hiểu:**
- [x] `SDL_Texture` với flag `SDL_TEXTUREACCESS_STREAMING`.
- [x] Khái niệm `Pitch` (số bytes của một hàng pixel).
- [x] Phép dịch bit (`<<`) và phép OR (`|`) để gộp kênh màu R, G, B.

**Các bước thực hiện (Coding):**
1.  **Khởi tạo Buffer (RAM):**
    - [x] Tạo `std::vector<uint32_t> m_Buffer` với kích thước `Width * Height`.
    - [x] Đảm bảo `m_Buffer` resize đúng kích thước sau khi tạo cửa sổ.

2.  **Khởi tạo Texture (GPU):**
    - [x] Gọi `SDL_CreateTexture()` với format `SDL_PIXELFORMAT_ARGB8888`.
    - [x] Quan trọng: Tham số access phải là `SDL_TEXTUREACCESS_STREAMING`.

3.  **Xử lý Logic "Tô màu" (Trong vòng lặp while):**
    - [x] Dùng 2 vòng lặp lồng nhau (for y, for x) duyệt qua từng pixel.
    - [x] Tính index mảng: `uint32_t index = y * Width + x;`.
    - [x] Tạo màu thử nghiệm (ví dụ màu hồng): `0xFFFF00FF`.
    - [x] Gán màu vào buffer: `m_Buffer[index] = color;`.

4.  **Hiển thị (Render):**
    - [x] Gọi `SDL_UpdateTexture(texture, NULL, m_Buffer.data(), Width * sizeof(uint32_t))` để đẩy dữ liệu từ RAM sang GPU.
    - [x] Gọi `SDL_RenderCopy` để vẽ texture đó lên màn hình.
    - [x] Gọi `SDL_RenderPresent`.

**Kết quả mong đợi:**
- Chạy chương trình, màn hình hiển thị toàn bộ một màu do mình định nghĩa trong code (không phải màu đen mặc định).
