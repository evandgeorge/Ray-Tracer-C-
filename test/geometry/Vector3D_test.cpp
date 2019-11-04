//
// Created by Evan George on 11/3/19.
//

#include <gtest/gtest.h>
#include <geometry/Vector3D.h>

namespace raytracer {

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
}