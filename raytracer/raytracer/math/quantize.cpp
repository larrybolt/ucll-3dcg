#include "math/quantize.h"
#include <cmath>
#include <assert.h>


double math::quantize(double x, unsigned levels)
{
    assert(levels > 1);

    return round(x * (levels - 1)) / (levels - 1);
}