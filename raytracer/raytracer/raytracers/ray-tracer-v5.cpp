#include "raytracers/ray-tracer-v5.h"
#include "raytracers/ray-tracer-v4.h"
#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

// Override trace to call new trace with parameter weight initialized at 1.0
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

	// Prevent infinite reflection from happening with the weight parameter
	if (weight > 0.01)
	{
		Hit reflect;

		// Find the intersection between the reflection ray and the scene
		if (scene.root->find_first_positive_hit(ray, &reflect))
		{
			double t = reflect.t;
			MaterialProperties props = reflect.material->at(reflect.local_position);
			
			result += compute_ambient(props);
			result += process_lights(scene, props, reflect, ray);

			// Call compute_reflection and add it to the result
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

		// Calculate the direction of the reflection
		Vector3D direction_Reflected = direction_Incoming.reflect_by(reflect.normal);

		// Calculate the origin of the reflection ray
		Point3D new_Origin = ray.at(reflect.t) + 0.00000001 * direction_Reflected;

		// Create a new ray with the new origin and the reflection direction
		Ray reflection = Ray(new_Origin, direction_Reflected);

		// Call trace with the new reflection ray
		result += (props.reflectivity * trace(scene, reflection, props.reflectivity * weight));
	}
	return result;
}

RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}
