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
        explicit RectF(float left, float top, float right, float bottom) noexcept;
        explicit RectF(const ::DirectX::XMFLOAT2& topLeft, float width, float height) noexcept;
        explicit RectF(const D2D1_POINT_2F topLeft, float width, float height) noexcept;
        explicit RectF(const D2D1_POINT_2F topLeft, const D2D1_POINT_2F bottomRight) noexcept;

        explicit RectF() = delete;
        explicit RectF(const RectF& src) = default;
        explicit RectF(RectF&& src) = default;

        auto operator = (const RectF& src) -> RectF& = default;
        auto operator = (RectF&& src)      -> RectF& = default;
        ~RectF() noexcept = default;


    public:
        static auto FromCenter(const D2D1_POINT_2F center, const float halfWidth, const float halfHeight) noexcept -> RectF;
        static auto FromCenter(const ::DirectX::XMFLOAT2& center, const float halfWidth, const float halfHeight) noexcept -> RectF;


    public:
        auto GetExpanded(float offset) const noexcept -> RectF;

        auto GetCenter() const noexcept -> D2D1_POINT_2F;

        bool IsOverlappingWith(const RectF& other) const noexcept;
        bool IsContainedBy(const RectF& other) const noexcept;


    public:
        D2D1_RECT_F rect;


    protected:


    private:
    };
}

module : private;