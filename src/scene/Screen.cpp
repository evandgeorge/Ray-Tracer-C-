//
// Created by Evan on 11/24/2019.
//

#include <cassert>
#include "Screen.h"
#include <cmath>

namespace raytracer {

	//construct the screen in 3D space given the origin of the camera, width, height, field of view, and rotation
	Screen::Screen(Vector3D origin,
				   const int width, const int height,
				   double hFOV,
				   double xy_rotation, double z_rotation, double roll)
			: width(width), height(height) {

		//initialize 2D pointer array
		pixelCenters = new Vector3D **[width];
		for(int x = 0; x < width; ++x)
			pixelCenters[x] = new Vector3D *[height];


		//width and height of the screen in 3D space, dependent on the field of view and spacial depth
		double spacialWidth = 2 * spacialDepth * tan(hFOV / 2);
		double spacialHeight = spacialWidth * height / width;

		double originToCorners = sqrt(pow(spacialWidth / 2, 2) + pow(spacialHeight / 2, 2) + spacialDepth);
		double azimuthFromCentralAxis = hFOV / 2;
		double inclinationFromCentralAxis = asin(.5 * sqrt(pow(spacialWidth, 2) + pow(spacialHeight, 2)) / originToCorners);

		//position of the "corners" of the viewport in 3D space
		Vector3D topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner;

		//initialize the corners centered a the origin
		makePreRotationCorners(topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner, originToCorners, inclinationFromCentralAxis, xy_rotation, azimuthFromCentralAxis);

		//rotate corners off z axis
		Vector3D inclinationAxis = -sphericalToCartesian(1, M_PI / 2, xy_rotation);
		rotateCorners(topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner, inclinationAxis, z_rotation);

		//rotate corners about the camera's center axis
		Vector3D centralAxis = -(topLeftCorner + topRightCorner + bottomRightCorner + bottomLeftCorner);
		rotateCorners(topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner, centralAxis, roll);

		//move from the origin to the camera center
		moveToCameraCenter(topLeftCorner, topRightCorner, bottomRightCorner, bottomLeftCorner, origin);

		//difference in position between neighboring pixels
		Vector3D horizontalDifference = (topRightCorner - topLeftCorner) / width;
		Vector3D verticalDifference = (bottomLeftCorner - topLeftCorner) / height;

		for(int x = 0; x < width; ++x)
			for(int y = 0; y < height; ++y)
				pixelCenters[x][y] = new Vector3D(topLeftCorner + (horizontalDifference * (x + .5)) + (verticalDifference * (y + .5)));
	}

	//create the corners with proper relative positions without any rotation, centered on the z axis
	void Screen::makePreRotationCorners(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner, Vector3D &bottomLeftCorner,
										double originToCorners, double inclinationFromCentralAxis, double xy_rotation, double azimuthFromCentralAxis) const {

		topLeftCorner = sphericalToCartesian(originToCorners, -inclinationFromCentralAxis, xy_rotation + azimuthFromCentralAxis);
		topRightCorner = sphericalToCartesian(originToCorners, inclinationFromCentralAxis, xy_rotation - azimuthFromCentralAxis);
		bottomRightCorner = sphericalToCartesian(originToCorners, inclinationFromCentralAxis, xy_rotation + azimuthFromCentralAxis);
		bottomLeftCorner = sphericalToCartesian(originToCorners, -inclinationFromCentralAxis, xy_rotation - azimuthFromCentralAxis);
	}

	//rotate the corners by a given angle about a given rotation axis
	void Screen::rotateCorners(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner,
							   Vector3D &bottomLeftCorner, const Vector3D &rotationAxis, double angle) const {

		topLeftCorner = topLeftCorner.rotatedAbout(rotationAxis, angle);
		topRightCorner = topRightCorner.rotatedAbout(rotationAxis, angle);
		bottomRightCorner = bottomRightCorner.rotatedAbout(rotationAxis, angle);
		bottomLeftCorner = bottomLeftCorner.rotatedAbout(rotationAxis, angle);
	}

	//translate the corners by the origin vector so they are in the correct position
	void Screen::moveToCameraCenter(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner,
									Vector3D &bottomLeftCorner, const Vector3D &origin) const {

		topLeftCorner = topLeftCorner + origin;
		topRightCorner = topRightCorner + origin;
		bottomRightCorner = topRightCorner + origin;
		bottomLeftCorner = bottomLeftCorner + origin;
	}

	//return the Vector3D describing the center of a pixel located at (x, y) on the screen
	Vector3D &raytracer::Screen::centerOfPixel(int x, int y) const {
		return *pixelCenters[x][y];
	}

	Screen::~Screen() {
		//memory cleanup

		for(int x = 0; x < width; ++x) {
			for(int y = 0; y < height; ++y)
				delete pixelCenters[x][y];

			delete[] pixelCenters[x];
		}

		delete[] pixelCenters;
		pixelCenters = nullptr;
	}

}