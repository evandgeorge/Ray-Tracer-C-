//
// Created by Evan George on 12/15/19.
//

#include "LightSource.h"

namespace raytracer {

	Luminance luminanceAtPoint(const SurfacePoint &p, const std::vector<LightSource> &lightSources, const std::vector<Shape> &shapes) {

		Luminance luminance(0, 0,0);

		for(auto lightSources_itr = lightSources.begin(); lightSources_itr != lightSources.end(); ++lightSources_itr)
			luminance += lightSources_itr->luminanceAtPoint(p, shapes);

		return luminance;
	}

}