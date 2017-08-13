#ifdef TEST_BUILD

#include "Catch.h"
#include "primitives/primitives.h"
#include "math/approx.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


TEST_CASE("[Disk] Vertical ray hits disk", "[Disk]")
{
    auto disk = raytracer::primitives::disk();

    for (double radius = 0; radius < 1; radius += 0.11)
    {
        for (Angle angle = 0_degrees; angle < 360_degrees; angle += 15_degrees)
        {
            for (double y = 0.1; y < 10; y += 3.5)
            {
                for (double dy = 0.1; dy < 5; dy += 0.7)
                {
                    // Downward rays
                    {
                        CylindricalY cylindrical_coordinates{ radius, angle, y };
                        Cartesian3D cartesian_coordinates = convert_coordinates<Cartesian3D>(cylindrical_coordinates);
                        Point3D ray_origin = Point3D::cartesian(cartesian_coordinates);
                        Vector3D ray_direction = Vector3D(0, -dy, 0);
                        Ray ray(ray_origin, ray_direction);
                        double expected_t = y / dy;
                        Point3D expected_hit_position = Point3D(cartesian_coordinates.x, 0, cartesian_coordinates.z);

                        INFO("Ray: " << ray);

                        Hit hit;
                        CHECK(disk->find_first_positive_hit(ray, &hit));
                        CHECK(hit.normal == approx(Vector3D(0, 1, 0)));
                        CHECK(hit.t == approx(expected_t));
                        CHECK(hit.position == approx(expected_hit_position));
                    }

                    // Upward rays
                    {
                        CylindricalY cylindrical_coordinates{ radius, angle, -y };
                        Cartesian3D cartesian_coordinates = convert_coordinates<Cartesian3D>(cylindrical_coordinates);
                        Point3D ray_origin = Point3D::cartesian(cartesian_coordinates);
                        Vector3D ray_direction = Vector3D(0, dy, 0);
                        Ray ray(ray_origin, ray_direction);
                        double expected_t = y / dy;
                        Point3D expected_hit_position = Point3D(cartesian_coordinates.x, 0, cartesian_coordinates.z);

                        INFO("Ray: " << ray);

                        Hit hit;
                        CHECK(disk->find_first_positive_hit(ray, &hit));
                        CHECK(hit.normal == approx(Vector3D(0, -1, 0)));
                        CHECK(hit.t == approx(expected_t));
                        CHECK(hit.position == approx(expected_hit_position));
                    }
                }
            }
        }
    }
}

TEST_CASE("[Disk] Vertical ray misses disk because hit with XZ plane is too far from center", "[Disk]")
{
    auto disk = raytracer::primitives::disk();

    for (double radius = 1.01; radius < 100; radius *= 1.5)
    {
        for (Angle angle = 0_degrees; angle < 360_degrees; angle += 15_degrees)
        {
            for (double y = 0.1; y < 10; y += 3.5)
            {
                for (double dy = 0.1; dy < 5; dy += 0.7)
                {
                    // Downward rays
                    {
                        CylindricalY cylindrical_coordinates{ radius, angle, y };
                        Cartesian3D cartesian_coordinates = convert_coordinates<Cartesian3D>(cylindrical_coordinates);

                        Point3D ray_origin = Point3D::cartesian(cartesian_coordinates);
                        Vector3D ray_direction = Vector3D(0, -dy, 0);
                        Ray ray(ray_origin, ray_direction);

                        INFO("Ray: " << ray);

                        Hit hit;
                        CHECK(!disk->find_first_positive_hit(ray, &hit));
                    }

                    // Upward rays
                    {
                        CylindricalY cylindrical_coordinates{ radius, angle, -y };
                        Cartesian3D cartesian_coordinates = convert_coordinates<Cartesian3D>(cylindrical_coordinates);

                        Point3D ray_origin = Point3D::cartesian(cartesian_coordinates);
                        Vector3D ray_direction = Vector3D(0, dy, 0);
                        Ray ray(ray_origin, ray_direction);

                        INFO("Ray: " << ray);

                        Hit hit;
                        CHECK(!disk->find_first_positive_hit(ray, &hit));
                    }
                }
            }
        }
    }
}

TEST_CASE("[Disk] Vertical rays miss disk because they point in the wrong direction", "[Disk]")
{
    auto disk = raytracer::primitives::disk();

    for (double radius = 1.01; radius < 100; radius *= 1.5)
    {
        for (Angle angle = 0_degrees; angle < 360_degrees; angle += 15_degrees)
        {
            for (double y = 0.1; y < 10; y += 3.5)
            {
                for (double dy = 0.1; dy < 5; dy += 0.7)
                {
                    // Downward rays
                    {
                        CylindricalY cylindrical_coordinates{ radius, angle, -y };
                        Cartesian3D cartesian_coordinates = convert_coordinates<Cartesian3D>(cylindrical_coordinates);

                        Point3D ray_origin = Point3D::cartesian(cartesian_coordinates);
                        Vector3D ray_direction = Vector3D(0, -dy, 0);
                        Ray ray(ray_origin, ray_direction);

                        INFO("Ray: " << ray);

                        Hit hit;
                        CHECK(!disk->find_first_positive_hit(ray, &hit));
                    }

                    // Upward rays
                    {
                        CylindricalY cylindrical_coordinates{ radius, angle, y };
                        Cartesian3D cartesian_coordinates = convert_coordinates<Cartesian3D>(cylindrical_coordinates);

                        Point3D ray_origin = Point3D::cartesian(cartesian_coordinates);
                        Vector3D ray_direction = Vector3D(0, dy, 0);
                        Ray ray(ray_origin, ray_direction);

                        INFO("Ray: " << ray);

                        Hit hit;
                        CHECK(!disk->find_first_positive_hit(ray, &hit));
                    }
                }
            }
        }
    }
}

TEST_CASE("[Disk] Horizontal rays miss disk", "[Disk]")
{
    auto disk = raytracer::primitives::disk();
    
    for (double x = -5; x < 5; x += 3.8)
    {
        for (double z = -5; z < 5; z += 4.1)
        {
            for (double y = 0.1; y < 100; y *= 1.5)
            {
                for (double dx = 0.1; dx < 10; dx *= 1.5)
                {
                    for (double dz = 0.1; dz < 10; dz *= 2.5)
                    {
                        Point3D ray_origin = Point3D(x, y, z);
                        Vector3D ray_direction = Vector3D(dx, 0, dz);
                        Ray ray(ray_origin, ray_direction);

                        INFO("Ray: " << ray);

                        Hit hit;
                        CHECK(!disk->find_first_positive_hit(ray, &hit));
                    }
                }                
            }
        }
    }
}

#endif