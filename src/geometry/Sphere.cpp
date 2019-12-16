//
// Created by Evan George on 11/4/19.
//

#include <cmath>
#include "Sphere.h"

//finds the time of the first intersection between the ray and *this
//returns true if non-negative intersections are found, false if not
bool raytracer::Sphere::findFirstIntersection(const raytracer::Ray &ray, double &time, raytracer::SurfacePoint &surfacePoint) const {
	//ray-sphere intersection equation is quadratic (in the form ax^2 + bx + c = 0)
	//where x is the time of intersection and a, b and c are defined as follows:

	double a = 1;
	double b = 2 * ray.direction.dotProduct(ray.origin - this->center);
	double c = (ray.origin - this->center).dotProduct(ray.origin - this->center) - pow(radius, 2);

	//calculate the discriminant to tell if there are solutions
	double discriminant = b*b - 4*a*c;

	if(discriminant < 0)
		return false;
	else {
		double t1 = (-b - sqrt(discriminant)) / (2 * a);
		double t2 = (-b + sqrt(discriminant)) / (2 * a);

		//set &time to the smallest non-negative solution, return false if neither solutions are non-negative
		if(t1 >= 0)
			time = t1;
		else if(t2 >= 0)
			time = t2;
		else
			return false;

		Vector3D intersectionPoint = ray.positionAt(time);
		Vector3D surfaceNormal = surfaceNormalAt(intersectionPoint);

		surfacePoint = SurfacePoint(intersectionPoint, surfaceNormal, this);

		return true;
	}
}