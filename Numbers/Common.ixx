module;

#include <_macros/STL.hxx>

export module FatPound.Numbers.Common;

import FatPound.Math.Common;
import FatPound.Math.Multiplicative;

import std;

export namespace fatpound::numbers
{
    template <std::floating_point T = float> constexpr auto       Pi = std::numbers::pi_v<T>;
    template <std::floating_point T = float> constexpr auto    twoPi = Pi<T> * static_cast<T>(2.0);
    template <std::floating_point T = float> constexpr auto   PiDiv2 = Pi<T> / static_cast<T>(2.0);
    template <std::floating_point T = float> constexpr auto   PiDiv4 = Pi<T> / static_cast<T>(4.0);
    template <std::floating_point T = float> constexpr auto    invPi = static_cast<T>(1.0) / Pi<T>;
    template <std::floating_point T = float> constexpr auto invTwoPi = invPi<T> / static_cast<T>(2.0);

    ///

    template <std::unsigned_integral T> CX_MATH26 auto IsSquare        (const T& num) noexcept -> bool
    {
        return Square<T>(std::sqrt(num)) == num;
    }
    template <std::unsigned_integral T> CX_MATH26 auto IsCube          (const T& num) noexcept -> bool
    {
        return Cube<T>(std::cbrt(num)) == num;
    }
    template <std::unsigned_integral T> CX_MATH26 auto IsPerfectSquare (const T& num) noexcept -> bool
    {
        return IsSquare<>(num);
    }
    template <std::unsigned_integral T> CX_MATH26 auto IsPerfectCube   (const T& num) noexcept -> bool
    {
        return IsCube<>(num);
    }
    template <std::unsigned_integral T> constexpr auto IsHarshad       (const T& num) noexcept -> bool
    {
        return num % DigitSum<>(num) == 0;
    }
    template <std::unsigned_integral T> constexpr auto IsNiven         (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }
    template <std::unsigned_integral T> constexpr auto IsMultidigital  (const T& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }

    template <std::integral T>          constexpr auto IsOdd           (const T& num) noexcept -> bool
    {
        return num bitand static_cast<T>(1);
    }
    template <std::integral T>          constexpr auto IsEven          (const T& num) noexcept -> bool
    {
        return not IsOdd<>(num);
    }
}

// module : private;
