#pragma once

#include "imaging/color.h"
#include "data-structures/grid.h"
#include <memory>
#include <string>
#include <functional>


namespace imaging
{
    /// <summary>
    /// Represents a bitmap, i.e. a 2D grid of colors.
    /// </summary>
    class Bitmap final
    {
    public:
        /// <summary>
        /// Creates a new bitmap width given <paramref name="width" /> and <paramref name="height" />.
        /// All pixels are initialized to black.
        /// </summary>
        Bitmap(unsigned width, unsigned height);

        /// <summary>
        /// Copy constructor.
        /// </summary>
        Bitmap(const Bitmap&) = default;

        /// <summary>
        /// Move constructor.
        /// </summary>
        Bitmap(Bitmap&&) = default;

        /// <summary>
        /// Checks if the given <paramref name="position" /> is inside the bitmap.
        /// </summary>
        bool is_inside(const Position2D& position) const;

        /// <summary>
        /// Gives access to the pixel at the given <paramref name="position" />.
        /// </summary>
        Color& operator [](const Position2D& position);

        /// <summary>
        /// Gives readonly access to the pixel at the given <paramref name="position" />.
        /// </summary>
        const Color& operator [](const Position2D&) const;

        /// <summary>
        /// Returns the width of the bitmap.
        /// </summary>
        unsigned width() const;

        /// <summary>
        /// Returns the height of the bitmap.
        /// </summary>
        unsigned height() const;

        /// <summary>
        /// Adds pixel colors together. The given <paramref name="bitmap" /> must have the same size.
        /// </summary>
        Bitmap& operator +=(const Bitmap& bitmap);

        /// <summary>
        /// Subtracts pixel colors. The given <paramref name="bitmap" /> must have the same size.
        /// </summary>
        Bitmap& operator -=(const Bitmap&);

        /// <summary>
        /// Multiplies each pixel color with the given <paramref name="constant" />.
        /// </summary>
        Bitmap& operator *=(double constant);

        /// <summary>
        /// Divides each pixel color by the given <paramref name="constant" />.
        /// </summary>
        Bitmap& operator /=(double constant);

        /// <summary>
        /// Calls the given <paramref name="function" /> once for each pixel position.
        /// This is basically a loop that iterates over the entire bitmap.
        /// No specific order is guaranteed.
        /// </summary>
        void for_each_position(std::function<void(const Position2D&)> function) const;

        /// <summary>
        /// Overwrites all pixels with the given <paramref name="color" />.
        /// </summary>
        void clear(const Color& color);

        /// <summary>
        /// Inverts each pixel color in the bitmap.
        /// </summary>
        void invert();

    private:
        data::Grid<Color> m_pixels;
    };
}
