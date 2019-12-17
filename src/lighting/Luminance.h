//
// Created by Evan George on 12/14/19.
//

#ifndef RAYTRACERCPP_LUMINANCE_H
#define RAYTRACERCPP_LUMINANCE_H

#include <cassert>
#include "geometry/Color.h"

namespace raytracer {

	class Luminance {
	public:
		//CONSTRUCTORS
		Luminance(double r, double b, double g);
		Luminance() : r(0), g(0), b(0) {}

		//ACCESSORS
		double getR() const { return r; }
		double getG() const { return g; }
		double getB() const { return b; }

		Luminance &operator+=(const Luminance &l);
	private:
		//red, green and blue components of the light
		double r, g, b;
	};

	//multiplies the luminance by a color, i.e. the light reflected off a colored surface instead of absorbed
	Luminance operator*(const Luminance &luminance, const Color &color);

	//multiplies the luminance by a scalar factor
	Luminance operator*(double f, const Luminance &luminance);
}

#endif //RAYTRACERCPP_LUMINANCE_H
