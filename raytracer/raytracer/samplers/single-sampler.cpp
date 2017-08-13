#include "samplers/single-sampler.h"

using namespace math;
using namespace raytracer;


namespace
{
    class SingleSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            function(rectangle.center());
        }
    };
}

Sampler raytracer::samplers::single()
{
    return Sampler(std::make_shared<SingleSampler>());
}