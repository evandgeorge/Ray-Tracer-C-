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
		//CONSTRUCTOR
		Luminance(double r, double b, double g);

		//ACCESSORS
		double getR() const { return r; }
		double getG() const { return g; }
		double getB() const { return b; }

	private:
		//red, green and blue components of the light
		double r, g, b;
	};

	//multiplies the luminance by a color, i.e. the light reflected off a colored surface instead of absorbed
	Luminance operator*(const Luminance &luminance, const Color &color);
}

#endif //RAYTRACERCPP_LUMINANCE_H
