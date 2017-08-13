#pragma once

#include "imaging/color.h"
#include "math/function.h"


namespace imaging
{
    namespace color_mapping
    {
        math::Function<Color(double)> grayscale();
    }
}
