//
// Created by Evan on 11/24/2019.
//

#include <gtest/gtest.h>
#include <scene/Screen.h>
#include <geometry/Vector3D.h>
#include <cmath>

namespace raytracer {

#define DELTA 1e-6

	class Screen_test : public ::testing::Test {
	public:
		double origin_x = 5000;
		double origin_y = 2;
		double origin_z = -3;
		Vector3D origin = Vector3D(origin_x, origin_y, origin_z);
		int width = 3;
		int height = 3;
		double hFOV = M_PI/2;
		double xy_rotation = 0;
		double z_rotation = 0;

		Screen testScreen = Screen(origin, width, height, hFOV, xy_rotation, z_rotation);
		Screen testScreen_rotated = Screen(origin, width, height, hFOV, xy_rotation, M_PI/2);
		Screen testScreen_rotated_both_axis = Screen(origin, width, height, hFOV, M_PI/2, M_PI/2);
		Screen testScreen_rotated_about_center = Screen(origin, width, height, hFOV, 0, 0, M_PI/4);

	};

	TEST_F(Screen_test, noRotation_middlePixel) {
		Vector3D centerPixelLocation = testScreen.centerOfPixel(1, 1);
		ASSERT_NEAR(centerPixelLocation.getX(), origin_x, DELTA);
		ASSERT_NEAR(centerPixelLocation.getY(), origin_y, DELTA);
		ASSERT_NEAR(centerPixelLocation.getZ(), origin_z + 1, DELTA);
	}

	TEST_F(Screen_test, noRotation_topLeftPixel) {
		Vector3D topLeftPixel = testScreen.centerOfPixel(0, 0);
		ASSERT_NEAR(topLeftPixel.getX(), origin_x - 2/3., DELTA);
		ASSERT_NEAR(topLeftPixel.getY(), origin_y - 2/3., DELTA);
		ASSERT_NEAR(topLeftPixel.getZ(), origin_z + 1, DELTA);
	}

	TEST_F(Screen_test, noRotation_topRightPixel) {
		Vector3D topRightPixel = testScreen.centerOfPixel(2, 0);
		ASSERT_NEAR(topRightPixel.getX(), origin_x + 2/3., DELTA);
		ASSERT_NEAR(topRightPixel.getY(), origin_y - 2/3., DELTA);
		ASSERT_NEAR(topRightPixel.getZ(), origin_z + 1, DELTA);
	}

	TEST_F(Screen_test, noRotation_bottomLeftPixel) {
		Vector3D bottomLeftPixel = testScreen.centerOfPixel(0, 2);
		ASSERT_NEAR(bottomLeftPixel.getX(), origin_x - 2/3., DELTA);
		ASSERT_NEAR(bottomLeftPixel.getY(), origin_y + 2/3., DELTA);
		ASSERT_NEAR(bottomLeftPixel.getZ(), origin_z + 1, DELTA);
	}

	TEST_F(Screen_test, noRotation_bottomRightPixel) {
		Vector3D bottomRightPixel = testScreen.centerOfPixel(2, 2);
		ASSERT_NEAR(bottomRightPixel.getX(), origin_x + 2/3., DELTA);
		ASSERT_NEAR(bottomRightPixel.getY(), origin_y + 2/3., DELTA);
		ASSERT_NEAR(bottomRightPixel.getZ(), origin_z + 1, DELTA);
	}

	TEST_F(Screen_test, rotated90_middlePixel) {
		Vector3D centerPixelLocation = testScreen_rotated.centerOfPixel(1, 1);
		ASSERT_NEAR(centerPixelLocation.getX(), origin_x, DELTA);
		ASSERT_NEAR(centerPixelLocation.getY(), origin_y + 1, DELTA);
		ASSERT_NEAR(centerPixelLocation.getZ(), origin_z, DELTA);
	}

	TEST_F(Screen_test, rotated90_zaxis_topLeftPixel) {
		Vector3D topLeftPixel = testScreen_rotated.centerOfPixel(0, 0);
		ASSERT_NEAR(topLeftPixel.getX(), origin_x - 2/3., DELTA);
		ASSERT_NEAR(topLeftPixel.getY(), origin_y + 1, DELTA);
		ASSERT_NEAR(topLeftPixel.getZ(), origin_z + 2/3., DELTA);
	}

	TEST_F(Screen_test, rotated90_zaxis_topRightPixel) {
		Vector3D topRightPixel = testScreen_rotated.centerOfPixel(2, 0);
		ASSERT_NEAR(topRightPixel.getX(), origin_x + 2/3., DELTA);
		ASSERT_NEAR(topRightPixel.getY(), origin_y + 1, DELTA);
		ASSERT_NEAR(topRightPixel.getZ(), origin_z + 2/3., DELTA);
	}

	TEST_F(Screen_test, rotated90_both_axis_topLeftPixel) {
		Vector3D topLeftPixel = testScreen_rotated_both_axis.centerOfPixel(0, 0);
		ASSERT_NEAR(topLeftPixel.getX(), origin_x - 1, DELTA);
		ASSERT_NEAR(topLeftPixel.getY(), origin_y - 2 / 3., DELTA);
		ASSERT_NEAR(topLeftPixel.getZ(), origin_z + 2 / 3., DELTA);
	}

	TEST_F(Screen_test, rotated90_both_axis_topRightPixel) {
		Vector3D topRightPixel = testScreen_rotated_both_axis.centerOfPixel(2, 0);
		ASSERT_NEAR(topRightPixel.getX(), origin_x - 1, DELTA);
		ASSERT_NEAR(topRightPixel.getY(), origin_y + 2/3., DELTA);
		ASSERT_NEAR(topRightPixel.getZ(), origin_z + 2/3., DELTA);
	}

	TEST_F(Screen_test, rotated45_about_center_middlePixel) {
		Vector3D centerPixelLocation = testScreen_rotated_about_center.centerOfPixel(1, 1);
		ASSERT_NEAR(centerPixelLocation.getX(), origin_x, DELTA);
		ASSERT_NEAR(centerPixelLocation.getY(), origin_y, DELTA);
		ASSERT_NEAR(centerPixelLocation.getZ(), origin_z + 1, DELTA);
	}

	TEST_F(Screen_test, rotated45_about_center_topLeftPixel) {
		Vector3D topLeftPixel = testScreen_rotated_about_center.centerOfPixel(0, 0);
		ASSERT_NEAR(topLeftPixel.getX(), origin_x - sqrt(2) * 2/3 , DELTA);
		ASSERT_NEAR(topLeftPixel.getY(), origin_y, DELTA);
		ASSERT_NEAR(topLeftPixel.getZ(), origin_z + 1, DELTA);
	}
}