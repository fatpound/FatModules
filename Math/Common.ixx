module;

#include <FatDefines.hpp>

export module FatPound.Math.Common;

import FatPound.Math.Multiplicative;
import FatPound.Traits.Bitwise;

import std;

export namespace fatpound::math
{
    template <std::unsigned_integral T>
    constexpr auto IsPowerOf2(const T& num) noexcept -> bool
    {
        return (num not_eq 0) and (not (num bitand (num - 1)));
    }

    template <std::unsigned_integral T>
    constexpr auto Factorial(T num) noexcept -> T
    {
        T prod{1};

        while (num not_eq 0)
        {
            prod *= num;
            --num;
        }

        return prod;
    }

    template <std::unsigned_integral T>
    constexpr auto DigitCount(T num) noexcept -> T
    {
        T count{};

        while (num not_eq 0)
        {
            num /= 10;
            ++count;
        }

        return count;
    }

    template <std::unsigned_integral T>
    FAT_CMATH_CONSTEXPR26
    auto DigitCount_Fast(const T& num) noexcept -> T
    {
        return std::log10(num) + static_cast<T>(1);
    }

    template <std::unsigned_integral T>
    constexpr auto DigitSum(T num) noexcept -> T
    {
        T sum{};

        while (num not_eq 0)
        {
            sum += num % 10;
            num /= 10;
        }

        return sum;
    }

    template <std::signed_integral T>
    constexpr auto DigitSum(const T& num) noexcept
    {
        return DigitSum<std::make_unsigned_t<T>>(num < 0 ? (-num) : num);
    }

    template <traits::IntegralOrFloating T>
    constexpr auto Gaussian(const T& x, const T& rho)
    {
        const auto& rhoSq2 = Square<>(rho) * 2.0;

        return (1.0 / std::sqrt(rhoSq2 * std::numbers::pi_v<T>)) * std::exp(-(Square<>(x) / rhoSq2));
    }
}

module : private;
