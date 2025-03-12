module;

export module FatPound.Math.Common;

import FatPound.Math.Numbers.Sets;

export namespace fatpound::math
{
    template <std::unsigned_integral N>
    constexpr bool IsPowerOf2(const N& num) noexcept
    {
        return (num not_eq 0) and (not (num bitand (num - 1)));
    }

    template <numbers::Natural N>
    constexpr auto Factorial(N num) noexcept -> N
    {
        N prod{1};

        while (num not_eq 0)
        {
            prod *= num;
            --num;
        }

        return prod;
    }

    template <numbers::Natural N>
    constexpr auto DigitCount(N num) noexcept -> N
    {
        N count{};

        while (num not_eq 0)
        {
            num /= 10;
            ++count;
        }

        return count;
    }

    template <numbers::Natural N>
    auto DigitCount_Fast(const N num) noexcept -> N
    {
        return std::log10(num) + static_cast<N>(1);
    }

    template <numbers::Natural N>
    constexpr auto DigitSum(N num) noexcept -> N
    {
        N sum{};

        while (num not_eq 0)
        {
            sum += num % 10;
            num /= 10;
        }

        return sum;
    }

    template <numbers::Integer Z>
    constexpr auto DigitSum(Z num) noexcept -> Z
    {
        if (num < 0)
        {
            num = -num;
        }

        return DigitSum<::std::make_unsigned_t<Z>>(num);
    }

    template <numbers::Rational Q>
    constexpr auto Gaussian(const Q x, const Q rho)
    {
        const auto rhoSq2 = Square<>(rho) * 2.0;

        return (1.0 / ::std::sqrt(rhoSq2 * ::std::numbers::pi_v<Q>)) * ::std::exp(-(Square<>(x) / rhoSq2));
    }
}

module : private;