//
// Created by Evan George on 11/4/19.
//

#include <gtest/gtest.h>
#include <geometry/Vector3D.h>
#include <geometry/Ray.h>

namespace raytracer {
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
}