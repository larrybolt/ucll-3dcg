#pragma once

#include "math/vector.h"
#include "math/point.h"


namespace math
{
    struct Plane
    {
        Point3D point;
        Vector3D normal;

        Plane(const math::Point3D&, const math::Vector3D&);

        static Plane from_point_and_normal(const math::Point3D&, const math::Vector3D&);
    };

    /// <summary>
    /// Computes the distance from <paramref name="point" /> to <paramref name="plane" />.
    /// The distance is positive if the point resides on the side of the plane the normal points to.
    /// </summary>
    double distance(const math::Plane& plane, const math::Point3D& point);

    /// <summary>
    /// Checks whether <paramref name="point" /> lies in front of the plane.
    /// The front is defined as the subspace <paramref name="point" />'s normal points to.
    /// If the point lies on the plane, this function returns false.
    /// </summary>
    bool lies_in_front_of(const math::Plane& plane, const math::Point3D& point);

    /// <summary>
    /// Checks whether <paramref name="point" /> lies behind the plane.
    /// The front is defined as the subspace <paramref name="point" />'s normal points to.
    /// If the point lies on the plane, this function returns false.
    /// </summary>
    bool lies_behind(const math::Plane& plane, const math::Point3D& point);

    /// <summary>
    /// Checks whether <paramref name="point" /> lies on the plane.
    /// </summary>
    bool lies_on(const math::Plane& plane, const math::Point3D& point, double epsilon = 0.00000001);
}
