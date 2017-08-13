#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "raytracers/scene.h"
#include "raytracers/trace-result.h"
#include <limits>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            /// <summary>
            /// Actual ray tracer implementation.
            /// </summary>
            class RayTracerImplementation
            {
            public:
                /// <summary>
                /// Give a scene and a ray, follows the ray's journey through the scene and determines which color the ray has.
                /// </summary>
                virtual TraceResult trace(const Scene& scene, const math::Ray& ray) const = 0;
            };
        }
    }

    /// <summary>
    /// Wrapper class for ray tracers. Actual members are accessed through -&gt;
    /// See RayTracerImplementation for a listing of members.
    /// </summary>
    class RayTracer
    {
    public:
        explicit RayTracer(std::shared_ptr<raytracers::_private_::RayTracerImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        const raytracers::_private_::RayTracerImplementation* operator ->() const
        {
            assert(m_implementation);

            return m_implementation.get();
        }

    private:
        std::shared_ptr<raytracers::_private_::RayTracerImplementation> m_implementation;
    };
}