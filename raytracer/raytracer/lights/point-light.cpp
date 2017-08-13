#include "lights/point-light.h"

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::lights::_private_::PointLightImplementation::PointLightImplementation(const math::Point3D& position)
    : m_position(position) { }

std::vector<LightRay> raytracer::lights::_private_::PointLightImplementation::lightrays_to(const math::Point3D& p) const
{
    auto result = this->cast_lightray_to(p);

    // Only return non-black light rays
    if (result.color != colors::black())
    {
        return std::vector<LightRay> { result };
    }
    else
    {
        return std::vector<LightRay>();
    }
}
