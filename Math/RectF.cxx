module;

#include <FatWin32_Settings.hpp>

#include <DirectXMath.h>

#include <d2d1.h>

module FatPound.Math.RectF;

namespace fatpound::math
{
    RectF::RectF(float left, float top, float right, float bottom) noexcept
        :
        rect{ left, top, right, bottom }
    {

    }
    RectF::RectF(const ::DirectX::XMFLOAT2& topLeft, float width, float height) noexcept
        :
        RectF(D2D1_POINT_2F{ topLeft.x, topLeft.y }, width, height)
    {

    }
    RectF::RectF(const D2D1_POINT_2F topLeft, float width, float height) noexcept
        :
        rect{ topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height }
    {

    }
    RectF::RectF(const D2D1_POINT_2F topLeft, const D2D1_POINT_2F bottomRight) noexcept
        :
        rect{ topLeft.x, topLeft.y, bottomRight.x, bottomRight.y }
    {

    }

    auto RectF::FromCenter(const D2D1_POINT_2F center, const float halfWidth, const float halfHeight) noexcept -> RectF
    {
        return RectF(center.x - halfWidth, center.y - halfHeight, center.x + halfWidth, center.y + halfHeight);
    }
    auto RectF::FromCenter(const DirectX::XMFLOAT2& center, const float halfWidth, const float halfHeight) noexcept -> RectF
    {
        return RectF(center.x - halfWidth, center.y - halfHeight, center.x + halfWidth, center.y + halfHeight);
    }

    auto RectF::GetExpanded(float offset) const noexcept -> RectF
    {
        return RectF(rect.left - offset, rect.top - offset, rect.right + offset, rect.bottom + offset);
    }

    auto RectF::GetCenter() const noexcept -> D2D1_POINT_2F
    {
        return D2D1_POINT_2F{ (rect.left + rect.right) / 2.0f, (rect.top + rect.bottom) / 2.0f };
    }

    bool RectF::IsOverlappingWith(const RectF& other) const noexcept
    {
        return rect.right > other.rect.left && rect.left < other.rect.right &&
            rect.bottom > other.rect.top && rect.top < other.rect.bottom;
    }
    bool RectF::IsContainedBy(const RectF& other) const noexcept
    {
        return rect.left >= other.rect.left && rect.right <= other.rect.right &&
            rect.top >= other.rect.top && rect.bottom <= other.rect.bottom;
    }
}