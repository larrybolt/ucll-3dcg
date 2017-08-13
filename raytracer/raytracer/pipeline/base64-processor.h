#pragma once

#include "pipeline/processor.h"
#include <string>
#include <vector>


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Processor<std::shared_ptr<std::vector<uint8_t>>, std::string>> base64();
    }
}