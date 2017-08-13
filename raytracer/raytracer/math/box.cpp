#include "math/box.h"
#include "math/ray.h"
#include <limits>

using namespace math;


math::Box::Box(const Interval<double>& x_interval, const Interval<double>& y_interval, const Interval<double>& z_interval)
    : m_x_interval(x_interval), m_y_interval(y_interval), m_z_interval(z_interval)
{
    // NOP
}

bool math::Box::is_hit_positively_by(const Ray& ray) const
{
    return
        hits_xy_face(ray, m_z_interval.lower, true) ||
        hits_xy_face(ray, m_z_interval.upper, true) ||
        hits_xz_face(ray, m_y_interval.lower, true) ||
        hits_xz_face(ray, m_y_interval.upper, true) ||
        hits_yz_face(ray, m_x_interval.lower, true) ||
        hits_yz_face(ray, m_x_interval.upper, true);
}

bool math::Box::is_hit_by(const Ray& ray) const
{
    return
        hits_xy_face(ray, m_z_interval.lower, false) ||
        hits_xy_face(ray, m_z_interval.upper, false) ||
        hits_xz_face(ray, m_y_interval.lower, false) ||
        hits_xz_face(ray, m_y_interval.upper, false) ||
        hits_yz_face(ray, m_x_interval.lower, false) ||
        hits_yz_face(ray, m_x_interval.upper, false);
}

bool math::Box::hits_xy_face(const Ray& ray, double z, bool only_positive) const
{
    if (ray.direction.z() == approx(0.0))
    {
        return false;
    }
    else
    {
        double t = -(ray.origin.z() - z) / ray.direction.z();
        Point3D p = ray.at(t);

        return (!only_positive || t > 0) && m_x_interval.contains(p.x()) && m_y_interval.contains(p.y());
    }
}

bool math::Box::hits_xz_face(const Ray& ray, double y, bool only_positive) const
{
    if (ray.direction.y() == approx(0.0))
    {
        return false;
    }
    else
    {
        double t = -(ray.origin.y() - y) / ray.direction.y();
        Point3D p = ray.at(t);

        return (!only_positive || t > 0) && m_x_interval.contains(p.x()) && m_z_interval.contains(p.z());
    }
}

bool math::Box::hits_yz_face(const Ray& ray, double x, bool only_positive) const
{
    if (ray.direction.x() == approx(0.0))
    {
        return false;
    }
    else
    {
        double t = -(ray.origin.x() - x) / ray.direction.x();
        Point3D p = ray.at(t);

        return (!only_positive || t > 0) && m_y_interval.contains(p.y()) && m_z_interval.contains(p.z());
    }
}

Box math::Box::empty()
{
    auto interval = Interval<double>::empty();

    return Box(interval, interval, interval);
}

Box math::Box::infinite()
{
    auto interval = Interval<double>::infinite();

    return Box(interval, interval, interval);
}

Box math::Box::from_raw_corners(const Point3D& lower_corner, const Point3D& upper_corner)
{
    auto x = interval(lower_corner.x(), upper_corner.x());
    auto y = interval(lower_corner.y(), upper_corner.y());
    auto z = interval(lower_corner.z(), upper_corner.z());

    return Box(x, y, z);
}

Box math::Box::from_corners(const Point3D& p, const Point3D& q)
{
    // Sort coordinates so that box is nonempty
    auto x = nonempty_interval(p.x(), q.x());
    auto y = nonempty_interval(p.y(), q.y());
    auto z = nonempty_interval(p.z(), q.z());

    return Box(x, y, z);
}

Box math::Box::merge(const Box& other) const
{
    return Box(m_x_interval.merge(other.m_x_interval), m_y_interval.merge(other.m_y_interval), m_z_interval.merge(other.m_z_interval));
}

Box math::Box::intersect(const Box& other) const
{
    return Box(m_x_interval.intersect(other.m_x_interval), m_y_interval.intersect(other.m_y_interval), m_z_interval.intersect(other.m_z_interval));
}

Interval<double> math::Box::x() const
{
    return m_x_interval;
}

Interval<double> math::Box::y() const
{
    return m_y_interval;
}

Interval<double> math::Box::z() const
{
    return m_z_interval;
}

Point3D math::Box::center() const
{
    return Point3D(m_x_interval.center(), m_y_interval.center(), m_z_interval.center());
}

bool math::Box::is_infinite() const
{
    return m_x_interval.is_infinite() || m_y_interval.is_infinite() || m_z_interval.is_infinite();
}

bool math::Box::contains(const Point3D& p) const
{
    return m_x_interval.contains(p.x()) && m_y_interval.contains(p.y()) && m_z_interval.contains(p.z());
}