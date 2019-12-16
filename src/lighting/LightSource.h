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
		void setLuminance(const Luminance &luminance) { rayLuminance = luminance; }
		virtual Luminance luminanceAtPoint(const SurfacePoint &point, const std::vector<Shape> &shapes) const = 0;

	private:
		Luminance rayLuminance;
	};

	//return the "Luminance" or light emitted from a point p on the surface of the shape from all light sources
	Luminance luminanceAtPoint(const SurfacePoint &p, const std::vector<LightSource> &lightSources, const std::vector<Shape> &shapes);
}

#endif //RAYTRACERCPP_LIGHTSOURCE_H
