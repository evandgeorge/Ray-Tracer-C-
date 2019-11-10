//
// Created by Evan George on 11/4/19.
//

#include "Camera.h"
#include <cmath>

//set the origin to v
void raytracer::Camera::moveTo(const raytracer::Vector3D &v) {
	origin = v;
	updateCamera();
}

//move the camera by v
void raytracer::Camera::translate(const raytracer::Vector3D &v) {
	origin = origin + v;
	updateCamera();
}

//set the azimuth angle of the camera
void raytracer::Camera::set_xy_rotation(double azimuth) {
	xy_rotation = azimuth;
	updateCamera();
}

//increment the xy_rotation by angle
void raytracer::Camera::turn(double angle) {
	xy_rotation += angle;
	updateCamera();
}

//set the inclination angle of the camera
void raytracer::Camera::set_z_rotation(double inclination) {
	z_rotation = inclination;
	updateCamera();
}

//increment the z_rotation by angle
void raytracer::Camera::incline(double angle) {
	z_rotation += angle;
	updateCamera();
}

//reset the axis rotation of the camera to 0
void raytracer::Camera::resetRotation() {
	roll = 0;
	updateCamera();
}

//rotate the camera by an additional amount about its axis
void raytracer::Camera::rotate(double rotation) {
	roll += rotation;
	updateCamera();
}

//set the resolution of the render image
void raytracer::Camera::setResolution(int w, int h) {
	renderWidth = w;
	renderHeight = h;
	updateCamera();
}

//updates the positions of the corners of the viewport
void raytracer::Camera::updateCornerPositions() {
	double aspectRatio = (double) renderWidth / renderHeight;
	spacialWidth = spacialHeight * aspectRatio;					//update the width of the viewport in the scene
	spacialDepth = aspectRatio / tan(hFOV / 2);					//update the height of the viewport in the scene

	//the positive difference in inclination (z) angle between the top or bottom sides of the viewport and the center axis
	double inclinationFromMiddle = atan(sqrt(1 + pow(aspectRatio, 2)) / spacialDepth);
	//the positive difference in azimuth (xy) angle between the left or right side of the viewport and the center axis
	double azimuthFromMiddle = atan(1 / aspectRatio);

	//the distance from the viewport corners to the origin of the camera
	double radius = sqrt(pow(spacialHeight / 2, 2) + pow(spacialWidth / 2, 2) + pow(spacialDepth, 2));

	//the corners of the viewport relative to the origin of the camera
	Vector3D cornersRelativeToCameraOrigin[4] = {
			sphericalToCartesian(radius, z_rotation - inclinationFromMiddle, xy_rotation + azimuthFromMiddle),
			sphericalToCartesian(radius, z_rotation - inclinationFromMiddle, xy_rotation - azimuthFromMiddle),
			sphericalToCartesian(radius, z_rotation + inclinationFromMiddle, xy_rotation + azimuthFromMiddle),
			sphericalToCartesian(radius, z_rotation + inclinationFromMiddle, xy_rotation - azimuthFromMiddle)};

	//direction vector describing the axis of rotation for the viewport corners, the line from the origin through the center of the camera
	Vector3D rotationAxis = sphericalToCartesian(1, z_rotation, xy_rotation);

	//the absolute positions of the pre-rotation viewport corners in the scene
	topLeftCorner = origin + cornersRelativeToCameraOrigin[0].rotatedAbout(rotationAxis, roll);
	topRightCorner = origin + cornersRelativeToCameraOrigin[1].rotatedAbout(rotationAxis, roll);
	bottomLeftCorner = origin + cornersRelativeToCameraOrigin[2].rotatedAbout(rotationAxis, roll);
	bottomRightCorner = origin + cornersRelativeToCameraOrigin[3].rotatedAbout(rotationAxis, roll);
}

//update the camera rays
void raytracer::Camera::updateCameraRays() {
	pixelCoordinateMap pixelCenters = getPixelCenters();

	//reinitialize cameraRays to clear it
	cameraRays = pixelCameraRayMap(renderWidth);

	//for each pixel in the viewport create a ray that starts at the camera origin and passes through the center of the pixel
	for(int w = 0; w < renderWidth; ++w)
		for(int h = 0; h < renderHeight; ++h)
			cameraRays[w].push_back(Ray(origin, pixelCenters[w][h] - origin));

}

//return a two dimensional vector of the center of each pixel on the viewport represented by a Vector3D
raytracer::Camera::pixelCoordinateMap raytracer::Camera::getPixelCenters() const {
	Vector3D heightUnit = (topLeftCorner - bottomLeftCorner) / renderHeight;	//height of one pixel
	Vector3D widthUnit = (topLeftCorner - topRightCorner) / renderWidth;		//width of one pixel

	pixelCoordinateMap pixelCenters(renderWidth);

	//for each pixel in the viewport add a Vector3D that represents the position of its center
	for(int x = 0; x < renderWidth; ++x)
		for(int y = 0; y < renderHeight; ++y)
			pixelCenters[x].push_back(Vector3D(bottomRightCorner + widthUnit * (x + .5) + heightUnit * (y + .5)));

	return pixelCenters;
}
