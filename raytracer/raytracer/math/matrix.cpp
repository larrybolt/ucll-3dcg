#include "math/matrix.h"
#include <assert.h>

using namespace math;


Vector2D math::operator *(const Matrix3x3& a, const Vector2D& v)
{
#   define AUX(row) a.at(row, 0) * v.x() + a.at(row, 1) * v.y()

    double x = AUX(0);
    double y = AUX(1);

    return Vector2D(x, y);

#   undef AUX
}

Vector3D math::operator *(const Matrix4x4& a, const Vector3D& v)
{
#   define AUX(row) a.at(row, 0) * v.x() + a.at(row, 1) * v.y() + a.at(row, 2) * v.z()

    double x = AUX(0);
    double y = AUX(1);
    double z = AUX(2);

    return Vector3D(x, y, z);

#   undef AUX
}

Point2D math::operator *(const Matrix3x3& a, const Point2D& p)
{
#   define AUX(row) a.at(row, 0) * p.x() + a.at(row, 1) * p.y() + a.at(row, 2)

    double x = AUX(0);
    double y = AUX(1);

    return Point2D(x, y);

#   undef AUX
}

Point3D math::operator *(const Matrix4x4& a, const Point3D& p)
{
#   define AUX(row) a.at(row, 0) * p.x() + a.at(row, 1) * p.y() + a.at(row, 2) * p.z() + a.at(row, 3)

    double x = AUX(0);
    double y = AUX(1);
    double z = AUX(2);

    return Point3D(x, y, z);

#   undef AUX
}
