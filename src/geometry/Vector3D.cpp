//
// Created by Evan George on 11/3/19.
//

#include <cmath>
#include "Vector3D.h"

//returns the magnitude of the vector
double raytracer::Vector3D::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

//returns the dot product of this and vector
double raytracer::Vector3D::dotProduct(const Vector3D &v) const {
	return (x * v.x) + (y * v.y) + (z * v.z);
}
