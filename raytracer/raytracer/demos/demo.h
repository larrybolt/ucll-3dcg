#pragma once

#include "materials/materials.h"
#include "cameras/cameras.h"
#include "raytracers/ray-tracers.h"
#include "renderers/renderers.h"
#include "samplers/samplers.h"
#include "raytracers/scene.h"
#include "math/function.h"
#include "animation/animations.h"
#include "pipeline/pipelines.h"
#include <memory>


namespace demos
{
    class Demo
    {
    public:
        Demo(unsigned bitmap_size, animation::Duration duration, unsigned fps, unsigned antialias);

    protected:
        virtual raytracer::Primitive create_root(animation::TimeStamp) = 0;
        virtual std::vector<raytracer::LightSource> create_light_sources(animation::TimeStamp) = 0;
        virtual raytracer::Camera create_camera(animation::TimeStamp) = 0;
        virtual animation::Animation<std::shared_ptr<raytracer::Scene>> create_scene_animation();
        virtual raytracer::RayTracer create_ray_tracer();
        virtual raytracer::Renderer create_renderer();
        virtual raytracer::Sampler create_sampler();
        virtual tasks::TaskScheduler create_scheduler();

    public:
        virtual void render(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);

    protected:
        unsigned m_bitmap_size;
        animation::Duration m_duration;
        unsigned m_fps;
        unsigned m_antialias;
    };
}
