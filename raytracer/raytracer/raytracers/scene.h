#pragma once

#include "primitives/primitives.h"
#include "lights/lights.h"
#include "cameras/camera.h"


namespace raytracer
{
    struct Scene
    {
        Scene(raytracer::Camera camera, raytracer::Primitive root, const std::vector<LightSource>& light_sources)
            : camera(camera), root(root), light_sources(light_sources) { }

        Scene(raytracer::Camera camera, raytracer::Primitive root)
            : camera(camera), root(root), light_sources() { }

        raytracer::Camera camera;
        raytracer::Primitive root;
        std::vector<LightSource> light_sources;
    };
}