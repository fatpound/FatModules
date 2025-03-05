module;

#include <DirectXMath.h>

export module FatPound.Math;

export import FatPound.Math.Numbers;
export import FatPound.Math.Multiplicable;
export import FatPound.Math.RectF;

import std;

export namespace fatpound::math
{
    template <std::unsigned_integral N>
    constexpr bool IsPowerOf2(const N& num) noexcept
    {
        return (num not_eq 0) and (not (num bitand (num - 1)));
    }

    template <Squarable T>
    constexpr auto Square(const T& x) noexcept(Squarable_NX<T>)
    {
        return x * x;
    }

    template <numbers::Natural N>
    constexpr auto IsPerfectSquare(const N& num) noexcept -> bool
    {
        return Square<>([](const N& x) constexpr noexcept -> N { return static_cast<N>(std::sqrt(x)); }(num)) == num;
    }

    template <numbers::Natural N>
    constexpr auto DigitSum(N num) -> N
    {
        N sum{};

        while (num not_eq 0)
        {
            sum += num % 10;
            num /= 10;
        }

        return sum;
    }

    template <std::integral N>
    constexpr auto DigitSum(N num) -> N
    {
        if (num < 0)
        {
            num = -num;
        }

        return DigitSum<>(static_cast<std::make_unsigned_t<N>>(num));
    }

    template <std::floating_point N>
    constexpr auto Gaussian(const N x, const N rho)
    {
        const auto rhoSq2 = Square<>(rho) * 2.0;

        return (1.0 / ::std::sqrt(rhoSq2 * ::std::numbers::pi_v<N>)) * ::std::exp(-(Square<>(x) / rhoSq2));
    }

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    auto GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept -> float;
    auto GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept -> float;
}

module : private;