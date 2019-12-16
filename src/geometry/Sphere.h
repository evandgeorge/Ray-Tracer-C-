//
// Created by Evan George on 11/4/19.
//

#ifndef RAYTRACERCPP_SPHERE_H
#define RAYTRACERCPP_SPHERE_H

#include "Shape.h"

namespace raytracer {
	class Sphere : public Shape {
	public:
		//initialize center and radius, as well as general Shape members color and reflectivity
		Sphere(const Vector3D &center, double radius, const Color &color, double ref) : Shape(color, ref), center(center), radius(radius) {}

		//finds the time of the first intersection between the ray and *this
		//returns true if non-negative intersections are found, false if not
		bool findFirstIntersection(const raytracer::Ray &ray, double &time, raytracer::SurfacePoint &surfacePoint) const override;
	private:
		Vector3D center;
		double radius;
	};
}


#endif //RAYTRACERCPP_SPHERE_H
