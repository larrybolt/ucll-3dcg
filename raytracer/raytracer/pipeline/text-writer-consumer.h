#pragma once

#include "pipeline/consumer.h"
#include <string>


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Consumer<std::string>> text_writer(std::ostream&);
    }
}