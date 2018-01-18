#pragma once

#include "primitives/primitive.h"
#include "math/transformation3d.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        Primitive transform(const math::Transformation3D&, Primitive);
        Primitive translate(const math::Vector3D&, Primitive);  
		Primitive scale(double, double, double, Primitive);
		Primitive rotate_around_x(math::Angle, Primitive );
    }
}