#ifdef TEST_BUILD

#include "raytracers/ray-tracer-v1.h"
#include "cameras/cameras.h"
#include "materials/materials.h"
#include "Catch.h"
#include <vector>
#include <limits>

using namespace math;
using namespace imaging;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[RayTracerV1] Hit", "[RayTracerV1]")
{
    std::vector<Color> colors = { colors::white(), colors::red(), colors::green() };
    
    for (auto& color : colors)
    {
        for (double z = 1.1; z < 100; z *= 1.4)
        {
            auto camera = cameras::perspective(Point3D(0, 0, z), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
            MaterialProperties properties(color, colors::black(), colors::black(), 0);
            auto material = materials::uniform(properties);
            auto root = decorate(material, sphere());
            Scene scene(camera, root);
            auto ray_tracer = raytracers::v1();
            Ray ray(Point3D(0, 0, z), Vector3D(0, 0, -1));
            auto trace_result = ray_tracer->trace(scene, ray);

            CHECK(trace_result.t == approx(z - 1));
            CHECK(trace_result.color == color);
            CHECK(trace_result.ray == approx(ray));
        }
    }
}


TEST_CASE("[RayTracerV1] No hit", "[RayTracerV1]")
{
    std::vector<Color> colors = { colors::white(), colors::red(), colors::green() };

    for (auto& color : colors)
    {
        for (double z = 1.1; z < 100; z *= 1.4)
        {
            auto camera = cameras::perspective(Point3D(0, 0, z), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
            MaterialProperties properties(color, colors::black(), colors::black(), 0);
            auto material = materials::uniform(properties);
            auto root = decorate(material, sphere());
            Scene scene(camera, root);
            auto ray_tracer = raytracers::v1();
            Ray ray(Point3D(0, 0, z), Vector3D(0, 0, 1));
            auto trace_result = ray_tracer->trace(scene, ray);

            CHECK(trace_result.t == std::numeric_limits<double>::infinity());
            CHECK(trace_result.color == colors::black());
            CHECK(trace_result.ray == approx(ray));
        }
    }
}

#endif
