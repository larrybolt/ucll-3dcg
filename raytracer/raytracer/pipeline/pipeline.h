#pragma once

#include <memory>


namespace raytracer
{
    namespace pipeline
    {
        class Pipeline
        {
        public:
            virtual ~Pipeline() { } // Needed to make class polymorphic
        };
    }
}