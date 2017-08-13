#include "performance/performance.h"
#include <atomic>
#include <vector>

using namespace performance;


namespace performance
{
    namespace _private_
    {
        class CounterImplementation
        {
        public:
            CounterImplementation(const std::string& name)
                : m_name(name), m_value(0)
            {
                // NOP
            }

            void increment()
            {
                ++m_value;
            }

            std::string name() const
            {
                return m_name;
            }

            uint64_t value() const
            {
                return m_value;
            }

        private:
            std::string m_name;
            std::atomic<uint64_t> m_value;
        };
    }
}

namespace
{
    std::vector<performance::_private_::CounterImplementation*> counters;
}

Counter& performance::Counter::operator++()
{
    m_impl->increment();

    return *this;
}

Counter performance::create_counter(const std::string& name)
{
    performance::_private_::CounterImplementation* p = new performance::_private_::CounterImplementation(name);

    counters.push_back(p);

    return Counter(p);
}

void performance::print_statistics(std::ostream& out)
{
    if (counters.empty())
    {
        out << "Performance statistics: no counters" << std::endl;    
    }
    else
    {
        out << "Performance statistics" << std::endl;

        for (auto p : counters)
        {
            out << p->name() << " " << p->value() << std::endl;
        }
    }
}

void performance::cleanup()
{
    for (auto p : counters)
    {
        delete p;
    }

    counters.clear();
}