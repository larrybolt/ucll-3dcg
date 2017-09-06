#ifdef TEST_BUILD

#include "math/rasterizer.h"
#include "Catch.h"

using namespace math;

TEST_CASE("[Rasterizer] Rasterizing [0,1]-[1,0] in 2x2", "[Rasterizer]")
{
    Rectangle2D rect(Point2D(0, 1), Vector2D(1, 0), Vector2D(0, -1));
    Rasterizer r(rect, 2, 2);
    
    REQUIRE(r[Position2D(0, 0)] == Rectangle2D(Point2D(0, 1), Vector2D(0.5, 0), Vector2D(0, -0.5)));
    REQUIRE(r[Position2D(1, 0)] == Rectangle2D(Point2D(0.5, 1), Vector2D(0.5, 0), Vector2D(0, -0.5)));
    REQUIRE(r[Position2D(0, 1)] == Rectangle2D(Point2D(0, 0.5), Vector2D(0.5, 0), Vector2D(0, -0.5)));
    REQUIRE(r[Position2D(1, 1)] == Rectangle2D(Point2D(0.5, 0.5), Vector2D(0.5, 0), Vector2D(0, -0.5)));
}

#endif
