#pragma once

#include <sstream>
#include <string>


class Base64
{
public:
    Base64();

    void feed(uint8_t);
    void close();

    unsigned chars_ready() const;
    std::string extract();

private:
    void accumulate(char);

    uint32_t m_buffer;
    unsigned m_bits;
    std::stringstream m_accumulator;
    unsigned m_accumulated;
};