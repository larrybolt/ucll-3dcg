#pragma once

#include "math/function.h"
#include "math/vector.h"
#include "data-structures/position.h"


namespace math
{
    namespace functions
    {
        math::Function<unsigned(unsigned)> random_function(unsigned);

        namespace random
        {
            math::Function<double(unsigned)> unsigned_to_double(unsigned seed);
            math::Function<math::Vector2D(const Position2D&)> position_to_vector2d(unsigned seed);
            math::Function<math::Vector3D(const Position3D&)> position3d_to_vector3d(unsigned seed);
        }
    }
}