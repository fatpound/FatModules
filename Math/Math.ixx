module;

#if FAT_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

export module FatPound.Math;

export import FatPound.Math.Numbers;
export import FatPound.Math.Geometry;

export import FatPound.Math.Common;
export import FatPound.Math.Multiplicative;

#if FAT_BUILDING_WITH_MSVC

namespace dx = DirectX;

export namespace fatpound::math
{
    auto operator - (const dx::XMVECTOR& pos1_vec, const dx::XMVECTOR& pos2_vec) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorSubtract(pos1_vec, pos2_vec);
    }
    auto operator - (const dx::XMFLOAT2& pos1, const dx::XMFLOAT2& pos2) noexcept -> float
    {
        return dx::XMVectorGetX(dx::XMVector2Length(dx::XMLoadFloat2(&pos1) - dx::XMLoadFloat2(&pos2)));
    }
    auto operator - (const dx::XMFLOAT3& pos1, const dx::XMFLOAT3& pos2) noexcept -> float
    {
        return dx::XMVectorGetX(dx::XMVector3Length(dx::XMLoadFloat3(&pos1) - dx::XMLoadFloat3(&pos2)));
    }
}

#endif

module : private;
