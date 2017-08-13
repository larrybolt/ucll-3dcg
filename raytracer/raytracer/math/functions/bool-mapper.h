#pragma once

#include "math/function.h"


namespace math
{
    namespace functions
    {
        template<typename R>
        Function<R(bool)> bool_mapper(R t, R f)
        {
            std::function<R(bool)> lambda = [t, f](bool b)
            {
                return b ? t : f;
            };

            return from_lambda(lambda);
        }
    }
}