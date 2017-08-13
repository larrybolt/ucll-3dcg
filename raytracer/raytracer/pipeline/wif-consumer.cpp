#include "pipeline/wif-consumer.h"
#include "imaging/wif-format.h"

using namespace raytracer::pipeline;
using namespace imaging;


namespace
{
    class Wif : public Consumer<std::shared_ptr<imaging::Bitmap>>
    {
    public:
        Wif(const std::string& path)
            : m_wif(path) { }

        void consume(std::shared_ptr<imaging::Bitmap> bitmap) override
        {
            m_wif.write_frame(*bitmap);
        }

    private:
        WIF m_wif;
    };
}

std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::wif(const std::string& path)
{
    return std::make_shared<Wif>(path);
}