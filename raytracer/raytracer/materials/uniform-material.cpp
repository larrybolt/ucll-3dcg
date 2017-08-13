#include "materials/uniform-material.h"

using namespace math;
using namespace raytracer;
using namespace imaging;

namespace
{
    class UniformMaterial : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        UniformMaterial(const MaterialProperties& properties)
            : m_properties(properties)
        {
            // NOP
        }

        MaterialProperties at(const HitPosition&) const
        {
            return m_properties;
        }

    private:
        MaterialProperties m_properties;
    };
}

Material raytracer::materials::uniform(const MaterialProperties& properties)
{
    return Material(std::make_shared<UniformMaterial>(properties));
}