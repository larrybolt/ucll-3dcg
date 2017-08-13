#pragma once

#include "math/functions/easing-function.h"
#include "math/interval.h"


namespace math
{
    namespace functions
    {
        namespace easing
        {
            math::functions::EasingFunction stretch_in_time(EasingFunction function, const math::Interval<double>& x_range);
            math::functions::EasingFunction stretch_in_space(EasingFunction function, const math::Interval<double>& y_range);
            math::functions::EasingFunction stretch(EasingFunction function, const math::Interval<double>& x_range, const math::Interval<double>& y_range);
        }
    }
}