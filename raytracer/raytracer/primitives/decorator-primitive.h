#pragma once

#include "primitives/primitive.h"
#include "materials/material.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        /// <summary>
        /// Decorates the given <paramref name="primitive" />
        /// with the given <paramref name="material" />.
        /// </summary>
        Primitive decorate(Material material, Primitive primitive);
    }
}