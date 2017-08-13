#pragma once

#include "imaging/color.h"
#include "math/point.h"
#include "math/function.h"
#include "primitives/hit-position.h"
#include "materials/material-properties.h"
#include "animation/time-stamp.h"
#include <assert.h>
#include <memory>


namespace raytracer
{
    namespace materials
    {
        namespace _private_
        {
            /// <summary>
            /// Behind-the-scenes class that represents materials. Meant for internal use only.
            /// </summary>
            class MaterialImplementation
            {
            public:
                /// <summary>
                /// Returns the material properties at the given point.
                /// </summary>
                virtual MaterialProperties at(const HitPosition&) const = 0;
            };

            class Material2DImplementation : public MaterialImplementation
            {
            public:
                MaterialProperties at(const HitPosition&) const override;

            protected:
                virtual MaterialProperties at(const math::Point2D&) const = 0;
            };

            class Material3DImplementation : public MaterialImplementation
            {
            public:
                MaterialProperties at(const HitPosition&) const override;

            protected:
                virtual MaterialProperties at(const math::Point3D&) const = 0;
            };
        }
    }

    /// <summary>
    /// Material wrapper. You can access a material's "true members" using the -&gt; operator.
    /// See MaterialImplementation.
    /// </summary>
    class Material
    {
    public:
        explicit Material(std::shared_ptr<materials::_private_::MaterialImplementation> impl = nullptr)
            : m_impl(impl) { }

        operator bool() const
        {
            return m_impl != nullptr;
        }

        materials::_private_::MaterialImplementation* operator ->() const
        {
            return m_impl.get();
        }

    private:
        std::shared_ptr<materials::_private_::MaterialImplementation> m_impl;
    };

    Material make_2d_material(math::Function<MaterialProperties(const math::Point2D&)>);
    Material make_3d_material(math::Function<MaterialProperties(const math::Point3D&)>);

    math::Function<Material(animation::TimeStamp)> to_animated_2d_material(Material material);
}