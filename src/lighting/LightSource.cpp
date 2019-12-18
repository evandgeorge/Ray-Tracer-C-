//
// Created by Evan George on 12/15/19.
//

#include "LightSource.h"

namespace raytracer {

	Luminance globalLuminanceAtPoint(const SurfacePoint &p, const std::vector<Shape *> &shapes,
									 const std::vector<LightSource *> &lightSources) {

		Luminance luminance(0, 0, 0);

		for(auto lightSources_itr = lightSources.begin(); lightSources_itr != lightSources.end(); ++lightSources_itr)
			luminance += (*lightSources_itr)->luminanceAtPoint(p, shapes);

		return luminance;
	}

	//returns true if the shadowRay is blocked before it reaches its light source
	bool inShadow(const Ray &shadowRay, double timeToLightSource, const std::vector<Shape*> &shapes) {
		double timeToShape;
		SurfacePoint pointOnShape;

		for(auto shapes_itr = shapes.begin(); shapes_itr != shapes.end(); ++shapes_itr) {
			if((*shapes_itr)->findFirstIntersection(shadowRay, timeToShape, pointOnShape)) {

				//return true if the time to reach the shape is less than to reach the light source
				if(timeToShape < timeToLightSource)
					return true;
			}
		}

		return false;
	}
}