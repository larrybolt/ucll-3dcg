#include "lights/spot-light.h"

using namespace math;
using namespace raytracer;

namespace
{
	class SpotLight : public raytracer::lights::_private_::PointLightImplementation
	{
	public:
		SpotLight(const Point3D& position, const Vector3D& direction, const Angle& angle, const imaging::Color& color)
			: PointLightImplementation(position), m_direction(direction), m_angle(angle), m_color(color) {}

	protected:
		LightRay cast_lightray_to(const Point3D& position) const override
		{
			Ray ray(m_position, position);
			double cosine = cos(m_angle / 2);
			Vector3D u = (position - m_position).normalized();
			if (u.dot(m_direction) >= cosine)
			{
				return LightRay(ray, m_color);
			}
			return LightRay(ray, imaging::colors::black());
		}

	private:
		Vector3D m_direction;
		Angle m_angle;
		imaging::Color m_color;
	};
}

LightSource raytracer::lights::spot(const Point3D& position, const Vector3D& direction, const Angle& angle, const imaging::Color& color)
{
	return LightSource(std::make_shared<SpotLight>(position, direction, angle, color));
}
