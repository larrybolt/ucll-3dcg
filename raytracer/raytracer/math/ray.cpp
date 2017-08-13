#include "math/ray.h"

using namespace math;

math::Ray::Ray(const Point3D& origin, const Vector3D& direction)
    : origin(origin), direction(direction) 
{
    // NOP
}

math::Ray::Ray(const Point3D& origin, const Point3D& through)
    : Ray(origin, through - origin) 
{
    // NOP
}

Ray math::Ray::transform(const Matrix4x4& m) const
{
    auto transformed_origin = m * origin;
    auto transformed_direction = m * direction;

    return Ray(transformed_origin, transformed_direction);
}

Point3D math::Ray::at(double t) const 
{
    return origin + direction * t; 
}

std::ostream& math::operator <<(std::ostream& out, const Ray& ray)
{
    return out << "RAY[" << ray.origin << " : " << ray.direction << "]";
}

bool math::operator ==(const Ray& r1, const Ray& r2)
{
    return r1.origin == r2.origin && r1.direction == r2.direction;
}
