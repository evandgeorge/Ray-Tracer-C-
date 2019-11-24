//
// Created by Evan George on 11/4/19.
//

#include <gtest/gtest.h>
#include <geometry/Vector3D.h>
#include <geometry/Ray.h>

namespace raytracer {
#define DELTA 1e-10

	class Ray_test : public ::testing::Test {
	public:

		//x, y, z components of test vector 1
		const double x1 = -3.3;
		const double y1 = 4.7;
		const double z1 = -5.3;
		const Vector3D directionInput = Vector3D(x1, y1, z1);
		//direction vector is expected to be normalized
		const Vector3D expectedDirection = getNormalizedVector(directionInput);

		const double x2 = 5.1;
		const double y2 = 1023;
		const double z2 = .234;
		const Vector3D position = Vector3D(x2, y2, z2);

		const Ray testRay = Ray(position, directionInput);
	};

	TEST_F(Ray_test, hasPosition) {
		ASSERT_EQ(position, testRay.position);
	}

	TEST_F(Ray_test, normalizesDirectionVector) {
		ASSERT_EQ(expectedDirection, testRay.direction);
	}

	TEST_F(Ray_test, positionAtGivenTime) {
		Ray simpleTestRay(Vector3D(-1, -1, -1), Vector3D(1, 1, 1));
		double expectedTimeToReachOrigin = 1.73205080757;
		Vector3D actualPosition = simpleTestRay.positionAt(expectedTimeToReachOrigin);
		//ray should reach the origin at t = ~1.732

		ASSERT_NEAR(actualPosition.getX(), 0, DELTA);
		ASSERT_NEAR(actualPosition.getY(), 0, DELTA);
		ASSERT_NEAR(actualPosition.getZ(), 0, DELTA);
	}
}