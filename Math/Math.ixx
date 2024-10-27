module;

#include <DirectXMath.h>

export module FatPound.Math;

export import :RectF;
export import :Multiplicable;

export import FatPound.Math.Number_Set;

import std;

export namespace fatpound::math
{
    template <SelfMultiplicable T>
    inline constexpr auto Square(const T& var) noexcept(SelfMultiplicable_Noexcept<T>)
    {
        return var * var;
    }

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    auto GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept -> float;
    auto GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept -> float;
}