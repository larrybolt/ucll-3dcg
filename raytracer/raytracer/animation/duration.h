#pragma once

#include "math/approx.h"
#include <iostream>


namespace animation
{
    class Duration
    {
    public:
        static Duration from_milliseconds(double);
        static Duration from_seconds(double);
        static Duration zero();
        static Duration infinite();

        double milliseconds() const;
        double seconds() const;

    private:
        explicit Duration(double);

        double m_milliseconds;
    };

    inline Duration operator""_ms(long long unsigned x)
    {
        return Duration::from_milliseconds(double(x));
    }

    inline Duration operator""_ms(long double x)
    {
        return Duration::from_milliseconds(double(x));
    }

    inline Duration operator""_s(long long unsigned x)
    {
        return Duration::from_seconds(double(x));
    }

    inline Duration operator""_s(long double x)
    {
        return Duration::from_seconds(double(x));
    }

    Duration operator +(const Duration&, const Duration&);
    Duration operator -(const Duration&);
    Duration operator -(const Duration&, const Duration&);
    Duration operator *(const Duration&, double);
    Duration operator *(double, const Duration&);
    Duration operator /(const Duration&, double);
    double operator /(const Duration&, const Duration&);

    bool operator <(const Duration&, const Duration&);
    bool operator <=(const Duration&, const Duration&);
    bool operator >=(const Duration&, const Duration&);
    bool operator >(const Duration&, const Duration&);

    bool operator ==(const Duration&, const Duration&);
    bool operator !=(const Duration&, const Duration&);

    std::ostream& operator <<(std::ostream&, const Duration&);
}

namespace math
{
    template<>
    struct approximately<animation::Duration>
    {
        animation::Duration value;
        double epsilon;

        explicit approximately(const animation::Duration& value, double epsilon = 0.00001)
            :value(value), epsilon(epsilon)
        {
            // NOP
        }

        bool close_enough(const animation::Duration& other) const
        {
            return (value.seconds() - other.seconds()) < epsilon;
        }
    };
}