#include "primitives/primitive.h"


bool raytracer::primitives::_private_::PrimitiveImplementation::find_first_positive_hit(const math::Ray& ray, Hit* output_hit) const
{
    assert(output_hit);

    // Collect all hits
    auto hits = find_all_hits(ray);

    for (auto hit : hits)
    {
        // Find first positive hit
        if (hit->t > 0)
        {
            // Is first positive hit closer than already existing hit?
            if (hit->t < output_hit->t)
            {
                // Overwrite hit with new hit
                *output_hit = *hit;
                return true;

            }
            else
            {
                // First positive hit is farther away than already existing hit
                return false;
            }
        }
    }

    // No positive hits were found
    return false;
}