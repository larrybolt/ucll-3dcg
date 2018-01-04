#include "raytracers/ray-tracer-v4.h"
#include "raytracers/ray-tracers.h"
#include <iostream>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace std;

Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene &scene, const MaterialProperties &props, const Hit &hit, const math::Ray &ray, const LightRay &lightray) const
{
	Hit rayhit;

	if (scene.root->find_first_positive_hit(lightray.ray, &rayhit))
	{
		// Find the intersection between the light ray and the scene.
		double t = rayhit.t;

		if ((0 <= t) && (t < 1))
		{
			// If there's a hit where 0 <= t < 1, return black
			return colors::black();
		}
		// Otherwise call RayTracerV3::process_light_rays and return its result.
		return RayTracerV3::process_light_ray(scene, props, hit, ray, lightray);
	}
}

raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}
