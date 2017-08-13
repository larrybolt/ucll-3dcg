#pragma once

#include "lights/point-light.h"
#include "imaging/color.h"
#include "math/point.h"
#include <memory>

namespace raytracer
{
    namespace lights
    {
        /// <summary>
        /// Creates an omnidirectional point light. This is a light source
        /// that is infinitely small (exists only in one point) and
        /// produces photons of the given <paramref name="color" /> uniformly in all directions.
        /// </summary>
        LightSource omnidirectional(const math::Point3D& position, const imaging::Color& color);
    }
}