#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Union][Intersection]", "[Union][Intersection]")
{
    Point3D ray_origin(-100, 0, 0);
    Vector3D ray_direction(1, 0, 0);

    auto left_sphere = translate(Vector3D(-1, 0, 0), sphere());
    auto middle_sphere = sphere();
    auto right_sphere = translate(Vector3D(-1, 0, 0), sphere());

    std::vector<Primitive> primitives = { left_sphere, right_sphere };
    auto left_and_right_spheres = make_union(primitives);
    auto sphere_intersection = intersection(middle_sphere, left_and_right_spheres);
    Ray ray(ray_origin, ray_direction);

    auto hits = sphere_intersection->find_all_hits(ray);

    REQUIRE(hits.size() == 2);
}

#endif