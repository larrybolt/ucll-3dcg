#include "imaging/bitmap.h"
#include <algorithm>
#include <assert.h>

using namespace imaging;


imaging::Bitmap::Bitmap(unsigned width, unsigned height)
    : m_pixels(width, height, colors::black())
{
    // NOP
}

unsigned imaging::Bitmap::width() const
{
    return m_pixels.width();
}

unsigned imaging::Bitmap::height() const
{
    return m_pixels.height();
}

bool imaging::Bitmap::is_inside(const Position2D& p) const
{
    return p.x < width() && p.y < height();
}

Color& imaging::Bitmap::operator[](const Position2D& p)
{
    assert(is_inside(p));

    return m_pixels[p];
}

const Color& imaging::Bitmap::operator[](const Position2D& p) const
{
    assert(is_inside(p));

    return m_pixels[p];
}

void imaging::Bitmap::clear(const Color& Color)
{
    for_each_position([this, &Color](const Position2D& p) {
        m_pixels[p] = Color;
    });
}

void imaging::Bitmap::for_each_position(std::function<void(const Position2D&)> callback) const
{
    m_pixels.for_each_position(callback);
}

Bitmap& imaging::Bitmap::operator +=(const Bitmap& bitmap)
{
    assert(width() == bitmap.width());
    assert(height() == bitmap.height());

    for_each_position([this, &bitmap](const Position2D& p) {
        (*this)[p] += bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator -=(const Bitmap& bitmap)
{
    assert(width() == bitmap.width());
    assert(height() == bitmap.height());

    for_each_position([this, &bitmap](const Position2D& p) {
        (*this)[p] -= bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator *=(double constant)
{
    for_each_position([this, constant](const Position2D& p) {
        (*this)[p] *= constant;
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator /=(double constant)
{
    return *this *= 1 / constant;
}

void imaging::Bitmap::invert()
{
    for_each_position([this](const Position2D& position) {
        (*this)[position].invert();
    });
}
