#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>

class Vec3 {
public: 
	double x, y, z;

	// constructor 
	Vec3() : x(0), y(0), z(0) {}
	Vec3(double e0, double e1, double e2) : x(e0), y(e1), z(e2) {}

	// operator 
	Vec3 operator-() const {
		return Vec3(-x, -y, -z);
	}

	Vec3& operator+=(const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vec3& operator*=(const double t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	Vec3& operator/=(const double t) {
		return *this *= (1 / t);
	}

	//Hàm tính độ dài(Geometry)
		double length_squared() const {
		return x * x + y * y + z * z;
	}

	double length() const {
		return sqrt(length_squared());
	}
};

// In vector ra màn hình (Debug): std::cout << v
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

// Cộng 2 vector: u + v
inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

// Trừ 2 vector: u - v
inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

// Nhân 2 vector (Hadamard product - nhân từng thành phần): u * v
inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

// Nhân vector với số thực: t * v
inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.x, t * v.y, t * v.z);
}

// Nhân số thực với vector (ngược lại): v * t
inline Vec3 operator*(const Vec3& v, double t) {
	return t * v;
}

// Chia vector cho số thực: v / t
inline Vec3 operator/(Vec3 v, double t) {
	return (1 / t) * v;
}

// Tích vô hướng (Dot Product)
// tinh goc, anh sang, cat bong
inline double dot(const Vec3& u, const Vec3& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

// Tích có hướng (Cross Product)
// Dùng để tìm vector pháp tuyến vuông góc với 2 vector khác
inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.y * v.z - v.y * u.z, u.z * v.x - v.z * u.x, u.x * v.y - v.x * u.y);
}

// Vector đơn vị (Unit Vector)
// Biến mọi vector thành vector có độ dài = 1 (giữ nguyên hướng)
inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

// Giúp code dễ đọc hơn: Point3 dùng cho vị trí, Color dùng cho màu sắc
using Point3 = Vec3;
using Color = Vec3;


#endif // !VEC3_H
