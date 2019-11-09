//
// Created by Evan George on 11/4/19.
//

#include "Camera.h"
#include <cmath>

void raytracer::Camera::updateCornerPositions() {
	double aspectRatio = (double) renderWidth / renderHeight;;
	spacialWidth = spacialHeight * aspectRatio;
	spacialDepth = aspectRatio / tan(hFOV / 2);

	double inclinationFromMiddle = atan(sqrt(1 + pow(aspectRatio, 2)) / spacialDepth);
	double azimuthFromMiddle = atan(1 / aspectRatio);

	double radius = sqrt(pow(spacialHeight / 2, 2) + pow(spacialWidth / 2, 2) + pow(spacialDepth, 2));

	Vector3D cornersRelativeToCameraOrigin[4] = {
		sphericalToCartesian(radius, z_rotation - inclinationFromMiddle, xy_rotation - azimuthFromMiddle),
		sphericalToCartesian(radius, z_rotation - inclinationFromMiddle, xy_rotation + azimuthFromMiddle),
		sphericalToCartesian(radius, z_rotation + inclinationFromMiddle, xy_rotation + azimuthFromMiddle),
		sphericalToCartesian(radius, z_rotation + inclinationFromMiddle, xy_rotation - azimuthFromMiddle)};

	Vector3D rotationAxis = sphericalToCartesian(1, z_rotation, xy_rotation);

	topLeftCorner = origin + cornersRelativeToCameraOrigin[0].rotatedAbout(rotationAxis, roll);
	topRightCorner = origin + cornersRelativeToCameraOrigin[1].rotatedAbout(rotationAxis, roll);
	bottomLeftCorner = origin + cornersRelativeToCameraOrigin[2].rotatedAbout(rotationAxis, roll);
	bottomRightCorner = origin + cornersRelativeToCameraOrigin[3].rotatedAbout(rotationAxis, roll);
}