#include "math/functions/random-function.h"
#include <random>
#include <array>

using namespace math;


math::Function<unsigned(unsigned)> math::functions::random_function(unsigned parameter)
{
    std::function<unsigned(unsigned)> lambda = [parameter](unsigned x) -> unsigned
    {
        std::array<unsigned, 16> xs = {
            0x49A40F45,
            0xF13FB1CC,
            0x76A12BC3,
            0x9075D13E,

            0x3F148AC9,
            0x13D67E10,
            0x7E79B3CA,
            0x4702F331,

            0x7213A977,
            0x347F8974,
            0x96FF641C,
            0xC78DD31A,

            0x13166A13,
            0x3789A110,
            0x18563DB3,
            0xB1675421
        };

        unsigned a = parameter;
        unsigned b = x;

        for (unsigned i = 0; i != 16; ++i)
        {
            a = (a << 1) ^ (a >> 1);
            b = b ^ xs[i];
            a += b;
            b *= a;
        }

        return a ^ b;
    };

    return from_lambda<unsigned, unsigned>(lambda);
}

math::Function<double(unsigned)> math::functions::random::unsigned_to_double(unsigned seed)
{
    constexpr unsigned size = 1024;
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<> dist(0, 1);
    std::shared_ptr<std::vector<double>> table = std::make_shared<std::vector<double>>(size);

    for (unsigned i = 0; i != table->size(); ++i)
    {
        (*table)[i] = dist(generator);
    }

    std::function<double(unsigned)> lambda = [table](unsigned i) -> double {
        return (*table)[i % table->size()];
    };

    return from_lambda(lambda);
}

math::Function<Vector2D(const Position2D&)> math::functions::random::position_to_vector2d(unsigned seed)
{
    auto helper = unsigned_to_double(seed);

    std::function<Vector2D(const Position2D&)> lambda = [helper](const Position2D& p) -> Vector2D {
        auto theta = helper(p.x * 73246 + p.y * 46976) * 360;

        return Vector2D::polar(1, Angle::degrees(theta));
    };

    return from_lambda(lambda);
}

math::Function<Vector3D(const Position3D&)> math::functions::random::position3d_to_vector3d(unsigned seed)
{
    auto helper = unsigned_to_double(seed);

    std::function<Vector3D(const Position3D&)> lambda = [helper](const Position3D& p) -> Vector3D {
        auto azimuth = helper((p.x * 0x1234) ^ (p.y * 0x5678) ^ (p.z * 0x9ABC)) * 360;
        auto elevation = helper((p.x * 0x7410) ^ (p.y * 0x8529) ^ (p.z * 0x63FE)) * 180 - 90;

        assert(interval(0.0, 360.0).contains(azimuth));
        assert(interval(-90.0, 90.0).contains(elevation));

        return Vector3D::spherical(1, Angle::degrees(azimuth), Angle::degrees(elevation));
    };

    return from_lambda(lambda);
}
