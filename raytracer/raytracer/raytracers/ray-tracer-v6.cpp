#include "ray-tracer-v6.h"
#include "ray-tracer-v5.h"
#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV6::trace(const Scene &, const math::Ray &, double) const
{
	return imaging::Color();
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_refraction(const Scene &, const MaterialProperties &, const math::Ray &, const Hit &, double) const
{
	return imaging::Color();
}

RayTracer raytracer::raytracers::v6()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}
