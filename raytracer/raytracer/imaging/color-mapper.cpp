#include "imaging/color-mapper.h"

using namespace imaging;


math::Function<Color(double)> imaging::color_mapping::grayscale()
{
    std::function<Color(double)> lambda = [](double x) -> Color
    {
        return colors::white() * x;
    };

    return math::from_lambda(lambda);
}