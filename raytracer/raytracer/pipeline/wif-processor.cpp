#include "pipeline/wif-processor.h"
#include "imaging/wif-format.h"

using namespace raytracer;
using namespace raytracer::pipeline;


namespace
{
    class WifProcessor : public Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<std::vector<uint8_t>>>
    {
    public:
        WifProcessor()
            : m_frame_index(0)
        {
            // NOP
        }

        void consume(std::shared_ptr<imaging::Bitmap> frame) override
        {
            LOG(INFO) << "Received frame " << m_frame_index++;

            auto buffer = std::make_shared<std::vector<uint8_t>>();
            imaging::wif::convert_frame(*buffer, *frame);

            produce(buffer);
        }

        void end() override
        {
            LOG(INFO) << "Writing WIF ending marker";

            auto buffer = std::make_shared<std::vector<uint8_t>>();
            imaging::wif::mark_eof(*buffer);

            produce(buffer);
            produce_end();
        }

    private:
        unsigned m_frame_index;
    };
}

std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<std::vector<uint8_t>>>> raytracer::pipeline::wif()
{
    return std::make_shared<WifProcessor>();
}
