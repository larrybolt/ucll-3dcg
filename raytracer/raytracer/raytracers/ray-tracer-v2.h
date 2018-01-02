#pragma once

#include "raytracers/ray-tracer-v1.h"
#include <memory>


namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV2 : public RayTracerV1
			{
			public:
				TraceResult trace(const Scene&, const math::Ray&) const override;
			protected:
				imaging::Color process_lights(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&) const;
			protected:
				imaging::Color process_light_source(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, LightSource) const;
			protected:
				imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			protected:
				imaging::Color compute_diffuse(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			};
		
		}

		/// <summary>
		/// Creates simplest ray tracer.
		/// </summary>
		RayTracer v2();
	}
}