#include "lights/light-ray.h"

raytracer::LightRay::LightRay(const math::Ray& ray, const imaging::Color& color)
    : ray(ray), color(color)
{
    // NOP
}