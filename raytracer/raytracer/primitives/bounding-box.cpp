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

		math::Box bounding_box() const override {
			return box;
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& r) const override {
			if (box.is_hit_by(r)) {
				return primitive->find_all_hits(r);
				

			}
			return std::vector<std::shared_ptr<Hit>>();


		}


	};
}
	Primitive raytracer::primitives::bounding_box_accelerator(const Primitive p) {
		return Primitive(std::make_shared<BoundingBox>(p));
	}
