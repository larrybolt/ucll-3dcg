#pragma once

#include "materials/material.h"


namespace raytracer
{
    namespace materials
    {
        Material composite(math::Function<Material(const math::Point2D&)> function);
        Material composite(math::Function<Material(const math::Point3D&)> function);
    }
}