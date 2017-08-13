#include "pipeline/text-writer-consumer.h"
#include <iostream>

using namespace raytracer::pipeline;


namespace
{
    class TextWriter : public Consumer<std::string>
    {
    public:
        TextWriter(std::ostream& out)
            : m_out(out.rdbuf())
        {
            // NOP
        }

        void consume(std::string string) override
        {
            m_out << string << std::endl;
        }

        void end() override
        {
            m_out.flush();
        }

    private:
        std::ostream m_out;
    };
}

std::shared_ptr<Consumer<std::string>> raytracer::pipeline::text_writer(std::ostream& out)
{
    return std::make_shared<TextWriter>(out);
}