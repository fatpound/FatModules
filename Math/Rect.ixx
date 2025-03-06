module;

#include <FatWin32_Settings.hpp>

export module FatPound.Math.Rect;

import FatPound.Math.Numbers.Sets;

import std;

export namespace fatpound::math
{
    template <numbers::Rational Q>
    class Rect final
    {
    public:
        explicit Rect(const Q left, const Q top, const Q right, const Q bottom) noexcept
            :
            m_left(left),
            m_top(top),
            m_right(right),
            m_bottom(bottom)
        {

        }

        explicit Rect()                = delete;
        explicit Rect(const Rect&)     = default;
        explicit Rect(Rect&&) noexcept = default;

        auto operator = (const Rect&)     -> Rect& = default;
        auto operator = (Rect&&) noexcept -> Rect& = default;
        ~Rect() noexcept                           = default;


    public:
        static auto FromCenter(const Q centerX, const Q centerY, const Q halfWidth, const Q halfHeight) noexcept -> Rect
        {
            return Rect(centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
        }


    public:
        auto GetCenter() const noexcept -> std::pair<Q, Q>
        {
            return {
                (m_left + m_right) / static_cast<Q>(2.0),
                (m_top + m_bottom) / static_cast<Q>(2.0)
            };
        }

        auto GetExpanded(const float offset) const noexcept -> Rect
        {
            return Rect(m_left - offset, m_top - offset, m_right + offset, m_bottom + offset);
        }

        auto IsOverlappingWith(const Rect& other) const noexcept -> bool
        {
            return m_left   < other.m_right
                   and
                   m_top    < other.m_bottom
                   and
                   m_right  > other.m_left
                   and
                   m_bottom > other.m_top;
        }
        auto IsContainedBy(const Rect& other) const noexcept -> bool
        {
            return m_left   >= other.m_left
                   and
                   m_top    >= other.m_top
                   and
                   m_right  <= other.m_right
                   and
                   m_bottom <= other.m_bottom;
        }


    public:
        Q m_left;
        Q m_top;
        Q m_right;
        Q m_bottom;


    protected:


    private:
    };
}

module : private;