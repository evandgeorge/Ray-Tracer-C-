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

		Vector3D normalizedVector(double x, double y, double z);

		//ACCESSORS
		double getX() const { return x; }
		double getY() const { return y; }
		double getZ() const { return z; }

		double magnitude() const;					//returns the magnitude of the vector
		double dotProduct(const Vector3D &v) const;	//returns the dot product of this and v
	private:
		double x, y, z;
	};

}
#endif //RAYTRACERCPP_VECTOR3D_H
