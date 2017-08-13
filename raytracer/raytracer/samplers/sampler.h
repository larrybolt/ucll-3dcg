#pragma once

#include "math/rectangle2d.h"
#include <functional>
#include <memory>
#include <vector>


namespace raytracer
{
    namespace samplers
    {
        namespace _private_
        {
            /// <summary>
            /// Sampler implementation. Its purpose is, given a 2D rectangle, to produce
            /// points within this rectangle. Each subclass is free to choose how many points
            /// and which points it produces.
            /// When subclassing, override only one of both sample methods.
            /// </summary>
            class SamplerImplementation
            {
            public:
                /// <summary>
                /// Returns a number of points in <paramref name="rectangle" />.
                /// How many and which points depends on the type of sampler.
                /// </summary>
                virtual std::vector<math::Point2D> sample(const math::Rectangle2D& rectangle) const;

                /// <summary>
                /// Same as other sample member function, but instead of putting all points in a vector,
                /// it calls the given <paramref name="callback" /> with each point. This
                /// overload should be slightly more efficient since no heap allocation is necessary for a vector.
                /// </summary>
                virtual void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> callback) const;
            };
        }        
    }
    
    /// <summary>
    /// Wrapper class for samplers. Access sampler members using -&gt;.
    /// </summary>
    class Sampler
    {
    public:
        explicit Sampler(std::shared_ptr<samplers::_private_::SamplerImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        samplers::_private_::SamplerImplementation* operator ->() const
        {
            return m_implementation.get();
        }

        operator bool() const
        {
            return m_implementation != nullptr;
        }

    private:
        std::shared_ptr<samplers::_private_::SamplerImplementation> m_implementation;
    };
}