#pragma once
#include "math/approx.h"
#include <iostream>


namespace math
{
    /// <summary>
    /// Represents an angle. Used to be able to distinguish angles from other double values.
    /// Also ensures that no mistakes are made w.r.t. degrees vs radians.
    /// </summary>
    class Angle final
    {
    public:
        /// <summary>
        /// Default constructor. Creates zero angle.
        /// </summary>
        Angle();

        /// <summary>
        /// Returns the angle in radians.
        /// </summary>
        double radians() const;

        /// <summary>
        /// Returns the angle in degrees.
        /// </summary>
        double degrees() const;

        /// <summary>
        /// Creates a new angle from a value expressed in degrees.
        /// If the size is known at compile time, you can also use the more readable user-defined literal (e.g. 90_degrees)
        /// </summary>
        /// <param name="size_in_degrees">Size of angle expressed in degrees.</param>
        /// <example>
        /// <code>
        /// auto angle = Angle::degrees(5);
        /// auto same_angle = 5_degrees;
        /// </code>
        /// </example>
        static Angle degrees(long double size_in_degrees);

        /// <summary>
        /// Creates a new angle from a value expressed in radians.
        /// If the size is known at compile time, you can also use the more readable user-defined literal (e.g. 0_rad)
        /// </summary>
        /// <param name="size_in_radians">Size of angle expressed in degrees.</param>
        static Angle radians(long double size_in_radians);

    private:
        explicit Angle(double);
        
        double m_radians;

#       ifndef NDEBUG
        double m_degrees;
#       endif
    };

    Angle operator+(const Angle& x, const Angle& y);
    Angle operator-(const Angle& x);
    Angle operator-(const Angle& x, const Angle& y);
    Angle operator *(const Angle& angle, double factor);
    Angle operator *(double factor, const Angle& angle);
    Angle operator /(const Angle& angle, double factor);
    double operator /(const Angle& angle1, const Angle& angle2);

    Angle& operator +=(Angle& x, const Angle& y);
    Angle& operator -=(Angle& x, const Angle& y);
    Angle& operator *=(Angle& x, double f);
    Angle& operator /=(Angle& x, double f);

    Angle operator"" _rad(long double x);
    Angle operator"" _degrees(long double x);
    Angle operator"" _rad(long long unsigned x);
    Angle operator"" _degrees(long long unsigned x);

    bool operator <(const Angle& a, const Angle& b);
    bool operator >(const Angle& a, const Angle& b);
    bool operator <=(const Angle& a, const Angle& b);
    bool operator >=(const Angle& a, const Angle& b);
    bool operator ==(const Angle& a, const Angle& b);
    bool operator !=(const Angle& a, const Angle& b);

    double sin(Angle);
    double cos(Angle);
    
    // Allows to compare angles, e.g. to check whether an angle x is close to 10 degrees, use x == approx(10_degrees)
    template<>
    struct approximately<Angle>
    {
        Angle value;
        double epsilon;

        explicit approximately(const Angle& value, double epsilon = 0.00001)
            :value(value), epsilon(epsilon)
        {
            // NOP
        }

        bool close_enough(const Angle& other) const
        {
            return (value.radians() - other.radians()) < epsilon;
        }
    };

    std::ostream& operator <<(std::ostream&, Angle);
}
