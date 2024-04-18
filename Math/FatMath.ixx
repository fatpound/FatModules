// module;

export module FatMath;

import <cassert>;

#if (_MSVC_LANG > 202002L)
import std;
#else
#if (_MSVC_LANG == 202002L)
#ifdef NDEBUG
import std.core;
#else
import <cmath>;
/**/
import <limits>;
import <numeric>;
import <numbers>;
import <concepts>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // (_MSVC_LANG == 202002L)
#endif // (_MSVC_LANG > 202002L)

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

    template <std::signed_integral T>
    bool IsPrime(const T& n)
    {
        if (n < static_cast<T>(4))
        {
            return n > 1;
        }

        if (n % 2 == 0 || n % 3 == 0)
        {
            return false;
        }

        const T m = n + 1;

        for (T i = 5; Square(i) < m; i += 6)
        {
            if ((n % i == 0) || (n % (i + 2) == 0))
            {
                return false;
            }
        }

        return true;
    }
    template <std::signed_integral T>
    T NextPrime(T n)
    {
        if (n % 2 == 0)
        {
            ++n;
        }

        while (!IsPrime<T>(n))
        {
            n += 2;
        }

        return n;
    }
    template <std::signed_integral T>
    T PrevPrime(T n)
    {
        if (n % 2 == 0)
        {
            --n;
        }

        while (!IsPrime<T>(n))
        {
            n -= 2;
        }

        return n;
    }
    template <std::signed_integral T>
    T NthPrime(T n)
    {
        assert(n > 0);

        if (n == 1)
        {
            return 2;
        }

        T i = 3;
        T counter = 1;

        while (true)
        {
            if (IsPrime(i))
            {
                if (++counter == n)
                {
                    break;
                }
            }

            i += 2;
        }

        return i;
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