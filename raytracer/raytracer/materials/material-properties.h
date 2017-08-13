#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
        MaterialProperties(const imaging::Color& ambient, const imaging::Color& diffuse, const imaging::Color& specular, double specular_exponent, double reflectivity = 0, double transparency = 0, double refractive_index = 0);

        const imaging::Color ambient;
        const imaging::Color diffuse;
        const imaging::Color specular;
        const double specular_exponent;
        const double reflectivity;
        const double transparency;
        const double refractive_index;
    };
}