//
// Created by Evan George on 11/3/19.
//

#include <cmath>
#include "Vector3D.h"

//returns the magnitude of the vector
double raytracer::Vector3D::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

//returns the dot product of this and v
double raytracer::Vector3D::dotProduct(const Vector3D &v) const {
	return (x * v.x) + (y * v.y) + (z * v.z);
}

//returns true if the vectors are exactly identical
bool raytracer::Vector3D::operator==(const raytracer::Vector3D &v) const {
	return (x == v.x) && (y == v.y) && (z == v.z);
}

//returns a Vector3D in the direction of (x, y, z) with size 1
raytracer::Vector3D raytracer::getNormalizedVector(double x, double y, double z) {
	double magnitude = sqrt(x*x + y*y + z*z);
	return raytracer::Vector3D(x / magnitude, y / magnitude, z / magnitude);
}
