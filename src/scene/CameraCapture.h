//
// Created by Evan George on 12/17/19.
//

#ifndef RAYTRACERCPP_CAMERACAPTURE_H
#define RAYTRACERCPP_CAMERACAPTURE_H

#include <lighting/Luminance.h>
#include <geometry/Ray.h>
#include <geometry/Shape.h>
#include <vector>
#include <lighting/LightSource.h>

namespace raytracer {

	//stores raw luminance data for each camera ray, analogous to a camera's sensor information

	class CameraCapture {
	public:
		//constructor
		CameraCapture(int width, int height);

		//destructor
		~CameraCapture();

		Luminance &luminanceAt(int x, int y) { return rayLuminance[x][y]; }
	private:
		Luminance **rayLuminance;		//luminance of all camera rays
		int width, height;				//resolution of capture
	};
}

#endif //RAYTRACERCPP_CAMERACAPTURE_H