module;

#include <_macros/Compiler.hxx>

export module FatPound.Colors.ARGB.Color;

import FatPound.Bit.Common;

import std;

export namespace fatpound::colors::argb
{
    /// @brief Represents a 32-bit color value with separate alpha, red, green, and blue channels
    /// 
    class [[nodiscard]] Color
    {
    public:
        using ChannelA_t = std::uint8_t;
        using ChannelR_t = ChannelA_t;
        using ChannelG_t = ChannelA_t;
        using ChannelB_t = ChannelA_t;
        using    Value_t = std::uint32_t;

        static_assert(requires { requires std::unsigned_integral<ChannelA_t>; }, "ChannelA_t is not an Unsigned Integral type!");
        static_assert(requires { requires std::unsigned_integral<ChannelR_t>; }, "ChannelR_t is not an Unsigned Integral type!");
        static_assert(requires { requires std::unsigned_integral<ChannelG_t>; }, "ChannelG_t is not an Unsigned Integral type!");
        static_assert(requires { requires std::unsigned_integral<ChannelB_t>; }, "ChannelB_t is not an Unsigned Integral type!");
        static_assert(requires { requires std::unsigned_integral<Value_t>;    },    "Value_t is not an Unsigned Integral type!");

        static_assert(sizeof(Value_t) >= (sizeof(ChannelA_t) + sizeof(ChannelR_t) + sizeof(ChannelG_t) + sizeof(ChannelB_t)), "Value_t size CANNOT be less than the sum of channel sizes!");


    public:
        static constexpr auto AlphaShift = static_cast<Value_t>((sizeof(ChannelB_t) * 8U) + (sizeof(ChannelG_t) * 8U) + (sizeof(ChannelR_t) * 8U));
        static constexpr auto   RedShift = static_cast<Value_t>((sizeof(ChannelB_t) * 8U) + (sizeof(ChannelG_t) * 8U));
        static constexpr auto GreenShift = static_cast<Value_t>( sizeof(ChannelB_t) * 8U);
        static constexpr auto  BlueShift = static_cast<Value_t>(0ULL);

        static constexpr auto  AlphaMask = bit::OneMask<Value_t>(AlphaShift + (sizeof(ChannelA_t) * 8U - 1U), AlphaShift);
        static constexpr auto    RedMask = bit::OneMask<Value_t>(  RedShift + (sizeof(ChannelR_t) * 8U - 1U),   RedShift);
        static constexpr auto  GreenMask = bit::OneMask<Value_t>(GreenShift + (sizeof(ChannelG_t) * 8U - 1U), GreenShift);
        static constexpr auto   BlueMask = bit::OneMask<Value_t>( BlueShift + (sizeof(ChannelB_t) * 8U - 1U),  BlueShift);


    public:
        // NOLINTBEGIN(google-explicit-constructor, hicpp-explicit-conversions)
        constexpr Color(const      Value_t& xrgb, const std::uint8_t& alpha = 0xFFU) noexcept
            :
            m_value_((xrgb bitand 0x00'FF'FF'FFU) bitor (static_cast<Value_t>(alpha) << AlphaShift))
        {

        }
        // NOLINTEND(google-explicit-constructor, hicpp-explicit-conversions)
        constexpr Color(const      Value_t& xrgb, bool) noexcept
            :
            m_value_(xrgb)
        {

        }
        constexpr Color(const std::uint8_t&  red, const std::uint8_t& green, const std::uint8_t& blue, const std::uint8_t& alpha = static_cast<std::uint8_t>(255U)) noexcept
            :
            Color((static_cast<Value_t>(red) << RedShift) bitor (static_cast<Value_t>(green) << GreenShift) bitor (static_cast<Value_t>(blue)), alpha)
        {
            
        }
        constexpr Color(const Color& col, const std::uint8_t& alpha) noexcept
            :
            Color(col.m_value_, alpha)
        {

        }

        constexpr Color()                 = default;
        constexpr Color(const Color&)     = default;
        constexpr Color(Color&&) noexcept = default;

        constexpr auto operator = (const Color&)     -> Color& = default;
        constexpr auto operator = (Color&&) noexcept -> Color& = default;
        constexpr ~Color() noexcept                            = default;


    public:
        constexpr auto operator <=> (const Color&) const noexcept -> bool = delete;
        constexpr auto operator ==  (const Color&) const noexcept -> bool = default;

        // NOLINTBEGIN(google-explicit-constructor, hicpp-explicit-conversions)
        constexpr operator Value_t () const noexcept
        {
            return m_value_;
        }
        // NOLINTEND(google-explicit-constructor, hicpp-explicit-conversions)


    public:
        [[nodiscard]] FATLIB_FORCEINLINE constexpr auto GetValue () const noexcept -> Value_t
        {
            return *this;
        }
        [[nodiscard]] FATLIB_FORCEINLINE constexpr auto GetA     () const noexcept -> std::uint8_t
        {
            return m_value_ >> AlphaShift;
        }
        [[nodiscard]] FATLIB_FORCEINLINE constexpr auto GetR     () const noexcept -> std::uint8_t
        {
            return (m_value_ >> RedShift) bitand 0xFFU;
        }
        [[nodiscard]] FATLIB_FORCEINLINE constexpr auto GetG     () const noexcept -> std::uint8_t
        {
            return (m_value_ >> GreenShift) bitand 0xFFU;
        }
        [[nodiscard]] FATLIB_FORCEINLINE constexpr auto GetB     () const noexcept -> std::uint8_t
        {
            return m_value_ bitand 0xFFU;
        }

        FATLIB_FORCEINLINE constexpr auto SetValue (const      Value_t& value) noexcept -> Color&
        {
            m_value_ = value;

            return *this;
        }
        FATLIB_FORCEINLINE constexpr auto SetA     (const std::uint8_t& alpha) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand AlphaMask) bitor (static_cast<Value_t>(alpha) << AlphaShift);

            return *this;
        }
        FATLIB_FORCEINLINE constexpr auto SetR     (const std::uint8_t&   red) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand RedMask) bitor (static_cast<Value_t>(red) << RedShift);

            return *this;
        }
        FATLIB_FORCEINLINE constexpr auto SetG     (const std::uint8_t& green) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand GreenMask) bitor (static_cast<Value_t>(green) << GreenShift);

            return *this;
        }
        FATLIB_FORCEINLINE constexpr auto SetB     (const std::uint8_t&  blue) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand BlueMask) bitor (static_cast<Value_t>(blue));

            return *this;
        }

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4686)
#endif

        [[nodiscard]]
#if __cplusplus > 202500L
        constexpr
#endif
        auto GetString(const std::string& prefix, const bool& withAlpha) const -> std::string
        {
            return std::format<>(
                "{}{}{:02X}{:02X}{:02X}",
                prefix,
                withAlpha ? std::format<>("{:02X}", GetA()) : "",
                GetR(),
                GetG(),
                GetB()
            );
        }

#ifdef _MSC_VER
#pragma warning (pop)
#endif


    protected:


    private:
        Value_t  m_value_ = std::numeric_limits<Value_t>::max();
    };
}

// module : private;
