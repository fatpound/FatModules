module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

export module FatPound.Geometry.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

namespace dx = DirectX;

export namespace fatpound::geometry
{
    auto operator +       (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorAdd(p0, p1);
    }
    auto operator -       (const dx::XMVECTOR& p1, const dx::XMVECTOR& p0) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorSubtract(p1, p0);
    }
    auto operator *       (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorMultiply(p0, p1);
    }
    auto operator /       (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorDivide(p0, p1);
    }

    auto operator *       (const float&     scale, const dx::XMVECTOR&  v) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorScale(v, scale);
    }
    auto operator *       (const dx::XMVECTOR&  v, const float&     scale) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorScale(v, scale);
    }
    auto operator /       (const dx::XMVECTOR&  v, const float&     scale) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorScale(v, 1.0F / scale);
    }

    auto DistanceVector2  (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> dx::XMVECTOR
    {
        return dx::XMVector2Length(p1 - p0);
    }
    auto DistanceVector3  (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> dx::XMVECTOR
    {
        return dx::XMVector3Length(p1 - p0);
    }
    auto DistanceVector4  (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> dx::XMVECTOR
    {
        return dx::XMVector4Length(p1 - p0);
    }

    auto Distance2        (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> float
    {
        return dx::XMVectorGetX(DistanceVector2(p0, p1));
    }
    auto Distance3        (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> float
    {
        return dx::XMVectorGetX(DistanceVector3(p0, p1));
    }
    auto Distance4        (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> float
    {
        return dx::XMVectorGetX(DistanceVector4(p0, p1));
    }
    auto Distance         (const dx::XMFLOAT2& p0, const dx::XMFLOAT2& p1) noexcept -> float
    {
        return Distance2(dx::XMLoadFloat2(&p0), dx::XMLoadFloat2(&p1));
    }
    auto Distance         (const dx::XMFLOAT3& p0, const dx::XMFLOAT3& p1) noexcept -> float
    {
        return Distance3(dx::XMLoadFloat3(&p0), dx::XMLoadFloat3(&p1));
    }
    auto Distance         (const dx::XMFLOAT4& p0, const dx::XMFLOAT4& p1) noexcept -> float
    {
        return Distance4(dx::XMLoadFloat4(&p0), dx::XMLoadFloat4(&p1));
    }

    auto CompareDistance2 (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> bool
    {
        return dx::XMVectorGetX(dx::XMVector2LengthSq(p0)) > dx::XMVectorGetX(dx::XMVector2LengthSq(p1));
    }
    auto CompareDistance  (const dx::XMFLOAT2& p0, const dx::XMFLOAT2& p1) noexcept -> bool
    {
        return CompareDistance2(dx::XMLoadFloat2(&p0), dx::XMLoadFloat2(&p1));
    }
}

#endif

module : private;
