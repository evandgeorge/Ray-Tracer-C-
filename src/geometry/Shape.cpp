//
// Created by Evan George on 12/17/19.
//

#include <cmath>
#include "Ray.h"
#include "SurfacePoint.h"
#include "Shape.h"


namespace raytracer {

	//find the first intersection a ray makes with any shape in the scene
	bool firstIntersectionInScene(const Ray &ray, SurfacePoint &surfacePoint, std::vector<Shape *> shapes) {
		double shortestTimeToShape = INFINITY;
		SurfacePoint earliestCollisionPoint;

		//find the nearest (lowest time) intersection for all shapes in the scene
		for(auto shapes_itr = shapes.begin(); shapes_itr != shapes.end(); ++shapes_itr) {
			double timeToShape;
			SurfacePoint collisionPoint;

			if((*shapes_itr)->findFirstIntersection(ray, timeToShape, collisionPoint)) {
				if(timeToShape < shortestTimeToShape) {
					shortestTimeToShape = timeToShape;
					earliestCollisionPoint = collisionPoint;
				}
			}
		}

		//if an intersection was found, set the surfacePoint reference to the intersection and return true
		if(shortestTimeToShape != INFINITY) {
			surfacePoint = earliestCollisionPoint;
			return true;
		} else
			return false;
	}
}