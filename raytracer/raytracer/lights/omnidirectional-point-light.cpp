#include "lights/omnidirectional-point-light.h"

using namespace math;
using namespace raytracer;

namespace
{
    /// <summary>
    /// Implementation for omnidirectional point lights.
    /// </summary>
    class OmnidirectionalPointLight : public raytracer::lights::_private_::PointLightImplementation
    {
    public:
        OmnidirectionalPointLight(const math::Point3D& position, const imaging::Color& color)
            : PointLightImplementation(position), m_color(color) { }

    protected:
        LightRay cast_lightray_to(const math::Point3D& p) const override
        {
            // Create ray starting at the light source's position and going through p
            math::Ray ray(m_position, p);

            return LightRay(ray, m_color);
        }

    private:
        imaging::Color m_color;
    };
}

LightSource raytracer::lights::omnidirectional(const math::Point3D& position, const imaging::Color& color)
{
    return LightSource(std::make_shared<OmnidirectionalPointLight>(position, color));
}
