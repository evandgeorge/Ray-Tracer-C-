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

//returns *this + v
raytracer::Vector3D raytracer::Vector3D::operator+(const raytracer::Vector3D &v) const {
	return {x + v.x,
		y + v.y,
		z + v.z};
}

//returns *this - v
raytracer::Vector3D raytracer::Vector3D::operator-(const raytracer::Vector3D &v) const {
	return {x - v.x,
		y - v.y,
		z - v.z};
}

//returns *this * f (scalar)
raytracer::Vector3D raytracer::Vector3D::operator*(double f) const {
	return {x * f,
		y * f,
		z * f};
}

//returns *this / f (scalar)
raytracer::Vector3D raytracer::Vector3D::operator/(double d) const {
	return {x / d,
		y / d,
		z / d};
}

//returns -(*this)
raytracer::Vector3D raytracer::Vector3D::operator-() const {
	return {-x,
		-y,
		-z};
}

//returns a Vector3D in the direction of (x, y, z) with size 1
raytracer::Vector3D raytracer::getNormalizedVector(const Vector3D &v) {
	return v / v.magnitude();
}
