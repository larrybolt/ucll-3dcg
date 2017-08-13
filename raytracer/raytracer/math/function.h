#pragma once

#include <functional>
#include <memory>


namespace math
{
    template<typename R, typename... Ts>
    struct FunctionBody
    {
        virtual R evaluate(Ts... args) const = 0;

        typedef R result;
        typedef std::tuple<Ts...> parameters;
    };

    template<typename R, typename... Ts>
    class LambdaFunctionBody : public FunctionBody<R, Ts...>
    {
    public:
        LambdaFunctionBody(std::function<R(Ts...)> lambda)
            : m_lambda(lambda) { }

        R evaluate(Ts... args) const override { return m_lambda(args...); }

    private:
        std::function<R(Ts...)> m_lambda;
    };

    template<typename R, typename... Ts>
    class Function;

    template<typename R, typename... Ts>
    class Function<R(Ts...)>
    {
    public:
        Function(std::shared_ptr<FunctionBody<R, Ts...>> body = nullptr)
            : m_body(std::move(body)) { }

        Function(const Function<R(Ts...)>&) = default;

        R operator ()(Ts... ts) const
        {
            return m_body->evaluate(ts...);
        }

        explicit operator bool() const
        {
            return m_body != nullptr;
        }

        typedef R result;
        typedef std::tuple<Ts...> parameters;

    private:
        std::shared_ptr<FunctionBody<R, Ts...>> m_body;
    };

    template<typename R, typename... Ts>
    Function<R(Ts...)> from_lambda(std::function<R(Ts...)> lambda)
    {
        return Function<R(Ts...)>(std::make_shared<LambdaFunctionBody<R, Ts...>>(lambda));
    }

    template<typename R2, typename RT, typename R1, typename... Ts>
    class Composition : public FunctionBody<R2, Ts...>
    {
    public:
        Composition(const Function<R1(Ts...)>& f, const Function<R2(RT)>& g)
            : m_f(f), m_g(g) { }

        R2 evaluate(Ts... args) const override
        {
            return m_g(m_f(args...));
        }

    private:
        Function<R1(Ts...)> m_f;
        Function<R2(RT)> m_g;
    };

    template<typename R2, typename R1, typename... Ts>
    Function<R2(Ts...)> compose(const Function<R1(Ts...)>& f, const Function<R2(R1)>& g)
    {
        return Function<R2(Ts...)>(std::make_shared<Composition<R2, R1, R1, Ts...>>(f, g));
    }

    template<typename R2, typename R1, typename... Ts>
    Function<R2(Ts...)> operator >> (const Function<R1(Ts...)>& f, const Function<R2(R1)>& g)
    {
        return Function<R2(Ts...)>(std::make_shared<Composition<R2, R1, R1, Ts...>>(f, g));
    }

    template<typename R2, typename R1, typename... Ts>
    Function<R2(Ts...)> operator >> (const Function<R1(Ts...)>& f, const Function<R2(const R1&)>& g)
    {
        return Function<R2(Ts...)>(std::make_shared<Composition<R2, const R1&, R1, Ts...>>(f, g));
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator +(const Function<R(Ts...)>& f, const R& constant)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return f(ts...) + constant; };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator +(const R& constant, const Function<R(Ts...)>& f)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return constant + f(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator +(const Function<R(Ts...)>& f, const Function<R(Ts...)>& g)
    {
        std::function<R(Ts...)> lambda = [f, g](Ts... ts) { return f(ts...) + g(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator -(const Function<R(Ts...)>& f, const R& constant)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return f(ts...) - constant; };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator -(const R& constant, const Function<R(Ts...)>& f)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return constant - f(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator -(const Function<R(Ts...)>& f, const Function<R(Ts...)>& g)
    {
        std::function<R(Ts...)> lambda = [f, g](Ts... ts) { return f(ts...) - g(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename T, typename... Ts>
    Function<R(Ts...)> operator *(const Function<R(Ts...)>& f, const T& constant)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return f(ts...) * constant; };

        return from_lambda<R, Ts...>( lambda );
    }

    template<typename R, typename T, typename... Ts>
    Function<R(Ts...)> operator *(const T& constant, const Function<R(Ts...)>& f)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return constant * f(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator *(const Function<R(Ts...)>& f, const Function<R(Ts...)>& g)
    {
        std::function<R(Ts...)> lambda = [f, g](Ts... ts) { return f(ts...) * g(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator /(const Function<R(Ts...)>& f, const R& constant)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return f(ts...) / constant; };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator /(const R& constant, const Function<R(Ts...)>& f)
    {
        std::function<R(Ts...)> lambda = [f, constant](Ts... ts) { return constant / f(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator /(const Function<R(Ts...)>& f, const Function<R(Ts...)>& g)
    {
        std::function<R(Ts...)> lambda = [f, g](Ts... ts) { return f(ts...) / g(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator &&(const Function<R(Ts...)>& f, const Function<R(Ts...)>& g)
    {
        std::function<R(Ts...)> lambda = [f, g](Ts... ts) { return f(ts...) && g(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }

    template<typename R, typename... Ts>
    Function<R(Ts...)> operator ||(const Function<R(Ts...)>& f, const Function<R(Ts...)>& g)
    {
        std::function<R(Ts...)> lambda = [f, g](Ts... ts) { return f(ts...) || g(ts...); };

        return from_lambda<R, Ts...>(lambda);
    }
}
