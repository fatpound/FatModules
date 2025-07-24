module;

#include <_macros/Compiler.hxx>

export module FatPound.Utility.Color;

import FatPound.Bit.Common;

import std;

export namespace fatpound::utility
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

export namespace fatpound::colors
{
    // Default: 140 + 1 Transparent colors
    // Default: Lime => 0x00FF00, Green => 0x008000, LimeGreen => 0x32CD32
    // Default: alpha channel value: 0xFF

#define Color utility::Color

    inline constexpr Color AliceBlue            = 0xF0F8FF;
    inline constexpr Color AntiqueWhite         = 0xFAEBD7;
    inline constexpr Color Aqua                 = 0x00FFFF;
    inline constexpr Color Aquamarine           = 0x7FFFD4;
    inline constexpr Color Azure                = 0xF0FFFF;
    inline constexpr Color Beige                = 0xF5F5DC;
    inline constexpr Color Bisque               = 0xFFE4C4;
    inline constexpr Color Black                = 0x000000;
    inline constexpr Color BlanchedAlmond       = 0xFFEBCD;
    inline constexpr Color Blue                 = 0x0000FF;
    inline constexpr Color BlueViolet           = 0x8A2BE2;
    inline constexpr Color Brown                = 0xA52A2A;
    inline constexpr Color BurlyWood            = 0xDEB887;
    inline constexpr Color CadetBlue            = 0x5F9EA0;
    inline constexpr Color Chartreuse           = 0x7FFF00;
    inline constexpr Color Chocolate            = 0xD2691E;
    inline constexpr Color Coral                = 0xFF7F50;
    inline constexpr Color CornflowerBlue       = 0x6495ED;
    inline constexpr Color Cornsilk             = 0xFFF8DC;
    inline constexpr Color Crimson              = 0xDC143C;
    inline constexpr Color Cyan                 = Aqua;
    inline constexpr Color DarkBlue             = 0x00008B;
    inline constexpr Color DarkCyan             = 0x008B8B;
    inline constexpr Color DarkGoldenrod        = 0xB8860B;
    inline constexpr Color DarkGray             = 0xA9A9A9;
    inline constexpr Color DarkGreen            = 0x006400;
    inline constexpr Color DarkKhaki            = 0xBDB76B;
    inline constexpr Color DarkMagenta          = 0x8B008B;
    inline constexpr Color DarkOliveGreen       = 0x556B2F;
    inline constexpr Color DarkOrange           = 0xFF8C00;
    inline constexpr Color DarkOrchid           = 0x9932CC;
    inline constexpr Color DarkRed              = 0x8B0000;
    inline constexpr Color DarkSalmon           = 0xE9967A;
    inline constexpr Color DarkSeaGreen         = 0x8FBC8F;
    inline constexpr Color DarkSlateBlue        = 0x483D8B;
    inline constexpr Color DarkSlateGray        = 0x2F4F4F;
    inline constexpr Color DarkTurquoise        = 0x00CED1;
    inline constexpr Color DarkViolet           = 0x9400D3;
    inline constexpr Color DeepPink             = 0xFF1493;
    inline constexpr Color DeepSkyBlue          = 0x00BFFF;
    inline constexpr Color DimGray              = 0x696969;
    inline constexpr Color DodgerBlue           = 0x1E90FF;
    inline constexpr Color Firebrick            = 0xB22222;
    inline constexpr Color FloralWhite          = 0xFFFAF0;
    inline constexpr Color ForestGreen          = 0x228B22;
    inline constexpr Color Fuchsia              = 0xFF00FF;
    inline constexpr Color Gainsboro            = 0xDCDCDC;
    inline constexpr Color GhostWhite           = 0xF8F8FF;
    inline constexpr Color Gold                 = 0xFFD700;
    inline constexpr Color Goldenrod            = 0xDAA520;
    inline constexpr Color Gray                 = 0x808080;
    inline constexpr Color Green                = 0x008000;
    inline constexpr Color GreenYellow          = 0xADFF2F;
    inline constexpr Color Honeydew             = 0xF0FFF0;
    inline constexpr Color HotPink              = 0xFF69B4;
    inline constexpr Color IndianRed            = 0xCD5C5C;
    inline constexpr Color Indigo               = 0x4B0082;
    inline constexpr Color Ivory                = 0xFFFFF0;
    inline constexpr Color Khaki                = 0xF0E68C;
    inline constexpr Color Lavender             = 0xE6E6FA;
    inline constexpr Color LavenderBlush        = 0xFFF0F5;
    inline constexpr Color LawnGreen            = 0x7CFC00;
    inline constexpr Color LemonChiffon         = 0xFFFACD;
    inline constexpr Color LightBlue            = 0xADD8E6;
    inline constexpr Color LightCoral           = 0xF08080;
    inline constexpr Color LightCyan            = 0xE0FFFF;
    inline constexpr Color LightGoldenrodYellow = 0xFAFAD2;
    inline constexpr Color LightGreen           = 0x90EE90;
    inline constexpr Color LightGray            = 0xD3D3D3;
    inline constexpr Color LightPink            = 0xFFB6C1;
    inline constexpr Color LightSalmon          = 0xFFA07A;
    inline constexpr Color LightSeaGreen        = 0x20B2AA;
    inline constexpr Color LightSkyBlue         = 0x87CEFA;
    inline constexpr Color LightSlateGray       = 0x778899;
    inline constexpr Color LightSteelBlue       = 0xB0C4DE;
    inline constexpr Color LightYellow          = 0xFFFFE0;
    inline constexpr Color Lime                 = 0x00FF00;
    inline constexpr Color LimeGreen            = 0x32CD32;
    inline constexpr Color Linen                = 0xFAF0E6;
    inline constexpr Color Magenta              = Fuchsia;
    inline constexpr Color Maroon               = 0x800000;
    inline constexpr Color MediumAquamarine     = 0x66CDAA;
    inline constexpr Color MediumBlue           = 0x0000CD;
    inline constexpr Color MediumOrchid         = 0xBA55D3;
    inline constexpr Color MediumPurple         = 0x9370DB;
    inline constexpr Color MediumSeaGreen       = 0x3CB371;
    inline constexpr Color MediumSlateBlue      = 0x7B68EE;
    inline constexpr Color MediumSpringGreen    = 0x00FA9A;
    inline constexpr Color MediumTurquoise      = 0x48D1CC;
    inline constexpr Color MediumVioletRed      = 0xC71585;
    inline constexpr Color MidnightBlue         = 0x191970;
    inline constexpr Color MintCream            = 0xF5FFFA;
    inline constexpr Color MistyRose            = 0xFFE4E1;
    inline constexpr Color Moccasin             = 0xFFE4B5;
    inline constexpr Color NavajoWhite          = 0xFFDEAD;
    inline constexpr Color Navy                 = 0x000080;
    inline constexpr Color OldLace              = 0xFDF5E6;
    inline constexpr Color Olive                = 0x808000;
    inline constexpr Color OliveDrab            = 0x6B8E23;
    inline constexpr Color Orange               = 0xFFA500;
    inline constexpr Color OrangeRed            = 0xFF4500;
    inline constexpr Color Orchid               = 0xDA70D6;
    inline constexpr Color PaleGoldenrod        = 0xEEE8AA;
    inline constexpr Color PaleGreen            = 0x98FB98;
    inline constexpr Color PaleTurquoise        = 0xAFEEEE;
    inline constexpr Color PaleVioletRed        = 0xDB7093;
    inline constexpr Color PapayaWhip           = 0xFFEFD5;
    inline constexpr Color PeachPuff            = 0xFFDAB9;
    inline constexpr Color Peru                 = 0xCD853F;
    inline constexpr Color Pink                 = 0xFFC0CB;
    inline constexpr Color Plum                 = 0xDDA0DD;
    inline constexpr Color PowderBlue           = 0xB0E0E6;
    inline constexpr Color Purple               = 0x800080;
    inline constexpr Color Red                  = 0xFF0000;
    inline constexpr Color RosyBrown            = 0xBC8F8F;
    inline constexpr Color RoyalBlue            = 0x4169E1;
    inline constexpr Color SaddleBrown          = 0x8B4513;
    inline constexpr Color Salmon               = 0xFA8072;
    inline constexpr Color SandyBrown           = 0xF4A460;
    inline constexpr Color SeaGreen             = 0x2E8B57;
    inline constexpr Color SeaShell             = 0xFFF5EE;
    inline constexpr Color Sienna               = 0xA0522D;
    inline constexpr Color Silver               = 0xC0C0C0;
    inline constexpr Color SkyBlue              = 0x87CEEB;
    inline constexpr Color SlateBlue            = 0x6A5ACD;
    inline constexpr Color SlateGray            = 0x708090;
    inline constexpr Color Snow                 = 0xFFFAFA;
    inline constexpr Color SpringGreen          = 0x00FF7F;
    inline constexpr Color SteelBlue            = 0x4682B4;
    inline constexpr Color Tan                  = 0xD2B48C;
    inline constexpr Color Teal                 = 0x008080;
    inline constexpr Color Thistle              = 0xD8BFD8;
    inline constexpr Color Tomato               = 0xFF6347;
    inline constexpr Color Turquoise            = 0x40E0D0;
    inline constexpr Color Violet               = 0xEE82EE;
    inline constexpr Color Wheat                = 0xF5DEB3;
    inline constexpr Color White                = 0xFFFFFF;
    inline constexpr Color WhiteSmoke           = 0xF5F5F5;
    inline constexpr Color Yellow               = 0xFFFF00;
    inline constexpr Color YellowGreen          = 0x9ACD32;
    /////////
    inline constexpr Color Transparent          = { White, 0U };

