module;

export module FatPound.Math.Geometry.Rectangle;

import FatPound.Traits.Bitwise;

import std;

export namespace fatpound::math::geometry
{
    template <traits::IntegralOrFloating T>
    class Rectangle final
    {
    public:
        explicit Rectangle(const T& left, const T& top, const T& right, const T& bottom) noexcept
            :
            m_left(left),
            m_top(top),
            m_right(right),
            m_bottom(bottom)
        {

        }

        explicit Rectangle()            = delete;
        Rectangle(const Rectangle&)     = default;
        Rectangle(Rectangle&&) noexcept = default;

        auto operator = (const Rectangle&)     -> Rectangle& = default;
        auto operator = (Rectangle&&) noexcept -> Rectangle& = default;
        ~Rectangle() noexcept                                = default;


    public:
        static auto FromCenter(const T& centerX, const T& centerY, const T& halfWidth, const T& halfHeight) noexcept -> Rectangle
        {
            return Rectangle(centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
        }


    public:
        auto GetCenter() const noexcept -> std::pair<T, T>
        {
            return
            {
                (m_left + m_right) / static_cast<T>(2.0),
                (m_top + m_bottom) / static_cast<T>(2.0)
            };
        }

        auto GetExpanded(const T& offset) const noexcept -> Rectangle
        {
            return Rectangle(m_left - offset, m_top - offset, m_right + offset, m_bottom + offset);
        }

        auto IsOverlappingWith(const Rectangle& other) const noexcept -> bool
        {
            return m_left   < other.m_right
                   and
                   m_top    < other.m_bottom
                   and
                   m_right  > other.m_left
                   and
                   m_bottom > other.m_top;
        }
        auto IsContainedBy(const Rectangle& other) const noexcept -> bool
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
        T m_left;
        T m_top;
        T m_right;
        T m_bottom;


    protected:


    private:
    };

    template <traits::IntegralOrFloating T>
    using Rect = Rectangle<T>;
}

module : private;
