#ifndef COLOUR_H
#define COLOUR_H
#include "Vector.h"
#include <vector>
#include <stdint.h>
//Colour
namespace FS {
	struct Colour {
		uint8_t R, G, B;
		Colour();
		Colour(uint8_t R, uint8_t G, uint8_t B);

		bool operator==(const Colour& op)const;
		Colour operator*(const float num);
		Colour operator+(const Colour& col);
		float luminance();
	};
	uint32_t getHex(const Colour&);
	Colour hexToRGB(uint32_t hex);
	uint32_t rgbtoHex(Colour RGB);
}
#endif
