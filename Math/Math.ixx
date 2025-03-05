module;

#include <DirectXMath.h>

export module FatPound.Math;

export import FatPound.Math.Geometry;
export import FatPound.Math.Multiplicative;
export import FatPound.Math.Numbers;
export import FatPound.Math.RectF;

import std;

export namespace fatpound::math
{
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

    template <std::integral N>
    constexpr auto DigitSum(N num) noexcept -> N
    {
        if (num < 0)
        {
            num = -num;
        }

        return DigitSum<std::make_unsigned_t<N>>(num);
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