//
// Created by Evan George on 11/30/19.
//

#include <cstdlib>
#include "Camera.h"

namespace raytracer {

	//construct the camera in 3D space given its origin, resolution, field of view and rotation
	Camera::Camera(Vector3D origin, int width, int height, double hFOV, double xy_rotation, double z_rotation, double roll)
		: origin(origin), width(width), height(height), hFOV(hFOV), xy_rotation(xy_rotation), z_rotation(z_rotation), roll(roll),
		  cameraScreen(Screen(origin, width, height, hFOV, xy_rotation, z_rotation, roll)) {

		allocateCameraRays();
		createCameraRays();
	}

	//create or update the cameraRays
	void Camera::createCameraRays() {
		for(int x = 0; x < width; ++x) {
			for(int y = 0; y < height; ++y) {
				const Vector3D& rayOrigin = cameraScreen.centerOfPixel(x, y);
				Vector3D direction = rayOrigin - origin;

				//delete the camera ray if it's already been allocated
				if(cameraRays[x][y] != nullptr)
					delete cameraRays;

				cameraRays[x][y] = new Ray(rayOrigin, direction);
			}
		}
	}

	//destructor
	Camera::~Camera() {
		//memory cleanup
		destroyCameraRays();
	}

	//allocate dynamic memory for camera rays
	void Camera::allocateCameraRays() {
		//allocate the memory for the camera rays
		cameraRays = new Ray **[width];
		for(int x = 0; x < width; ++x) {
			cameraRays[x] = new Ray *[height];

			for(int y = 0; y < height; ++y)
				cameraRays[x][y] = nullptr;
		}
	}

	//cleanup dynamic memory for camera rays
	void Camera::destroyCameraRays() {
		for(int x = 0; x < width; ++x) {
			for(int y = 0; y < height; ++y)
				delete cameraRays[x][y];

			delete[] cameraRays[x];
		}

		delete[] cameraRays;
		cameraRays = nullptr;
	}

	//recreates cameraScreen
	void Camera::rebuildScreen() {
		cameraScreen = Screen(origin, width, height, hFOV, xy_rotation, z_rotation, roll);
	}
}