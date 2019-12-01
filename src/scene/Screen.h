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
		Screen(Vector3D origin,
			   const int width, const int height,
			   double hFOV,
			   double xy_rotation = 0, double z_rotation = 0, double roll = 0);

		~Screen();

		Vector3D & centerOfPixel(int x, int y) const;

	private:
		void makePreRotationCorners(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner, Vector3D &bottomLeftCorner,
									double originToCorners, double inclinationFromCentralAxis, double xy_rotation, double azimuthFromCentralAxis) const;

		void rotateCorners(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner,
						   Vector3D &bottomLeftCorner, const Vector3D &rotationAxis, double angle) const;

		void moveToCameraCenter(Vector3D &topLeftCorner, Vector3D &topRightCorner, Vector3D &bottomRightCorner,
								Vector3D &bottomLeftCorner, const Vector3D &origin) const;

		const int width, height;

		const double spacialDepth = 1;	//distance between the origin and the center of the viewport, arbitrarily unit length

		Vector3D ***pixelCenters;
	};

}
#endif //RAYTRACERCPP_SCREEN_H
