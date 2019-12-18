//
// Created by Evan George on 12/14/19.
//

#include "Luminance.h"

namespace raytracer {

	raytracer::Luminance::Luminance(double r, double g, double b) : r(r), g(g), b(b) {
		//check that all components are non-negative
		assert(r >= 0);
		assert(g >= 0);
		assert(b >= 0);
	}

	Luminance &Luminance::operator+=(const Luminance &l) {
		this->r += l.r;
		this->g += l.g;
		this->b += l.b;

		return *this;
	}

	//adds luminances
	Luminance operator+(const Luminance &l1, const Luminance &l2) {
		return {l1.getR() + l2.getR(),
				l1.getG() + l2.getG(),
				l1.getB() + l2.getB()};
	}

	//multiplies the luminance by a color, i.e. the light reflected off a colored surface instead of absorbed
	Luminance operator*(const Luminance &luminance, const Color &color) {
		return {luminance.getR() * color.r,
				luminance.getG() * color.g,
				luminance.getB() * color.b};
	}

	//multiplies the luminance by a scalar factor
	Luminance operator*(double f, const Luminance &luminance) {
		return {luminance.getR() * f,
				luminance.getG() * f,
				luminance.getB() * f};
	}
}