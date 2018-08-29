#include "primitives/bounding-box.h"
#include <assert.h>
using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;

namespace 
{
	class BoundingBox : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		Box box;

		Primitive primitive;

		BoundingBox(const Primitive p) : primitive(p), box(p->bounding_box()) {} //door primitive te gebruiken ipv zeker dat we child hebben.

		Box bounding_box() const override {
			return box;
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& r) const override {
			if (box.is_hit_by(r)) {
				
				return primitive->find_all_hits(r);
				
				
			}
			return std::vector<std::shared_ptr<Hit>>();


		}


	};

	class BoundingBoxx : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		Box box;

		Primitive primitive;

		BoundingBoxx(const Primitive p) : primitive(p), box(p->bounding_box()) {} //door primitive te gebruiken ipv zeker dat we child hebben.

		Box bounding_box() const override {
			return box;
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& r) const override {
			if (box.is_hit_by(r)) {
				
			/*	
				std::vector<std::shared_ptr<Hit>> hits;

				double denom = ray.direction.dot(m_normal);

				if (denom != approx(0.0))
				{
					double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));
					double t = numer / denom;

					if (bounding_box().contains(ray.at(t)))
					{
						auto hit = std::make_shared<Hit>();

						initialize_hit(hit.get(), ray, t);

						hits.push_back(hit);
					}
				}
				return hits;*/







			/*	double lower = box.z().lower;
				double upper = box.z().upper;
				double center = upper - lower;
				Box boxleft = Box(box.x(), box.y(), Interval<double>(lower,center));
				Box boxright = Box(box.x(), box.y(), Interval<double>(center, upper));

				

				if (boxleft.is_hit_by(r)) {
					return boxleft.
				}*/
				
				
				return primitive->find_all_hits(r);


			}
			return std::vector<std::shared_ptr<Hit>>();


		}
		void initialize_hit(Hit* hit, const Ray& ray, double t) const
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			
		}

	};
}
	Primitive raytracer::primitives::bounding_box_accelerator(const Primitive p) {
		return Primitive(std::make_shared<BoundingBox>(p));
	}

	Primitive raytracer::primitives::bounding_box_accelerator2(const Primitive p) {
		return Primitive(std::make_shared<BoundingBox>(p));
	}