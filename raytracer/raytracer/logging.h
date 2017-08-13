#pragma once

#include <string>


namespace logging
{
    void configure();
    void quiet();
    void enable(const std::string&);
}