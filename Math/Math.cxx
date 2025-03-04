module;

#include <DirectXMath.h>

module FatPound.Math;

namespace dx = DirectX;

namespace fatpound::math
{
    auto GetDifferenceVector(const ::dx::XMVECTOR pos1_vec, const ::dx::XMVECTOR pos2_vec) noexcept -> ::dx::XMVECTOR
    {
        return ::dx::XMVectorSubtract(pos1_vec, pos2_vec);
    }

    auto GetDistanceBetweenXMF2(const ::dx::XMFLOAT2& pos1, const ::dx::XMFLOAT2& pos2) noexcept -> float
    {
        return ::dx::XMVectorGetX(
            ::dx::XMVector2Length(
                ::dx::XMVectorSubtract(
                    ::dx::XMLoadFloat2(&pos1),
                    ::dx::XMLoadFloat2(&pos2)
                )
            )
        );
    }
    auto GetDistanceBetweenXMF3(const ::dx::XMFLOAT3& pos1, const ::dx::XMFLOAT3& pos2) noexcept -> float
    {
        return ::dx::XMVectorGetX(
            ::dx::XMVector3Length(
                GetDifferenceVector(
                    ::dx::XMLoadFloat3(&pos1),
                    ::dx::XMLoadFloat3(&pos2)
                )
            )
        );
    }
}