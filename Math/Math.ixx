module;

#include <DirectXMath.h>

export module FatPound.Math;

export import FatPound.Math.Common;
export import FatPound.Math.Geometry;
export import FatPound.Math.Multiplicative;
export import FatPound.Math.Numbers;
export import FatPound.Math.Rect;

import std;

export namespace fatpound::math
{
    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    auto GetDistanceBetweenXMF2(const ::DirectX::XMFLOAT2& pos1, const ::DirectX::XMFLOAT2& pos2) noexcept -> float;
    auto GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept -> float;
}

module : private;