#pragma once

#include "pipeline/pipeline.h"
#include <memory>


namespace raytracer
{
    namespace pipeline
    {
        namespace _private_
        {
            class ConsumerTag { };
        }

        template<typename T>
        struct is_consumer
        {
            static constexpr bool value = std::is_base_of<pipeline::_private_::ConsumerTag, T>();
        };

        template<typename INPUT>
        class Consumer : public _private_::ConsumerTag, public virtual Pipeline
        {
        public:
            using input_type = INPUT;

            virtual void consume(INPUT) = 0;
            virtual void end() { }
        };
    }
}