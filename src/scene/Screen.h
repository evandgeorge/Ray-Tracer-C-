//
// Created by Evan on 11/24/2019.
//

#ifndef RAYTRACERCPP_SCREEN_H
#define RAYTRACERCPP_SCREEN_H

#include <geometry/Ray.h>
#include "geometry/Vector3D.h"

namespace raytracer {

#define SPACIAL_DEPTH 1.0

	struct ScreenCorners { Vector3D topLeft, topRight, bottomRight, bottomLeft; };

	class Screen {
	public:

		//construct the screen in 3D space given the origin of the camera, width, height, field of view, and rotation
		Screen(Vector3D origin,
			   int width, int height,
			   double hFOV,
			   double xy_rotation = 0, double z_rotation = 0, double roll = 0);

		//destructor
		~Screen();

		//accessor for pixelCenters
		const Vector3D & centerOfPixel(int x, int y) const { return pixelCenters[x][y]; }

	private:
		//assigns the position of the center of each pixel in 3D space
		void setPixelCenters(const ScreenCorners &corners);

		const int width, height;		//resolution of the camera
		Vector3D **pixelCenters;		//2D array of Vector3D pointers containing the position of the center of each pixel on the screen in the scene
	};

	//generate the corners of the screen
	ScreenCorners getScreenCorners(Vector3D origin, double spacialWidth, double spacialHeight, double xy_rotation, double z_rotation, double roll);

	//rotate the corners by an angle about a rotation axis
	void rotateCorners(ScreenCorners &corners, const Vector3D &rotationAxis, double angle);

	//translate the corners by the origin vector so they are in the correct position
	void moveToCameraCenter(ScreenCorners &corners, const Vector3D &origin);
}

#endif //RAYTRACERCPP_SCREEN_H