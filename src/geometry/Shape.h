//
// Created by Evan George on 11/4/19.
//

#ifndef RAYTRACERCPP_SHAPE_H
#define RAYTRACERCPP_SHAPE_H

#include <vector>
#include "Color.h"
#include "Vector3D.h"
#include "Ray.h"
#include "SurfacePoint.h"

namespace raytracer {
	class Shape {
	public:
		Shape(const Color &c, double r) : color(c), reflectivity(r) {}

		//abstract method to be implemented by subclasses of shape that find the time of the first intersection between the ray and the shape
		//returns true if non-negative intersections are found, false if not
		virtual bool findFirstIntersection(const Ray &ray, double &time, SurfacePoint &surfacePoint) const = 0;

		const Color &getColor() const { return color; }
		double getReflectivity() const { return reflectivity; }
	private:
		//abstract method to be implemented by subclasses of shape that returns the surface normal at a point on the shapes surface
		virtual Vector3D surfaceNormalAt(const Vector3D &point) const = 0;

		Color color;
		double reflectivity;	//Proportion of light that is reflected, complement of proportion of light that is scattered (matte reflectance)
	};

	//find the first intersection a ray makes with any shape in the scene
	bool firstIntersectionInScene(const Ray &ray, SurfacePoint &surfacePoint, std::vector<Shape *> shapes);
}

#endif //RAYTRACERCPP_SHAPE_H
