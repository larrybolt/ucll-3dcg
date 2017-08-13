#pragma once

#include "math/interval.h"

namespace math
{
    template<typename T1, typename T2>
    struct IntervalMapper
    {
        Interval<T1> from;
        Interval<T2> to;

        IntervalMapper(const Interval<T1>& from, const Interval<T2>& to)
            : from(from), to(to) { }

        IntervalMapper(const IntervalMapper<T1, T2>&) = default;

        T2 operator [](T1 x) const
        {
            return to.from_relative(from.to_relative(x));
        }
    };
}
