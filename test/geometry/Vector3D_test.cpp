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

		//x, y, z components of test vector 1
		const double x1 = -3.3;
		const double y1 = 4.7;
		const double z1 = -5.3;
		const Vector3D testVec1 = Vector3D(x1, y1, z1);
		const Vector3D normalizedVec1 = getNormalizedVector(x1, y1, z1);
		const double actualMagnitudeVec1 = 7.814729681825213;

		const double x2 = 5.1;
		const double y2 = 1023;
		const double z2 = .234;
		const Vector3D testVec2 = Vector3D(x2, y2, z2);
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

	TEST_F(Vector3D_test, test_operator_exact_equality) {
		Vector3D identicalToVec1(x1, y1, z1);
		ASSERT_TRUE(testVec1 == identicalToVec1);
		ASSERT_FALSE(testVec1 == testVec2);
	}

	TEST_F(Vector3D_test, test_getNormalizedVector) {
		double x1_norm_actual = x1 / actualMagnitudeVec1;
		double y1_norm_actual = y1 / actualMagnitudeVec1;
		double z1_norm_actual = z1 / actualMagnitudeVec1;

		ASSERT_NEAR(x1_norm_actual, normalizedVec1.getX(), DELTA);
		ASSERT_NEAR(y1_norm_actual, normalizedVec1.getY(), DELTA);
		ASSERT_NEAR(z1_norm_actual, normalizedVec1.getZ(), DELTA);
	}

	TEST_F(Vector3D_test, test_getNormalizedVector_magnitudeIs1) {
		ASSERT_NEAR(1, normalizedVec1.magnitude(), 0);
	}
}