module;

#include <DirectXMath.h>

export module FatPound.Math;

export import :RectF;

import std;

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> or std::floating_point<T>;

    template <typename T>
    concept Multiplicable = requires(T var1, T var2)
    {
        { var1 * var2 } noexcept -> std::same_as<T>;
    };

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    float GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept;
    float GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept;

    template <Multiplicable T>
    inline auto Square(const T& var) noexcept
    {
        return var * var;
    }
}