//
// Created by Evan George on 12/14/19.
//

#include "Luminance.h"

namespace raytracer {

	raytracer::Luminance::Luminance(double r, double b, double g) : r(r), g(g), b(b) {
		//check that all components are non-negative
		assert(r >= 0);
		assert(g >= 0);
		assert(b >= 0);
	}

	//multiplies the luminance by a color, i.e. the light reflected off a colored surface instead of absorbed
	Luminance operator*(const Luminance &luminance, const Color &color) {
		return {luminance.getR() * color.r,
				luminance.getG() * color.g,
				luminance.getB() * color.b};
	}

}