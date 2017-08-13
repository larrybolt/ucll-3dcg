#pragma once

#include "lights/light-source.h"
#include "imaging/color.h"
#include "math/point.h"


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            /// <summary>
            /// Helper class for point lights, i.e. lights that exist only in a single point.
            /// Point lights always only cast one light ray.
            /// </summary>
            class PointLightImplementation : public LightSourceImplementation
            {
            public:
                /// <summary>
                /// Constructor.
                /// </summary>
                /// <param name="position">Position of the point light.</param>
                PointLightImplementation(const math::Point3D& position);

                std::vector<LightRay> lightrays_to(const math::Point3D&) const override;

            protected:
                /// <summary>
                /// Returns the single light ray. Called by lightrays_to, which
                /// puts the result of this function in a list.
                /// </summary>
                virtual LightRay cast_lightray_to(const math::Point3D&) const = 0;

                /// <summary>
                /// Point light's position.
                /// </summary>
                math::Point3D m_position;
            };
        }
    }
}