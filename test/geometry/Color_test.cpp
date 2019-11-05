//
// Created by Evan George on 11/4/19.
//

#include <gtest/gtest.h>
#include <geometry/Color.h>

namespace raytracer {
	class Color_test : public ::testing::Test {
	public:
		double r = .6;
		double g = .3;
		double b = 1;

		Color testColor = Color(r, g, b);
	};

	TEST_F(Color_test, storesColorComponents) {
		ASSERT_EQ(r, testColor.r);
		ASSERT_EQ(g, testColor.g);
		ASSERT_EQ(b, testColor.b);
	}
}