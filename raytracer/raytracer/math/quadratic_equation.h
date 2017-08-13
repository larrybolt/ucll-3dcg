#pragma once

namespace math
{
    /// <summary>
    /// Helper class for solving quadratic equations.
    /// </summary>
    class QuadraticEquation
    {
    public:
        /// <summary>
        /// Constructor for quadratic equation a x^2 + b x + c = 0.
        /// </summary>
        QuadraticEquation(double a, double b, double c);

        /// <summary>
        /// Checks if there are solutions.
        /// </summary>
        bool has_solutions() const;

        /// <summary>
        /// Returns first solution. This is not necessarily the least solution.
        /// </summary>
        double x1() const;

        /// <summary>
        /// Returns second solution. This is not necessarily the greatest solution.
        /// </summary>
        double x2() const;

    private:
        double m_x1, m_x2;
        bool m_has_solutions;
    };
}