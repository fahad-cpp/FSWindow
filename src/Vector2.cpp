#include "Vector2.h"
#include <cmath>
namespace FS {
Vector2 operator+(const Vector2 &vec1, const Vector2 &vec2) {
    return { vec1.x + vec2.x, vec1.y + vec2.y };
}
Vector2 operator+(const Vector2 &vec, const float &val) {
    return { vec.x + val, vec.y + val };
}
Vector2 operator*(const Vector2 &vec1, const Vector2 &vec2) {
    return { vec1.x * vec2.x, vec1.y * vec2.y };
}
Vector2 operator*(const Vector2 &vec, const float &val) {
    return { val * vec.x, val * vec.y };
}
Vector2 operator/(const Vector2 &vec1, const Vector2 &vec2) {
    return { vec1.x / vec2.x, vec1.y / vec2.y };
}
Vector2 operator/(const Vector2 &vec, const float &val) {
    return { vec.x / val, vec.y / val };
}
Vector2 operator-(const Vector2 &vec1, const Vector2 &vec2) {
    return { vec1.x - vec2.x, vec1.y - vec2.y };
}
Vector2 operator-(const Vector2 &vec, const float &val) {
    return { vec.x - val, vec.y - val };
}
Vector2 operator-(const Vector2 &vec) {
    return { -vec.x, -vec.y };
}
bool operator==(const Vector2 &vec1, const Vector2 &vec2) {
    return ((vec1.x == vec2.x) && (vec1.y == vec2.y));
}
bool operator!=(const Vector2 &vec1, const Vector2 &vec2) {
    return ((vec1.x != vec2.x) || (vec1.y != vec2.y));
}
Vector2 operator*(const float val, const Vector2 &vec) {
    return { val * vec.x, val * vec.y };
}
Vector2 operator/(const float val, const Vector2 &vec) {
    return { val / vec.x, val / vec.y };
}
float dot(const Vector2 &vec1, const Vector2 &vec2) {
    return ((vec1.x * vec2.x) + (vec1.y * vec2.y));
}
float length(const Vector2 &vec) {
    return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}
} // namespace FS
