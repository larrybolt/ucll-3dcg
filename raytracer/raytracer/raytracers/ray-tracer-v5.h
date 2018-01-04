#pragma once

#include "raytracers/ray-tracer-v4.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV5 : public RayTracerV4
			{
			public:
				TraceResult trace(const Scene&, const math::Ray&) const override;
			protected:
				imaging::Color trace(const Scene&, const math::Ray&, double) const;
				imaging::Color compute_reflection(const Scene&, const MaterialProperties&, const math::Ray&, const Hit&, double) const;
			};
		}
		RayTracer v5();
	}
}