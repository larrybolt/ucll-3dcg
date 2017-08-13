#pragma once

#include "pipeline/pipeline.h"
#include "pipeline/consumer.h"
#include "easylogging++.h"
#include <memory>
#include <stdexcept>


namespace raytracer
{
    namespace pipeline
    {
        namespace _private_
        {
            class ProducerTag { };
        }

        template<typename T>
        struct is_producer
        {
            static constexpr bool value = std::is_base_of<pipeline::_private_::ProducerTag, T>();
        };

        template<typename OUTPUT>
        class Producer : public _private_::ProducerTag, public virtual Pipeline
        {
        public:
            using output_type = OUTPUT;

            template<typename T>
            T link_to(T receiver)
            {
                m_receiver = receiver;

                return receiver;
            }

        protected:
            void produce(const OUTPUT& output)
            {
                if (m_receiver != nullptr)
                {
                    m_receiver->consume(output);
                }
                else
                {
                    LOG(ERROR) << "Missing receiver";
                    abort();
                }
            }

            void produce_end()
            {
                m_receiver->end();
            }

        private:
            std::shared_ptr<Consumer<OUTPUT>> m_receiver;
        };

    }
}
