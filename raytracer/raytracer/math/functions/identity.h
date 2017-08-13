#pragma once

#include "math/function.h"


namespace math
{
    namespace functions
    {
        template<typename R>
        Function<R(R)> identity()
        {
            std::function<R(R)> lambda = [](R x) { return x; };

            return from_lambda<R, R>(lambda);
        }
    }
}
