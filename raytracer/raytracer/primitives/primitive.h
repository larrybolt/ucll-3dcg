#pragma once

#include "primitives/hit.h"
#include "math/ray.h"
#include "math/box.h"
#include <iostream>
#include <vector>
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class PrimitiveImplementation
            {
            public:
                /// <summary>
                /// Finds the first positive hit between <paramref name="ray" /> and this object which
                /// is closer than the hit described in parameter <paramref name="hit" />.
                /// If such a hit is found, information about the hit is written to the <paramref name="hit" /> argument.
                /// </summary>
                /// <param name="ray">Ray of which to find the intersections with this primitive.</param>
                /// <param name="hit">Pointer to Hit data structure</param>
                /// <returns>True if a positive hit was found that is closer than the one already in <paramref name="hit" />, false otherwise.</returns>
                virtual bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const;

                /// <summary>
                /// Returns all intersections of <paramref name="ray" /> and this primitive.
                /// The hits are sorted by increasing t. Negative hits are also included.
                /// </summary>
                /// <param name="ray">Ray of which to find the intersections with this primitive.</param>
                /// <returns>List of hits in order of increasing t. Negative hits are included.</returns>
                virtual std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const = 0;

                /// <summary>
                /// Returns a bounding box.
                /// </summary>
                /// <returns>A box fully containing this primitive.</returns>
                virtual math::Box bounding_box() const = 0;
            };
        }
    }

    class Primitive
    {
    public:
        explicit Primitive(std::shared_ptr<primitives::_private_::PrimitiveImplementation> impl = nullptr)
            : m_impl(impl) { }

        primitives::_private_::PrimitiveImplementation* operator ->()
        {
            return m_impl.get();
        }

        primitives::_private_::PrimitiveImplementation* operator ->() const
        {
            return m_impl.get();
        }

        operator bool() const
        {
            return m_impl != nullptr;
        }

    private:
        std::shared_ptr<primitives::_private_::PrimitiveImplementation> m_impl;
    };
}
