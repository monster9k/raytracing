#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
public:
    // Constructor mặc định
    Ray() {}

    // Constructor với Gốc (origin) và Hướng (direction)
    Ray(const Point3& origin, const Vec3& direction)
        : orig(origin), dir(direction)
    {
    }

    // Getter (Lấy dữ liệu)
    Point3 origin() const { return orig; }
    Vec3 direction() const { return dir; }

    // HÀM QUAN TRỌNG NHẤT: P(t) = A + t*b
    // Trả về tọa độ điểm tại thời gian t
    Point3 at(double t) const {
        return orig + t * dir;
    }

public:
    Point3 orig; // Điểm xuất phát A
    Vec3 dir;    // Hướng đi b
};

#endif // !RAY_H
