//
// Created by Evan George on 11/4/19.
//

#ifndef RAYTRACERCPP_COLOR_H
#define RAYTRACERCPP_COLOR_H

#include <assert.h>

namespace raytracer {

	//structure storing rgb components of color

	struct Color {
		Color(double r, double g, double b) : r(r), g(g), b(b) {
			assert(r <= 1 && r >= 0);
			assert(g <= 1 && g >= 0);
			assert(b <= 1 && b >= 0);
		}

		const double r, g, b;
	};
}

#endif //RAYTRACERCPP_COLOR_H