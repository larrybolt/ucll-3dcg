#pragma once

#include <iostream>
#include <string>
#include <atomic>


#define CREATE_PERFORMANCE_COUNTER(VAR, NAME)    performance::Counter PERFORMACE_COUNTER_ ## VAR = performance::create_counter(NAME)
#define INCREMENT_PERFORMANCE_COUNTER(VAR)       ++PERFORMACE_COUNTER_ ## VAR


namespace performance
{
    namespace _private_
    {
        class CounterImplementation;
    }

    class Counter
    {
    public:
        Counter(performance::_private_::CounterImplementation* impl)
            : m_impl(impl) { }

        Counter& operator++();

    private:
        performance::_private_::CounterImplementation* m_impl;
    };

    Counter create_counter(const std::string& name);
    void print_statistics(std::ostream&);
    void cleanup();

    class PerformanceCleanerUpper
    {
    public:
        PerformanceCleanerUpper(bool print_statistics_on_destruction = false)
            : m_statistics_on_destruction(print_statistics_on_destruction) { }

        ~PerformanceCleanerUpper()
        {
            if (m_statistics_on_destruction)
            {
                print_statistics(std::cerr);
            }

            cleanup();
        }

    private:
        bool m_statistics_on_destruction;
    };    
}
