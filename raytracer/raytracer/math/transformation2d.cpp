#include "math/transformation2d.h"
#include "math/transformation-matrices.h"

using namespace math;


Transformation2D math::transformations::translation(const Vector2D& v)
{
    Matrix3x3 tm = transformation_matrices::translation(v);
    Matrix3x3 itm = transformation_matrices::translation(-v);

    return Transformation2D(tm, itm);
}
