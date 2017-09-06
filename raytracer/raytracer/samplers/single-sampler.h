#pragma once

#include "samplers/sampler.h"


namespace raytracer
{
    namespace samplers
    {
        /// <summary>
        /// Creates a sampler that always picks the center of the given rectangle.
        /// </summary>
        Sampler single();
    }
}
