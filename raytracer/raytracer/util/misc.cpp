#include "util/misc.h"
#include <algorithm>


bool starts_with(const std::string& prefix, const std::string& string)
{
    if (string.size() < prefix.size())
    {
        return false;
    }
    else
    {
        return std::equal(prefix.begin(), prefix.end(), string.begin());
    }
}

bool ends_with(const std::string& string, const std::string& suffix)
{
    if (string.size() < suffix.size())
    {
        return false;
    }
    else
    {
        return std::equal(suffix.rbegin(), suffix.rend(), string.rbegin());
    }
}