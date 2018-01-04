#include "raytracers/ray-tracer-v5.h"
#include "raytracers/ray-tracer-v4.h"
#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene &scene, const math::Ray &ray) const
{
	Hit hit;

	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		unsigned group_id = hit.group_id;
		double t = hit.t;
		return TraceResult(trace(scene, ray, 1.0), group_id, ray, t);
	}
	else
	{
		return TraceResult::no_hit(ray);
	}
}

imaging::Color raytracer::raytracers::_private_::RayTracerV5::trace(const Scene &scene, const math::Ray &ray, double weight) const
{
	Color result = colors::black();

	if (weight > 0.01)
	{
		Hit reflect;
		if (scene.root->find_first_positive_hit(ray, &reflect))
		{
			double t = reflect.t;
			MaterialProperties props = reflect.material->at(reflect.local_position);
			
			result += compute_ambient(props);
			result += process_lights(scene, props, reflect, ray);
			result += compute_reflection(scene, props, ray, reflect, weight);
		}
	}

	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(const Scene &scene, const MaterialProperties &props, const math::Ray &ray, const Hit& reflect, double weight) const
{
	Color result = colors::black();

	if (props.reflectivity > 0)
	{
		Vector3D direction_Incoming = (reflect.position - ray.origin).normalized();
		Vector3D direction_Reflected = direction_Incoming.reflect_by(reflect.normal);
		Point3D new_Origin = ray.at(reflect.t);
		Ray reflect = Ray(new_Origin, direction_Reflected);
		result += (props.reflectivity * trace(scene, reflect, props.reflectivity * weight));
	}
	return result;
}

RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}
