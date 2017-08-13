#include "math/transformation-matrices.h"
#include <assert.h>

using namespace math;


Matrix4x4 math::transformation_matrices::translation(const Vector3D& v)
{
    std::array<double, 16> xs = {
        1, 0, 0, v.x(),
        0, 1, 0, v.y(),
        0, 0, 1, v.z(),
        0, 0, 0, 1
    };

    return Matrix4x4(xs);
}

Matrix4x4 math::transformation_matrices::scaling(double sx, double sy, double sz)
{
    std::array<double, 16> xs = {
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    };

    return Matrix4x4(xs);
}

Matrix4x4 math::transformation_matrices::rotation_around_x(Angle angle)
{
    double s = sin(angle);
    double c = cos(angle);

    std::array<double, 16> xs = {
        1, 0, 0, 0,
        0, c, -s, 0,
        0, s, c, 0,
        0, 0, 0, 1
    };

    return Matrix4x4(xs);
}

Matrix4x4 math::transformation_matrices::rotation_around_y(Angle angle)
{
    double s = sin(angle);
    double c = cos(angle);

    std::array<double, 16> xs = {
        c, 0, s, 0,
        0, 1, 0, 0,
        -s, 0, c, 0,
        0, 0, 0, 1
    };

    return Matrix4x4(xs);
}

Matrix4x4 math::transformation_matrices::rotation_around_z(Angle angle)
{
    double s = sin(angle);
    double c = cos(angle);

    std::array<double, 16> xs = {
        c, -s , 0, 0,
        s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    return Matrix4x4(xs);
}

Matrix4x4 math::transformation_matrices::coordinate_system(const Point3D& origin, const Vector3D& x_axis, const Vector3D& y_axis, const Vector3D& z_axis)
{
    std::array<double, 16> xs = {
        x_axis.x(), y_axis.x(), z_axis.x(), origin.x(),
        x_axis.y(), y_axis.y(), z_axis.y(), origin.y(),
        x_axis.z(), y_axis.z(), z_axis.z(), origin.z(),
        0, 0, 0, 1
    };

    return Matrix4x4(xs);
}

Matrix3x3 math::transformation_matrices::translation(const Vector2D& v)
{
    std::array<double, 9> xs = {
        1, 0, v.x(),
        0, 1, v.y(),
        0, 0, 1
    };

    return Matrix3x3(xs);
}

Matrix3x3 math::transformation_matrices::scaling(double sx, double sy)
{
    std::array<double, 9> xs = {
        sx, 0, 0,
        0, sy, 0,
        0, 0, 1
    };

    return Matrix3x3(xs);
}

Matrix3x3 math::transformation_matrices::rotation(Angle angle)
{
    double s = sin(angle);
    double c = cos(angle);

    std::array<double, 9> xs = {
        c, -s , 0,
        s, c, 0,
        0, 0, 1
    };

    return Matrix3x3(xs);
}
