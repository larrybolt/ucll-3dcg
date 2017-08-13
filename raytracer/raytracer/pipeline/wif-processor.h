#pragma once

#include "pipeline/processor.h"
#include "imaging/wif-format.h"
#include <string>


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<std::vector<uint8_t>>>> wif();
    }
}