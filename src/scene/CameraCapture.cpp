//
// Created by Evan George on 12/17/19.
//

#include "CameraCapture.h"

namespace raytracer {

	CameraCapture::CameraCapture(int width, int height) : width(width), height(height) {
		//initialize 2D array
		rayLuminance = new Luminance*[width];

		for(int x = 0; x < width; ++x)
			rayLuminance[x] = new Luminance[height];
	}

	//destructor
	CameraCapture::~CameraCapture() {
		//memory cleanup
		for(int x = 0; x < width; ++x)
			delete[] rayLuminance[x];

		delete[] rayLuminance;
		rayLuminance = nullptr;
	}

}