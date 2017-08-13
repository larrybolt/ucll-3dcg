#include "math/rasterizer.h"

using namespace math;


unsigned math::Rasterizer::horizontal_subdivisions() const
{
    return m_horizontal_subdivisions;
}

unsigned math::Rasterizer::vertical_subdivisions() const
{
    return m_vertical_subdivisions;
}

Rectangle2D math::Rasterizer::operator [](const Position2D& position) const
{
    Vector2D x_axis = this->rect.x_axis / this->m_horizontal_subdivisions;
    Vector2D y_axis = this->rect.y_axis / this->m_vertical_subdivisions;
    Point2D origin = this->rect.origin + position.x * x_axis + position.y * y_axis;

    return Rectangle2D(origin, x_axis, y_axis);
}