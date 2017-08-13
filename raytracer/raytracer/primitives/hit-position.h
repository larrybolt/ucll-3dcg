#pragma once

#include "math/point.h"
#include "math/point.h"


namespace raytracer
{
    /// <summary>
    /// Represents to local position of a hit, i.e. in the primitive's own coordinate system
    /// instead of the world's.
    /// </summary>
    struct HitPosition
    {
        /// <summary>
        /// 2D uv-coordinates.
        /// </summary>
        math::Point2D uv;

        /// <summary>
        /// 3D xyz-coordinates.
        /// </summary>
        math::Point3D xyz;
    };
}