#include "primitives/triangle-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:

		TriangleImplementation(const Point3D& v0, const Point3D& v1, const Point3D& v2)
			: m_v0(v0), m_v1(v1), m_v2(v2) {}

		bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
		{
			auto hits = find_all_hits(ray);
			if (hits.size() > 0)
			{
				auto found = hits.back();
				if (found->t > 0 && found->t < hit->t)
				{
					*hit = *found;
					return true;
				}
			}
			return false;
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{

			std::vector<std::shared_ptr<Hit>> hits;

			// Möller-Trumbore intersection algorithm, source: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
			double EPSILON = 0.0000001;
			Vector3D vertex0 = Vector3D(m_v0.x(), m_v0.y(), m_v0.z());
			Vector3D vertex1 = Vector3D(m_v1.x(), m_v1.y(), m_v1.z());
			Vector3D vertex2 = Vector3D(m_v2.x(), m_v2.y(), m_v2.z());;
			Vector3D edge1, edge2, h, s, q;
			double a, f, u, v;
			edge1 = vertex1 - vertex0;
			edge2 = vertex2 - vertex0;
			h = ray.direction.cross(edge2);
			a = edge1.dot(h);
			if (a < EPSILON)
			{
				return hits;
			}
			f = 1 / a;
			Vector3D rayOrigin = Vector3D(ray.origin.x(), ray.origin.y(), ray.origin.z());
			s = rayOrigin - vertex0;
			u = f * (s.dot(h));
			if (u < 0.0 || u > 1.0)
			{
				return hits;
			}
			q = s.cross(edge1);
			v = f * ray.direction.dot(q);
			if (v < 0.0 || u + v > 1.0)
			{
				return hits;
			}
			double t = f * edge2.dot(q);
			if (t > 0.0)
			{
				auto hit = std::make_shared<Hit>();
				initialize_hit(hit.get(), ray, t);
				hit->normal = -edge2.cross(edge1);
				hits.push_back(hit);
			}
			return hits;
		}

		Box bounding_box() const override
		{
			double min_x = std::min(std::min(m_v0.x(), m_v1.x()), m_v2.x());
			double max_x = std::max(std::max(m_v0.x(), m_v1.x()), m_v2.x());
			double min_y = std::min(std::min(m_v0.y(), m_v1.y()), m_v2.y());
			double max_y = std::max(std::max(m_v0.y(), m_v1.y()), m_v2.y());
			double min_z = std::min(std::min(m_v0.z(), m_v1.z()), m_v2.z());
			double max_z = std::max(std::max(m_v0.z(), m_v1.z()), m_v2.z());
			return Box(interval(min_x, max_x), interval(min_y, max_y), interval(min_z, max_z));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const
		{
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
		}

	private:
		Point3D m_v0;
		Point3D m_v1;
		Point3D m_v2;
	};
}

Primitive raytracer::primitives::triangle(const Point3D& v0, const Point3D& v1, const Point3D& v2)
{
	return Primitive(std::make_shared<TriangleImplementation>(v0, v1, v2));
}