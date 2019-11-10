//
// Created by Evan George on 11/4/19.
//

#ifndef RAYTRACERCPP_CAMERA_H
#define RAYTRACERCPP_CAMERA_H

#include <geometry/Vector3D.h>
#include <geometry/Ray.h>
#include <vector>

namespace raytracer {

	class Camera {
	public:
		Camera(Vector3D origin, int width, int height, double hFOV, double xy_rotation = 0, double z_rotation = 0, double roll = 0)
				: renderWidth(width), renderHeight(height), origin(origin), hFOV(hFOV), xy_rotation(xy_rotation), z_rotation(z_rotation), roll(roll) {

			updateCornerPositions();
			updateCameraRays();
		}

		void moveTo(const Vector3D &v);			//set the origin to v
		void translate(const Vector3D &v);		//move the camera by v

		void set_xy_rotation(double azimuth);	//set the azimuth angle of the camera
		void turn(double angle);				//increment the xy_rotation by angle

		void set_z_rotation(double inclination);//set the inclination angle of the camera
		void incline(double angle);				//increment the z_rotation by angle

		void resetRotation();					//reset the axis rotation of the camera to 0
		void rotate(double rotation);			//rotate the camera by an additional amount about its axis

		void setResolution(int w, int h);		//set the resolution of the render image

	private:
		//two dimensional vector of Vector3Ds, used for storing the position of the center of each pixel on the viewport
		typedef std::vector<std::vector<Vector3D>> pixelCoordinateMap;
		//two dimensional vector of Rays, used for storing the camera ray for each pixel
		typedef std::vector<std::vector<Ray>> pixelCameraRayMap;

		//updates the corner vectors and the camera rays
		void updateCamera() { updateCornerPositions(); updateCameraRays(); }

		void updateCornerPositions();			//updates the positions of the corners of the viewport
		void updateCameraRays();				//updates the camera rays

		//return a two dimensional vector of the center of each pixel on the viewport represented by a Vector3D
		pixelCoordinateMap getPixelCenters() const;

		//GIVEN VALUES
		int renderWidth, renderHeight;			//width and height in pixels of rendered scene with camera
		Vector3D origin;						//position of the "aperture" of the camera
		double hFOV;							//the horizontal field of view of the camera
		double xy_rotation, z_rotation;			//spherical coordinates of center of camera viewport ind 3D space, xy_rotation (azimuth), z_rotation(inclination)
		double roll;							//rotation of camera about the axis drawn from the origin to the center of the viewport

		const double spacialHeight = 2;			//height of camera viewport in 3D space, fixed to arbitrary 2 units tall

		//DEPENDENT VALUES
		double spacialWidth;					//width of camera viewport in 3D space, dependent on the aspect ratio and spacialHeight (constant)
		double spacialDepth;					//distance between the origin and the center of the viewport, dependent on hFOV and spacialHeight (constant)

		Vector3D 	topLeftCorner,				//position of the "corners" of the viewport in 3D space
					topRightCorner,
					bottomLeftCorner,
					bottomRightCorner;

		pixelCameraRayMap cameraRays;
	};
}

#endif //RAYTRACERCPP_CAMERA_H
