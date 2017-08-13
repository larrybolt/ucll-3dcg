#include "primitives/union-primitive.h"
#include "easylogging++.h"
#include <algorithm>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
    class BinaryUnionImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        BinaryUnionImplementation(Primitive child1, Primitive child2)
            : m_child1(child1), m_child2(child2)
        {
            // NOP
        }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            // Always assume hit already contains a hit

            // Ask child1 for a "better" hit. If there is one, it will return true
            // and overwrite hit with new data
            bool found_hit1 = m_child1->find_first_positive_hit(ray, hit);

            // Even if child1 found a hit, child2 might have a better one.
            bool found_hit2 = m_child2->find_first_positive_hit(ray, hit);

            // Return whether there has been a hit
            return found_hit1 || found_hit2;
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> result;

            bool inside1 = false;
            bool inside2 = false;
            bool was_inside_union = false;

            // Collect children's hits
            auto hits1 = m_child1->find_all_hits(ray);
            auto hits2 = m_child2->find_all_hits(ray);

            // Append hits at infinity
            hits1.push_back(std::make_shared<Hit>());
            hits2.push_back(std::make_shared<Hit>());

            // Start iterating over hit lists
            auto i1 = hits1.begin();
            auto i2 = hits2.begin();

            while (i1 + 1 != hits1.end() || i2 + 1 != hits2.end())
            {
                // Get hits
                auto hit1 = *i1;
                auto hit2 = *i2;
                std::shared_ptr<Hit> active_hit = nullptr;

                // Get t-values of hits
                double t1 = hit1->t;
                double t2 = hit2->t;

                // Find closest hit
                if (t1 < t2)
                {
                    // If we were inside child1, we're now outside, and vice versa
                    inside1 = !inside1;

                    // Save hit for later
                    active_hit = hit1;

                    // Move to next hit
                    ++i1;
                }
                else if ( t1 > t2 )
                {
                    // If we were inside child1, we're now outside, and vice versa
                    inside2 = !inside2;

                    // Save hit for later
                    active_hit = hit2;

                    // Move to next hit
                    ++i2;
                }
                else
                {
                    inside1 = !inside1;
                    inside2 = !inside2;

                    active_hit = hit1;

                    ++i1;
                    ++i2;
                }

                // We're inside the union if we're inside one of the children
                bool inside_union = inside1 || inside2;

                // Check if there was a change
                if (was_inside_union != inside_union)
                {
                    // The active hit is important; add it to the result list
                    result.push_back(active_hit);

                    // Overwrite value
                    was_inside_union = inside_union;
                }
            }

            return result;
        }

        math::Box bounding_box() const override
        {
            return m_child1->bounding_box().merge(m_child2->bounding_box());
        }

    private:
        Primitive m_child1;
        Primitive m_child2;
    };
}

Primitive raytracer::primitives::make_union(std::vector<Primitive>& children)
{
    if (children.size() == 0)
    {
        LOG(ERROR) << "Union needs at least one child";
        abort();
    }
    else
    {
        // TODO: This creates a linked list of children, would a balanced tree be more efficient
        auto i = children.begin();

        Primitive result = *i;

        ++i;
        while (i != children.end())
        {
            result = Primitive(std::make_shared<BinaryUnionImplementation>(result, *i));

            ++i;
        }

        return result;
    }
}
