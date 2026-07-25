#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>
namespace FS {
struct Vector2 {
    float x;
    float y;
    Vector2(float x = 0, float y = 0) {
        Vector2::x = x;
        Vector2::y = y;
    }
    friend Vector2 operator+(const Vector2, const Vector2);
    friend Vector2 operator+(const Vector2, const float);
    friend Vector2 operator*(const Vector2, const Vector2);
    friend Vector2 operator*(const Vector2, const float);
    friend Vector2 operator/(const Vector2, const Vector2);
    friend Vector2 operator/(const Vector2, const float);
    friend Vector2 operator-(const Vector2, const Vector2);
    friend Vector2 operator-(const Vector2, const float);
    friend Vector2 operator-(const Vector2);
    friend bool operator==(const Vector2, const Vector2);
    friend bool operator!=(const Vector2 vec, const Vector2);
    friend Vector2 operator*(const float, const Vector2);
    friend Vector2 operator/(const float, const Vector2);
    friend float dot(const Vector2, const Vector2);
    friend float length(const Vector2);
};
} // namespace FS
#endif
