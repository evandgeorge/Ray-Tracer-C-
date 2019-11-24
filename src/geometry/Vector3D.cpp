//
// Created by Evan George on 11/3/19.
//

#include <cmath>
#include "Vector3D.h"

namespace raytracer {

    //returns the magnitude of the vector
    double Vector3D::magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    //returns the dot product of *this and v
    double Vector3D::dotProduct(const Vector3D &v) const {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }

    //returns *this cross v
    Vector3D Vector3D::crossProduct(const Vector3D &v) const {
        double x_cross = y * v.z - z * v.y;
        double y_cross = z * v.x - x * v.z;
        double z_cross = x * v.y - y * v.x;

        return {x_cross, y_cross, z_cross};
    }

    //returns true if the vectors are exactly identical
    bool Vector3D::operator==(const Vector3D &v) const {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    //returns *this + v
    Vector3D Vector3D::operator+(const Vector3D &v) const {
        return {x + v.x,
                y + v.y,
                z + v.z};
    }

    //returns *this - v
    Vector3D Vector3D::operator-(const Vector3D &v) const {
        return {x - v.x,
                y - v.y,
                z - v.z};
    }

    //returns *this * f (scalar)
    Vector3D Vector3D::operator*(double f) const {
        return {x * f,
                y * f,
                z * f};
    }

    //returns *this / f (scalar)
    Vector3D Vector3D::operator/(double d) const {
        return {x / d,
                y / d,
                z / d};
    }

    //returns -(*this)
    Vector3D Vector3D::operator-() const {
        return {-x,
                -y,
                -z};
    }

    //returns *this rotated about the rotation axis described by v.
    //it is not required that v is normal because its normal is used for calculations.
    //Uses Rodrigues' rotation formula https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
    Vector3D Vector3D::rotatedAbout(const Vector3D &v, double angle) const {
        Vector3D axisNormal = getNormalizedVector(v);
        return *this * cos(angle)
               + (axisNormal.crossProduct(*this) * sin(angle)
               + axisNormal * (axisNormal.dotProduct(*this)) * (1 - cos(angle)));
    }

    //returns a Vector3D in the direction of (x, y, z) with size 1
    Vector3D getNormalizedVector(const Vector3D &v) {
        return v / v.magnitude();
    }

    Vector3D sphericalToCartesian(double r, double theta, double phi) {
        return {r * sin(theta) * cos(phi),
                r * sin(theta) * sin(phi),
                r * cos(theta)};
    }
}