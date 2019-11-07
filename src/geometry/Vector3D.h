//
// Created by Evan George on 11/3/19.
//

#ifndef RAYTRACERCPP_VECTOR3D_H
#define RAYTRACERCPP_VECTOR3D_H

namespace raytracer {

	class Vector3D {
	public:
		//CONSTRUCTOR
		Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
		Vector3D() : x(0), y(0), z(0) {}

		//ACCESSORS
		double getX() const { return x; }
		double getY() const { return y; }
		double getZ() const { return z; }

		double magnitude() const;						//returns the magnitude of the vector
		double dotProduct(const Vector3D &v) const;		//returns the dot product of *this and v
		Vector3D crossProduct(const Vector3D &v) const;	//returns *this cross v

		//returns *this rotated about the rotation axis described by v. It is not required that v is normalized
		raytracer::Vector3D rotatedAbout(const raytracer::Vector3D &v, double angle) const;

		//OPERATORS
		bool operator==(const Vector3D &v) const;		//returns true if the vectors are exactly identical
		Vector3D operator-(const Vector3D &v) const;	//returns *this - v
		Vector3D operator+(const Vector3D &v) const;	//returns *this + v
		Vector3D operator*(double f) const;				//returns *this * f (scalar)
		Vector3D operator/(double d) const;				//returns *this / f (scalar)
		Vector3D operator-() const;						//returns -(*this)
	private:
		double x, y, z;
	};

	//returns a Vector3D in the direction of (x, y, z) with size 1
	Vector3D getNormalizedVector(const Vector3D &v);
	Vector3D sphericalToCartesian(double r, double theta, double phi);
}
#endif //RAYTRACERCPP_VECTOR3D_H
