#pragma once

#include "animation/animation.h"
#include "math/interval.h"


namespace animation
{
    template<typename T>
    Animation<T> animate(const math::Interval<T>& animation_interval, animation::Duration duration)
    {
        // Create an animation for 0 to 1
        auto double_animation = basic(0, 1, duration);

        // Creates a local function which takes a TimeStamp and returns a T.
        // The local function requires access to variables in the surrounding scope, in this case, double_animation and animation_interval.
        // These variables must be listed between [].
        std::function<T(TimeStamp)> lambda = [double_animation, animation_interval](TimeStamp now) -> T {
            // Get the current value for t.
            // t == 0 at the beginning of the animation and grows linearly to 1.
            double t = double_animation(now);

            // Sanity check
            assert(math::interval(0.0, 1.0).contains(t));

            // Map [0, 1] to target interval. Say animation_interval equals [3, 9],
            // then 0 -> 3, 0.5 -> 6, 1 -> 9, etc.
            return animation_interval.from_relative(double_animation(now));
        };

        // Turns the function into an Animation object
        return make_animation(math::from_lambda(lambda), duration);
    }

    template<typename T>
    Animation<T> animate(T from, T to, animation::Duration duration)
    {
        return animate(math::interval(from, to), duration);
    }
}