//
// Created by Evan George on 11/4/19.
//

#ifndef RAYTRACERCPP_CAMERA_H
#define RAYTRACERCPP_CAMERA_H


#include <geometry/Vector3D.h>
#include <cmath>

namespace raytracer {

	class Camera {
	public:
		Camera(Vector3D origin, int width, int height, double hFOV, double xy_rotation = 0, double z_rotation = 0, double roll = 0)
				: renderWidth(width), renderHeight(height), origin(origin), hFOV(hFOV), xy_rotation(xy_rotation), z_rotation(z_rotation), roll(roll) {

			updateCornerPositions();
		}

	private:
		void updateCornerPositions();

		//GIVEN VALUES
		int renderWidth, renderHeight;			//width and height in pixels of rendered scene with camera
		Vector3D origin;						//position of the "aperture" of the camera
		double hFOV;							//the horizontal field of view of the camera
		double xy_rotation, z_rotation;			//spherical coordinates of center of camera viewport ind 3D space, xy_rotation (azimuth), z_rotation(inclination)
		double roll;							//rotation of camera about the axis drawn from the origin to the center of the viewport

		const double spacialHeight = 0;			//height of camera viewport in 3D space, fixed to arbitrary 2 units tall

		//DEPENDENT VALUES
		double spacialWidth;					//width of camera viewport in 3D space, dependent on the aspect ratio and spacialHeight (constant)
		double spacialDepth;					//distance between the origin and the center of the viewport, dependent on hFOV and spacialHeight (constant)

		Vector3D 	topLeftCorner,				//position of the "corners" of the viewport in 3D space
					topRightCorner,
					bottomLeftCorner,
					bottomRightCorner;
	};
}

#endif //RAYTRACERCPP_CAMERA_H
