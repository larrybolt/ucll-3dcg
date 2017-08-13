#include "materials/material.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;


namespace
{
    class FunctionMaterial2D : public materials::_private_::Material2DImplementation
    {
    public:
        FunctionMaterial2D(math::Function<MaterialProperties(const Point2D&)> function)
            : m_function(function) 
        {
            // NOP
        }

    protected:
        MaterialProperties at(const math::Point2D& p) const override
        {
            return m_function(p);
        }

    private:
        math::Function<MaterialProperties(const Point2D&)> m_function;
    };

    class FunctionMaterial3D : public materials::_private_::Material3DImplementation
    {
    public:
        FunctionMaterial3D(math::Function<MaterialProperties(const Point3D&)> function)
            : m_function(function)
        {
            // NOP
        }

    protected:
        MaterialProperties at(const math::Point3D& p) const override
        {
            return m_function(p);
        }

    private:
        math::Function<MaterialProperties(const Point3D&)> m_function;
    };
}

MaterialProperties raytracer::materials::_private_::Material2DImplementation::at(const HitPosition& hp) const
{
    return at(hp.uv);
}

MaterialProperties raytracer::materials::_private_::Material3DImplementation::at(const HitPosition& hp) const
{
    return at(hp.xyz);
}

Material raytracer::make_2d_material(math::Function<MaterialProperties(const Point2D&)> function)
{
    return Material(std::make_shared<FunctionMaterial2D>(function));
}

Material raytracer::make_3d_material(math::Function<MaterialProperties(const Point3D&)> function)
{
    return Material(std::make_shared<FunctionMaterial3D>(function));
}

math::Function<Material( animation::TimeStamp)> raytracer::to_animated_2d_material(Material material)
{
    std::function<Material(animation::TimeStamp)> lambda = [material](animation::TimeStamp ts) {
        std::function<MaterialProperties(const Point2D&)> lam = [material, ts](const Point2D& p) {
            HitPosition hp;
            hp.xyz.x() = p.x();
            hp.xyz.y() = p.y();
            hp.xyz.z() = ts.seconds();
            hp.uv = p;

            return material->at(hp);
        };

        return make_2d_material(from_lambda(lam));
    };

    return from_lambda(lambda);
}