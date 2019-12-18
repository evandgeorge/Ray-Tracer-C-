//
// Created by Evan George on 12/15/19.
//

#include <cmath>
#include "DirectionalLight.h"

namespace raytracer {

	Luminance DirectionalLight::luminanceAtPoint(const SurfacePoint &point, const std::vector<Shape*> &shapes) const {
		Ray shadowRay = shadowRayFromPoint(point);

		//if the point is in shadow return 0 Luminance
		if(inShadow(shadowRay, INFINITY, shapes))
			return {0, 0, 0};

		//ratio between the intensity of emitted (scattered) light to the intensity of the incident light, for a perfectly matte surface
		double diffuseFactor = point.getSurfaceNormal().dotProduct(shadowRay.direction);

		return diffuseFactor * sourceLuminance * point.getShapePointer()->getColor();
	}

	Ray DirectionalLight::shadowRayFromPoint(const SurfacePoint &point) const {
		return {point.getPosition() + direction * 1e-12, direction};
	}

}