#pragma once

#include "math/vector.h"
#include "math/point.h"
#include "math/matrix.h"
#include <iostream>

namespace math
{
    /// <summary>
    /// A ray is a 3D geometric entity. It has a starting point (origin) and a direction.
    /// </summary>
    struct Ray final
    {
        Point3D origin;
        Vector3D direction;

        /// <summary>
        /// Creates a ray from an origin and a direction.
        /// </summary>
        Ray(const Point3D& origin, const Vector3D& direction);

        /// <summary>
        /// Creates a ray from two points, so that the first point <paramref name="origin" /> acts as the origin of the ray
        /// and the ray passes through the second point <paramref name="through" /> at t = 1.
        /// </summary>
        Ray(const Point3D& origin, const Point3D& through);

        /// <summary>
        /// Returns the point on the ray at the location specified by <paramref name="t">.
        /// <code>ray.at(0)</code> returns the origin, <code>ray.at(1)</code>
        /// returns one step away from the origin in the ray's direction.
        /// </summary>
        Point3D at(double t) const;

        /// <summary>
        /// Returns a new ray equal to the transformation matrix <paramref name="m"> applied to this ray.
        /// </summary>
        Ray transform(const Matrix4x4& m) const;
    };

    /// <summary>
    /// Checks rays for equality.
    /// </summary>
    bool operator ==(const Ray&, const Ray&);

    std::ostream& operator <<(std::ostream& out, const Ray&);

    template<>
    struct approximately<Ray>
    {
        math::Ray value;
        double epsilon;

        explicit approximately(const math::Ray& value, double epsilon = 0.00001)
            :value(value), epsilon(epsilon)
        {
            // NOP
        }

        bool close_enough(const math::Ray& other) const
        {
            return value.origin == approx(other.origin, epsilon) && value.direction == approx(other.direction, epsilon);
        }
    };
}