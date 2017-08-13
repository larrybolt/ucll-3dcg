#include "math/rectangle3d.h"

using namespace math;


math::Rectangle3D::Rectangle3D(const Point3D& origin, const Vector3D& x_axis, const Vector3D& y_axis)
    : origin(origin), x_axis(x_axis), y_axis(y_axis) 
{
    // NOP
}

Point3D math::Rectangle3D::project(const Point2D& p) const
{
    return origin + x_axis * p.x() + y_axis * p.y();
}
