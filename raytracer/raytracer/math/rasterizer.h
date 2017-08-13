#pragma once

#include "math/rectangle2d.h"
#include "data-structures/position.h"

namespace math
{
    /// <summary>
    /// A rasterizer takes a 2D rectangle and divides it into smaller rectangles in a grid-like fashion.
    /// </summary>
    class Rasterizer
    {
    private:
        Rectangle2D rect;
        unsigned m_horizontal_subdivisions;
        unsigned m_vertical_subdivisions;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="rect">Rectangle to be subdivided into a grid.</param>
        /// <param name="horizontal_subdivisions">Number of columns.</param>
        /// <param name="vertical_subdivisions">Number of rows.</param>
        Rasterizer(const Rectangle2D& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
            : rect(rect), m_horizontal_subdivisions(horizontal_subdivisions), m_vertical_subdivisions(vertical_subdivisions) { }

        /// <summary>
        /// Copy constructor.
        /// </summary>
        Rasterizer(const Rasterizer&) = default;

        Rasterizer& operator =(const Rasterizer&) = default;

        /// <summary>
        /// Returns the number of columns.
        /// </summary>
        unsigned horizontal_subdivisions() const;

        /// <summary>
        /// Returns the number of rows.
        /// </summary>
        unsigned vertical_subdivisions() const;

        /// <summary>
        /// Returns the subrectangle at the given <paramref name="position" />.
        /// </summary>
        Rectangle2D operator [](const Position2D& position) const;
    };
}
