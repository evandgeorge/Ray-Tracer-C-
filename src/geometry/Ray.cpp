//
// Created by Evan George on 11/4/19.
//

#include "Ray.h"

//returns the position of the ray at time t
raytracer::Vector3D raytracer::Ray::positionAt(double t) const {
	return origin + direction * t;
}