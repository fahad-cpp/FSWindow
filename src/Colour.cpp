#include "Colour.h"
//Colour
namespace FS {
	Colour::Colour() {
		R = 0;
		G = 0;
		B = 0;
	}
	Colour::Colour(uint8_t R, uint8_t G, uint8_t B) {
		this->R = R;
		this->G = G;
		this->B = B;
	}

	bool Colour::operator==(const Colour& op)const {
		return (this->R == op.R && this->G == op.G && this->B == op.B);
	}
	Colour Colour::operator*(const float num) {
		Vector newcol = { float(this->R * num),float(this->G * num),float(this->B * num) };
		if (newcol.x > 255) {
			newcol.x = 255;
		}
		if (newcol.y > 255) {
			newcol.y = 255;
		}
		if (newcol.z > 255) {
			newcol.z = 255;
		}
		return { uint8_t(newcol.x),uint8_t(newcol.y),uint8_t(newcol.z) };
	}
	Colour Colour::operator+(const Colour& col) {
		Vector newcol = { float(this->R + col.R),float(this->G + col.G),float(this->B + col.B) };
		if (newcol.x > 255) {
			newcol.x = 255;
		}
		if (newcol.y > 255) {
			newcol.y = 255;
		}
		if (newcol.z > 255) {
			newcol.z = 255;
		}
		return { uint8_t(newcol.x),uint8_t(newcol.y),uint8_t(newcol.z) };
	}
	float Colour::luminance() {
		return ((0.2126f * float(R)) + (0.7152f * float(G)) + (0.0722f * float(B)));
	}

	uint32_t getHex(const Colour& RGB) {
		return uint32_t((RGB.R << 16) | (RGB.G << 8) | RGB.B);
	}
	Colour hexToRGB(uint32_t hex) {
		Colour color;
		color.R = uint8_t((hex >> 16) & 0xff);
		color.G = uint8_t((hex >> 8) & 0xff);
		color.B = uint8_t(hex & 0xff);
		return color;
	}
	uint32_t rgbtoHex(Colour RGB) {
		return uint32_t((RGB.R << 16) | (RGB.G << 8) | RGB.B);
	}
}
