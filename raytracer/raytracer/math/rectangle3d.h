#pragma once

#include "math/point.h"
#include "math/point.h"

namespace math
{
    /// <summary>
    /// Represents a rectangle (i.e. still a 2D figure) located in 3D space.
    /// If x_axis and y_axis are not perpendicular, objects model parallelograms instead.
    /// </summary>
    struct Rectangle3D
    {
        Point3D origin;
        Vector3D x_axis;
        Vector3D y_axis;

        /// <summary>
        /// Constructs a rectangle from an origin point and two axes.
        /// </summary>
        Rectangle3D(const Point3D& origin, const Vector3D& x_axis, const Vector3D& y_axis);

        /// <summary>
        /// Projects <paramref name="p" /> into 3D space. (0,0) corresponds to the origin,
        /// (0,1), (1, 0) and (1,1) correspond to the other corners of the rectangle.
        /// </summary>
        Point3D project(const Point2D& p) const;
    };
}