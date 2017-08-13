#pragma once

#include <functional>


template<typename T>
class Lazy
{
public:
    Lazy(std::function<T()> function)
        : m_function(function), m_evaluated(false) { }

    T value()
    {
        if (!m_evaluated)
        {
            m_value = m_function();
            m_evaluated = true;
        }

        return m_value;
    }

private:
    std::function<T()> m_function;
    T m_value;
    bool m_evaluated;
};