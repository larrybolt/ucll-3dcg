#ifdef TEST_BUILD

#include "Catch.h"
#include "math/transformation3d.h"

using namespace math;


TEST_CASE("[Transformation] rotate_align_y", "[Transformation]")
{
    SECTION("y_axis = (0,1,0)")
    {
        Vector3D y_axis(0, 1, 0);

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    SECTION("y_axis = (1,1,0)")
    {
        Vector3D y_axis = Vector3D(1, 1, 0).normalized();

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    SECTION("y_axis = (1,1,1)")
    {
        Vector3D y_axis = Vector3D(1, 1, 1).normalized();

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    SECTION("y_axis = (1,-1,1)")
    {
        Vector3D y_axis = Vector3D(1, -1, 1).normalized();

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    for (double x = -1; x <= 1; x += 0.25)
    {
        for (double y = -1; y <= 1; y += 0.25)
        {
            for (double z = -1; z <= 1; z += 0.25)
            {
                if (x != 0 || y != 0 || z != 0)
                {
                    Vector3D y_axis = Vector3D(x, y, z).normalized();

                    auto transformation = transformations::rotate_align_y(y_axis);

                    auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
                    CHECK(transformed == approx(y_axis));
                }
            }
        }
    }
}

#endif
