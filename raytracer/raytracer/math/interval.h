#pragma once

#include <limits>
#include <algorithm>
#include <iostream>


namespace math
{
    /// <summary>
    /// Represents a interval. The interval is closed, meaning that the bounds are included in the interval.
    /// </summary>
    template<typename T>
    struct Interval final
    {
        T lower, upper;

        /// <summary>
        /// Use the factory function instead.
        /// </summary>
        constexpr Interval(T lower, T upper)
            : lower(lower), upper(upper) { }


        /// <summary>
        /// Creates an empty interval.
        /// </summary>
        static constexpr Interval<T> empty()
        {
            return Interval<T>(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());
        }

        /// <summary>
        /// Creates an infinite interval.
        /// </summary>
        static constexpr Interval<T> infinite()
        {
            return Interval<T>(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
        }

        /// <summary>
        /// Computes the size of the interval.
        /// </summary>
        constexpr decltype(upper - lower) size() const
        {
            return upper - lower;
        }

        /// <summary>
        /// Checks whether <paramref name="x" /> is contained within the interval's bounds.
        /// The bounds themselves are part of the interval.
        /// </summary>
        constexpr bool contains(T x) const
        {
            return lower <= x && x <= upper;
        }

        /// <summary>
        /// Computes the relative position of <paramref name="x" /> in this interval.
        /// This is equal to a value between 0 and 1 if <paramref name="x" /> is inside the interval.
        /// </summary>
        constexpr double to_relative(T x) const
        {
            return (x - lower) / size();
        }

        /// <summary>
        /// Inverse operation of to_relative. from_relative(0) yields the lower bound,
        /// from_relative(1) the upper bound.
        /// </summary>
        constexpr T from_relative(double t) const
        {
            return t * size() + lower;
        }

        /// <summary>
        /// Returs a new interval equal to the merger of this interval and <paramref name="other" />.
        /// </summary>
        Interval<T> merge(const Interval& other) const
        {
            return Interval(std::min(lower, other.lower), std::max(upper, other.upper));
        }

        /// <summary>
        /// Returns the intersection of this interval and <paramref name="other" />.
        /// </summary>
        Interval<T> intersect(const Interval& other) const
        {
            return Interval(std::max(lower, other.lower), std::min(upper, other.upper));
        }

        template<unsigned I>
        constexpr T bound() const
        {
            static_assert(I == 0 || I == 1, "I must be either 0 or 1");

            return I == 0 ? this->lower : this->upper;
        }

        /// <summary>
        /// Returns the center of the interval.
        /// </summary>
        T center() const
        {
            return lower + size() / 2;
        }


        /// <summary>
        /// Returns true if the interval is infinitely sized, false otherwise.
        /// </summary>
        bool is_infinite() const
        {
            return lower == -std::numeric_limits<T>::infinity() || upper == std::numeric_limits<T>::infinity();
        }
    };

    template<typename T>
    std::ostream& operator <<(std::ostream& out, const Interval<T>& interval)
    {
        return out << "[" << interval.lower << ", " << interval.upper << "]";
    }

    /// <summary>
    /// Factory function for intervals. Easier to use than the constructor
    /// as it is not necessary to specify the type T. If <paramref name="lower" /> is greater than
    /// <paramref name="upper" />, the interval will be considered empty.
    /// </summary>
    /// <example>
    /// <code>
    /// // Creates the object Interval&lt;double&gt;(0, 5)
    /// auto range = interval(0.0, 5.0);
    /// </code>
    /// </example>
    template<typename T>
    constexpr Interval<T> interval(const T& lower, const T& upper)
    {
        // To catch interval(0, 1) vs interval(0.0, 1.0) errors
        static_assert(!std::is_same<T, int>::value, "Interval of ints is forbidden");

        return Interval<T>(lower, upper);
    }

    /// <summary>
    /// Factory function for intervals. Easier to use than the constructor
    /// as it is not necessary to specify the type T. If <paramref name="lower" /> is greater than
    /// <paramref name="upper" />, the bounds will be switched around so as to make the interval nonempty.
    /// </summary>
    /// <example>
    /// <code>
    /// // Switches bounds resulting in Interval&lt;double&gt;(5, 7)
    /// auto range = nonempty_interval(7.0, 5.0);
    /// </code>
    /// </example>
    template<typename T>
    constexpr Interval<T> nonempty_interval(const T& lower, const T& upper)
    {
        // To catch interval(0, 1) vs interval(0.0, 1.0) errors
        static_assert(!std::is_same<T, int>::value, "Interval of ints is forbidden");

        return lower <= upper ? interval(lower, upper) : interval(upper, lower);
    }
}
