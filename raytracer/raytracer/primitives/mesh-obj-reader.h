#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		Primitive mesh_obj(const std::string&);
	//	Primitive optimize_mesh(std::vector<Primitive>);
		Primitive optimize_mesh(std::vector<Primitive>&);

	}
}
