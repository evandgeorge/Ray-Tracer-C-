//
// Created by Evan George on 11/4/19.
//

#ifndef RAYTRACERCPP_RAY_H
#define RAYTRACERCPP_RAY_H

#include "Vector3D.h"

namespace raytracer {
	class Ray {
	public:
		Ray(const Vector3D &origin, const Vector3D &direction) : origin(origin), direction(getNormalizedVector(direction)) {}

		//returns the position of the ray at time t
		Vector3D positionAt(double t) const;

		const Vector3D origin;
		const Vector3D direction;
	};
}

#endif //RAYTRACERCPP_RAY_H
