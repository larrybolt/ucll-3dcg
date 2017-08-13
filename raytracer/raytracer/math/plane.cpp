#include "math/plane.h"
#include <assert.h>

using namespace math;


math::Plane::Plane(const Point3D& p, const Vector3D& n)
    : point(p), normal(n)
{
    assert(n.is_unit());
}

Plane math::Plane::from_point_and_normal(const Point3D& p, const Vector3D& n)
{
    assert(n.is_unit());

    return Plane{ p, n };
}

double math::distance(const Plane& plane, const Point3D& point)
{
    assert(plane.normal.is_unit());

    return (point - plane.point).dot(plane.normal);
}

bool math::lies_in_front_of(const math::Plane& plane, const Point3D& point)
{
    return math::distance(plane, point) > 0;
}

bool math::lies_behind(const math::Plane& plane, const math::Point3D& point)
{
    return math::distance(plane, point) < 0;
}

bool math::lies_on(const math::Plane& plane, const math::Point3D& point, double epsilon)
{
    return math::distance(plane, point) == approx(0.0, epsilon);
}
