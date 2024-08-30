module;

#include <DirectXMath.h>

export module FatPound.Math;

export import :RectF;

import std;

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> or std::floating_point<T>;

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    float GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept;
    float GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept;

    template <typename T>
    inline auto Square(const T& x)
    {
        return x * x;
    }
}