#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
			class ObjMesh : public raytracer::primitives::_private_::PrimitiveImplementation
			{
			public:
				std::vector<Primitive> m_triangles;
				ObjMesh(const std::string& path) : m_triangles(read_mesh(path))
				{ }
				std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override;
				math::Box bounding_box() const override;
				std::vector<Primitive> read_mesh(const std::string&) const;
			};
		std::shared_ptr<ObjMesh> obj_mesh(std::string path);
		Primitive mesh(std::string path);
	}
}