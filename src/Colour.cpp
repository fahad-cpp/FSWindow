#include "Colour.h"
#include <algorithm>
// Colour
namespace FS {
Colour::Colour() {
    R = 0;
    G = 0;
    B = 0;
}
Colour::Colour(float R, float G, float B) {
    this->R = uint8_t(std::clamp(R, 0.f, 255.f));
    this->G = uint8_t(std::clamp(G, 0.f, 255.f));
    this->B = uint8_t(std::clamp(B, 0.f, 255.f));
}

bool Colour::operator==(const Colour &op) const {
    return (this->R == op.R && this->G == op.G && this->B == op.B);
}
Colour Colour::operator*(const float num) const {
    return { this->R * num, this->G * num, this->B * num };
}
Colour Colour::operator*(const Colour &col) const {
    return { float(this->R * col.R), float(this->G * col.G), float(this->B * col.B) };
}
Colour Colour::operator+(const Colour &col) const {
    return { float(this->R + col.R), float(this->G + col.G), float(this->B + col.B) };
}
Colour Colour::operator+(const float &num) const {
    return { this->R + num, this->G + num, this->B + num };
}
Colour Colour::operator-(const Colour &col) const {
    return { float(this->R - col.R), float(this->G - col.G), float(this->B - col.B) };
}
Colour operator*(const float num, const Colour &color) {
    return {
        color.R * num,
        color.G * num,
        color.B * num
    };
}
float Colour::luminance() {
    return ((0.2126f * float(R)) + (0.7152f * float(G)) + (0.0722f * float(B)));
}

uint32_t getHex(const Colour &RGB) {
    return uint32_t((RGB.R << 16) | (RGB.G << 8) | RGB.B);
}
Colour hexToRGB(uint32_t hex) {
    Colour color;
    color.R = uint8_t((hex >> 16) & 0xff);
    color.G = uint8_t((hex >> 8) & 0xff);
    color.B = uint8_t(hex & 0xff);
    return color;
}
uint32_t rgbtoHex(const Colour &RGB) {
    return uint32_t((RGB.R << 16) | (RGB.G << 8) | RGB.B);
}

// Colourf
Colourf::Colourf() {
    R = 0.f;
    G = 0.f;
    B = 0.f;
}
Colourf::Colourf(float R, float G, float B) {
    this->R = std::clamp(R, 0.f, 1.f);
    this->G = std::clamp(G, 0.f, 1.f);
    this->B = std::clamp(B, 0.f, 1.f);
}
bool Colourf::operator==(const Colourf &op) const {
    return (this->R == op.R && this->G == op.G && this->B == op.B);
}
Colourf Colourf::operator*(const float num) const {
    Colourf color;
    color.R = this->R * num;
    color.G = this->G * num;
    color.B = this->B * num;
    return color;
}
Colourf Colourf::operator*(const Colourf &col) const {
    Colourf color;
    color.R = this->R * col.R;
    color.G = this->G * col.G;
    color.B = this->B * col.B;
    return color;
}
Colourf Colourf::operator+(const Colourf &op) const {
    Colourf color;
    color.R = this->R + op.R;
    color.G = this->G + op.G;
    color.B = this->B + op.B;
    return color;
}
Colourf Colourf::operator+(const float &num) const {
    Colourf color;
    color.R = this->R + num;
    color.G = this->G + num;
    color.B = this->B + num;
    return color;
}
Colourf Colourf::operator-(const Colourf &col) const {
    Colourf color;
    color.R = this->R - col.R;
    color.G = this->G - col.G;
    color.B = this->B - col.B;
    return color;
}
Colourf Colourf::operator/(const float num) const {
    if (num == 0.f) {
        return {};
    }
    Colourf color;
    color.R = this->R / num;
    color.G = this->G / num;
    color.B = this->B / num;
    return color;
}
Colourf operator*(const float num, const Colourf &col) {
    Colourf color;
    color.R = col.R * num;
    color.G = col.G * num;
    color.B = col.B * num;
    return color;
}
uint32_t rgbtoHex(const Colourf &colorf) {
    Colour color{ colorf.R * 255.f, colorf.G * 255.f, colorf.B * 255.f };
    return rgbtoHex(color);
}
Colourf hexToRGBf(uint32_t hex) {
    Colour color = hexToRGB(hex);
    Colourf colorf = { color.R / 255.f, color.G / 255.f, color.B / 255.f };
    return colorf;
}
} // namespace FS
