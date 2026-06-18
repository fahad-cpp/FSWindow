#ifndef COLOUR_H
#define COLOUR_H
#include <stdint.h>
// Colour
namespace FS {
struct Colour {
    uint8_t R, G, B;
    Colour();
    Colour(float R, float G, float B);

    bool operator==(const Colour &op) const;
    Colour operator*(const float num);
    Colour operator*(const Colour &col);
    Colour operator+(const Colour &col);
    Colour operator+(const float &num);
    Colour operator-(const Colour &col);
    friend Colour operator*(const float num, const Colour &color);
    float luminance();
};
Colour hexToRGB(uint32_t hex);
uint32_t rgbtoHex(const Colour &RGB);
// Colourf
struct Colourf {
    float R, G, B;
    Colourf();
    Colourf(float R, float G, float B);
    bool operator==(const Colourf &op) const;
    Colourf operator*(const float num);
    Colourf operator*(const Colourf& col);
    Colourf operator+(const Colourf &col);
    Colourf operator+(const float &num);
    Colourf operator-(const Colourf &col);
    Colourf operator/(const float num);
    friend Colourf operator*(const float num, const Colourf &col);
};
Colourf hexToRGBf(uint32_t hex);
uint32_t rgbtoHex(const Colourf &RGB);
} // namespace FS
#endif
