#pragma once

#include "math/function.h"
#include "math/point.h"
#include "imaging/color.h"
#include "imaging/bitmap.h"


namespace imaging
{
    math::Function<Color(const math::Point2D&)> bitmap_function(std::shared_ptr<imaging::Bitmap>);
}