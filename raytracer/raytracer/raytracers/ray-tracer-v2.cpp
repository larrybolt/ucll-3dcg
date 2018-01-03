#include "raytracers/ray-tracer-v2.h"
#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV2::trace(const Scene& scene, const Ray& ray) const
{
	Hit hit;

	//Determine the first positive hit between the ray and the scene.
	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		unsigned group_id = hit.group_id;

		double t = hit.t;

		//Initialize a Color result to colors::black(), i.e. with start with zero photons.
		Color result = colors::black();

		//Ask the hit.material for the MaterialProperties at the hit location.
		MaterialProperties props = hit.material->at(hit.local_position);

		//Compute the ambient lighting (as you did in v1) and add the color to result.
		result += compute_ambient(props);

		//Call process_lights, which will iterate over all lights. Add the return value (a color) to result.
		result += process_lights(scene, props, hit, ray);

		//Return a TraceResult containing all necessary data, with as color result's final value.
		return TraceResult(result, group_id, ray, t);
	}
	else
	{
		//If there is no hit, return a TraceResult::no_hit.
		return TraceResult::no_hit(ray);
	}
}

Color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& props, const Hit& hit, const math::Ray& ray) const
{
	//Start with a fresh Color result set to black.
	Color result = colors::black();

	//Iterate over the scene's light sources. Call process_light_source for each light source and add the return value to result.
	for each (LightSource light in scene.light_sources)
	{
		result += process_light_source(scene, props, hit, ray, light);
	}

	return result;
}

Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene&scene, const MaterialProperties&props, const Hit&hit, const math::Ray& ray, LightSource light) const
{
	//Initialize a local variable result of type Color to black.
	Color result = colors::black();

	//Ask the light source to enumerate all light rays that reach hit.position.
	for each (LightRay lightray in light->lightrays_to(hit.position))
	{
		//Iterate over each of these light rays. Give each to process_light_ray. Add the return values to result.
		result += process_light_ray(scene, props, hit, ray, lightray);
	}

	return result;
}

Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& props, const Hit& hit, const math::Ray& ray, const LightRay& lightray) const
{
	//Initialize local variable result to black.
	Color result = colors::black();

	//Call compute_diffuse and add its return value to result.
	result += compute_diffuse(props, hit, ray, lightray);

	return result;
}

Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& props, const Hit& hit, const Ray& ray, const LightRay& lightray) const
{
	//Initialize local variable result to black.
	Color result = colors::black();

	//Compute the cosine of the angle alpha
	double cosAlpha = ((lightray.ray.origin - hit.position).normalized()).dot(hit.normal);

	//Translate the mathematical formula for diffuse lighting into code
	if (cosAlpha > 0)
	{
		result += (cosAlpha * lightray.color * props.diffuse);
	}

	return result;
}

raytracer::RayTracer raytracer::raytracers::v2()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}