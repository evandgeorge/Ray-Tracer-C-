//
// Created by Evan George on 11/3/19.
//

#include <gtest/gtest.h>
#include <geometry/Vector3D.h>
#include <cmath>

namespace raytracer {

	//delta for floating point comparisons
	const double DELTA = 1e-10;

	//VECTOR3D TEST FIXTURE

	class Vector3D_test : public ::testing::Test {
	public:

		void setUp() {
			//reset test vector
			testVec1 = Vector3D(x1, y1, z1);
		}

		//x, y, z components of test vector 1
		double x1 = -3.3;
		double y1 = 4.7;
		double z1 = -5.3;
		Vector3D testVec1 = Vector3D(x1, y1, z1);

		double x2 = 5.1;
		double y2 = 1023;
		double z2 = .234;
		Vector3D testVec2 = Vector3D(x2, y2, z2);
	};

	//TESTS

	TEST_F(Vector3D_test, test_getX) {
		ASSERT_EQ(testVec1.getX(), x1);
	}

	TEST_F(Vector3D_test, test_getY) {
		ASSERT_EQ(testVec1.getY(), y1);
	}

	TEST_F(Vector3D_test, test_getZ) {
		ASSERT_EQ(testVec1.getZ(), z1);
	}

	TEST_F(Vector3D_test, test_magnitude) {
		double actualMagnitudeVec1 = 7.814729681825213;
		ASSERT_NEAR(actualMagnitudeVec1, testVec1.magnitude(), DELTA);
	}

	TEST_F(Vector3D_test, test_dotProduct) {
		double actualDotProductVec12 = 4790.0298;
		ASSERT_NEAR(actualDotProductVec12, testVec1.dotProduct(testVec2), DELTA);
	}

	TEST_F(Vector3D_test, test_dotProductIsCommutative) {
		ASSERT_NEAR(testVec1.dotProduct(testVec2), testVec2.dotProduct(testVec1), DELTA);
	}

	TEST_F(Vector3D_test, test_dotProductOfSelfIsMagnitudeSquared) {
		ASSERT_NEAR(pow(testVec1.magnitude(), 2), testVec1.dotProduct(testVec1), DELTA);
	}
}