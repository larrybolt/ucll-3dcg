#pragma once

#include "raytracers/ray-tracer-v2.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV3 : public RayTracerV2
			{
			protected:
				imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			protected:
				imaging::Color compute_diffuse(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			};
		}
		RayTracer v3();
	}
}