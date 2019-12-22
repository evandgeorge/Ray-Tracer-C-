//
// Created by Evan George on 12/17/19.
//

#ifndef RAYTRACERCPP_PIXEL_H
#define RAYTRACERCPP_PIXEL_H


#include <cassert>

namespace raytracer {

	struct Pixel {

		Pixel(int red, int green, int blue) : red(red), green(green), blue(blue) {
			assert(red >= 0 && red <= 255);
			assert(green >= 0 && green <= 255);
			assert(blue >= 0 && blue <= 255);
		}

		Pixel() : red(0), green(0), blue(0) {}

		unsigned char getR() const { return red; }
		unsigned char getG() const { return green; }
		unsigned char getB() const { return blue; }

	private:
		unsigned char red, green, blue;
	};

}

#endif //RAYTRACERCPP_PIXEL_H
