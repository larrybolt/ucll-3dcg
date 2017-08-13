#pragma once

#include "math/matrix.h"
#include "math/angle.h"


namespace math
{
    namespace transformation_matrices
    {
        Matrix4x4 coordinate_system(const Point3D&, const Vector3D&, const Vector3D&, const Vector3D&);
        Matrix3x3 translation(const Vector2D&);
        Matrix4x4 translation(const Vector3D&);
        Matrix3x3 scaling(double sx, double sy);
        Matrix4x4 scaling(double sx, double sy, double sz);
        Matrix3x3 rotation(Angle);
        Matrix4x4 rotation_around_x(Angle);
        Matrix4x4 rotation_around_y(Angle);
        Matrix4x4 rotation_around_z(Angle);
    }
}
