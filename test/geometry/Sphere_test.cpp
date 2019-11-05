//
// Created by Evan George on 11/4/19.
//

#include <gtest/gtest.h>
#include <geometry/Vector3D.h>
#include <geometry/Color.h>
#include <geometry/Sphere.h>

namespace raytracer {
	//delta for floating point comparisons
	const double DELTA = 1e-10;

	class Sphere_test : public ::testing::Test {
	public:
		const Vector3D center = Vector3D(0, 0, 1);
		const double radius = .3;
		//sphere centered at (0, 0, 1) with radius .3, arbitrary color and reflectivity
		const Sphere sphere = Sphere(center, radius, Color(0, 0, 0), 0);

		//ray starting at (0, 0, -1) and moving forward in the z direction (+0, +0, +1)
		const Ray ray = Ray(Vector3D(0, 0, -1), Vector3D(0, 0, 1));
		const Ray opositeRay = Ray(Vector3D(0, 0, -1), Vector3D(0, 0, -1));
	};

	TEST_F(Sphere_test, findFirstIntersection) {
		//ray should intersect with sphere surface at t=1.7
		double t;
		bool intersects = sphere.findFirstIntersection(ray, t);
		ASSERT_TRUE(intersects);
		ASSERT_NEAR(1.7, t, DELTA);
	}

	TEST_F(Sphere_test, findFirstIntersection_noIntersection) {
		//ray should not intersect sphere
		double t;
		bool intersects = sphere.findFirstIntersection(Ray(opositeRay), t);
		ASSERT_FALSE(intersects);
	}
}