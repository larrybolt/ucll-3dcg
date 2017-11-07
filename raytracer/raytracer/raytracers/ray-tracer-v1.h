#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV1 : public RayTracerImplementation
            {
            public:
                TraceResult trace(const Scene&, const math::Ray&) const override;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v1();
    }
}