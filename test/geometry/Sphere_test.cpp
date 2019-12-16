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
		SurfacePoint s;
		bool intersects = sphere.findFirstIntersection(ray, t, s);

		//check function found intersection
		ASSERT_TRUE(intersects);

		//check time parameter
		ASSERT_NEAR(1.7, t, DELTA);

		//check position of SurfacePoint parameter
		ASSERT_NEAR(s.getPosition().getX(), 0, DELTA);
		ASSERT_NEAR(s.getPosition().getY(), 0, DELTA);
		ASSERT_NEAR(s.getPosition().getZ(), .7, DELTA);

		//check surfaceNormal of SurfacePoint parameter
		ASSERT_NEAR(s.getSurfaceNormal().getX(), 0, DELTA);
		ASSERT_NEAR(s.getSurfaceNormal().getY(), 0, DELTA);
		ASSERT_NEAR(s.getSurfaceNormal().getZ(), -1, DELTA);

		//check the Shape pointer of the SurfacePoint parameter
		ASSERT_EQ(s.getShapePointer(), &sphere);
	}

	TEST_F(Sphere_test, findFirstIntersection_noIntersection) {
		//ray should not intersect sphere
		double t;
		SurfacePoint s;
		bool intersects = sphere.findFirstIntersection(Ray(opositeRay), t, s);
		ASSERT_FALSE(intersects);
	}
}