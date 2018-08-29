#pragma once
#include "animation.h"
using namespace math;

namespace animation {
	Animation<Point3D> lissajous(const int, const int, const int, const int, const int, const int, const Angle, const Angle, const Angle, const Duration&);

}