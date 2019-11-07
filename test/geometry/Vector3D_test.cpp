//
// Created by Evan George on 11/3/19.
//

#include <gtest/gtest.h>
#include <geometry/Vector3D.h>
#include <cmath>

namespace raytracer {

	//delta for floating point comparisons
	const double DELTA = 1e-5;

	//VECTOR3D TEST FIXTURE

	class Vector3D_test : public ::testing::Test {
	public:

		//x, y, z components of test vector 1
		const double x1 = -3.3;
		const double y1 = 4.7;
		const double z1 = -5.3;
		const Vector3D testVec1 = Vector3D(x1, y1, z1);
		const Vector3D normalizedVec1 = getNormalizedVector(testVec1);
		const double actualMagnitudeVec1 = 7.814729681825213;
		const double thetaVec1 = 2.31611556000232367;
		const double phiVec1 = 2.18294882373997998;

		const double x2 = 5.1;
		const double y2 = 1023;
		const double z2 = .234;
		const Vector3D testVec2 = Vector3D(x2, y2, z2);

		const Vector3D testVec1_rotatedAbout_testVec2_halfPi = Vector3D(-5.27767, 4.70789, 3.32446);
		const Vector3D testVec1_cross_testVec2 = Vector3D(5422.9998, -26.2578, -3399.87);
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

	TEST_F(Vector3D_test, test_crossProduct) {
		Vector3D calculatedCrossProduct = testVec1.crossProduct(testVec2);
		ASSERT_NEAR(calculatedCrossProduct.getX(), testVec1_cross_testVec2.getX(), DELTA);
		ASSERT_NEAR(calculatedCrossProduct.getY(), testVec1_cross_testVec2.getY(), DELTA);
		ASSERT_NEAR(calculatedCrossProduct.getZ(), testVec1_cross_testVec2.getZ(), DELTA);
	}

	TEST_F(Vector3D_test, test_operator_exact_equality) {
		Vector3D identicalToVec1(x1, y1, z1);
		ASSERT_TRUE(testVec1 == identicalToVec1);
		ASSERT_FALSE(testVec1 == testVec2);
	}

	TEST_F(Vector3D_test, test_operator_add) {
		ASSERT_EQ(Vector3D(x1 + x2, y1 + y2, z1 + z2), testVec1 + testVec2);
	}

	TEST_F(Vector3D_test, test_operator_subtract) {
		ASSERT_EQ(Vector3D(x1 - x2, y1 - y2, z1 - z2), testVec1 - testVec2);
	}

	TEST_F(Vector3D_test, test_operator_multiply) {
		//test multiplication with arbitrary factor 3.42
		ASSERT_EQ(Vector3D(x1 * 3.42, y1 * 3.42, z1 * 3.42), testVec1 * 3.42);
	}

	TEST_F(Vector3D_test, test_operator_divide) {
		//test multiplication with arbitrary factor 3.42
		ASSERT_EQ(Vector3D(x1 / 3.42, y1 / 3.42, z1 / 3.42), testVec1 / 3.42);
	}

	TEST_F(Vector3D_test, test_operator_negate) {
		ASSERT_EQ(Vector3D(-x1, -y1, -z1), -testVec1);
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

	TEST_F(Vector3D_test, test_sphericalToCartesian) {
		Vector3D cartesian = sphericalToCartesian(actualMagnitudeVec1, thetaVec1, phiVec1);

		ASSERT_NEAR(x1, cartesian.getX(), DELTA);
		ASSERT_NEAR(y1, cartesian.getY(), DELTA);
		ASSERT_NEAR(z1, cartesian.getZ(), DELTA);
	}

	TEST_F(Vector3D_test, test_rotatedAbout) {
		Vector3D calculatedRotation = testVec1.rotatedAbout(testVec2, M_PI / 2);

		ASSERT_NEAR(testVec1_rotatedAbout_testVec2_halfPi.getX(), calculatedRotation.getX(), DELTA);
		ASSERT_NEAR(testVec1_rotatedAbout_testVec2_halfPi.getY(), calculatedRotation.getY(), DELTA);
		ASSERT_NEAR(testVec1_rotatedAbout_testVec2_halfPi.getZ(), calculatedRotation.getZ(), DELTA);
	}
}