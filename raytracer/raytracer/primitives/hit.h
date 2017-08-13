#pragma once

#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
#include "imaging/color.h"
#include "materials/material.h"
#include "primitives/hit-position.h"
#include <limits>
#include <memory>

namespace raytracer
{
    const unsigned MISSING_ID = unsigned(-1);

    /// <summary>
    /// Ray tracers use hit objects to contain all information about the intersection between a
    /// ray and a primitive.
    /// </summary>
    struct Hit
    {
        /// <summary>
        /// Default constructor. Sets t to infinity, which corresponds to "no hit".
        /// </summary>
        Hit() : t(std::numeric_limits<double>::infinity()), group_id(MISSING_ID) { }

        /// <summary>
        /// t-value of the hit. It indicates where on the ray the hit is located.
        /// </summary>
        double t;

        /// <summary>
        /// The location of the hit in the primitive's own coordinate system.
        /// </summary>
        HitPosition local_position;

        /// <summary>
        /// The location of the hit in the world's coordinate system.
        /// </summary>
        math::Point3D position;

        /// <summary>
        /// Vector perpendicular on the primitive at the location that's been hit.
        /// </summary>
        math::Vector3D normal;

        /// <summary>
        /// Material of the primitive that's been hit.
        /// </summary>
        Material material;

        /// <summary>
        /// Group id. Groups indicate which objects belong together. Used for edge detection.
        /// </summary>
        unsigned group_id;
    };
}