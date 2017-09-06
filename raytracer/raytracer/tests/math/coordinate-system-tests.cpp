#ifdef TEST_BUILD

#include "Catch.h"
#include "math/coordinate-systems.h"
#include "math/angle.h"

using namespace math;



#define TEST_TO_AND_FROM_3D(COORDINATE_SYSTEM) \
    TEST_CASE("[CoordinateSystems] Convert to and from " #COORDINATE_SYSTEM, "[CoordinateSystems]") \
    { \
        for (double x = -2; x <= 2; x += 1) \
        { \
            for (double y = -2; y <= 2; y += 1) \
            { \
                for (double z = -2; z <= 2; z += 1) \
                { \
                    Cartesian3D c1 { x,y,z }; \
                    COORDINATE_SYSTEM c2 = convert_coordinates<COORDINATE_SYSTEM>(c1); \
                    Cartesian3D c3 = convert_coordinates<Cartesian3D>(c2); \
                    \
                    CHECK(c1.x == Approx(c3.x)); \
                    CHECK(c1.y == Approx(c3.y)); \
                    CHECK(c1.z == Approx(c3.z)); \
                } \
            } \
        } \
    }


#define TEST_CARTESIAN3D_SPHERICAL(X,Y,Z,RADIUS,AZIMUTH,ELEVATION) \
    TEST_CASE("[CoordinateSystems] Conversion between Cartesian (" #X ", " #Y ", " #Z ") to Spherical (" #RADIUS ", " #AZIMUTH ", " #ELEVATION ")", "[CoordinateSystems]" ) \
    { \
        SECTION("Cartesian to Spherical") \
        { \
            Cartesian3D xyz{ X, Y, Z }; \
            auto spherical = convert_coordinates<Spherical>(xyz); \
            \
            CHECK(spherical.radius == Approx(RADIUS)); \
            CHECK(spherical.azimuth == approx(AZIMUTH)); \
            CHECK(spherical.elevation == approx(ELEVATION)); \
        }\
        SECTION("Spherical to Cartesian") \
        { \
            Spherical spherical{ RADIUS, AZIMUTH, ELEVATION }; \
            auto cartesian = convert_coordinates<Cartesian3D>(spherical); \
            \
            CHECK(cartesian.x == Approx(X)); \
            CHECK(cartesian.y == Approx(Y)); \
            CHECK(cartesian.z == Approx(Z)); \
        } \
    }

#define TEST_CARTESIAN3D_CYLINDRICALY(X,Y,Z,RADIUS,AZIMUTH,CY) \
    TEST_CASE("[CoordinateSystems] Conversion between Cartesian (" #X ", " #Y ", " #Z ") to CylindricalY (" #RADIUS ", " #AZIMUTH ", " #CY ")", "[CoordinateSystems]" ) \
    { \
        SECTION("Cartesian to CylindricalY") \
        { \
            Cartesian3D xyz{ X, Y, Z }; \
            auto cylindrical = convert_coordinates<CylindricalY>(xyz); \
            \
            CHECK(cylindrical.radius == Approx(RADIUS)); \
            CHECK(cylindrical.azimuth == approx(AZIMUTH)); \
            CHECK(cylindrical.y == Approx(CY)); \
        }\
        SECTION("CylindricalY to Cartesian") \
        { \
            CylindricalY spherical{ RADIUS, AZIMUTH, CY }; \
            auto cartesian = convert_coordinates<Cartesian3D>(spherical); \
            \
            CHECK(cartesian.x == Approx(X)); \
            CHECK(cartesian.y == Approx(Y)); \
            CHECK(cartesian.z == Approx(Z)); \
        } \
    }


TEST_CARTESIAN3D_SPHERICAL(0, 0, 0, 0, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(1, 0, 0, 1, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(2, 0, 0, 2, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(3, 0, 0, 3, 0_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(-3, 0, -0.000000001, 3, 180_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(-3, 0, 0.000000001, 3, -180_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 1, 0, 1, 0_degrees, 90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 2, 0, 2, 0_degrees, 90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 3, 0, 3, 0_degrees, 90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, -1, 0, 1, 0_degrees, -90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, -2, 0, 2, 0_degrees, -90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, -3, 0, 3, 0_degrees, -90_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, -1, 1, 90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, -2, 2, 90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, -3, 3, 90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, 1, 1, -90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, 2, 2, -90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(0, 0, 3, 3, -90_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(1, 0, -1, sqrt(2), 45_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(-1, 0, -1, sqrt(2), 135_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(1, 0, 1, sqrt(2), -45_degrees, 0_degrees)
TEST_CARTESIAN3D_SPHERICAL(-1, 0, 1, sqrt(2), -135_degrees, 0_degrees)

TEST_CARTESIAN3D_CYLINDRICALY(0, 0, 0, 0, 0_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(1, 0, 0, 1, 0_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(2, 0, 0, 2, 0_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(0, 1, 0, 0, 0_degrees, 1)
TEST_CARTESIAN3D_CYLINDRICALY(0, 2, 0, 0, 0_degrees, 2)
TEST_CARTESIAN3D_CYLINDRICALY(0, 0, -1, 1, 90_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(0, 0, -2, 2, 90_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(0, 0, 1, 1, -90_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(0, 0, 2, 2, -90_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(-1, 0, 0.00000001, 1, -180_degrees, 0)
TEST_CARTESIAN3D_CYLINDRICALY(-1, 0, -0.00000001, 1, 180_degrees, 0)

TEST_TO_AND_FROM_3D(Cartesian3D)
TEST_TO_AND_FROM_3D(Spherical)
TEST_TO_AND_FROM_3D(CylindricalX)
TEST_TO_AND_FROM_3D(CylindricalY)
TEST_TO_AND_FROM_3D(CylindricalZ)

#endif