    namespace X11
    {
        inline constexpr auto GhostWhite            = Color{248, 248, 255};
        inline constexpr auto WhiteSmoke            = Color{245, 245, 245};
        inline constexpr auto Gainsboro             = Color{220, 220, 220};
        inline constexpr auto FloralWhite           = Color{255, 250, 240};
        inline constexpr auto OldLace               = Color{253, 245, 230};
        inline constexpr auto Linen                 = Color{250, 240, 230};
        inline constexpr auto PapayaWhip            = Color{255, 239, 213};
        inline constexpr auto BlanchedAlmond        = Color{255, 235, 205};
        inline constexpr auto Moccasin              = Color{255, 228, 181};
        inline constexpr auto MintCream             = Color{245, 255, 250};
        inline constexpr auto AliceBlue             = Color{240, 248, 255};
        inline constexpr auto Lavender              = Color{230, 230, 250};
        inline constexpr auto White                 = Color{255, 255, 255};
        inline constexpr auto Black                 = Color{  0,   0,   0};
        inline constexpr auto DimGray               = Color{105, 105, 105};
        inline constexpr auto DimGrey               = DimGray;
        inline constexpr auto LightSlateGray        = Color{119, 136, 153};
        inline constexpr auto LightSlateGrey        = LightSlateGray;
        inline constexpr auto Gray                  = Color{190, 190, 190};
        inline constexpr auto Grey                  = Gray;
        inline constexpr auto WebGray               = Color{128, 128, 128};
        inline constexpr auto WebGrey               = WebGray;
        inline constexpr auto LightGray             = Color{211, 211, 211};
        inline constexpr auto LightGrey             = LightGray;
        inline constexpr auto MidnightBlue          = Color{ 25,  25, 112};
        inline constexpr auto Navy                  = Color{  0,   0, 128};
        inline constexpr auto NavyBlue              = Navy;
        inline constexpr auto CornflowerBlue        = Color{100, 149, 237};
        inline constexpr auto DarkSlateBlue         = Color{ 72,  61, 139};
        inline constexpr auto MediumSlateBlue       = Color{123, 104, 238};
        inline constexpr auto LightSlateBlue        = Color{132, 112, 255};
        inline constexpr auto MediumBlue            = Color{  0,   0, 205};
        inline constexpr auto PowderBlue            = Color{176, 224, 230};
        inline constexpr auto DarkTurquoise         = Color{  0, 206, 209};
        inline constexpr auto MediumTurquoise       = Color{ 72, 209, 204};
        inline constexpr auto Cyan                  = Color{  0, 255, 255};
        inline constexpr auto Aqua                  = Cyan;
        inline constexpr auto MediumAquamarine      = Color{102, 205, 170};
        inline constexpr auto DarkGreen             = Color{  0, 100,   0};
        inline constexpr auto MediumSeaGreen        = Color{ 60, 179, 113};
        inline constexpr auto LightSeaGreen         = Color{ 32, 178, 170};
        inline constexpr auto LawnGreen             = Color{124, 252,   0};
        inline constexpr auto Green                 = Color{  0, 255,   0};
        inline constexpr auto Lime                  = Green;
        inline constexpr auto WebGreen              = Color{  0, 128,   0};
        inline constexpr auto MediumSpringGreen     = Color{  0, 250, 154};
        inline constexpr auto GreenYellow           = Color{173, 255,  47};
        inline constexpr auto LimeGreen             = Color{ 50, 205,  50};
        inline constexpr auto YellowGreen           = Color{154, 205,  50};
        inline constexpr auto ForestGreen           = Color{ 34, 139,  34};
        inline constexpr auto DarkKhaki             = Color{189, 183, 107};
        inline constexpr auto PaleGoldenrod         = Color{238, 232, 170};
        inline constexpr auto LightGoldenrodYellow  = Color{250, 250, 210};
        inline constexpr auto SaddleBrown           = Color{139,  69,  19};
        inline constexpr auto Peru                  = Color{205, 133,  63};
        inline constexpr auto Beige                 = Color{245, 245, 220};
        inline constexpr auto SandyBrown            = Color{244, 164,  96};
        inline constexpr auto DarkSalmon            = Color{233, 150, 122};
        inline constexpr auto LightCoral            = Color{240, 128, 128};
        inline constexpr auto DeepPink              = Color{255,  20, 147};
        inline constexpr auto WebMaroon             = Color{128,   0,   0};
        inline constexpr auto MediumVioletRed       = Color{199,  21, 133};
        inline constexpr auto Fuchsia               = Color{255,   0, 255};
        inline constexpr auto Violet                = Color{238, 130, 238};
        inline constexpr auto DarkViolet            = Color{148,   0, 211};
        inline constexpr auto BlueViolet            = Color{138,  43, 226};
        inline constexpr auto WebPurple             = Color{128,   0, 128};
        inline constexpr auto Snow                  = Color{255, 250, 250};
        inline constexpr auto Snow1                 = Snow;
        inline constexpr auto Snow2                 = Color{238, 233, 233};
        inline constexpr auto Snow3                 = Color{205, 201, 201};
        inline constexpr auto Snow4                 = Color{139, 137, 137};
        inline constexpr auto Seashell              = Color{255, 245, 238};
        inline constexpr auto Seashell1             = Seashell;
        inline constexpr auto Seashell2             = Color{238, 229, 222};
        inline constexpr auto Seashell3             = Color{205, 197, 191};
        inline constexpr auto Seashell4             = Color{139, 134, 130};
        inline constexpr auto AntiqueWhite          = Color{250, 235, 215};
        inline constexpr auto AntiqueWhite1         = Color{255, 239, 219};
        inline constexpr auto AntiqueWhite2         = Color{238, 223, 204};
        inline constexpr auto AntiqueWhite3         = Color{205, 192, 176};
        inline constexpr auto AntiqueWhite4         = Color{139, 131, 120};
        inline constexpr auto Bisque                = Color{255, 228, 196};
        inline constexpr auto Bisque1               = Bisque;
        inline constexpr auto Bisque2               = Color{238, 213, 183};
        inline constexpr auto Bisque3               = Color{205, 183, 158};
        inline constexpr auto Bisque4               = Color{139, 125, 107};
        inline constexpr auto PeachPuff             = Color{255, 218, 185};
        inline constexpr auto PeachPuff1            = PeachPuff;
        inline constexpr auto PeachPuff2            = Color{238, 203, 173};
        inline constexpr auto PeachPuff3            = Color{205, 175, 149};
        inline constexpr auto PeachPuff4            = Color{139, 119, 101};
        inline constexpr auto NavajoWhite           = Color{255, 222, 173};
        inline constexpr auto NavajoWhite1          = NavajoWhite;
        inline constexpr auto NavajoWhite2          = Color{238, 207, 161};
        inline constexpr auto NavajoWhite3          = Color{205, 179, 139};
        inline constexpr auto NavajoWhite4          = Color{139, 121,  94};
        inline constexpr auto LemonChiffon          = Color{255, 250, 205};
        inline constexpr auto LemonChiffon1         = LemonChiffon;
        inline constexpr auto LemonChiffon2         = Color{238, 233, 191};
        inline constexpr auto LemonChiffon3         = Color{205, 201, 165};
        inline constexpr auto LemonChiffon4         = Color{139, 137, 112};
        inline constexpr auto Cornsilk              = Color{255, 248, 220};
        inline constexpr auto Cornsilk1             = Cornsilk;
        inline constexpr auto Cornsilk2             = Color{238, 232, 205};
        inline constexpr auto Cornsilk3             = Color{205, 200, 177};
        inline constexpr auto Cornsilk4             = Color{139, 136, 120};
        inline constexpr auto Ivory                 = Color{255, 255, 240};
        inline constexpr auto Ivory1                = Ivory;
        inline constexpr auto Ivory2                = Color{238, 238, 224};
        inline constexpr auto Ivory3                = Color{205, 205, 193};
        inline constexpr auto Ivory4                = Color{139, 139, 131};
        inline constexpr auto Honeydew              = Color{240, 255, 240};
        inline constexpr auto Honeydew1             = Honeydew;
        inline constexpr auto Honeydew2             = Color{224, 238, 224};
        inline constexpr auto Honeydew3             = Color{193, 205, 193};
        inline constexpr auto Honeydew4             = Color{131, 139, 131};
        inline constexpr auto LavenderBlush         = Color{255, 240, 245};
        inline constexpr auto LavenderBlush1        = LavenderBlush;
        inline constexpr auto LavenderBlush2        = Color{238, 224, 229};
        inline constexpr auto LavenderBlush3        = Color{205, 193, 197};
        inline constexpr auto LavenderBlush4        = Color{139, 131, 134};
        inline constexpr auto MistyRose             = Color{255, 228, 225};
        inline constexpr auto MistyRose1            = MistyRose;
        inline constexpr auto MistyRose2            = Color{238, 213, 210};
        inline constexpr auto MistyRose3            = Color{205, 183, 181};
        inline constexpr auto MistyRose4            = Color{139, 125, 123};
        inline constexpr auto Azure                 = Color{240, 255, 255};
        inline constexpr auto Azure1                = Azure;
        inline constexpr auto Azure2                = Color{224, 238, 238};
        inline constexpr auto Azure3                = Color{193, 205, 205};
        inline constexpr auto Azure4                = Color{131, 139, 139};
        inline constexpr auto SlateBlue             = Color{106,  90, 205};
        inline constexpr auto SlateBlue1            = Color{131, 111, 255};
        inline constexpr auto SlateBlue2            = Color{122, 103, 238};
        inline constexpr auto SlateBlue3            = Color{105,  89, 205};
        inline constexpr auto SlateBlue4            = Color{ 71,  60, 139};
        inline constexpr auto RoyalBlue             = Color{ 65, 105, 225};
        inline constexpr auto RoyalBlue1            = Color{ 72, 118, 255};
        inline constexpr auto RoyalBlue2            = Color{ 67, 110, 238};
        inline constexpr auto RoyalBlue3            = Color{ 58,  95, 205};
        inline constexpr auto RoyalBlue4            = Color{ 39,  64, 139};
        inline constexpr auto Blue                  = Color{  0,   0, 255};
        inline constexpr auto Blue1                 = Blue;
        inline constexpr auto Blue2                 = Color{  0,   0, 238};
        inline constexpr auto Blue3                 = Color{  0,   0, 205};
        inline constexpr auto Blue4                 = Color{  0,   0, 139};
        inline constexpr auto DodgerBlue            = Color{ 30, 144, 255};
        inline constexpr auto DodgerBlue1           = DodgerBlue;
        inline constexpr auto DodgerBlue2           = Color{ 28, 134, 238};
        inline constexpr auto DodgerBlue3           = Color{ 24, 116, 205};
        inline constexpr auto DodgerBlue4           = Color{ 16,  78, 139};
        inline constexpr auto SteelBlue             = Color{ 70, 130, 180};
        inline constexpr auto SteelBlue1            = Color{ 99, 184, 255};
        inline constexpr auto SteelBlue2            = Color{ 92, 172, 238};
        inline constexpr auto SteelBlue3            = Color{ 79, 148, 205};
        inline constexpr auto SteelBlue4            = Color{ 54, 100, 139};
        inline constexpr auto DeepSkyBlue           = Color{  0, 191, 255};
        inline constexpr auto DeepSkyBlue1          = Color{  0, 191, 255};
        inline constexpr auto DeepSkyBlue2          = Color{  0, 178, 238};
        inline constexpr auto DeepSkyBlue3          = Color{  0, 154, 205};
        inline constexpr auto DeepSkyBlue4          = Color{  0, 104, 139};
        inline constexpr auto SkyBlue               = Color{135, 206, 235};
        inline constexpr auto SkyBlue1              = Color{135, 206, 255};
        inline constexpr auto SkyBlue2              = Color{126, 192, 238};
        inline constexpr auto SkyBlue3              = Color{108, 166, 205};
        inline constexpr auto SkyBlue4              = Color{ 74, 112, 139};
        inline constexpr auto LightSkyBlue          = Color{135, 206, 250};
        inline constexpr auto LightSkyBlue1         = Color{176, 226, 255};
        inline constexpr auto LightSkyBlue2         = Color{164, 211, 238};
        inline constexpr auto LightSkyBlue3         = Color{141, 182, 205};
        inline constexpr auto LightSkyBlue4         = Color{ 96, 123, 139};
        inline constexpr auto SlateGray             = Color{112, 128, 144};
        inline constexpr auto SlateGrey             = SlateGray;
        inline constexpr auto SlateGray1            = Color{198, 226, 255};
        inline constexpr auto SlateGray2            = Color{185, 211, 238};
        inline constexpr auto SlateGray3            = Color{159, 182, 205};
        inline constexpr auto SlateGray4            = Color{108, 123, 139};
        inline constexpr auto LightSteelBlue        = Color{176, 196, 222};
        inline constexpr auto LightSteelBlue1       = Color{202, 225, 255};
        inline constexpr auto LightSteelBlue2       = Color{188, 210, 238};
        inline constexpr auto LightSteelBlue3       = Color{162, 181, 205};
        inline constexpr auto LightSteelBlue4       = Color{110, 123, 139};
        inline constexpr auto LightBlue             = Color{173, 216, 230};
        inline constexpr auto LightBlue1            = Color{191, 239, 255};
        inline constexpr auto LightBlue2            = Color{178, 223, 238};
        inline constexpr auto LightBlue3            = Color{154, 192, 205};
        inline constexpr auto LightBlue4            = Color{104, 131, 139};
        inline constexpr auto LightCyan             = Color{224, 255, 255};
        inline constexpr auto LightCyan1            = LightCyan;
        inline constexpr auto LightCyan2            = Color{209, 238, 238};
        inline constexpr auto LightCyan3            = Color{180, 205, 205};
        inline constexpr auto LightCyan4            = Color{122, 139, 139};
        inline constexpr auto PaleTurquoise         = Color{175, 238, 238};
        inline constexpr auto PaleTurquoise1        = Color{187, 255, 255};
        inline constexpr auto PaleTurquoise2        = Color{174, 238, 238};
        inline constexpr auto PaleTurquoise3        = Color{150, 205, 205};
        inline constexpr auto PaleTurquoise4        = Color{102, 139, 139};
        inline constexpr auto CadetBlue             = Color{ 95, 158, 160};
        inline constexpr auto CadetBlue1            = Color{152, 245, 255};
        inline constexpr auto CadetBlue2            = Color{142, 229, 238};
        inline constexpr auto CadetBlue3            = Color{122, 197, 205};
        inline constexpr auto CadetBlue4            = Color{ 83, 134, 139};
        inline constexpr auto Turquoise             = Color{ 64, 224, 208};
        inline constexpr auto Turquoise1            = Color{  0, 245, 255};
        inline constexpr auto Turquoise2            = Color{  0, 229, 238};
        inline constexpr auto Turquoise3            = Color{  0, 197, 205};
        inline constexpr auto Turquoise4            = Color{  0, 134, 139};
        inline constexpr auto Cyan1                 = Color{  0, 255, 255};
        inline constexpr auto Cyan2                 = Color{  0, 238, 238};
        inline constexpr auto Cyan3                 = Color{  0, 205, 205};
        inline constexpr auto Cyan4                 = Color{  0, 139, 139};
        inline constexpr auto DarkSlateGray         = Color{ 47,  79,  79};
        inline constexpr auto DarkSlateGrey         = DarkSlateGray;
        inline constexpr auto DarkSlateGray1        = Color{151, 255, 255};
        inline constexpr auto DarkSlateGray2        = Color{141, 238, 238};
        inline constexpr auto DarkSlateGray3        = Color{121, 205, 205};
        inline constexpr auto DarkSlateGray4        = Color{ 82, 139, 139};
        inline constexpr auto Aquamarine            = Color{127, 255, 212};
        inline constexpr auto Aquamarine1           = Aquamarine;
        inline constexpr auto Aquamarine2           = Color{118, 238, 198};
        inline constexpr auto Aquamarine3           = Color{102, 205, 170};
        inline constexpr auto Aquamarine4           = Color{ 69, 139, 116};
        inline constexpr auto DarkSeaGreen          = Color{143, 188, 143};
        inline constexpr auto DarkSeaGreen1         = Color{193, 255, 193};
        inline constexpr auto DarkSeaGreen2         = Color{180, 238, 180};
        inline constexpr auto DarkSeaGreen3         = Color{155, 205, 155};
        inline constexpr auto DarkSeaGreen4         = Color{105, 139, 105};
        inline constexpr auto SeaGreen              = Color{ 46, 139,  87};
        inline constexpr auto SeaGreen1             = Color{ 84, 255, 159};
        inline constexpr auto SeaGreen2             = Color{ 78, 238, 148};
        inline constexpr auto SeaGreen3             = Color{ 67, 205, 128};
        inline constexpr auto SeaGreen4             = Color{ 46, 139,  87};
        inline constexpr auto PaleGreen             = Color{152, 251, 152};
        inline constexpr auto PaleGreen1            = Color{154, 255, 154};
        inline constexpr auto PaleGreen2            = Color{144, 238, 144};
        inline constexpr auto PaleGreen3            = Color{124, 205, 124};
        inline constexpr auto PaleGreen4            = Color{ 84, 139,  84};
        inline constexpr auto SpringGreen           = Color{  0, 255, 127};
        inline constexpr auto SpringGreen1          = SpringGreen;
        inline constexpr auto SpringGreen2          = Color{  0, 238, 118};
        inline constexpr auto SpringGreen3          = Color{  0, 205, 102};
        inline constexpr auto SpringGreen4          = Color{  0, 139,  69};
        inline constexpr auto Green1                = Green;
        inline constexpr auto Green2                = Color{  0, 238,   0};
        inline constexpr auto Green3                = Color{  0, 205,   0};
        inline constexpr auto Green4                = Color{  0, 139,   0};
        inline constexpr auto Chartreuse            = Color{127, 255,   0};
        inline constexpr auto Chartreuse1           = Chartreuse;
        inline constexpr auto Chartreuse2           = Color{118, 238,   0};
        inline constexpr auto Chartreuse3           = Color{102, 205,   0};
        inline constexpr auto Chartreuse4           = Color{ 69, 139,   0};
        inline constexpr auto OliveDrab             = Color{107, 142,  35};
        inline constexpr auto OliveDrab1            = Color{192, 255,  62};
        inline constexpr auto OliveDrab2            = Color{179, 238,  58};
        inline constexpr auto OliveDrab3            = Color{154, 205,  50};
        inline constexpr auto OliveDrab4            = Color{105, 139,  34};
        inline constexpr auto DarkOliveGreen        = Color{ 85, 107,  47};
        inline constexpr auto DarkOliveGreen1       = Color{202, 255, 112};
        inline constexpr auto DarkOliveGreen2       = Color{188, 238, 104};
        inline constexpr auto DarkOliveGreen3       = Color{162, 205,  90};
        inline constexpr auto DarkOliveGreen4       = Color{110, 139,  61};
        inline constexpr auto Khaki                 = Color{240, 230, 140};
        inline constexpr auto Khaki1                = Color{255, 246, 143};
        inline constexpr auto Khaki2                = Color{238, 230, 133};
        inline constexpr auto Khaki3                = Color{205, 198, 115};
        inline constexpr auto Khaki4                = Color{139, 134,  78};
        inline constexpr auto LightGoldenrod        = Color{238, 221, 130};
        inline constexpr auto LightGoldenrod1       = Color{255, 236, 139};
        inline constexpr auto LightGoldenrod2       = Color{238, 220, 130};
        inline constexpr auto LightGoldenrod3       = Color{205, 190, 112};
        inline constexpr auto LightGoldenrod4       = Color{139, 129,  76};
        inline constexpr auto LightYellow           = Color{255, 255, 224};
        inline constexpr auto LightYellow1          = LightYellow;
        inline constexpr auto LightYellow2          = Color{238, 238, 209};
        inline constexpr auto LightYellow3          = Color{205, 205, 180};
        inline constexpr auto LightYellow4          = Color{139, 139, 122};
        inline constexpr auto Yellow                = Color{255, 255,   0};
        inline constexpr auto Yellow1               = Yellow;
        inline constexpr auto Yellow2               = Color{238, 238,   0};
        inline constexpr auto Yellow3               = Color{205, 205,   0};
        inline constexpr auto Yellow4               = Color{139, 139,   0};
        inline constexpr auto Gold                  = Color{255, 215,   0};
        inline constexpr auto Gold1                 = Color{255, 215,   0};
        inline constexpr auto Gold2                 = Color{238, 201,   0};
        inline constexpr auto Gold3                 = Color{205, 173,   0};
        inline constexpr auto Gold4                 = Color{139, 117,   0};
        inline constexpr auto Goldenrod             = Color{218, 165,  32};
        inline constexpr auto Goldenrod1            = Color{255, 193,  37};
        inline constexpr auto Goldenrod2            = Color{238, 180,  34};
        inline constexpr auto Goldenrod3            = Color{205, 155,  29};
        inline constexpr auto Goldenrod4            = Color{139, 105,  20};
        inline constexpr auto DarkGoldenrod         = Color{184, 134,  11};
        inline constexpr auto DarkGoldenrod1        = Color{255, 185,  15};
        inline constexpr auto DarkGoldenrod2        = Color{238, 173,  14};
        inline constexpr auto DarkGoldenrod3        = Color{205, 149,  12};
        inline constexpr auto DarkGoldenrod4        = Color{139, 101,   8};
        inline constexpr auto RosyBrown             = Color{188, 143, 143};
        inline constexpr auto RosyBrown1            = Color{255, 193, 193};
        inline constexpr auto RosyBrown2            = Color{238, 180, 180};
        inline constexpr auto RosyBrown3            = Color{205, 155, 155};
        inline constexpr auto RosyBrown4            = Color{139, 105, 105};
        inline constexpr auto IndianRed             = Color{205,  92,  92};
        inline constexpr auto IndianRed1            = Color{255, 106, 106};
        inline constexpr auto IndianRed2            = Color{238,  99,  99};
        inline constexpr auto IndianRed3            = Color{205,  85,  85};
        inline constexpr auto IndianRed4            = Color{139,  58,  58};
        inline constexpr auto Sienna                = Color{160,  82,  45};
        inline constexpr auto Sienna1               = Color{255, 130,  71};
        inline constexpr auto Sienna2               = Color{238, 121,  66};
        inline constexpr auto Sienna3               = Color{205, 104,  57};
        inline constexpr auto Sienna4               = Color{139,  71,  38};
        inline constexpr auto Burlywood             = Color{222, 184, 135};
        inline constexpr auto Burlywood1            = Color{255, 211, 155};
        inline constexpr auto Burlywood2            = Color{238, 197, 145};
        inline constexpr auto Burlywood3            = Color{205, 170, 125};
        inline constexpr auto Burlywood4            = Color{139, 115,  85};
        inline constexpr auto Wheat                 = Color{245, 222, 179};
        inline constexpr auto Wheat1                = Color{255, 231, 186};
        inline constexpr auto Wheat2                = Color{238, 216, 174};
        inline constexpr auto Wheat3                = Color{205, 186, 150};
        inline constexpr auto Wheat4                = Color{139, 126, 102};
        inline constexpr auto Tan                   = Color{210, 180, 140};
        inline constexpr auto Tan1                  = Color{255, 165,  79};
        inline constexpr auto Tan2                  = Color{238, 154,  73};
        inline constexpr auto Tan3                  = Color{205, 133,  63};
        inline constexpr auto Tan4                  = Color{139,  90,  43};
        inline constexpr auto Chocolate             = Color{210, 105,  30};
        inline constexpr auto Chocolate1            = Color{255, 127,  36};
        inline constexpr auto Chocolate2            = Color{238, 118,  33};
        inline constexpr auto Chocolate3            = Color{205, 102,  29};
        inline constexpr auto Chocolate4            = Color{139,  69,  19};
        inline constexpr auto Firebrick             = Color{178,  34,  34};
        inline constexpr auto Firebrick1            = Color{255,  48,  48};
        inline constexpr auto Firebrick2            = Color{238,  44,  44};
        inline constexpr auto Firebrick3            = Color{205,  38,  38};
        inline constexpr auto Firebrick4            = Color{139,  26,  26};
        inline constexpr auto Brown                 = Color{165,  42,  42};
        inline constexpr auto Brown1                = Color{255,  64,  64};
        inline constexpr auto Brown2                = Color{238,  59,  59};
        inline constexpr auto Brown3                = Color{205,  51,  51};
        inline constexpr auto Brown4                = Color{139,  35,  35};
        inline constexpr auto Salmon                = Color{250, 128, 114};
        inline constexpr auto Salmon1               = Color{255, 140, 105};
        inline constexpr auto Salmon2               = Color{238, 130,  98};
        inline constexpr auto Salmon3               = Color{205, 112,  84};
        inline constexpr auto Salmon4               = Color{139,  76,  57};
        inline constexpr auto LightSalmon           = Color{255, 160, 122};
        inline constexpr auto LightSalmon1          = LightSalmon;
        inline constexpr auto LightSalmon2          = Color{238, 149, 114};
        inline constexpr auto LightSalmon3          = Color{205, 129,  98};
        inline constexpr auto LightSalmon4          = Color{139,  87,  66};
        inline constexpr auto Orange                = Color{255, 165,   0};
        inline constexpr auto Orange1               = Orange;
        inline constexpr auto Orange2               = Color{238, 154,   0};
        inline constexpr auto Orange3               = Color{205, 133,   0};
        inline constexpr auto Orange4               = Color{139,  90,   0};
        inline constexpr auto DarkOrange            = Color{255, 140,   0};
        inline constexpr auto DarkOrange1           = Color{255, 127,   0};
        inline constexpr auto DarkOrange2           = Color{238, 118,   0};
        inline constexpr auto DarkOrange3           = Color{205, 102,   0};
        inline constexpr auto DarkOrange4           = Color{139,  69,   0};
        inline constexpr auto Coral                 = Color{255, 127,  80};
        inline constexpr auto Coral1                = Color{255, 114,  86};
        inline constexpr auto Coral2                = Color{238, 106,  80};
        inline constexpr auto Coral3                = Color{205,  91,  69};
        inline constexpr auto Coral4                = Color{139,  62,  47};
        inline constexpr auto Tomato                = Color{255,  99,  71};
        inline constexpr auto Tomato1               = Tomato;
        inline constexpr auto Tomato2               = Color{238,  92,  66};
        inline constexpr auto Tomato3               = Color{205,  79,  57};
        inline constexpr auto Tomato4               = Color{139,  54,  38};
        inline constexpr auto OrangeRed             = Color{255,  69,   0};
        inline constexpr auto OrangeRed1            = OrangeRed;
        inline constexpr auto OrangeRed2            = Color{238,  64,   0};
        inline constexpr auto OrangeRed3            = Color{205,  55,   0};
        inline constexpr auto OrangeRed4            = Color{139,  37,   0};
        inline constexpr auto Red                   = Color{255,   0,   0};
        inline constexpr auto Red1                  = Red;
        inline constexpr auto Red2                  = Color{238,   0,   0};
        inline constexpr auto Red3                  = Color{205,   0,   0};
        inline constexpr auto Red4                  = Color{139,   0,   0};
        inline constexpr auto DeepPink1             = Color{255,  20, 147};
        inline constexpr auto DeepPink2             = Color{238,  18, 137};
        inline constexpr auto DeepPink3             = Color{205,  16, 118};
        inline constexpr auto DeepPink4             = Color{139,  10,  80};
        inline constexpr auto HotPink               = Color{255, 105, 180};
        inline constexpr auto HotPink1              = Color{255, 110, 180};
        inline constexpr auto HotPink2              = Color{238, 106, 167};
        inline constexpr auto HotPink3              = Color{205,  96, 144};
        inline constexpr auto HotPink4              = Color{139,  58,  98};
        inline constexpr auto Pink                  = Color{255, 192, 203};
        inline constexpr auto Pink1                 = Color{255, 181, 197};
        inline constexpr auto Pink2                 = Color{238, 169, 184};
        inline constexpr auto Pink3                 = Color{205, 145, 158};
        inline constexpr auto Pink4                 = Color{139,  99, 108};
        inline constexpr auto LightPink             = Color{255, 182, 193};
        inline constexpr auto LightPink1            = Color{255, 174, 185};
        inline constexpr auto LightPink2            = Color{238, 162, 173};
        inline constexpr auto LightPink3            = Color{205, 140, 149};
        inline constexpr auto LightPink4            = Color{139,  95, 101};
        inline constexpr auto PaleVioletRed         = Color{219, 112, 147};
        inline constexpr auto PaleVioletRed1        = Color{255, 130, 171};
        inline constexpr auto PaleVioletRed2        = Color{238, 121, 159};
        inline constexpr auto PaleVioletRed3        = Color{205, 104, 137};
        inline constexpr auto PaleVioletRed4        = Color{139,  71,  93};
        inline constexpr auto Maroon                = Color{176,  48,  96};
        inline constexpr auto Maroon1               = Color{255,  52, 179};
        inline constexpr auto Maroon2               = Color{238,  48, 167};
        inline constexpr auto Maroon3               = Color{205,  41, 144};
        inline constexpr auto Maroon4               = Color{139,  28,  98};
        inline constexpr auto VioletRed             = Color{208,  32, 144};
        inline constexpr auto VioletRed1            = Color{255,  62, 150};
        inline constexpr auto VioletRed2            = Color{238,  58, 140};
        inline constexpr auto VioletRed3            = Color{205,  50, 120};
        inline constexpr auto VioletRed4            = Color{139,  34,  82};
        inline constexpr auto Magenta               = Fuchsia;
        inline constexpr auto Magenta1              = Magenta;
        inline constexpr auto Magenta2              = Color{238,   0, 238};
        inline constexpr auto Magenta3              = Color{205,   0, 205};
        inline constexpr auto Magenta4              = Color{139,   0, 139};
        inline constexpr auto Orchid                = Color{218, 112, 214};
        inline constexpr auto Orchid1               = Color{255, 131, 250};
        inline constexpr auto Orchid2               = Color{238, 122, 233};
        inline constexpr auto Orchid3               = Color{205, 105, 201};
        inline constexpr auto Orchid4               = Color{139,  71, 137};
        inline constexpr auto Plum                  = Color{221, 160, 221};
        inline constexpr auto Plum1                 = Color{255, 187, 255};
        inline constexpr auto Plum2                 = Color{238, 174, 238};
        inline constexpr auto Plum3                 = Color{205, 150, 205};
        inline constexpr auto Plum4                 = Color{139, 102, 139};
        inline constexpr auto MediumOrchid          = Color{186,  85, 211};
        inline constexpr auto MediumOrchid1         = Color{224, 102, 255};
        inline constexpr auto MediumOrchid2         = Color{209,  95, 238};
        inline constexpr auto MediumOrchid3         = Color{180,  82, 205};
        inline constexpr auto MediumOrchid4         = Color{122,  55, 139};
        inline constexpr auto DarkOrchid            = Color{153,  50, 204};
        inline constexpr auto DarkOrchid1           = Color{191,  62, 255};
        inline constexpr auto DarkOrchid2           = Color{178,  58, 238};
        inline constexpr auto DarkOrchid3           = Color{154,  50, 205};
        inline constexpr auto DarkOrchid4           = Color{104,  34, 139};
        inline constexpr auto Purple                = Color{160,  32, 240};
        inline constexpr auto Purple1               = Color{155,  48, 255};
        inline constexpr auto Purple2               = Color{145,  44, 238};
        inline constexpr auto Purple3               = Color{125,  38, 205};
        inline constexpr auto Purple4               = Color{ 85,  26, 139};
        inline constexpr auto MediumPurple          = Color{147, 112, 219};
        inline constexpr auto MediumPurple1         = Color{171, 130, 255};
        inline constexpr auto MediumPurple2         = Color{159, 121, 238};
        inline constexpr auto MediumPurple3         = Color{137, 104, 205};
        inline constexpr auto MediumPurple4         = Color{ 93,  71, 139};
        inline constexpr auto Thistle               = Color{216, 191, 216};
        inline constexpr auto Thistle1              = White;
        inline constexpr auto Thistle2              = Color{238, 210, 238};
        inline constexpr auto Thistle3              = Color{205, 181, 205};
        inline constexpr auto Thistle4              = Color{139, 123, 139};
        inline constexpr auto Gray0                 = Black;
        inline constexpr auto Gray1                 = Color{  3,   3,   3};
        inline constexpr auto Gray2                 = Color{  5,   5,   5};
        inline constexpr auto Gray3                 = Color{  8,   8,   8};
        inline constexpr auto Gray4                 = Color{ 10,  10,  10};
        inline constexpr auto Gray5                 = Color{ 13,  13,  13};
        inline constexpr auto Gray6                 = Color{ 15,  15,  15};
        inline constexpr auto Gray7                 = Color{ 18,  18,  18};
        inline constexpr auto Gray8                 = Color{ 20,  20,  20};
        inline constexpr auto Gray9                 = Color{ 23,  23,  23};
        inline constexpr auto Gray10                = Color{ 26,  26,  26};
        inline constexpr auto Gray11                = Color{ 28,  28,  28};
        inline constexpr auto Gray12                = Color{ 31,  31,  31};
        inline constexpr auto Gray13                = Color{ 33,  33,  33};
        inline constexpr auto Gray14                = Color{ 36,  36,  36};
        inline constexpr auto Gray15                = Color{ 38,  38,  38};
        inline constexpr auto Gray16                = Color{ 41,  41,  41};
        inline constexpr auto Gray17                = Color{ 43,  43,  43};
        inline constexpr auto Gray18                = Color{ 46,  46,  46};
        inline constexpr auto Gray19                = Color{ 48,  48,  48};
        inline constexpr auto Gray20                = Color{ 51,  51,  51};
        inline constexpr auto Gray21                = Color{ 54,  54,  54};
        inline constexpr auto Gray22                = Color{ 56,  56,  56};
        inline constexpr auto Gray23                = Color{ 59,  59,  59};
        inline constexpr auto Gray24                = Color{ 61,  61,  61};
        inline constexpr auto Gray25                = Color{ 64,  64,  64};
        inline constexpr auto Gray26                = Color{ 66,  66,  66};
        inline constexpr auto Gray27                = Color{ 69,  69,  69};
        inline constexpr auto Gray28                = Color{ 71,  71,  71};
        inline constexpr auto Gray29                = Color{ 74,  74,  74};
        inline constexpr auto Gray30                = Color{ 77,  77,  77};
        inline constexpr auto Gray31                = Color{ 79,  79,  79};
        inline constexpr auto Gray32                = Color{ 82,  82,  82};
        inline constexpr auto Gray33                = Color{ 84,  84,  84};
        inline constexpr auto Gray34                = Color{ 87,  87,  87};
        inline constexpr auto Gray35                = Color{ 89,  89,  89};
        inline constexpr auto Gray36                = Color{ 92,  92,  92};
        inline constexpr auto Gray37                = Color{ 94,  94,  94};
        inline constexpr auto Gray38                = Color{ 97,  97,  97};
        inline constexpr auto Gray39                = Color{ 99,  99,  99};
        inline constexpr auto Gray40                = Color{102, 102, 102};
        inline constexpr auto Gray41                = Color{105, 105, 105};
        inline constexpr auto Gray42                = Color{107, 107, 107};
        inline constexpr auto Gray43                = Color{110, 110, 110};
        inline constexpr auto Gray44                = Color{112, 112, 112};
        inline constexpr auto Gray45                = Color{115, 115, 115};
        inline constexpr auto Gray46                = Color{117, 117, 117};
        inline constexpr auto Gray47                = Color{120, 120, 120};
        inline constexpr auto Gray48                = Color{122, 122, 122};
        inline constexpr auto Gray49                = Color{125, 125, 125};
        inline constexpr auto Gray50                = Color{127, 127, 127};
        inline constexpr auto Gray51                = Color{130, 130, 130};
        inline constexpr auto Gray52                = Color{133, 133, 133};
        inline constexpr auto Gray53                = Color{135, 135, 135};
        inline constexpr auto Gray54                = Color{138, 138, 138};
        inline constexpr auto Gray55                = Color{140, 140, 140};
        inline constexpr auto Gray56                = Color{143, 143, 143};
        inline constexpr auto Gray57                = Color{145, 145, 145};
        inline constexpr auto Gray58                = Color{148, 148, 148};
        inline constexpr auto Gray59                = Color{150, 150, 150};
        inline constexpr auto Gray60                = Color{153, 153, 153};
        inline constexpr auto Gray61                = Color{156, 156, 156};
        inline constexpr auto Gray62                = Color{158, 158, 158};
        inline constexpr auto Gray63                = Color{161, 161, 161};
        inline constexpr auto Gray64                = Color{163, 163, 163};
        inline constexpr auto Gray65                = Color{166, 166, 166};
        inline constexpr auto Gray66                = Color{168, 168, 168};
        inline constexpr auto Gray67                = Color{171, 171, 171};
        inline constexpr auto Gray68                = Color{173, 173, 173};
        inline constexpr auto Gray69                = Color{176, 176, 176};
        inline constexpr auto Gray70                = Color{179, 179, 179};
        inline constexpr auto Gray71                = Color{181, 181, 181};
        inline constexpr auto Gray72                = Color{184, 184, 184};
        inline constexpr auto Gray73                = Color{186, 186, 186};
        inline constexpr auto Gray74                = Color{189, 189, 189};
        inline constexpr auto Gray75                = Color{191, 191, 191};
        inline constexpr auto Gray76                = Color{194, 194, 194};
        inline constexpr auto Gray77                = Color{196, 196, 196};
        inline constexpr auto Gray78                = Color{199, 199, 199};
        inline constexpr auto Gray79                = Color{201, 201, 201};
        inline constexpr auto Gray80                = Color{204, 204, 204};
        inline constexpr auto Gray81                = Color{207, 207, 207};
        inline constexpr auto Gray82                = Color{209, 209, 209};
        inline constexpr auto Gray83                = Color{212, 212, 212};
        inline constexpr auto Gray84                = Color{214, 214, 214};
        inline constexpr auto Gray85                = Color{217, 217, 217};
        inline constexpr auto Gray86                = Color{219, 219, 219};
        inline constexpr auto Gray87                = Color{222, 222, 222};
        inline constexpr auto Gray88                = Color{224, 224, 224};
        inline constexpr auto Gray89                = Color{227, 227, 227};
        inline constexpr auto Gray90                = Color{229, 229, 229};
        inline constexpr auto Gray91                = Color{232, 232, 232};
        inline constexpr auto Gray92                = Color{235, 235, 235};
        inline constexpr auto Gray93                = Color{237, 237, 237};
        inline constexpr auto Gray94                = Color{240, 240, 240};
        inline constexpr auto Gray95                = Color{242, 242, 242};
        inline constexpr auto Gray96                = Color{245, 245, 245};
        inline constexpr auto Gray97                = Color{247, 247, 247};
        inline constexpr auto Gray98                = Color{250, 250, 250};
        inline constexpr auto Gray99                = Color{252, 252, 252};
        inline constexpr auto Gray100               = White;
        inline constexpr auto Grey0                 = Gray0;
        inline constexpr auto Grey1                 = Gray1;
        inline constexpr auto Grey2                 = Gray2;
        inline constexpr auto Grey3                 = Gray3;
        inline constexpr auto Grey4                 = Gray4;
        inline constexpr auto Grey5                 = Gray5;
        inline constexpr auto Grey6                 = Gray6;
        inline constexpr auto Grey7                 = Gray7;
        inline constexpr auto Grey8                 = Gray8;
        inline constexpr auto Grey9                 = Gray9;
        inline constexpr auto Grey10                = Gray10;
        inline constexpr auto Grey11                = Gray11;
        inline constexpr auto Grey12                = Gray12;
        inline constexpr auto Grey13                = Gray13;
        inline constexpr auto Grey14                = Gray14;
        inline constexpr auto Grey15                = Gray15;
        inline constexpr auto Grey16                = Gray16;
        inline constexpr auto Grey17                = Gray17;
        inline constexpr auto Grey18                = Gray18;
        inline constexpr auto Grey19                = Gray19;
        inline constexpr auto Grey20                = Gray20;
        inline constexpr auto Grey21                = Gray21;
        inline constexpr auto Grey22                = Gray22;
        inline constexpr auto Grey23                = Gray23;
        inline constexpr auto Grey24                = Gray24;
        inline constexpr auto Grey25                = Gray25;
        inline constexpr auto Grey26                = Gray26;
        inline constexpr auto Grey27                = Gray27;
        inline constexpr auto Grey28                = Gray28;
        inline constexpr auto Grey29                = Gray29;
        inline constexpr auto Grey30                = Gray30;
        inline constexpr auto Grey31                = Gray31;
        inline constexpr auto Grey32                = Gray32;
        inline constexpr auto Grey33                = Gray33;
        inline constexpr auto Grey34                = Gray34;
        inline constexpr auto Grey35                = Gray35;
        inline constexpr auto Grey36                = Gray36;
        inline constexpr auto Grey37                = Gray37;
        inline constexpr auto Grey38                = Gray38;
        inline constexpr auto Grey39                = Gray39;
        inline constexpr auto Grey40                = Gray40;
        inline constexpr auto Grey41                = Gray41;
        inline constexpr auto Grey42                = Gray42;
        inline constexpr auto Grey43                = Gray43;
        inline constexpr auto Grey44                = Gray44;
        inline constexpr auto Grey45                = Gray45;
        inline constexpr auto Grey46                = Gray46;
        inline constexpr auto Grey47                = Gray47;
        inline constexpr auto Grey48                = Gray48;
        inline constexpr auto Grey49                = Gray49;
        inline constexpr auto Grey50                = Gray50;
        inline constexpr auto Grey51                = Gray51;
        inline constexpr auto Grey52                = Gray52;
        inline constexpr auto Grey53                = Gray53;
        inline constexpr auto Grey54                = Gray54;
        inline constexpr auto Grey55                = Gray55;
        inline constexpr auto Grey56                = Gray56;
        inline constexpr auto Grey57                = Gray57;
        inline constexpr auto Grey58                = Gray58;
        inline constexpr auto Grey59                = Gray59;
        inline constexpr auto Grey60                = Gray60;
        inline constexpr auto Grey61                = Gray61;
        inline constexpr auto Grey62                = Gray62;
        inline constexpr auto Grey63                = Gray63;
        inline constexpr auto Grey64                = Gray64;
        inline constexpr auto Grey65                = Gray65;
        inline constexpr auto Grey66                = Gray66;
        inline constexpr auto Grey67                = Gray67;
        inline constexpr auto Grey68                = Gray68;
        inline constexpr auto Grey69                = Gray69;
        inline constexpr auto Grey70                = Gray70;
        inline constexpr auto Grey71                = Gray71;
        inline constexpr auto Grey72                = Gray72;
        inline constexpr auto Grey73                = Gray73;
        inline constexpr auto Grey74                = Gray74;
        inline constexpr auto Grey75                = Gray75;
        inline constexpr auto Grey76                = Gray76;
        inline constexpr auto Grey77                = Gray77;
        inline constexpr auto Grey78                = Gray78;
        inline constexpr auto Grey79                = Gray79;
        inline constexpr auto Grey80                = Gray80;
        inline constexpr auto Grey81                = Gray81;
        inline constexpr auto Grey82                = Gray82;
        inline constexpr auto Grey83                = Gray83;
        inline constexpr auto Grey84                = Gray84;
        inline constexpr auto Grey85                = Gray85;
        inline constexpr auto Grey86                = Gray86;
        inline constexpr auto Grey87                = Gray87;
        inline constexpr auto Grey88                = Gray88;
        inline constexpr auto Grey89                = Gray89;
        inline constexpr auto Grey90                = Gray90;
        inline constexpr auto Grey91                = Gray91;
        inline constexpr auto Grey92                = Gray92;
        inline constexpr auto Grey93                = Gray93;
        inline constexpr auto Grey94                = Gray94;
        inline constexpr auto Grey95                = Gray95;
        inline constexpr auto Grey96                = Gray96;
        inline constexpr auto Grey97                = Gray97;
        inline constexpr auto Grey98                = Gray98;
        inline constexpr auto Grey99                = Gray99;
        inline constexpr auto Grey100               = Gray100;
        inline constexpr auto DarkGray              = Color{169, 169, 169};
        inline constexpr auto DarkGrey              = DarkGray;
        inline constexpr auto DarkBlue              = Color{  0,   0, 139};
        inline constexpr auto DarkCyan              = Color{  0, 139, 139};
        inline constexpr auto DarkMagenta           = Color{139,   0, 139};
        inline constexpr auto DarkRed               = Color{139,   0,   0};
        inline constexpr auto LightGreen            = Color{144, 238, 144};
        inline constexpr auto Crimson               = Color{220,  20,  60};
        inline constexpr auto Indigo                = Color{ 75,   0, 130};
        inline constexpr auto Olive                 = Color{128, 128,   0};
        inline constexpr auto RebeccaPurple         = Color{102,  51, 153};
        inline constexpr auto Silver                = Color{192, 192, 192};
        inline constexpr auto Teal                  = Color{  0, 128, 128};
    }

