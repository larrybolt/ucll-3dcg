#include "imaging/bitmap-function.h"

using namespace imaging;
using namespace math;


Function<Color(const Point2D&)> imaging::bitmap_function(std::shared_ptr<Bitmap> bitmap)
{
    std::function<Color(const Point2D&)> lambda = [bitmap](const Point2D& p) -> Color {
        unsigned x = unsigned(floor(p.x()*bitmap->width()));
        unsigned y = unsigned(floor(p.y()*bitmap->height()));

        if (x < bitmap->width() && y < bitmap->height())
        {
            return (*bitmap)[Position2D(x, y)];
        }
        else
        {
            return colors::black();
        }
    };

    return from_lambda(lambda);
}