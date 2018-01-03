#include "raytracers/ray-tracer-v3.h"
#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

Color raytracers::_private_::RayTracerV3::process_light_ray(const Scene &scene, const MaterialProperties &props, const Hit &hit, const math::Ray &ray, const LightRay &lightray) const
{

	//Call the base class's (RayTracerV2) version of process_light_ray.
	Color result = raytracers::_private_::RayTracerV2::process_light_ray(scene, props, hit, ray, lightray);

	//Call compute_specular and add its return value to result.
	result += compute_diffuse(props, hit, ray, lightray);

	return result;
}

Color raytracers::_private_::RayTracerV3::compute_diffuse(const MaterialProperties &props, const Hit &hit, const math::Ray &ray, const LightRay &lightray) const
{
	Color result = colors::black();

	//Implement the specular highlight algorithm.

	//1. Compute the direction of the incoming light.
	Vector3D direction_Incoming = (hit.position - lightray.ray.origin).normalized();

	//2. Compute the reflected direction.
	Vector3D direction_Reflected = direction_Incoming.reflect_by(hit.normal);

	//3. Compute the unit vector going from the hit position to the eyes position.
	Vector3D unit_Vector = (ray.origin - hit.position).normalized();

	//4. Compute the cosine of the angle between reflected_Direction and unit_Vector.
	double cos_Alpha = unit_Vector.dot(direction_Reflected);

	if (cos_Alpha > 0)
	{
		result += lightray.color * props.ambient * pow(cos_Alpha, props.specular_exponent);
	}

	return result;
}

raytracer::RayTracer raytracer::raytracers::v3()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}
