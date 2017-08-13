#include "animation/time-stamp.h"

using namespace animation;


animation::TimeStamp::TimeStamp()
    : m_since_epoch(Duration::zero())
{
    // NOP
}

animation::TimeStamp::TimeStamp(const Duration& since_epoch)
    : m_since_epoch(since_epoch)
{
    // NOP
}

double animation::TimeStamp::seconds() const
{
    return m_since_epoch.seconds();
}

TimeStamp animation::operator +(const TimeStamp& ts, const Duration& d)
{
    return TimeStamp::from_epoch(Duration::from_seconds(ts.seconds() + d.seconds()));
}

TimeStamp animation::operator +(const Duration& d, const TimeStamp& ts)
{
    return ts + d;
}

TimeStamp animation::operator -(const TimeStamp& ts, const Duration& d)
{
    return ts + -d;
}

Duration animation::operator -(const TimeStamp& ts1, const TimeStamp& ts2)
{
    return Duration::from_seconds(ts1.seconds() - ts2.seconds());
}

bool animation::TimeStamp::operator <(const TimeStamp& ts) const
{
    return m_since_epoch < ts.m_since_epoch;
}

bool animation::TimeStamp::operator >(const TimeStamp& ts) const
{
    return m_since_epoch > ts.m_since_epoch;
}

bool animation::TimeStamp::operator <=(const TimeStamp& ts) const
{
    return m_since_epoch <= ts.m_since_epoch;
}

bool animation::TimeStamp::operator >=(const TimeStamp& ts) const
{
    return m_since_epoch >= ts.m_since_epoch;
}

TimeStamp& animation::operator +=(TimeStamp& ts, const Duration& duration)
{
    return (ts = ts + duration);
}

bool animation::TimeStamp::operator ==(const TimeStamp& ts) const
{
    return m_since_epoch == ts.m_since_epoch;
}

bool animation::TimeStamp::operator !=(const TimeStamp& ts) const
{
    return !(*this == ts);
}

std::ostream& animation::operator <<(std::ostream& out, const TimeStamp& duration)
{
    return out << "@" << duration.seconds() << "s";
}