module;

export module FatPound.Math.Numbers;

export import FatPound.Math.Numbers.Primes;
export import FatPound.Math.Numbers.Sets;

import FatPound.Math.Common;

import std;

export namespace fatpound::math::numbers
{
    template <Rational Q>
    constexpr auto twoPi = std::numbers::pi_v<Q> * static_cast<Q>(2.0);

    template <Integer Z>
    constexpr auto IsOdd(const Z& num) noexcept -> bool
    {
        return num bitand static_cast<Z>(1);
    }

    template <Integer Z>
    constexpr auto IsEven(const Z& num) noexcept -> bool
    {
        return not IsOdd<>(num);
    }

    template <Natural N>
    constexpr auto IsPowerOf2(const N& num) noexcept -> bool
    {
        return (num not_eq 0) and (not (num bitand (num - 1)));
    }

    template <Natural N>
    constexpr auto IsPerfectSquare(const N& num) noexcept -> bool
    {
        return Square<>([](const N& x) constexpr noexcept -> N { return static_cast<N>(std::sqrt(x)); }(num)) == num;
    }

    template <Natural N>
    constexpr auto IsHarshad(const N& num) noexcept -> bool
    {
        return num % DigitSum<>(num) == 0;
    }

    template <Natural N>
    constexpr auto IsNiven(const N& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }

    template <Natural N>
    constexpr auto IsMultidigital(const N& num) noexcept -> bool
    {
        return IsHarshad<>(num);
    }
}

module : private;