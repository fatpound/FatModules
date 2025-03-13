module;

export module FatPound.Math.Rect;

import FatPound.Bitwise.Concepts;

export namespace fatpound::math
{
    template <bitwise::Integral_Or_Floating T>
    class Rect final
    {
    public:
        explicit Rect(const T& left, const T& top, const T& right, const T& bottom) noexcept
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
        static auto FromCenter(const T& centerX, const T& centerY, const T& halfWidth, const T& halfHeight) noexcept -> Rect
        {
            return Rect(centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
        }


    public:
        auto GetCenter() const noexcept -> std::pair<T, T>
        {
            return {
                (m_left + m_right) / static_cast<T>(2.0),
                (m_top + m_bottom) / static_cast<T>(2.0)
            };
        }

        auto GetExpanded(const T& offset) const noexcept -> Rect
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
        T m_left;
        T m_top;
        T m_right;
        T m_bottom;


    protected:


    private:
    };
}

module : private;