#pragma once

#include "animation/duration.h"


namespace animation
{
    class TimeStamp
    {
    public:
        TimeStamp();

        static TimeStamp zero() { return TimeStamp(); }
        static TimeStamp from_epoch(const Duration& duration) { return TimeStamp(duration); }
        static TimeStamp from_seconds_since_epoch(double duration) { return TimeStamp(Duration::from_seconds(duration)); }

        double seconds() const;

        bool operator <(const TimeStamp&) const;
        bool operator <=(const TimeStamp&) const;
        bool operator >(const TimeStamp&) const;
        bool operator >=(const TimeStamp&) const;

        bool operator ==(const TimeStamp&) const;
        bool operator !=(const TimeStamp&) const;

    private:
        explicit TimeStamp(const Duration&);

        Duration m_since_epoch;
    };

    TimeStamp operator +(const TimeStamp&, const Duration&);
    TimeStamp operator +(const Duration&, const TimeStamp&);
    TimeStamp operator -(const TimeStamp&, const Duration&);
    Duration operator -(const TimeStamp&, const TimeStamp&);

    TimeStamp& operator +=(TimeStamp&, const Duration&);

    std::ostream& operator <<(std::ostream&, const TimeStamp&);
}

namespace math
{
    template<>
    struct approximately<animation::TimeStamp>
    {
        animation::TimeStamp value;
        double epsilon;

        explicit approximately(const animation::TimeStamp& value, double epsilon = 0.00001)
            :value(value), epsilon(epsilon)
        {
            // NOP
        }

        bool close_enough(const animation::TimeStamp& other) const
        {
            return (value.seconds() - other.seconds()) < epsilon;
        }
    };
}
