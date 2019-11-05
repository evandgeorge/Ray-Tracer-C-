//
// Created by Evan George on 11/4/19.
//

#ifndef RAYTRACERCPP_SHAPE_H
#define RAYTRACERCPP_SHAPE_H

#include "Color.h"
#include "Vector3D.h"
#include "Ray.h"

namespace raytracer {
	class Shape {
	public:
		Shape(const Color &c, double r) : color(c), reflectivity(r) {}

		//abstract method to be implemented by subclasses of shape that find the time of the first intersection between the ray and the shape
		virtual double findIntersection(const Ray &ray) const = 0;
	private:
		Color color;
		double reflectivity;	//Proportion of light that is reflected, complement of proportion of light that is scattered (matte reflectance)
	};
}

#endif //RAYTRACERCPP_SHAPE_H
