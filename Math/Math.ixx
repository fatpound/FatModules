module;

#include <DirectXMath.h>

export module FatPound.Math;

export import :RectF;

import std;

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> or std::floating_point<T>;

    template
    <
        typename T,
        typename U
    >
    concept Multiplicable = requires(T var1, U var2)
    {
        { var1 * var2 };
    };

    template
    <
        typename T,
        typename U,
        typename Which = T
    >
    concept Multiplicable_SameAs_Which = Multiplicable<T, U>
    and
    requires(T var1, U var2)
    {
        { var1 * var2 } -> std::same_as<Which>;
    };

    template
    <
        typename T,
        typename U
    >
    concept Multiplicable_Noexcept = Multiplicable<T, U>
    and
    requires(T var1, U var2)
    {
        { var1 * var2 } noexcept;
    };

    template <typename T> concept SelfMultiplicable          = Multiplicable<T, T>;
    template <typename T> concept SelfMultiplicable_SameAs   = Multiplicable_SameAs_Which<T, T>;
    template <typename T> concept SelfMultiplicable_Noexcept = Multiplicable_Noexcept<T, T>;

    template <SelfMultiplicable_SameAs T>
    inline constexpr auto Square(const T& var) noexcept(SelfMultiplicable_Noexcept<T>)
    {
        return var * var;
    }

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    float GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept;
    float GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept;
}