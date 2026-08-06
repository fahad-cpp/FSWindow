#ifndef FSVECTOR_H
#define FSVECTOR_H
namespace FS {
struct Vector {
    float x;
    float y;
    float z;
    Vector(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    friend Vector operator+(const Vector, const Vector);
    friend Vector operator+(const Vector, const float);
    friend Vector operator*(const Vector, const Vector);
    friend Vector operator*(const Vector, const float);
    friend Vector operator/(const Vector, const Vector);
    friend Vector operator/(const Vector, const float);
    friend Vector operator-(const Vector, const Vector);
    friend Vector operator-(const Vector, const float);
    friend Vector operator-(const Vector);
    friend bool operator==(const Vector, const Vector);
    friend bool operator!=(const Vector vec, const Vector);
    friend Vector operator*(const float, const Vector);
    friend Vector operator/(const float, const Vector);
    friend Vector operator-(const Vector, const Vector);
    friend Vector cross(const Vector, const Vector);
    friend float dot(const Vector, const Vector);
    friend float length(const Vector);
};
}; // namespace FS
#endif
