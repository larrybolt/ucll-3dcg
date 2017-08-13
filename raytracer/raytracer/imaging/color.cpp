#include "imaging/color.h"
#include "math/approx.h"
#include "math/quantize.h"

using namespace imaging;


namespace
{
    double clamp(double x)
    {
        if (x < 0) return 0;
        else if (x > 1) return 1;
        else return x;
    }
}

void imaging::Color::clamp()
{
    r = ::clamp(r);
    g = ::clamp(g);
    b = ::clamp(b);
}

Color imaging::Color::clamped() const
{
    Color copy = *this;
    copy.clamp();
    return copy;
}

Color imaging::operator +(const Color& c1, const Color& c2)
{
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

Color imaging::operator -(const Color& c1, const Color& c2)
{
    return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

Color imaging::operator *(const Color& c, double f)
{
    return Color(c.r * f, c.g * f, c.b * f);
}

Color imaging::operator *(double f, const Color& c)
{
    return c * f;
}

Color imaging::operator *(const Color& c1, const Color& c2)
{
    return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

Color imaging::operator /(const Color& c, double f)
{
    return c * (1 / f);
}

Color& imaging::operator +=(Color& c1, const Color& c2)
{
    return c1 = c1 + c2;
}

Color& imaging::operator -=(Color& c1, const Color& c2)
{
    return c1 = c1 - c2;
}

Color& imaging::operator *=(Color& c, double f)
{
    return c = c * f;
}

Color& imaging::operator /=(Color& c, double f)
{
    return c = c / f;
}

bool imaging::operator ==(const Color& c1, const Color& c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

bool imaging::operator !=(const Color& c1, const Color& c2)
{
    return !(c1 == c2);
}

std::ostream& imaging::operator <<(std::ostream& out, const Color& c)
{
    return out << "RGB[" << c.r << "," << c.g << "," << c.b << "]";
}

void imaging::Color::quantize(unsigned levels)
{
    r = math::quantize(r, levels);
    g = math::quantize(g, levels);
    b = math::quantize(b, levels);
}

Color imaging::Color::quantized(unsigned levels) const
{
    Color copy = *this;

    copy.quantize(levels);

    return copy;
}

void imaging::Color::invert()
{
    r = 1 - r;
    g = 1 - g;
    b = 1 - b;
}

Color imaging::Color::inverted() const
{
    Color copy = *this;
    copy.invert();
    return copy;
}