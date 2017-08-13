#include "renderers/renderer.h"
#include "tasks/task-helpers.h"

using namespace math;
using namespace tasks;

raytracer::renderers::_private_::RendererImplementation::RendererImplementation(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler)
    : m_horizontal_size(horizontal_size), m_vertical_size(vertical_size), m_sampler(sampler), m_ray_tracer(ray_tracer), m_scheduler(scheduler)
{
    // NOP
}

void raytracer::renderers::_private_::RendererImplementation::for_each_pixel(std::function<void(Position2D)> callback) const
{
    auto tasks = tasks::range<unsigned>(0, m_vertical_size, [this, callback](unsigned y) {
        for (unsigned x = 0; x != m_horizontal_size; ++x)
        {
            callback(Position2D(x, y));
        }
    });

    m_scheduler->perform(tasks);
}