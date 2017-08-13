#include "math/angle.h"
#include <cmath>

using namespace math;

namespace
{
  const double PI = 3.141592653589793238;
}


math::Angle::Angle()
    : Angle(0) { }

math::Angle::Angle(double x)
    : m_radians(x) 
{
#   ifndef NDEBUG
    // m_degrees member variable only available in debug mode
    m_degrees = m_radians * 180 / PI;
#   endif // NDEBUG
}

double math::Angle::radians() const 
{
    return m_radians; 
}

double math::Angle::degrees() const
{
    return m_radians * 180 / PI; 
}

Angle math::Angle::degrees(long double x)
{
    return Angle(double(x) / 180 * PI); 
}

Angle math::Angle::radians(long double x)
{
    return Angle(double(x)); 
}

Angle math::operator+(const Angle& x, const Angle& y)
{
    return Angle::radians(x.radians() + y.radians());
}

Angle math::operator-(const Angle& x)
{
    return Angle::radians(-x.radians());
}

Angle math::operator-(const Angle& x, const Angle& y)
{
    return Angle::radians(x.radians() - y.radians());
}

Angle math::operator *(const Angle& angle, double factor)
{
    return Angle::radians(angle.radians() * factor);
}

Angle math::operator *(double factor, const Angle& angle)
{
    return angle * factor;
}

Angle math::operator /(const Angle& angle, double factor)
{
    return Angle::radians(angle.radians() / factor);
}

double math::operator /(const Angle& a, const Angle& b)
{
    return a.radians() / b.radians();
}

Angle& math::operator +=(Angle& x, const Angle& y)
{
    return (x = x + y);
}

Angle& math::operator -=(Angle& x, const Angle& y)
{
    return (x = x - y);
}

Angle& math::operator *=(Angle& x, double f)
{
    return (x = x * f);
}

Angle& math::operator /=(Angle& x, double f)
{
    return (x = x / f);
}

Angle math::operator "" _rad(long double x)
{
    return Angle::radians(x);
}

Angle math::operator "" _degrees(long double x)
{
    return Angle::degrees(x);
}

Angle math::operator "" _rad(long long unsigned x)
{
    return Angle::radians((long double)x);
}

Angle math::operator "" _degrees(long long unsigned x)
{
    return Angle::degrees((long double)x);
}

bool math::operator <(const Angle& a, const Angle& b)
{
    return a.radians() < b.radians();
}

bool math::operator >(const Angle& a, const Angle& b)
{
    return a.radians() > b.radians();
}

bool math::operator <=(const Angle& a, const Angle& b)
{
    return a.radians() <= b.radians();
}

bool math::operator >=(const Angle& a, const Angle& b)
{
    return a.radians() >= b.radians();
}

bool math::operator ==(const Angle& a, const Angle& b)
{
    return a.radians() == b.radians();
}

bool math::operator !=(const Angle& a, const Angle& b)
{
    return a.radians() != b.radians();
}

double math::sin(Angle a)
{
    return ::sin(a.radians()); 
}

double math::cos(Angle a)
{
    return ::cos(a.radians()); 
}

std::ostream& math::operator <<(std::ostream& out, Angle angle)
{
    return out << angle.degrees() << "deg";
}
