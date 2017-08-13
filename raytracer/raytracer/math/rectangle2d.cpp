#include "math/rectangle2d.h"

using namespace math;


math::Rectangle2D::Rectangle2D(const Point2D& origin, const Vector2D& x_axis, const Vector2D& y_axis)
    : origin(origin), x_axis(x_axis), y_axis(y_axis) { }

Point2D math::Rectangle2D::center() const
{
    return origin + x_axis / 2 + y_axis / 2;
}

Point2D math::Rectangle2D::from_relative(const Point2D& p) const
{
    return origin + x_axis * p.x() + y_axis * p.y();
}

bool math::operator ==(const Rectangle2D& r1, const Rectangle2D& r2)
{
    return r1.origin == r2.origin && r1.x_axis == r2.x_axis && r1.y_axis == r2.y_axis;
}

bool math::operator !=(const Rectangle2D& r1, const Rectangle2D& r2)
{
    return !(r1 == r2);
}
