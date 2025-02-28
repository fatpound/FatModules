module;

#include <FatWin32_Settings.hpp>

#include <DirectXMath.h>

#include <d2d1.h>

export module FatPound.Math.RectF;

import std;

export namespace fatpound::math
{
    class RectF final
    {
    public:
        explicit RectF(float left, float top, float right, float bottom) noexcept
            :
            m_rect{ left, top, right, bottom }
        {

        }
        explicit RectF(const ::DirectX::XMFLOAT2& topLeft, float width, float height) noexcept
            :
            RectF(D2D1_POINT_2F{ topLeft.x, topLeft.y }, width, height)
        {

        }
        explicit RectF(const D2D1_POINT_2F topLeft, float width, float height) noexcept
            :
            m_rect{ topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height }
        {

        }
        explicit RectF(const D2D1_POINT_2F topLeft, const D2D1_POINT_2F bottomRight) noexcept
            :
            m_rect{ topLeft.x, topLeft.y, bottomRight.x, bottomRight.y }
        {

        }

        explicit RectF()             = delete;
        explicit RectF(const RectF&) = default;
        explicit RectF(RectF&&)      = default;

        auto operator = (const RectF&) -> RectF& = default;
        auto operator = (RectF&&)      -> RectF& = default;
        ~RectF() noexcept = default;


    public:
        static auto FromCenter(const D2D1_POINT_2F center, const float halfWidth, const float halfHeight) noexcept -> RectF
        {
            return RectF(center.x - halfWidth, center.y - halfHeight, center.x + halfWidth, center.y + halfHeight);
        }
        static auto FromCenter(const ::DirectX::XMFLOAT2& center, const float halfWidth, const float halfHeight) noexcept -> RectF
        {
            return RectF(center.x - halfWidth, center.y - halfHeight, center.x + halfWidth, center.y + halfHeight);
        }


    public:
        auto GetExpanded(float offset) const noexcept -> RectF
        {
            return RectF(m_rect.left - offset, m_rect.top - offset, m_rect.right + offset, m_rect.bottom + offset);
        }

        auto GetCenter() const noexcept -> D2D1_POINT_2F
        {
            return D2D1_POINT_2F{ (m_rect.left + m_rect.right) / 2.0f, (m_rect.top + m_rect.bottom) / 2.0f };
        }

        bool IsOverlappingWith(const RectF& other) const noexcept
        {
            return m_rect.right > other.m_rect.left && m_rect.left < other.m_rect.right &&
                m_rect.bottom > other.m_rect.top && m_rect.top < other.m_rect.bottom;
        }
        bool IsContainedBy(const RectF& other) const noexcept
        {
            return m_rect.left >= other.m_rect.left && m_rect.right <= other.m_rect.right &&
                m_rect.top >= other.m_rect.top && m_rect.bottom <= other.m_rect.bottom;
        }


    public:
        D2D1_RECT_F m_rect;


    protected:


    private:
    };
}

module : private;