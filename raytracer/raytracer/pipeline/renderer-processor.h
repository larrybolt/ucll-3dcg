#pragma once

#include "pipeline/processor.h"
#include "renderers/renderer.h"
#include "imaging/bitmap.h"


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Processor<std::shared_ptr<Scene>, std::shared_ptr<imaging::Bitmap>>> renderer(raytracer::Renderer);
    }
}