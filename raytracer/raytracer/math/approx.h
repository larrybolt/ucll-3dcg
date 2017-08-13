#pragma once

#include <cmath>
#include <iostream>
#include <limits>


namespace math
{
    template<typename>
    struct approximately;

    template<>
    struct approximately<double>
    {
        double value;
        double epsilon;

        explicit approximately(double value, double epsilon = 0.00000001)
            : value(value), epsilon(epsilon) { }

        bool close_enough(double other) const
        {
            if (value == std::numeric_limits<double>::infinity())
            {
                return other == std::numeric_limits<double>::infinity();
            }
            else if (value == -std::numeric_limits<double>::infinity())
            {
                return other == -std::numeric_limits<double>::infinity();
            }
            else
            {
                return std::abs(other - value) < epsilon;
            }
        }
    };

    template<typename T>
    approximately<T> approx(T x, double epsilon = 0.00000001)
    {
        return approximately<T>(x, epsilon);
    }

    template<typename T>
    bool operator ==(const approximately<T>& x, T y)
    {
        return x.close_enough(y);
    }

    template<typename T>
    bool operator ==(T x, const approximately<T>& y)
    {
        return y == x;
    }

    template<typename T>
    bool operator !=(const approximately<T>& x, T y)
    {
        return !(x == y);
    }

    template<typename T>
    bool operator !=(T x, const approximately<T>& y)
    {
        return !(x == y);
    }

    template<typename T>
    std::ostream& operator <<(std::ostream& out, const approximately<T>& x)
    {
        return out << "approximately(" << x.value << ")";
    }
}
