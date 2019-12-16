//
// Created by Evan George on 12/15/19.
//

#ifndef RAYTRACERCPP_DIRECTIONALLIGHT_H
#define RAYTRACERCPP_DIRECTIONALLIGHT_H

#include "LightSource.h"

namespace raytracer {

	class DirectionalLight : public LightSource {
	public:
		DirectionalLight(const Luminance &sourceLuminance, Vector3D direction) : LightSource(sourceLuminance), direction(getNormalizedVector(direction)) {};

		//returns the luminance at a SurfacePoint on a shape
		Luminance luminanceAtPoint(const SurfacePoint &point, const std::vector<Shape*> &shapes) const override;

		//returns the shadow ray at a SurfacePoint on a shape
		Ray shadowRayFromPoint(const SurfacePoint &point) const override;

	private:
		Vector3D direction;
	};

}

#endif //RAYTRACERCPP_DIRECTIONALLIGHT_H