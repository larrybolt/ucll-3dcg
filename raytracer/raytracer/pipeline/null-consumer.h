#pragma once

#include "pipeline/processor.h"
#include "imaging/wif-format.h"
#include <string>


namespace raytracer
{
    namespace pipeline
    {
        namespace _private_
        {
            template<typename T>
            class NullConsumer : public Consumer<T>
            {
            public:
                void consume(T) override
                {
                    // NOP
                }
            };
        }

        template<typename T>
        std::shared_ptr<Consumer<T>> null()
        {
            return std::make_shared<_private_::NullConsumer<T>>();
        }
    }
}