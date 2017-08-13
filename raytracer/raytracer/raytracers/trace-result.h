#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "primitives/hit.h"
#include <limits>


namespace raytracer
{
    /// <summary>
    /// Returned by RayTracer::trace. Its sole purpose
    /// is to be able to easily return multiple pieces of data from RayTracer::trace.
    /// </summary>
    struct TraceResult
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="color">Color of the hit</param>
        /// <param name="group_id">Group id</param>
        /// <param name="ray">Ray</param>
        /// <param name="t">T-value, indicates location of hit</param>
        TraceResult(imaging::Color color, unsigned group_id, const math::Ray& ray, double t)
            : color(color), group_id(group_id), ray(ray), t(t) { }

        /// <summary>
        /// Static factory. Creates a TraceResult object which represents "no hit found".
        /// The color is black, there's no group id, an the t-value is infinity.
        /// </summary>
        static TraceResult no_hit(const math::Ray& ray)
        {
            return TraceResult(imaging::colors::black(), MISSING_ID, ray, std::numeric_limits<double>::infinity());
        }

        /// <summary>
        /// Most important piece of information: the ray tracer determined the ray must have this color.
        /// Used by the renderer to paint a pixel.
        /// </summary>
        imaging::Color color;

        /// <summary>
        /// For edge detection. Every primitive belongs to a group.
        /// </summary>
        unsigned group_id;

        /// <summary>
        /// Ray that was being traced.
        /// </summary>
        math::Ray ray;

        /// <summary>
        /// Indicates where on the ray the ray-scene intersection was found.
        /// </summary>
        double t;

        /// <summary>
        /// Position where the ray-scene intersection occurred.
        /// </summary>
        math::Point3D hit_position() const
        {
            return ray.at(t);
        }
    };
}