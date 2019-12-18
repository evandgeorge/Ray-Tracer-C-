//
// Created by Evan George on 11/30/19.
//

#ifndef RAYTRACERCPP_CAMERA_H
#define RAYTRACERCPP_CAMERA_H

#include <geometry/Vector3D.h>
#include <geometry/Ray.h>
#include "Screen.h"
#include "CameraCapture.h"

namespace raytracer {

	class Camera {
	public:

		//construct the camera in 3D space given its origin, resolution, field of view and rotation
		Camera(Vector3D origin,
			   int width, int height,
			   double hFOV,
			   double xy_rotation = 0, double z_rotation = 0, double roll = 0);

		//destructor
		~Camera();

		//capture the camera image and return it in CameraCapture format
		CameraCapture capture(const std::vector<Shape *> &shapes, const std::vector<LightSource *> &lightSources, int maxRecursionDepth);

	private:
		Vector3D origin;				//origin/aperture of the camera
		int width, height;				//resolution of the camera
		double hFOV;					//horizontal field of view of the camera

		double xy_rotation;				//rotation of the camera in the xy plane, about the z axis
		double z_rotation;				//rotation of the camera off the z axis
		double roll;					//rotation of the camera about its axis

		Screen cameraScreen;			//screen of the camera
		Ray ***cameraRays = nullptr;	//2D array of pointers to the pixel's camera rays

		//allocate dynamic memory for camera rays
		void allocateCameraRays();

		//cleanup dynamic memory for camera rays
		void destroyCameraRays();

		//methods for creating or updating cameraScreen and cameraRays
		void rebuildScreen();
		void createCameraRays();

	};

	//recursively find the luminance of a single camera ray by finding the matte luminance and reflective luminance
	Luminance luminanceOfRay(const Ray &ray, const std::vector<Shape*> &shapes, const std::vector<LightSource*> &lightSources, int remainingReflectionDepth);
}

#endif //RAYTRACERCPP_CAMERA_H