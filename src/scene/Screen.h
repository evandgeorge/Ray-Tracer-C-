//
// Created by Evan on 11/24/2019.
//

#ifndef RAYTRACERCPP_SCREEN_H
#define RAYTRACERCPP_SCREEN_H

#include <geometry/Ray.h>
#include "geometry/Vector3D.h"

namespace raytracer {

	class Screen {
	public:

		//construct the screen in 3D space given the origin of the camera, width, height, field of view, and rotation
		Screen(Vector3D origin,
			   const int width, const int height,
			   double hFOV,
			   double xy_rotation = 0, double z_rotation = 0, double roll = 0);

		//destructor
		~Screen();

		//return the Vector3D describing the center of a pixel located at (x, y) on the screen
		Vector3D & centerOfPixel(int x, int y) const;

	private:

		//create the corners with proper relative positions without any rotation, centered on the z axis
		void makePreRotationCorners(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner, Vector3D &bottomLeftCorner,
									double originToCorners, double inclinationFromCentralAxis, double xy_rotation, double azimuthFromCentralAxis) const;

		//rotate the corners by a given angle about a given rotation axis
		void rotateCorners(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner,
						   Vector3D &bottomLeftCorner, const Vector3D &rotationAxis, double angle) const;

		//translate the corners by the origin vector so they are in the correct position
		void moveToCameraCenter(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner,
								Vector3D &bottomLeftCorner, const Vector3D &origin) const;

		//resolution of the camera
		const int width, height;

		//distance between the origin and the center of the viewport, arbitrarily unit length
		const double spacialDepth = 1;

		//2D array of Vector3D pointers containing the position of the center of each pixel on the screen in the scene
		Vector3D ***pixelCenters;
	};

}
#endif //RAYTRACERCPP_SCREEN_H
