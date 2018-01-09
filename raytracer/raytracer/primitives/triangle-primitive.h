#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		Primitive triangle(const math::Point3D&, const math::Point3D&, const math::Point3D&);
	}
}