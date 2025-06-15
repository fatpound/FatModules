module;

#include <_macros/STL.hxx>

export module FatPound.Math.Numbers;

export import FatPound.Math.Numbers.Common;
export import FatPound.Math.Numbers.Primes;
export import FatPound.Math.Numbers.Sets;

import FatPound.Math.Common;
import FatPound.Math.Multiplicative;

import std;

export namespace fatpound::math::numbers
{
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

module : private;
