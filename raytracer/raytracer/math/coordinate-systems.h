#pragma once

#include "math/angle.h"
#include "math/interval.h"
#include <cmath>
#include <assert.h>


namespace math
{
    struct Cartesian2D
    {
        double x, y;
    };

    struct Polar
    {
        double radius;
        math::Angle theta;
    };

    struct Cartesian3D
    {
        double x, y, z;
    };

    struct Spherical
    {
        double radius;
        math::Angle azimuth, elevation;
    };

    struct CylindricalX
    {
        double radius;
        math::Angle azimuth;
        double x;
    };

    struct CylindricalY
    {
        double radius;
        math::Angle azimuth;
        double y;
    };

    struct CylindricalZ
    {
        double radius;
        math::Angle azimuth;
        double z;
    };

    template<typename> struct is_2d_coordinate_system : std::false_type { };
    template<> struct is_2d_coordinate_system<Cartesian2D> : std::true_type { };
    template<> struct is_2d_coordinate_system<Polar> : std::true_type { };

    template<typename> struct is_3d_coordinate_system : std::false_type { };
    template<> struct is_3d_coordinate_system<Cartesian3D> : std::true_type { };
    template<> struct is_3d_coordinate_system<Spherical> : std::true_type { };
    template<> struct is_3d_coordinate_system<CylindricalX> : std::true_type { };
    template<> struct is_3d_coordinate_system<CylindricalY> : std::true_type { };
    template<> struct is_3d_coordinate_system<CylindricalZ> : std::true_type { };

    namespace _private_
    {
        template<typename FROM, typename TO>
        struct CoordinateConverter;        

        template<typename T>
        struct CoordinateConverter<T, T>
        {
            static T convert(const T& x)
            {
                return x;
            }
        };

        template<>
        struct CoordinateConverter<Cartesian2D, Polar>
        {
            static Polar convert(const Cartesian2D& cartesian)
            {
                double radius = sqrt(pow(cartesian.x, 2) + pow(cartesian.y, 2));
                Angle theta = Angle::radians(atan2(cartesian.y, cartesian.x));

                return Polar{ radius, theta };
            }
        };

        template<>
        struct CoordinateConverter<Polar, Cartesian2D>
        {
            static Cartesian2D convert(const Polar& polar)
            {
                double x = polar.radius * cos(polar.theta);
                double y = polar.radius * sin(polar.theta);

                return Cartesian2D{ x, y };
            }
        };

        template<>
        struct CoordinateConverter<Cartesian3D, Spherical>
        {
            static Spherical convert(const Cartesian3D& cartesian)
            {
                double radius = sqrt(pow(cartesian.x, 2) + pow(cartesian.y, 2) + pow(cartesian.z, 2));
                Angle azimuth = Angle::radians(atan2(-cartesian.z, cartesian.x));
                Angle elevation = radius > 0 ? 90_degrees - Angle::radians(acos(cartesian.y / radius)) : 0_degrees;

                assert(radius >= 0);
                assert(interval(-180_degrees, 180_degrees).contains(azimuth));
                assert(interval(-90_degrees, 90_degrees).contains(elevation));

                return Spherical{ radius, azimuth, elevation };
            }
        };

        template<>
        struct CoordinateConverter<Spherical, Cartesian3D>
        {
            static Cartesian3D convert(const Spherical& spherical)
            {
                double x = spherical.radius * cos(spherical.azimuth) * cos(spherical.elevation);
                double y = spherical.radius * sin(spherical.elevation);
                double z = -spherical.radius * sin(spherical.azimuth) * cos(spherical.elevation);

                return Cartesian3D{ x,y,z };
            }
        };

        template<>
        struct CoordinateConverter<Cartesian3D, CylindricalX>
        {
            static CylindricalX convert(const Cartesian3D& c3d)
            {
                Cartesian2D c2d{ c3d.y, c3d.z };
                Polar polar = CoordinateConverter<Cartesian2D, Polar>::convert(c2d);

                return CylindricalX{ polar.radius, polar.theta, c3d.x };
            }
        };

        template<>
        struct CoordinateConverter<CylindricalX, Cartesian3D>
        {
            static Cartesian3D convert(const CylindricalX& cyl)
            {
                Polar polar{ cyl.radius, cyl.azimuth };
                Cartesian2D c2d = CoordinateConverter<Polar, Cartesian2D>::convert(polar);

                return Cartesian3D{ cyl.x, c2d.x, c2d.y };
            }
        };

        template<>
        struct CoordinateConverter<Cartesian3D, CylindricalY>
        {
            static CylindricalY convert(const Cartesian3D& c3d)
            {
                Cartesian2D c2d{ c3d.x, -c3d.z };
                Polar polar = CoordinateConverter<Cartesian2D, Polar>::convert(c2d);

                return CylindricalY{ polar.radius, polar.theta, c3d.y };
            }
        };

        template<>
        struct CoordinateConverter<CylindricalY, Cartesian3D>
        {
            static Cartesian3D convert(const CylindricalY& cyl)
            {
                Polar polar{ cyl.radius, cyl.azimuth };
                Cartesian2D c2d = CoordinateConverter<Polar, Cartesian2D>::convert(polar);

                return Cartesian3D{ c2d.x, cyl.y, -c2d.y };
            }
        };

        template<>
        struct CoordinateConverter<Cartesian3D, CylindricalZ>
        {
            static CylindricalZ convert(const Cartesian3D& c3d)
            {
                Cartesian2D c2d{ c3d.x, c3d.y };
                Polar polar = CoordinateConverter<Cartesian2D, Polar>::convert(c2d);

                return CylindricalZ{ polar.radius, polar.theta, c3d.z };
            }
        };

        template<>
        struct CoordinateConverter<CylindricalZ, Cartesian3D>
        {
            static Cartesian3D convert(const CylindricalZ& cyl)
            {
                Polar polar{ cyl.radius, cyl.azimuth };
                Cartesian2D c2d = CoordinateConverter<Polar, Cartesian2D>::convert(polar);

                return Cartesian3D{ c2d.x, c2d.y, cyl.z };
            }
        };
    }

    // TO template parameter comes first: since FROM can be deduced from argument types, it can be omitted
    template<typename TO, typename FROM>
    std::enable_if_t<is_2d_coordinate_system<FROM>::value && is_2d_coordinate_system<TO>::value, TO> convert_coordinates(const FROM& from)
    {
        auto cartesian = _private_::CoordinateConverter<FROM, Cartesian2D>::convert(from);

        return _private_::CoordinateConverter<Cartesian2D, TO>::convert(cartesian);
    }

    template<typename TO, typename FROM>
    std::enable_if_t<is_3d_coordinate_system<FROM>::value && is_3d_coordinate_system<TO>::value, TO> convert_coordinates(const FROM& from)
    {
        auto cartesian = _private_::CoordinateConverter<FROM, Cartesian3D>::convert(from);

        return _private_::CoordinateConverter<Cartesian3D, TO>::convert(cartesian);
    }
}