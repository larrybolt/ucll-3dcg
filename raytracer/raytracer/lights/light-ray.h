#pragma once

#include "math/ray.h"
#include "imaging/color.h"


namespace raytracer
{
    struct LightRay
    {
        LightRay(const math::Ray&, const imaging::Color&);

        math::Ray ray;
        imaging::Color color;
    };
}