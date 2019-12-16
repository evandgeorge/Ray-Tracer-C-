//
// Created by Evan George on 12/15/19.
//

#include <gtest/gtest.h>
#include "geometry/Sphere.h"
#include "lighting/DirectionalLight.h"


namespace raytracer {

	//delta for floating point comparisons
	const double DELTA = 1e-5;


	class DirectionalLight_test : public ::testing::Test {


	public:

		DirectionalLight_test() { shapes.push_back(&sphere); }

		DirectionalLight directionalLight = DirectionalLight(Luminance(2, 4, 5), Vector3D(0, 0, 1));
		SurfacePoint incidentPoint = SurfacePoint(Vector3D(0, 0, 0), Vector3D(0, 0, 1), &sphere);

		Sphere sphere = Sphere({0, 0, -1}, 1, {.2, 1, .5}, 0);
		std::vector<Shape*> shapes;

		const double DELTA = 1e-7;
	};

	TEST_F(DirectionalLight_test, test_luminaneAtPoint_notInShadow) {

		Luminance luminanceAtPoint = directionalLight.luminanceAtPoint(incidentPoint, shapes);

		ASSERT_NEAR(.4, luminanceAtPoint.getR(), DELTA);
		ASSERT_NEAR(4, luminanceAtPoint.getG(), DELTA);
		ASSERT_NEAR(2.5, luminanceAtPoint.getB(), DELTA);
	}

}