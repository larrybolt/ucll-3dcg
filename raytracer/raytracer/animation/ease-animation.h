#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> ease(Animation<T> animation, math::functions::EasingFunction easing_function)
    {
        auto target = math::interval(0.0, animation.duration().seconds());
        auto stretched_easing_function = math::functions::easing::stretch(easing_function, target, target);

        return preprocess<T>(timestamp_to_seconds() >> stretched_easing_function >> seconds_to_timestamp(), animation);
    }
}
