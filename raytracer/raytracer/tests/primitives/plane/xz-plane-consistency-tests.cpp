#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"
#include <algorithm>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[PlaneXZ] find_all_hits consistent with find_first_positive_hit", "[PlaneXZ]")
{
    for (double x = -2; x < 2; x += 0.37)
    {
        for (double y = -2; y < 2; y += 0.14)
        {
            for (double z = -2; z < 2; z += 0.72)
            {
                for (double dx = -2; dx < 2; dx += 0.87)
                {
                    for (double dy = -2; dy < 2; dy += .47)
                    {
                        for (double dz = -2; dz < 2; dz += 61)
                        {
                            Point3D ray_origin(x, y, z);
                            Vector3D ray_direction(dx, dy, dz);
                            Ray ray(ray_origin, ray_direction);

                            Primitive primitive = xz_plane();

                            Hit hit1;
                            bool found_hit = primitive->find_first_positive_hit(ray, &hit1);

                            auto hits = primitive->find_all_hits(ray);

                            if (found_hit)
                            {
                                REQUIRE(hits.size() > 0);

                                auto first_positive_position = std::find_if(hits.begin(), hits.end(), [](std::shared_ptr<Hit> h) { return h->t > 0; });
                                REQUIRE(first_positive_position != hits.end());
                                auto hit2 = *first_positive_position;

                                CHECK(hit1.t == approx(hit2->t));
                                CHECK(hit1.position == approx(hit2->position));
                                CHECK(hit1.local_position.uv == approx(hit2->local_position.uv));
                                CHECK(hit1.local_position.xyz == approx(hit2->local_position.xyz));
                                CHECK(hit1.normal == approx(hit2->normal));
                            }
                            else
                            {
                                for (auto h : hits)
                                {
                                    REQUIRE(h->t <= 0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

#endif