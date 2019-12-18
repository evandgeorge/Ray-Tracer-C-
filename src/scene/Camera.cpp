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

	//capture the camera image and return it in CameraCapture format
	CameraCapture Camera::capture(const std::vector<Shape *> &shapes, const std::vector<LightSource *> &lightSources, int maxRecursionDepth) {
		CameraCapture cameraCapture(width, height);

		//find the luminance of each camera ray and store it in the CameraCapture object
		for(int x = 0; x < width; ++x)
			for(int y = 0; y < height; ++y)
				cameraCapture.luminanceAt(x, y) = luminanceOfRay(*cameraRays[x][y], shapes, lightSources, maxRecursionDepth);

		return cameraCapture;
	}

	//recursively find the luminance of a single camera ray by finding the matte luminance and reflective luminance
	Luminance luminanceOfRay(const Ray &ray, const std::vector<Shape *> &shapes, const std::vector<LightSource *> &lightSources, int remainingReflectionDepth) {
		//if the max recursion depth is reached, return 0 luminance
		if(remainingReflectionDepth == 0)
			return {0, 0, 0};

		SurfacePoint intersectionPoint;
		bool hasIntersection = firstIntersectionInScene(ray, intersectionPoint, shapes);

		//if the ray does not intersect with a shape, return 0 luminance
		if(!hasIntersection)
			return {0, 0, 0};

		//calculate the total matte luminance at the point for a perfectly matte surface
		Luminance totalMatteLuminance = globalLuminanceAtPoint(intersectionPoint, shapes, lightSources);

		//surface normal and direction of the incident ray used for calculating the direction of the reflected ray
		const Vector3D& surfaceNormal = intersectionPoint.getSurfaceNormal();
		const Vector3D& incidentLightDirection = ray.direction;

		//calculate the reflected ray direction
		Vector3D reflectionDirection = incidentLightDirection - surfaceNormal * (incidentLightDirection.dotProduct(surfaceNormal)) * 2;

		//make the reflected ray origin be slightly above where the incident ray hits the surface to prevent it hitting the surface again
		Vector3D reflectionOrigin = intersectionPoint.getPosition() + surfaceNormal * 1e-12;

		//create the reflection ray
		Ray reflectionRay(reflectionOrigin, reflectionDirection);

		//the reflective and matte factors are compliments because the more light reflected -> less light scattered
		double reflectiveFactor = intersectionPoint.getShapePointer()->getReflectivity();
		double matteFactor = 1 - intersectionPoint.getShapePointer()->getReflectivity();

		//calculate the total reflective luminance at the point for a perfectly smooth surface
		Luminance reflectionLuminance = luminanceOfRay(reflectionRay, shapes, lightSources, remainingReflectionDepth - 1);

		//return a combination of the two based on their respective factors
		return matteFactor * totalMatteLuminance + reflectiveFactor * reflectionLuminance;
	}
}