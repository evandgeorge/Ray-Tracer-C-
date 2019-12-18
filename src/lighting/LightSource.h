//
// Created by Evan George on 12/14/19.
//

#ifndef RAYTRACERCPP_LIGHTSOURCE_H
#define RAYTRACERCPP_LIGHTSOURCE_H

#include "geometry/Vector3D.h"
#include <vector>
#include <geometry/SurfacePoint.h>
#include "Luminance.h"
#include "geometry/Shape.h"

namespace raytracer {

	class LightSource {

	public:
		LightSource(const Luminance &sourceLuminance) : sourceLuminance(sourceLuminance) {}

		//abstract method with default implementation returning the luminance at a SurfacePoint on a shape
		virtual Luminance luminanceAtPoint(const SurfacePoint &point, const std::vector<Shape*> &shapes) const = 0;

		void setLuminance(const Luminance &luminance) { sourceLuminance = luminance; }

	protected:
		//abstract method to be implemented by subclasses of LightSource that returns the shadow ray from a given point
		virtual Ray shadowRayFromPoint(const SurfacePoint &point) const = 0;

		Luminance sourceLuminance;
	};

	//return the "Luminance" or light emitted from a point p on the surface of the shape from all light sources
	Luminance globalLuminanceAtPoint(const SurfacePoint &p, const std::vector<Shape *> &shapes,
									 const std::vector<LightSource *> &lightSources);

	//returns true if the light source shadowRay belongs to is blocked before it reaches a certain shape
	bool inShadow(const Ray &shadowRay, double timeToLightSource, const std::vector<Shape*> &shapes);
}

#endif //RAYTRACERCPP_LIGHTSOURCE_H
