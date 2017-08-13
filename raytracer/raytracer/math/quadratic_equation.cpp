#include "math/quadratic_equation.h"
#include <cmath>
#include <assert.h>


math::QuadraticEquation::QuadraticEquation(double a, double b, double c)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        m_has_solutions = false;
    }
    else
    {
        m_has_solutions = true;

        double sqrt_d = sqrt(discriminant);

        m_x1 = (-b - sqrt_d) / (2 * a);
        m_x2 = (-b + sqrt_d) / (2 * a);
    }
}

bool math::QuadraticEquation::has_solutions() const
{
    return m_has_solutions;
}

double math::QuadraticEquation::x1() const
{
    assert(has_solutions());

    return m_x1;
}

double math::QuadraticEquation::x2() const
{
    assert(has_solutions());

    return m_x2;
}
