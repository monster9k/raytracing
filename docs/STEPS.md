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


## [Giai đoạn 2] - Toán học & Camera cơ bản
**Mục tiêu:** Xây dựng các class toán học cốt lõi và render bầu trời dựa trên tia sáng (Rays).


### 2.1. Xây dựng Class Vector3 (Vec3.h)
- [x] Tạo file `include/Vec3.h`.
- [x] Định nghĩa 3 thành phần: `double x, y, z`.
- [x] **Operator Overloading:** Cài đặt các toán tử `+`, `-`, `*`, `/` để cộng trừ vector như số học.
- [x] **Utility Functions:**
    - `dot(v1, v2)`: Tích vô hướng (tính góc/ánh sáng).
    - `cross(v1, v2)`: Tích có hướng (tìm pháp tuyến).
    - `unit_vector(v)`: Chuẩn hóa vector về độ dài 1.
- [x] Định nghĩa `using Color = Vec3;` để code rõ nghĩa hơn.

### 2.2. Xây dựng Class Ray (Ray.h)
- [x] Tạo file `include/Ray.h`.
- [x] Class gồm 2 thành phần `Vec3 origin` (gốc) và `Vec3 direction` (hướng).
- [x] Hàm quan trọng nhất: `Point3D at(double t)` trả về vị trí tia sáng tại thời điểm t.
      Công thức: `P(t) = origin + t * direction`.

### 2.3. Tích hợp & Render Bầu trời (Gradient Sky)
**Mục tiêu:** Sử dụng `Vec3` và `Ray` để tạo ra hình ảnh đầu tiên dựa trên hướng nhìn.

- [x] **Thiết lập Camera ảo (Viewport):**
    - Xác định khung nhìn ảo trong không gian 3D.
    - `aspect_ratio` = 16:9.
    - `viewport_height` = 2.0.
    - `focal_length` = 1.0 (Khoảng cách từ mắt đến khung nhìn).
    - Tính toán `lower_left_corner`: Điểm góc trái dưới cùng của màn hình ảo.

- [x] **Tạo hàm `ray_color(Ray r)`:**
    - Input: Một tia sáng bắn ra từ camera.
    - Logic: Lấy hướng `unit_direction.y` (từ -1.0 đến 1.0) chuyển về `t` (0.0 đến 1.0).
    - Công thức pha màu (Linear Interpolation / Lerp):
      `color = (1.0 - t)*White + t*Blue`.
    - Kết quả: Bầu trời chuyển màu mượt mà từ trắng sang xanh.

- [x] **Chuyển đổi hệ tọa độ (Coordinate Mapping):**
    - Ánh xạ từ pixel màn hình `(i, j)` sang tọa độ texture `(u, v)` trong khoảng [0,1].
    - Lưu ý: Đảo ngược trục Y (`image_height - 1 - j`) vì SDL gốc (0,0) ở trên cùng, còn 3D gốc (0,0) ở dưới cùng.

- [x] **Helper `to_argb`:**
    - Chuyển đổi màu `Vec3` (float 0.0 - 1.0) sang `uint32_t` (byte 0 - 255) để SDL hiển thị.

**Kết quả:** Cửa sổ hiển thị background gradient xanh dương - trắng đúng chuẩn Raytracing.

## [Giai đoạn 3] - Vật thể đầu tiên: Quả cầu đỏ
**Mục tiêu:** Tính toán giao điểm giữa tia Ray và Quả cầu (Ray-Sphere Intersection).

### 3.1. Lý thuyết va chạm (Math)
- [x] Hiểu phương trình mặt cầu: `dot((P-C), (P-C)) = r^2`.
- [x] Thiết lập phương trình bậc 2: `at^2 + bt + c = 0`.
    - `a = dot(ray_direction, ray_direction)`
    - `b = 2.0 * dot(oc, ray_direction)` (với `oc = origin - center`)
    - `c = dot(oc, oc) - radius*radius`
- [x] Tính Delta (discriminant): `delta = b*b - 4*a*c`.

### 3.2. Cài đặt hàm `hit_sphere`
- [x] Viết hàm `bool hit_sphere(center, radius, ray)` trả về true/false.
- [x] Cập nhật hàm `ray_color`:
    - Nếu `hit_sphere` trả về true -> Trả về màu Đỏ `Color(1, 0, 0)`.
    - Nếu false -> Trả về màu bầu trời (gradient cũ).

**Kết quả mong đợi:**
- Màn hình hiển thị một hình tròn màu đỏ nằm giữa nền trời xanh. (Lưu ý: Nó là hình cầu 3D, nhưng vì chưa có ánh sáng bóng đổ nên nhìn như hình tròn dẹt 2D).


## [Giai đoạn 4] - Hiển thị độ cong 3D (Surface Normals)
**Mục tiêu:** Thay màu đỏ đơn điệu bằng bản đồ pháp tuyến (Normal Map) để nhìn thấy hình khối 3D thực sự.

### 4.1. Tính toán Vector pháp tuyến
- [x] Công thức: `normal = unit_vector(hit_point - center)`.
- [x] Logic: Vector pháp tuyến của mặt cầu chính là hướng từ Tâm cầu đi ra điểm bề mặt.

### 4.2. Tô màu theo pháp tuyến
- [x] Logic toán học: Vector pháp tuyến có giá trị từ -1 đến 1. Màu sắc cần từ 0 đến 1.
- [x] Công thức chuyển đổi: `color = 0.5 * (normal + 1.0)`.
    - Ví dụ: Normal (-1, -1, 0) -> Color (0, 0, 0.5).
- [x] Cập nhật hàm `hit_sphere` để trả về giá trị `t` (thời điểm va chạm) thay vì chỉ true/false, để ta tính được tọa độ điểm va chạm `P(t)`.

**Kết quả mong đợi:**
- Một quả cầu "cầu vồng":
    - Đỉnh cầu: Màu xanh lá (Y dương).
    - Bên phải: Màu đỏ (X dương).
    - Phía trước: Màu xanh dương (Z dương).