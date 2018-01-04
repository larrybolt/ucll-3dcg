#include "raytracers/ray-tracer-v4.h"
#include "raytracers/ray-tracers.h"
#include <iostream>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace std;

Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene &scene, const MaterialProperties &props, const Hit &hit, const math::Ray &ray, const LightRay &lightray) const
{

	Color result = colors::black();

	Hit rayhit;

	if (scene.root->find_first_positive_hit(lightray.ray, &rayhit))
	{
		// Find the intersection between the light ray and the scene.
		double t = rayhit.t;

		// Problem: when checking if t < 1, sometimes black gets returned while it shouldn't be (resulting in black "spots" in the scene)
		// Presumably, the t value of rayhit when there shouldn't be a shadow is sometimes very close to 1, but not exactly 1
		// However, checking if t <= 0.99 feels like a dirty / incorrect solution, but it works.
		if ((0.00 <= t) && (t <= 0.99)) 
		{
			// If there's a hit where 0 <= t < 1, return black
			return result;
		}
	}
	// Otherwise call RayTracerV3::process_light_rays and return its result.
	result += RayTracerV3::process_light_ray(scene, props, hit, ray, lightray);
	return result;
}

raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}
