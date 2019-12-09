//
// Created by Evan George on 11/30/19.
//

#include <cstdlib>
#include "Camera.h"

namespace raytracer {

	//construct the camera in 3D space given its origin, resolution, field of view and rotation
	Camera::Camera(Vector3D origin, int width, int height, double hFOV, double xy_rotation, double z_rotation, double roll)
		: origin(origin), width(width), height(height), hFOV(hFOV), xy_rotation(xy_rotation), z_rotation(z_rotation), roll(roll) {

		createScreen();
		createCameraRays();
	}

	//create or update the cameraRays
	void Camera::createCameraRays() {
		if(cameraRays != nullptr)
			destroyCameraRays();

		//allocate the memory for the camera rays
		cameraRays = new Ray **[width];
		for(int x = 0; x < width; ++x)
			cameraRays[x] = new Ray *[height];

		for(int x = 0; x < width; ++x) {
			for(int y = 0; y < height; ++y) {
				Vector3D& rayOrigin = cameraScreen->centerOfPixel(x, y);
				Vector3D direction = rayOrigin - origin;

				cameraRays[x][y] = new Ray(rayOrigin, direction);
			}
		}
	}

	//destructor
	Camera::~Camera() {
		//memory cleanup
		delete cameraScreen;
		cameraScreen = nullptr;

		destroyCameraRays();
	}

	void Camera::destroyCameraRays() {
		for(int x = 0; x < width; ++x) {
			for(int y = 0; y < height; ++y)
				delete cameraRays[x][y];

			delete[] cameraRays[x];
		}

		delete[] cameraRays;
		cameraRays = nullptr;
	}

	void Camera::createScreen() {
		if(cameraScreen != nullptr)
			delete cameraScreen;

		cameraScreen = new Screen(origin, width, height, hFOV, xy_rotation, z_rotation, roll);
	}
}