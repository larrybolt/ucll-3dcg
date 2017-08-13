#include "util/base64.h"

namespace
{
    const std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}

Base64::Base64()
    : m_buffer(0), m_bits(0), m_accumulated(0)
{
    // NOP
}

void Base64::feed(uint8_t datum)
{
    m_buffer = (m_buffer << 8) | datum;
    m_bits += 8;

    while (m_bits >= 6)
    {
        m_bits -= 6;
        uint8_t sextet = (uint8_t) (m_buffer >> m_bits);
        m_buffer ^= (uint32_t(sextet) << m_bits);

        accumulate(base64[sextet]);
    }
}

void Base64::close()
{
    if (m_bits > 0)
    {        
        m_buffer <<= (6 - m_bits);        
        accumulate(base64[m_buffer]);
        
        while (m_bits % 6 != 0)
        {
            accumulate('=');
            m_bits += 8;
        }
    }
}

void Base64::accumulate(char c)
{
    m_accumulator << c;
    ++m_accumulated;
}

unsigned Base64::chars_ready() const
{
    return m_accumulated;
}

std::string Base64::extract()
{
    // Fetch string from stringstream
    std::string result = m_accumulator.str();

    // Reset stringstream
    m_accumulator.str("");
    m_accumulated = 0;

    // Return string
    return result;
}
