#pragma once

#include "math/function.h"


namespace math
{
    namespace functions
    {
        template<typename R, typename T>
        math::Function<R(T)> constant(R value)
        {
            std::function<R(T)> lambda = [value](T) {
                return value;
            };

            return from_lambda(lambda);
        }
    }
}