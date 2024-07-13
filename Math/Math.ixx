module;

export module FatPound.Math;

export import :Primes;

import std;

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template <std::signed_integral T>
    T GCD(T x, T y)
    {
        while (y != 0)
        {
            const T temp = x % y;
            x = y;
            y = temp;
        }

        return x;
    }
    template <std::signed_integral T>
    T LCM(T x, T y)
    {
        return (x * y) / GCD<T>(y, x % y);
    }

    template <typename T>
    inline auto Square(const T& x)
    {
        return x * x;
    }

    template <std::signed_integral T>
    inline bool IsPowerOf2(const T n)
    {
        return !(n & (~-n));
    }

    template <std::floating_point T>
    inline constexpr T twoPi = 2.0f * std::numbers::pi_v<T>;

    template <std::floating_point T>
    T WrapAngle(T theta)
    {
        const T modded = std::fmod(theta, twoPi<T>);

        return modded > std::numbers::pi_v<T>
            ? modded - twoPi<T>
            : modded
            ;
    }

    template <typename T>
    T Interpolate(const T& src, const T& dst, float splitRatio)
    {
        return src + (dst - src) * splitRatio;
    }

    template <std::floating_point F>
    constexpr F ToRadians(F deg)
    {
        return deg * std::numbers::pi_v<F> / static_cast<F>(180.0);
    }
}