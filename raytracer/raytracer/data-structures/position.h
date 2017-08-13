#pragma once

#include <iostream>


struct Position2D final
{
    unsigned x, y;

    Position2D(unsigned x, unsigned y)
        : x(x), y(y) { }

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    Position2D moved(int dx, int dy) const
    {
        Position2D copy = *this;
        copy.move(dx, dy);
        return copy;
    }
};

struct Position3D final
{
    unsigned x, y, z;

    Position3D(unsigned x, unsigned y, unsigned z)
        : x(x), y(y), z(z) { }
};

inline std::ostream& operator <<(std::ostream& out, const Position2D& p)
{
    return out << "(" << p.x << "," << p.y << ")";
}

inline std::ostream& operator <<(std::ostream& out, const Position3D& p)
{
    return out << "(" << p.x << "," << p.y << "," << p.z << ")";
}
