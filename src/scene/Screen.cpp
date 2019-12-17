//
// Created by Evan on 11/24/2019.
//

#include "Screen.h"
#include <cmath>

namespace raytracer {

	//construct the screen in 3D space given the origin of the camera, width, height, field of view, and rotation
	Screen::Screen(Vector3D origin,
				   int width, int height,
				   double hFOV,
				   double xy_rotation, double z_rotation, double roll)
				   : width(width), height(height) {

		//initialize 2D array
		pixelCenters = new Vector3D *[width];
		for(int x = 0; x < width; ++x)
			pixelCenters[x] = new Vector3D[height];

		//width and height of the screen in 3D space, dependent on the field of view and spacial depth
		double spacialWidth = 2 * SPACIAL_DEPTH * tan(hFOV / 2);
		double spacialHeight = spacialWidth * height / width;

		//find the center of each pixel in the screen
		setPixelCenters(getScreenCorners(origin, spacialWidth, spacialHeight, xy_rotation, z_rotation, roll));
	}

	ScreenCorners getScreenCorners(Vector3D origin, double spacialWidth, double spacialHeight, double xy_rotation, double z_rotation, double roll) {
		ScreenCorners corners;
		corners.topLeft = Vector3D(-spacialHeight / 2, spacialWidth / 2, SPACIAL_DEPTH);
		corners.topRight = Vector3D(-spacialHeight / 2, -spacialWidth / 2, SPACIAL_DEPTH);
		corners.bottomLeft = Vector3D(spacialHeight / 2, spacialWidth / 2, SPACIAL_DEPTH);
		corners.bottomRight = Vector3D(spacialHeight / 2, -spacialWidth / 2, SPACIAL_DEPTH);

		//rotate corners about z axis, in xy plane
		Vector3D azimuthalAxis = sphericalToCartesian(1, 0, 0);
		rotateCorners(corners, azimuthalAxis, xy_rotation);

		//rotate corners off z axis
		Vector3D inclinationAxis = sphericalToCartesian(1, M_PI / 2, xy_rotation + M_PI / 2);
		rotateCorners(corners, inclinationAxis, z_rotation);

		//rotate corners about the camera's center axis
		Vector3D centralAxis = -(corners.topLeft + corners.topRight + corners.bottomRight + corners.bottomLeft);
		rotateCorners(corners, centralAxis, roll);

		//move from the origin to the camera center
		moveToCameraCenter(corners, origin);

		return corners;
	}

	//assigns the position of the center of each pixel in 3D space
	void Screen::setPixelCenters(const ScreenCorners &corners) {
		//difference in position between neighboring pixels
		Vector3D horizontalDifference = (corners.topRight - corners.topLeft) / width;
		Vector3D verticalDifference = (corners.bottomLeft - corners.topLeft) / height;

		for(int x = 0; x < width; ++x)
			for(int y = 0; y < height; ++y)
				pixelCenters[x][y] = Vector3D(corners.topLeft + (horizontalDifference * (x + .5)) + (verticalDifference * (y + .5)));
	}

	//destructor
	Screen::~Screen() {
		//memory cleanup
		for(int x = 0; x < width; ++x)
			delete[] pixelCenters[x];

		delete[] pixelCenters;
		pixelCenters = nullptr;
	}

	//rotate the corners by an angle about a rotation axis
	void rotateCorners(ScreenCorners &corners, const Vector3D &rotationAxis, double angle) {
		corners.topLeft = corners.topLeft.rotatedAbout(rotationAxis, angle);
		corners.topRight = corners.topRight.rotatedAbout(rotationAxis, angle);
		corners.bottomRight = corners.bottomRight.rotatedAbout(rotationAxis, angle);
		corners.bottomLeft = corners.bottomLeft.rotatedAbout(rotationAxis, angle);
	}

	//translate the corners by the origin vector so they are in the correct position
	void moveToCameraCenter(ScreenCorners &corners, const Vector3D &origin) {
		corners.topLeft = corners.topLeft + origin;
		corners.topRight = corners.topRight + origin;
		corners.bottomRight = corners.topRight + origin;
		corners.bottomLeft = corners.bottomLeft + origin;
	}
}