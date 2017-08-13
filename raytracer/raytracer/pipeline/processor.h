#pragma once

#include "pipeline/consumer.h"
#include "pipeline/producer.h"


namespace raytracer
{
    namespace pipeline
    {
        template<typename T>
        struct is_processor
        {
            static constexpr bool value = is_consumer<T>::value && is_producer<T>::value;
        };

        template<typename INPUT, typename OUTPUT>
        class Processor : public Consumer<INPUT>, public Producer<OUTPUT>
        {
        public:
            void end() override
            {
                Producer<OUTPUT>::produce_end();
            }
        };
    }
}
