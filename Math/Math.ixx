module;

#include <DirectXMath.h>

export module FatPound.Math;

export import :RectF;

export import FatPound.Math.Concepts;

import std;

export namespace fatpound::math
{
    template <concepts::SelfMultiplicable T>
    inline constexpr auto Square(const T& var) noexcept(concepts::SelfMultiplicable_Noexcept<T>)
    {
        return var * var;
    }

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    float GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept;
    float GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept;
}