#pragma once

#include "math/vector.h"
#include "math/point.h"

namespace math
{
    /// <summary>
    /// Represents a rectangle (actually a parallelogram if x_axis and y_axis are not perpendicular) in 2D space. 
    /// </summary>
    struct Rectangle2D
    {
        Point2D origin;
        Vector2D x_axis;
        Vector2D y_axis;

        /// <summary>
        /// Creates a rectangle from an origin and two sides.
        /// </summary>
        Rectangle2D(const Point2D& origin, const Vector2D& x_axis, const Vector2D& y_axis);

        /// <summary>
        /// Sees the rectangle as a coordinate system.
        /// (0,0) returns the origin, (0,1), (1,0) and (1,1) correspond to the other corners.
        /// If x and y are between 0 and 1, from_relative(x, y) returns a point inside the rectangle.
        /// </summary>
        Point2D from_relative(const Point2D&) const;

        /// <summary>
        /// Returns the center of the rectangle, i.e. <code>from_relative(Point2D(0.5, 0.5))</code>
        /// </summary>
        Point2D center() const;
    };

    bool operator ==(const Rectangle2D&, const Rectangle2D&);
    bool operator !=(const Rectangle2D&, const Rectangle2D&);
}