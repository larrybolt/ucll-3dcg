#include "ray-tracer-v6.h"
#include "ray-tracer-v5.h"
#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV6::trace(const Scene &scene, const math::Ray &ray, double weight) const
{
	Hit hit;

	Color result = colors::black();

	if (scene.root->find_first_positive_hit(ray, &hit))
	{
		result += RayTracerV5::trace(scene, ray, weight);

		MaterialProperties props = hit.material->at(hit.local_position);

		result += compute_refraction(scene, props, ray, hit, weight);
	}
	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_refraction(const Scene &scene, const MaterialProperties &props, const math::Ray &ray, const Hit &hit, double weight) const
{
	Color result = colors::black();

	if (props.transparency > 0)
	{
		double n1 = 1.0;
		double n2 = props.refractive_index;
		Vector3D direction_incoming = (hit.position - ray.origin).normalized();
		Vector3D normal = hit.normal;
		Vector3D outgoing_x = (n1 / n2) * (direction_incoming - (direction_incoming.dot(normal)) * normal);
		if ((1 - outgoing_x.dot(outgoing_x)) < 0)
		{
			return result;
		}
		Vector3D outgoing_y = (0 - sqrt(1 - (outgoing_x.dot(outgoing_x)))) * normal;
		Vector3D direction_outgoing = outgoing_x + outgoing_y;
		Ray refracted_ray = Ray(hit.position + (0.00000001 * direction_outgoing), direction_outgoing);

		Hit exit_hit;

		if (scene.root->find_first_positive_hit(refracted_ray, &exit_hit))
		{
			n1 = exit_hit.material->at(exit_hit.local_position).refractive_index;
			n2 = 1.0;
			direction_incoming = (exit_hit.position - refracted_ray.origin).normalized();
			normal = exit_hit.normal;
			outgoing_x = (n1 / n2) * (direction_incoming - (direction_incoming.dot(normal)) * normal);
			outgoing_y = (0 - sqrt(1 - (outgoing_x.dot(outgoing_x)))) * normal;
			direction_outgoing = outgoing_x + outgoing_y;
			Ray exit_ray = Ray(exit_hit.position + (0.00000001 * direction_outgoing), direction_outgoing);

			result += (trace(scene, exit_ray, weight * props.transparency) * props.transparency);
		}
		else
		{
			return result;
		}
	
	}
	return result;
}

RayTracer raytracer::raytracers::v6()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}