    namespace SGI
    {
        inline constexpr Color Gray0                = 0x000000;
        inline constexpr Color Gray4                = 0xa0a0a0;
        inline constexpr Color Gray8                = 0x141414;
        inline constexpr Color Gray12               = 0x1e1e1e;
        inline constexpr Color Gray16               = 0x282828;
        inline constexpr Color Gray20               = 0x333333;
        inline constexpr Color Gray24               = 0x3d3d3d;
        inline constexpr Color Gray28               = 0x474747;
        inline constexpr Color Gray32               = 0x515151;
        inline constexpr Color Gray36               = 0x5b5b5b;
        inline constexpr Color Gray40               = 0x666666;
        inline constexpr Color Gray44               = 0x707070;
        inline constexpr Color Gray48               = 0x7a7a7a;
        inline constexpr Color Gray52               = 0x848484;
        inline constexpr Color Gray56               = 0x8e8e8e;
        inline constexpr Color Gray60               = 0x999999;
        inline constexpr Color Gray64               = 0xa3a3a3;
        inline constexpr Color Gray68               = 0xadadad;
        inline constexpr Color Gray72               = 0xb7b7b7;
        inline constexpr Color Gray76               = 0xc1c1c1;
        inline constexpr Color Gray80               = 0xcccccc;
        inline constexpr Color Gray84               = 0xd6d6d6;
        inline constexpr Color Gray88               = 0xe0e0e0;
        inline constexpr Color Gray92               = 0xeaeaea;
        inline constexpr Color Gray96               = 0xf4f4f4;
        inline constexpr Color Gray100              = 0xffffff;
        inline constexpr Color Grey0                = Gray0;
        inline constexpr Color Grey4                = Gray4;
        inline constexpr Color Grey8                = Gray8;
        inline constexpr Color Grey12               = Gray12;
        inline constexpr Color Grey16               = Gray16;
        inline constexpr Color Grey20               = Gray20;
        inline constexpr Color Grey24               = Gray24;
        inline constexpr Color Grey28               = Gray28;
        inline constexpr Color Grey32               = Gray32;
        inline constexpr Color Grey36               = Gray36;
        inline constexpr Color Grey40               = Gray40;
        inline constexpr Color Grey44               = Gray44;
        inline constexpr Color Grey48               = Gray48;
        inline constexpr Color Grey52               = Gray52;
        inline constexpr Color Grey56               = Gray56;
        inline constexpr Color Grey60               = Gray60;
        inline constexpr Color Grey64               = Gray64;
        inline constexpr Color Grey68               = Gray68;
        inline constexpr Color Grey72               = Gray72;
        inline constexpr Color Grey76               = Gray76;
        inline constexpr Color Grey80               = Gray80;
        inline constexpr Color Grey84               = Gray84;
        inline constexpr Color Grey88               = Gray88;
        inline constexpr Color Grey92               = Gray92;
        inline constexpr Color Grey96               = Gray96;
        inline constexpr Color Grey100              = Gray100;
        inline constexpr Color LightBlue            = 0x7d9ec0;
        inline constexpr Color DarkGray             = 0x555555;
        inline constexpr Color DarkGrey             = 0x555555;
        inline constexpr Color Salmon               = 0xc67171;
        inline constexpr Color Chartreuse           = 0x71c671;
        inline constexpr Color OliveDrab            = 0x8e8e38;
        inline constexpr Color SlateBlue            = 0x7171c6;
        inline constexpr Color Beet                 = 0x8e388e;
        inline constexpr Color Teal                 = 0x388e8e;
        inline constexpr Color LightGray            = 0xaaaaaa;
        inline constexpr Color LightGrey            = 0xaaaaaa;
        inline constexpr Color VeryLightGray        = 0xd6d6d6;
        inline constexpr Color VeryLightGrey        = 0xd6d6d6;
        inline constexpr Color MediumGray           = 0x848484;
        inline constexpr Color MediumGrey           = 0x848484;
        inline constexpr Color VeryDarkGray         = 0x282828;
        inline constexpr Color VeryDarkGrey         = 0x282828;
        inline constexpr Color BrightGray           = 0xc5c1aa;
        inline constexpr Color BrightGrey           = 0xc5c1aa;
        inline constexpr Color Indigo               = 0x4b0082;
        inline constexpr Color Indigo2              = 0x218868;
        inline constexpr Color Crimson              = 0xdc143c;
    }

#undef Color
}

// module : private;
