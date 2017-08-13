#pragma once

namespace math
{
    template<typename T>
    constexpr T sign(T n)
    {
        return n < 0 ? -1 : (n > 0 ? 1 : 0);
    }   

    template<typename... Ts>
    struct ExtremumFinder;

    template<typename T>
    struct ExtremumFinder<T>
    {
        using result = T;

        constexpr static T minimum(T t) { return t; }
        constexpr static T maximum(T t) { return t; }
    };

    template<typename T, typename... Ts>
    struct ExtremumFinder<T, Ts...>
    {
        using result = T;

        constexpr static T minimum(T t, Ts... ts) {
            return std::min(t, ExtremumFinder<Ts...>::minimum(ts...));
        }

        constexpr static T maximum(T t, Ts... ts) {
            return std::max(t, ExtremumFinder<Ts...>::maximum(ts...));
        }
    };

    template<typename... Ts>
    constexpr typename ExtremumFinder<Ts...>::result minimum(Ts... ts)
    {
        return ExtremumFinder<Ts...>::minimum(ts...);
    }

    template<typename... Ts>
    constexpr typename ExtremumFinder<Ts...>::result maximum(Ts... ts)
    {
        return ExtremumFinder<Ts...>::maximum(ts...);
    }
}
