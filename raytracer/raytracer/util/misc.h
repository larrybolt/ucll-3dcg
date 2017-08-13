#pragma once

#include <string>
#include <assert.h>


/// <summary>
/// Swaps values of <paramref name="x" /> and <paramref name="y" />.
/// </summary>
template<typename T>
void swap(T& x, T& y)
{
    T temp = x;
    x = y;
    y = temp;
}

/// <summary>
/// Swaps values of <paramref name="x" /> and <paramref name="y" /> if <paramref name="x" /> is greater than <paramref name="y" />.
/// </summary>
template<typename T>
void sort(T& x, T& y)
{
    if (x > y)
    {
        swap(x, y);
    }
}

/// <summary>
/// Given two values <paramref name="x" /> and <paramref name="y" />,
/// find the smallest positive one. If this value exists, it is written to <paramref name="result" /> and true is returned.
/// If both values are negative, false is returned.
/// </summary>
template<typename T>
bool smallest_greater_than_zero(T x, T y, T* result)
{
    sort(x, y);

    assert(x <= y);

    if (0 < x)
    {
        *result = x;

        return true;
    }
    else if (0 < y)
    {
        *result = y;

        return true;
    }
    else
    {
        return false;
    }
}

bool starts_with(const std::string&, const std::string&);
bool ends_with(const std::string&, const std::string&);
