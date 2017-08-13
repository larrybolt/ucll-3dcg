#pragma once

#include "lights/light-ray.h"
#include "math/point.h"
#include <vector>
#include <memory>

namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            /// <summary>
            /// Light source implementation.
            /// </summary>
            class LightSourceImplementation
            {
            public:
                /// <summary>
                /// Generates a list of light rays that go from the light source to the given <paramref name="point" />.
                /// For shadowing purposes, it is important that all light rays are constructed in such a manner
                /// that t=0 coincides with the source of the photons and t=1 coincides with the given <paramref name="point" />.
                /// Only objects that are located between t=0 and t=1 are taken into consideration for shadowing.
                /// </summary>
                virtual std::vector<LightRay> lightrays_to(const math::Point3D& point) const = 0;
            };
        }        
    }

    /// <summary>
    /// Wrapper class for lights. Members are to be accessed using -&gt;.
    /// </summary>
    class LightSource
    {
    public:
        explicit LightSource(std::shared_ptr<lights::_private_::LightSourceImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        lights::_private_::LightSourceImplementation* operator ->() const
        {
            return m_implementation.get();
        }

    private:
        std::shared_ptr<lights::_private_::LightSourceImplementation> m_implementation;
    };
}