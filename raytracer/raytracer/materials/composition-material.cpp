#include "materials/composition-material.h"

using namespace raytracer;
using namespace math;


namespace
{
    class CompositionMaterial2D : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        CompositionMaterial2D(math::Function<Material(const Point2D&)> function)
            : m_function(function) { }

        MaterialProperties at(const HitPosition& hp) const override
        {
            return m_function(hp.uv)->at(hp);
        }

    private:
        math::Function<Material(const Point2D&)> m_function;
    };

    class CompositionMaterial3D : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        CompositionMaterial3D(math::Function<Material(const Point3D&)> function)
            : m_function(function) { }

        MaterialProperties at(const HitPosition& hp) const override
        {
            return m_function(hp.xyz)->at(hp);
        }

    private:
        math::Function<Material(const Point3D&)> m_function;
    };
}

Material raytracer::materials::composite(math::Function<Material(const math::Point2D&)> function)
{
    return Material(std::make_shared<CompositionMaterial2D>(function));
}

Material raytracer::materials::composite(math::Function<Material(const math::Point3D&)> function)
{
    return Material(std::make_shared<CompositionMaterial3D>(function));
}
