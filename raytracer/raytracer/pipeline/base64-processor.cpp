#include "pipeline/base64-processor.h"
#include "util/base64.h"
#include <list>
#include <sstream>
#include <assert.h>

using namespace raytracer::pipeline;


namespace
{
    const std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    class Base64Processor : public Processor<std::shared_ptr<std::vector<uint8_t>>, std::string>
    {
    public:
        void consume(std::shared_ptr<std::vector<uint8_t>> buffer) override
        {
            LOG(INFO) << "Received " << buffer->size() << " bytes to convert to base64";

            Base64 base64;

            produce("<<<");
            for (auto datum : *buffer)
            {
                base64.feed(datum);

                if (base64.chars_ready() > 10000)
                {
                    produce(base64.extract());
                }
            }

            base64.close();

            if (base64.chars_ready() > 0)
            {
                produce(base64.extract());
            }
            
            produce(">>>");
        }

        void end() override
        {
            // NOP
        }
    };
}

std::shared_ptr<Processor<std::shared_ptr<std::vector<uint8_t>>, std::string>> raytracer::pipeline::base64()
{
    return std::make_shared<Base64Processor>();
}
