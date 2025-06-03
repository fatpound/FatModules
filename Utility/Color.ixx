module;

#include <FatMacros.hxx>

export module FatPound.Utility.Color;

import FatPound.Bit;

import std;

export namespace fatpound::utility
{
    class [[nodiscard]] Color final
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
        static_assert(requires { requires std::unsigned_integral<   Value_t>; },    "Value_t is not an Unsigned Integral type!");

        static_assert(sizeof(Value_t) >= (sizeof(ChannelA_t) + sizeof(ChannelR_t) + sizeof(ChannelG_t) + sizeof(ChannelB_t)), "Value_t size CANNOT be less than the sum of channel sizes!");


    public:
        static constexpr auto  BlueShift = 0ULL;
        static constexpr auto GreenShift =  sizeof(ChannelB_t) * 8U;
        static constexpr auto   RedShift = (sizeof(ChannelB_t) * 8U) + (sizeof(ChannelG_t) * 8U);
        static constexpr auto AlphaShift = (sizeof(ChannelB_t) * 8U) + (sizeof(ChannelG_t) * 8U) + (sizeof(ChannelR_t) * 8U);

        static constexpr auto AlphaMask = bit::OneMask<>(AlphaShift + (sizeof(ChannelA_t) * 8U - 1U), AlphaShift);
        static constexpr auto   RedMask = bit::OneMask<>(  RedShift + (sizeof(ChannelR_t) * 8U - 1U),   RedShift);
        static constexpr auto GreenMask = bit::OneMask<>(GreenShift + (sizeof(ChannelG_t) * 8U - 1U), GreenShift);
        static constexpr auto  BlueMask = bit::OneMask<>( BlueShift + (sizeof(ChannelB_t) * 8U - 1U),  BlueShift);


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
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetValue () const noexcept -> Value_t
        {
            return *this;
        }
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetA     () const noexcept -> std::uint8_t
        {
            return m_value_ >> AlphaShift;
        }
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetR     () const noexcept -> std::uint8_t
        {
            return (m_value_ >> RedShift) bitand 0xFFU;
        }
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetG     () const noexcept -> std::uint8_t
        {
            return (m_value_ >> GreenShift) bitand 0xFFU;
        }
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetB     () const noexcept -> std::uint8_t
        {
            return m_value_ bitand 0xFFU;
        }

        FAT_FORCEINLINE constexpr auto SetValue (const      Value_t& value) noexcept -> Color&
        {
            m_value_ = value;

            return *this;
        }
        FAT_FORCEINLINE constexpr auto SetA     (const std::uint8_t& alpha) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand AlphaMask) bitor (static_cast<std::uint32_t>(alpha) << AlphaShift);

            return *this;
        }
        FAT_FORCEINLINE constexpr auto SetR     (const std::uint8_t&   red) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand RedMask) bitor (static_cast<std::uint32_t>(red) << RedShift);

            return *this;
        }
        FAT_FORCEINLINE constexpr auto SetG     (const std::uint8_t& green) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand GreenMask) bitor (static_cast<std::uint32_t>(green) << GreenShift);

            return *this;
        }
        FAT_FORCEINLINE constexpr auto SetB     (const std::uint8_t&  blue) noexcept -> Color&
        {
            m_value_ = (m_value_ bitand BlueMask) bitor (static_cast<std::uint32_t>(blue));

            return *this;
        }

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4686)
#if __cplusplus > 202400L
        constexpr
#endif
#endif
        [[nodiscard]] auto GetString(const std::string& prefix, const bool& withAlpha) const -> std::string
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
        Value_t m_value_ = std::numeric_limits<Value_t>::max();
    };
}

export namespace fatpound::colors
{
    // NOLINTBEGIN(google-build-using-namespace)
    using namespace utility;
    // NOLINTEND(google-build-using-namespace)

    // This namespace uses Microsoft-style colors by default.

    inline namespace Microsoft
    {
        // Count: 140+1 (Direct2D and GDI+)
        // Lime => 0x00FF00, Green => 0x008000, LimeGreen => 0x32CD32
        // 
        // default alpha channel value: 0xFF

        constexpr Color AliceBlue            = 0xF0F8FF;
        constexpr Color AntiqueWhite         = 0xFAEBD7;
        constexpr Color Aqua                 = 0x00FFFF;
        constexpr Color Aquamarine           = 0x7FFFD4;
        constexpr Color Azure                = 0xF0FFFF;
        constexpr Color Beige                = 0xF5F5DC;
        constexpr Color Bisque               = 0xFFE4C4;
        constexpr Color Black                = 0x000000;
        constexpr Color BlanchedAlmond       = 0xFFEBCD;
        constexpr Color Blue                 = 0x0000FF;
        constexpr Color BlueViolet           = 0x8A2BE2;
        constexpr Color Brown                = 0xA52A2A;
        constexpr Color BurlyWood            = 0xDEB887;
        constexpr Color CadetBlue            = 0x5F9EA0;
        constexpr Color Chartreuse           = 0x7FFF00;
        constexpr Color Chocolate            = 0xD2691E;
        constexpr Color Coral                = 0xFF7F50;
        constexpr Color CornflowerBlue       = 0x6495ED;
        constexpr Color Cornsilk             = 0xFFF8DC;
        constexpr Color Crimson              = 0xDC143C;
        constexpr Color Cyan                 = Aqua;
        constexpr Color DarkBlue             = 0x00008B;
        constexpr Color DarkCyan             = 0x008B8B;
        constexpr Color DarkGoldenrod        = 0xB8860B;
        constexpr Color DarkGray             = 0xA9A9A9;
        constexpr Color DarkGreen            = 0x006400;
        constexpr Color DarkKhaki            = 0xBDB76B;
        constexpr Color DarkMagenta          = 0x8B008B;
        constexpr Color DarkOliveGreen       = 0x556B2F;
        constexpr Color DarkOrange           = 0xFF8C00;
        constexpr Color DarkOrchid           = 0x9932CC;
        constexpr Color DarkRed              = 0x8B0000;
        constexpr Color DarkSalmon           = 0xE9967A;
        constexpr Color DarkSeaGreen         = 0x8FBC8F;
        constexpr Color DarkSlateBlue        = 0x483D8B;
        constexpr Color DarkSlateGray        = 0x2F4F4F;
        constexpr Color DarkTurquoise        = 0x00CED1;
        constexpr Color DarkViolet           = 0x9400D3;
        constexpr Color DeepPink             = 0xFF1493;
        constexpr Color DeepSkyBlue          = 0x00BFFF;
        constexpr Color DimGray              = 0x696969;
        constexpr Color DodgerBlue           = 0x1E90FF;
        constexpr Color Firebrick            = 0xB22222;
        constexpr Color FloralWhite          = 0xFFFAF0;
        constexpr Color ForestGreen          = 0x228B22;
        constexpr Color Fuchsia              = 0xFF00FF;
        constexpr Color Gainsboro            = 0xDCDCDC;
        constexpr Color GhostWhite           = 0xF8F8FF;
        constexpr Color Gold                 = 0xFFD700;
        constexpr Color Goldenrod            = 0xDAA520;
        constexpr Color Gray                 = 0x808080;
        constexpr Color Green                = 0x008000;
        constexpr Color GreenYellow          = 0xADFF2F;
        constexpr Color Honeydew             = 0xF0FFF0;
        constexpr Color HotPink              = 0xFF69B4;
        constexpr Color IndianRed            = 0xCD5C5C;
        constexpr Color Indigo               = 0x4B0082;
        constexpr Color Ivory                = 0xFFFFF0;
        constexpr Color Khaki                = 0xF0E68C;
        constexpr Color Lavender             = 0xE6E6FA;
        constexpr Color LavenderBlush        = 0xFFF0F5;
        constexpr Color LawnGreen            = 0x7CFC00;
        constexpr Color LemonChiffon         = 0xFFFACD;
        constexpr Color LightBlue            = 0xADD8E6;
        constexpr Color LightCoral           = 0xF08080;
        constexpr Color LightCyan            = 0xE0FFFF;
        constexpr Color LightGoldenrodYellow = 0xFAFAD2;
        constexpr Color LightGreen           = 0x90EE90;
        constexpr Color LightGray            = 0xD3D3D3;
        constexpr Color LightPink            = 0xFFB6C1;
        constexpr Color LightSalmon          = 0xFFA07A;
        constexpr Color LightSeaGreen        = 0x20B2AA;
        constexpr Color LightSkyBlue         = 0x87CEFA;
        constexpr Color LightSlateGray       = 0x778899;
        constexpr Color LightSteelBlue       = 0xB0C4DE;
        constexpr Color LightYellow          = 0xFFFFE0;
        constexpr Color Lime                 = 0x00FF00;
        constexpr Color LimeGreen            = 0x32CD32;
        constexpr Color Linen                = 0xFAF0E6;
        constexpr Color Magenta              = Fuchsia;
        constexpr Color Maroon               = 0x800000;
        constexpr Color MediumAquamarine     = 0x66CDAA;
        constexpr Color MediumBlue           = 0x0000CD;
        constexpr Color MediumOrchid         = 0xBA55D3;
        constexpr Color MediumPurple         = 0x9370DB;
        constexpr Color MediumSeaGreen       = 0x3CB371;
        constexpr Color MediumSlateBlue      = 0x7B68EE;
        constexpr Color MediumSpringGreen    = 0x00FA9A;
        constexpr Color MediumTurquoise      = 0x48D1CC;
        constexpr Color MediumVioletRed      = 0xC71585;
        constexpr Color MidnightBlue         = 0x191970;
        constexpr Color MintCream            = 0xF5FFFA;
        constexpr Color MistyRose            = 0xFFE4E1;
        constexpr Color Moccasin             = 0xFFE4B5;
        constexpr Color NavajoWhite          = 0xFFDEAD;
        constexpr Color Navy                 = 0x000080;
        constexpr Color OldLace              = 0xFDF5E6;
        constexpr Color Olive                = 0x808000;
        constexpr Color OliveDrab            = 0x6B8E23;
        constexpr Color Orange               = 0xFFA500;
        constexpr Color OrangeRed            = 0xFF4500;
        constexpr Color Orchid               = 0xDA70D6;
        constexpr Color PaleGoldenrod        = 0xEEE8AA;
        constexpr Color PaleGreen            = 0x98FB98;
        constexpr Color PaleTurquoise        = 0xAFEEEE;
        constexpr Color PaleVioletRed        = 0xDB7093;
        constexpr Color PapayaWhip           = 0xFFEFD5;
        constexpr Color PeachPuff            = 0xFFDAB9;
        constexpr Color Peru                 = 0xCD853F;
        constexpr Color Pink                 = 0xFFC0CB;
        constexpr Color Plum                 = 0xDDA0DD;
        constexpr Color PowderBlue           = 0xB0E0E6;
        constexpr Color Purple               = 0x800080;
        constexpr Color Red                  = 0xFF0000;
        constexpr Color RosyBrown            = 0xBC8F8F;
        constexpr Color RoyalBlue            = 0x4169E1;
        constexpr Color SaddleBrown          = 0x8B4513;
        constexpr Color Salmon               = 0xFA8072;
        constexpr Color SandyBrown           = 0xF4A460;
        constexpr Color SeaGreen             = 0x2E8B57;
        constexpr Color SeaShell             = 0xFFF5EE;
        constexpr Color Sienna               = 0xA0522D;
        constexpr Color Silver               = 0xC0C0C0;
        constexpr Color SkyBlue              = 0x87CEEB;
        constexpr Color SlateBlue            = 0x6A5ACD;
        constexpr Color SlateGray            = 0x708090;
        constexpr Color Snow                 = 0xFFFAFA;
        constexpr Color SpringGreen          = 0x00FF7F;
        constexpr Color SteelBlue            = 0x4682B4;
        constexpr Color Tan                  = 0xD2B48C;
        constexpr Color Teal                 = 0x008080;
        constexpr Color Thistle              = 0xD8BFD8;
        constexpr Color Tomato               = 0xFF6347;
        constexpr Color Turquoise            = 0x40E0D0;
        constexpr Color Violet               = 0xEE82EE;
        constexpr Color Wheat                = 0xF5DEB3;
        constexpr Color White                = 0xFFFFFF;
        constexpr Color WhiteSmoke           = 0xF5F5F5;
        constexpr Color Yellow               = 0xFFFF00;
        constexpr Color YellowGreen          = 0x9ACD32;
        /////////
        constexpr Color Transparent          = { White, 0U };
    }

    namespace X11
    {
        constexpr auto GhostWhite              = Color{248, 248, 255};
        constexpr auto WhiteSmoke              = Color{245, 245, 245};
        constexpr auto Gainsboro               = Color{220, 220, 220};
        constexpr auto FloralWhite             = Color{255, 250, 240};
        constexpr auto OldLace                 = Color{253, 245, 230};
        constexpr auto Linen                   = Color{250, 240, 230};
        constexpr auto PapayaWhip              = Color{255, 239, 213};
        constexpr auto BlanchedAlmond          = Color{255, 235, 205};
        constexpr auto Moccasin                = Color{255, 228, 181};
        constexpr auto MintCream               = Color{245, 255, 250};
        constexpr auto AliceBlue               = Color{240, 248, 255};
        constexpr auto Lavender                = Color{230, 230, 250};
        constexpr auto White                   = Color{255, 255, 255};
        constexpr auto Black                   = Color{  0,   0,   0};
        constexpr auto DimGray                 = Color{105, 105, 105};
        constexpr auto DimGrey                 = DimGray;
        constexpr auto LightSlateGray          = Color{119, 136, 153};
        constexpr auto LightSlateGrey          = LightSlateGray;
        constexpr auto Gray                    = Color{190, 190, 190};
        constexpr auto Grey                    = Gray;
        constexpr auto WebGray                 = Color{128, 128, 128};
        constexpr auto WebGrey                 = WebGray;
        constexpr auto LightGray               = Color{211, 211, 211};
        constexpr auto LightGrey               = LightGray;
        constexpr auto MidnightBlue            = Color{ 25,  25, 112};
        constexpr auto Navy                    = Color{  0,   0, 128};
        constexpr auto NavyBlue                = Navy;
        constexpr auto CornflowerBlue          = Color{100, 149, 237};
        constexpr auto DarkSlateBlue           = Color{ 72,  61, 139};
        constexpr auto MediumSlateBlue         = Color{123, 104, 238};
        constexpr auto LightSlateBlue          = Color{132, 112, 255};
        constexpr auto MediumBlue              = Color{  0,   0, 205};
        constexpr auto PowderBlue              = Color{176, 224, 230};
        constexpr auto DarkTurquoise           = Color{  0, 206, 209};
        constexpr auto MediumTurquoise         = Color{ 72, 209, 204};
        constexpr auto Cyan                    = Color{  0, 255, 255};
        constexpr auto Aqua                    = Cyan;
        constexpr auto MediumAquamarine        = Color{102, 205, 170};
        constexpr auto DarkGreen               = Color{  0, 100,   0};
        constexpr auto MediumSeaGreen          = Color{ 60, 179, 113};
        constexpr auto LightSeaGreen           = Color{ 32, 178, 170};
        constexpr auto LawnGreen               = Color{124, 252,   0};
        constexpr auto Green                   = Color{  0, 255,   0};
        constexpr auto Lime                    = Green;
        constexpr auto WebGreen                = Color{  0, 128,   0};
        constexpr auto MediumSpringGreen       = Color{  0, 250, 154};
        constexpr auto GreenYellow             = Color{173, 255,  47};
        constexpr auto LimeGreen               = Color{ 50, 205,  50};
        constexpr auto YellowGreen             = Color{154, 205,  50};
        constexpr auto ForestGreen             = Color{ 34, 139,  34};
        constexpr auto DarkKhaki               = Color{189, 183, 107};
        constexpr auto PaleGoldenrod           = Color{238, 232, 170};
        constexpr auto LightGoldenrodYellow    = Color{250, 250, 210};
        constexpr auto SaddleBrown             = Color{139,  69,  19};
        constexpr auto Peru                    = Color{205, 133,  63};
        constexpr auto Beige                   = Color{245, 245, 220};
        constexpr auto SandyBrown              = Color{244, 164,  96};
        constexpr auto DarkSalmon              = Color{233, 150, 122};
        constexpr auto LightCoral              = Color{240, 128, 128};
        constexpr auto DeepPink                = Color{255,  20, 147};
        constexpr auto WebMaroon               = Color{128,   0,   0};
        constexpr auto MediumVioletRed         = Color{199,  21, 133};
        constexpr auto Fuchsia                 = Color{255,   0, 255};
        constexpr auto Violet                  = Color{238, 130, 238};
        constexpr auto DarkViolet              = Color{148,   0, 211};
        constexpr auto BlueViolet              = Color{138,  43, 226};
        constexpr auto WebPurple               = Color{128,   0, 128};
        constexpr auto Snow                    = Color{255, 250, 250};
        constexpr auto Snow1                   = Snow;
        constexpr auto Snow2                   = Color{238, 233, 233};
        constexpr auto Snow3                   = Color{205, 201, 201};
        constexpr auto Snow4                   = Color{139, 137, 137};
        constexpr auto Seashell                = Color{255, 245, 238};
        constexpr auto Seashell1               = Seashell;
        constexpr auto Seashell2               = Color{238, 229, 222};
        constexpr auto Seashell3               = Color{205, 197, 191};
        constexpr auto Seashell4               = Color{139, 134, 130};
        constexpr auto AntiqueWhite            = Color{250, 235, 215};
        constexpr auto AntiqueWhite1           = Color{255, 239, 219};
        constexpr auto AntiqueWhite2           = Color{238, 223, 204};
        constexpr auto AntiqueWhite3           = Color{205, 192, 176};
        constexpr auto AntiqueWhite4           = Color{139, 131, 120};
        constexpr auto Bisque                  = Color{255, 228, 196};
        constexpr auto Bisque1                 = Bisque;
        constexpr auto Bisque2                 = Color{238, 213, 183};
        constexpr auto Bisque3                 = Color{205, 183, 158};
        constexpr auto Bisque4                 = Color{139, 125, 107};
        constexpr auto PeachPuff               = Color{255, 218, 185};
        constexpr auto PeachPuff1              = PeachPuff;
        constexpr auto PeachPuff2              = Color{238, 203, 173};
        constexpr auto PeachPuff3              = Color{205, 175, 149};
        constexpr auto PeachPuff4              = Color{139, 119, 101};
        constexpr auto NavajoWhite             = Color{255, 222, 173};
        constexpr auto NavajoWhite1            = NavajoWhite;
        constexpr auto NavajoWhite2            = Color{238, 207, 161};
        constexpr auto NavajoWhite3            = Color{205, 179, 139};
        constexpr auto NavajoWhite4            = Color{139, 121,  94};
        constexpr auto LemonChiffon            = Color{255, 250, 205};
        constexpr auto LemonChiffon1           = LemonChiffon;
        constexpr auto LemonChiffon2           = Color{238, 233, 191};
        constexpr auto LemonChiffon3           = Color{205, 201, 165};
        constexpr auto LemonChiffon4           = Color{139, 137, 112};
        constexpr auto Cornsilk                = Color{255, 248, 220};
        constexpr auto Cornsilk1               = Cornsilk;
        constexpr auto Cornsilk2               = Color{238, 232, 205};
        constexpr auto Cornsilk3               = Color{205, 200, 177};
        constexpr auto Cornsilk4               = Color{139, 136, 120};
        constexpr auto Ivory                   = Color{255, 255, 240};
        constexpr auto Ivory1                  = Ivory;
        constexpr auto Ivory2                  = Color{238, 238, 224};
        constexpr auto Ivory3                  = Color{205, 205, 193};
        constexpr auto Ivory4                  = Color{139, 139, 131};
        constexpr auto Honeydew                = Color{240, 255, 240};
        constexpr auto Honeydew1               = Honeydew;
        constexpr auto Honeydew2               = Color{224, 238, 224};
        constexpr auto Honeydew3               = Color{193, 205, 193};
        constexpr auto Honeydew4               = Color{131, 139, 131};
        constexpr auto LavenderBlush           = Color{255, 240, 245};
        constexpr auto LavenderBlush1          = LavenderBlush;
        constexpr auto LavenderBlush2          = Color{238, 224, 229};
        constexpr auto LavenderBlush3          = Color{205, 193, 197};
        constexpr auto LavenderBlush4          = Color{139, 131, 134};
        constexpr auto MistyRose               = Color{255, 228, 225};
        constexpr auto MistyRose1              = MistyRose;
        constexpr auto MistyRose2              = Color{238, 213, 210};
        constexpr auto MistyRose3              = Color{205, 183, 181};
        constexpr auto MistyRose4              = Color{139, 125, 123};
        constexpr auto Azure                   = Color{240, 255, 255};
        constexpr auto Azure1                  = Azure;
        constexpr auto Azure2                  = Color{224, 238, 238};
        constexpr auto Azure3                  = Color{193, 205, 205};
        constexpr auto Azure4                  = Color{131, 139, 139};
        constexpr auto SlateBlue               = Color{106,  90, 205};
        constexpr auto SlateBlue1              = Color{131, 111, 255};
        constexpr auto SlateBlue2              = Color{122, 103, 238};
        constexpr auto SlateBlue3              = Color{105,  89, 205};
        constexpr auto SlateBlue4              = Color{ 71,  60, 139};
        constexpr auto RoyalBlue               = Color{ 65, 105, 225};
        constexpr auto RoyalBlue1              = Color{ 72, 118, 255};
        constexpr auto RoyalBlue2              = Color{ 67, 110, 238};
        constexpr auto RoyalBlue3              = Color{ 58,  95, 205};
        constexpr auto RoyalBlue4              = Color{ 39,  64, 139};
        constexpr auto Blue                    = Color{  0,   0, 255};
        constexpr auto Blue1                   = Blue;
        constexpr auto Blue2                   = Color{  0,   0, 238};
        constexpr auto Blue3                   = Color{  0,   0, 205};
        constexpr auto Blue4                   = Color{  0,   0, 139};
        constexpr auto DodgerBlue              = Color{ 30, 144, 255};
        constexpr auto DodgerBlue1             = DodgerBlue;
        constexpr auto DodgerBlue2             = Color{ 28, 134, 238};
        constexpr auto DodgerBlue3             = Color{ 24, 116, 205};
        constexpr auto DodgerBlue4             = Color{ 16,  78, 139};
        constexpr auto SteelBlue               = Color{ 70, 130, 180};
        constexpr auto SteelBlue1              = Color{ 99, 184, 255};
        constexpr auto SteelBlue2              = Color{ 92, 172, 238};
        constexpr auto SteelBlue3              = Color{ 79, 148, 205};
        constexpr auto SteelBlue4              = Color{ 54, 100, 139};
        constexpr auto DeepSkyBlue             = Color{  0, 191, 255};
        constexpr auto DeepSkyBlue1            = Color{  0, 191, 255};
        constexpr auto DeepSkyBlue2            = Color{  0, 178, 238};
        constexpr auto DeepSkyBlue3            = Color{  0, 154, 205};
        constexpr auto DeepSkyBlue4            = Color{  0, 104, 139};
        constexpr auto SkyBlue                 = Color{135, 206, 235};
        constexpr auto SkyBlue1                = Color{135, 206, 255};
        constexpr auto SkyBlue2                = Color{126, 192, 238};
        constexpr auto SkyBlue3                = Color{108, 166, 205};
        constexpr auto SkyBlue4                = Color{ 74, 112, 139};
        constexpr auto LightSkyBlue            = Color{135, 206, 250};
        constexpr auto LightSkyBlue1           = Color{176, 226, 255};
        constexpr auto LightSkyBlue2           = Color{164, 211, 238};
        constexpr auto LightSkyBlue3           = Color{141, 182, 205};
        constexpr auto LightSkyBlue4           = Color{ 96, 123, 139};
        constexpr auto SlateGray               = Color{112, 128, 144};
        constexpr auto SlateGrey               = SlateGray;
        constexpr auto SlateGray1              = Color{198, 226, 255};
        constexpr auto SlateGray2              = Color{185, 211, 238};
        constexpr auto SlateGray3              = Color{159, 182, 205};
        constexpr auto SlateGray4              = Color{108, 123, 139};
        constexpr auto LightSteelBlue          = Color{176, 196, 222};
        constexpr auto LightSteelBlue1         = Color{202, 225, 255};
        constexpr auto LightSteelBlue2         = Color{188, 210, 238};
        constexpr auto LightSteelBlue3         = Color{162, 181, 205};
        constexpr auto LightSteelBlue4         = Color{110, 123, 139};
        constexpr auto LightBlue               = Color{173, 216, 230};
        constexpr auto LightBlue1              = Color{191, 239, 255};
        constexpr auto LightBlue2              = Color{178, 223, 238};
        constexpr auto LightBlue3              = Color{154, 192, 205};
        constexpr auto LightBlue4              = Color{104, 131, 139};
        constexpr auto LightCyan               = Color{224, 255, 255};
        constexpr auto LightCyan1              = LightCyan;
        constexpr auto LightCyan2              = Color{209, 238, 238};
        constexpr auto LightCyan3              = Color{180, 205, 205};
        constexpr auto LightCyan4              = Color{122, 139, 139};
        constexpr auto PaleTurquoise           = Color{175, 238, 238};
        constexpr auto PaleTurquoise1          = Color{187, 255, 255};
        constexpr auto PaleTurquoise2          = Color{174, 238, 238};
        constexpr auto PaleTurquoise3          = Color{150, 205, 205};
        constexpr auto PaleTurquoise4          = Color{102, 139, 139};
        constexpr auto CadetBlue               = Color{ 95, 158, 160};
        constexpr auto CadetBlue1              = Color{152, 245, 255};
        constexpr auto CadetBlue2              = Color{142, 229, 238};
        constexpr auto CadetBlue3              = Color{122, 197, 205};
        constexpr auto CadetBlue4              = Color{ 83, 134, 139};
        constexpr auto Turquoise               = Color{ 64, 224, 208};
        constexpr auto Turquoise1              = Color{  0, 245, 255};
        constexpr auto Turquoise2              = Color{  0, 229, 238};
        constexpr auto Turquoise3              = Color{  0, 197, 205};
        constexpr auto Turquoise4              = Color{  0, 134, 139};
        constexpr auto Cyan1                   = Color{  0, 255, 255};
        constexpr auto Cyan2                   = Color{  0, 238, 238};
        constexpr auto Cyan3                   = Color{  0, 205, 205};
        constexpr auto Cyan4                   = Color{  0, 139, 139};
        constexpr auto DarkSlateGray           = Color{ 47,  79,  79};
        constexpr auto DarkSlateGrey           = DarkSlateGray;
        constexpr auto DarkSlateGray1          = Color{151, 255, 255};
        constexpr auto DarkSlateGray2          = Color{141, 238, 238};
        constexpr auto DarkSlateGray3          = Color{121, 205, 205};
        constexpr auto DarkSlateGray4          = Color{ 82, 139, 139};
        constexpr auto Aquamarine              = Color{127, 255, 212};
        constexpr auto Aquamarine1             = Aquamarine;
        constexpr auto Aquamarine2             = Color{118, 238, 198};
        constexpr auto Aquamarine3             = Color{102, 205, 170};
        constexpr auto Aquamarine4             = Color{ 69, 139, 116};
        constexpr auto DarkSeaGreen            = Color{143, 188, 143};
        constexpr auto DarkSeaGreen1           = Color{193, 255, 193};
        constexpr auto DarkSeaGreen2           = Color{180, 238, 180};
        constexpr auto DarkSeaGreen3           = Color{155, 205, 155};
        constexpr auto DarkSeaGreen4           = Color{105, 139, 105};
        constexpr auto SeaGreen                = Color{ 46, 139,  87};
        constexpr auto SeaGreen1               = Color{ 84, 255, 159};
        constexpr auto SeaGreen2               = Color{ 78, 238, 148};
        constexpr auto SeaGreen3               = Color{ 67, 205, 128};
        constexpr auto SeaGreen4               = Color{ 46, 139,  87};
        constexpr auto PaleGreen               = Color{152, 251, 152};
        constexpr auto PaleGreen1              = Color{154, 255, 154};
        constexpr auto PaleGreen2              = Color{144, 238, 144};
        constexpr auto PaleGreen3              = Color{124, 205, 124};
        constexpr auto PaleGreen4              = Color{ 84, 139,  84};
        constexpr auto SpringGreen             = Color{  0, 255, 127};
        constexpr auto SpringGreen1            = SpringGreen;
        constexpr auto SpringGreen2            = Color{  0, 238, 118};
        constexpr auto SpringGreen3            = Color{  0, 205, 102};
        constexpr auto SpringGreen4            = Color{  0, 139,  69};
        constexpr auto Green1                  = Green;
        constexpr auto Green2                  = Color{  0, 238,   0};
        constexpr auto Green3                  = Color{  0, 205,   0};
        constexpr auto Green4                  = Color{  0, 139,   0};
        constexpr auto Chartreuse              = Color{127, 255,   0};
        constexpr auto Chartreuse1             = Chartreuse;
        constexpr auto Chartreuse2             = Color{118, 238,   0};
        constexpr auto Chartreuse3             = Color{102, 205,   0};
        constexpr auto Chartreuse4             = Color{ 69, 139,   0};
        constexpr auto OliveDrab               = Color{107, 142,  35};
        constexpr auto OliveDrab1              = Color{192, 255,  62};
        constexpr auto OliveDrab2              = Color{179, 238,  58};
        constexpr auto OliveDrab3              = Color{154, 205,  50};
        constexpr auto OliveDrab4              = Color{105, 139,  34};
        constexpr auto DarkOliveGreen          = Color{ 85, 107,  47};
        constexpr auto DarkOliveGreen1         = Color{202, 255, 112};
        constexpr auto DarkOliveGreen2         = Color{188, 238, 104};
        constexpr auto DarkOliveGreen3         = Color{162, 205,  90};
        constexpr auto DarkOliveGreen4         = Color{110, 139,  61};
        constexpr auto Khaki                   = Color{240, 230, 140};
        constexpr auto Khaki1                  = Color{255, 246, 143};
        constexpr auto Khaki2                  = Color{238, 230, 133};
        constexpr auto Khaki3                  = Color{205, 198, 115};
        constexpr auto Khaki4                  = Color{139, 134,  78};
        constexpr auto LightGoldenrod          = Color{238, 221, 130};
        constexpr auto LightGoldenrod1         = Color{255, 236, 139};
        constexpr auto LightGoldenrod2         = Color{238, 220, 130};
        constexpr auto LightGoldenrod3         = Color{205, 190, 112};
        constexpr auto LightGoldenrod4         = Color{139, 129,  76};
        constexpr auto LightYellow             = Color{255, 255, 224};
        constexpr auto LightYellow1            = LightYellow;
        constexpr auto LightYellow2            = Color{238, 238, 209};
        constexpr auto LightYellow3            = Color{205, 205, 180};
        constexpr auto LightYellow4            = Color{139, 139, 122};
        constexpr auto Yellow                  = Color{255, 255,   0};
        constexpr auto Yellow1                 = Yellow;
        constexpr auto Yellow2                 = Color{238, 238,   0};
        constexpr auto Yellow3                 = Color{205, 205,   0};
        constexpr auto Yellow4                 = Color{139, 139,   0};
        constexpr auto Gold                    = Color{255, 215,   0};
        constexpr auto Gold1                   = Color{255, 215,   0};
        constexpr auto Gold2                   = Color{238, 201,   0};
        constexpr auto Gold3                   = Color{205, 173,   0};
        constexpr auto Gold4                   = Color{139, 117,   0};
        constexpr auto Goldenrod               = Color{218, 165,  32};
        constexpr auto Goldenrod1              = Color{255, 193,  37};
        constexpr auto Goldenrod2              = Color{238, 180,  34};
        constexpr auto Goldenrod3              = Color{205, 155,  29};
        constexpr auto Goldenrod4              = Color{139, 105,  20};
        constexpr auto DarkGoldenrod           = Color{184, 134,  11};
        constexpr auto DarkGoldenrod1          = Color{255, 185,  15};
        constexpr auto DarkGoldenrod2          = Color{238, 173,  14};
        constexpr auto DarkGoldenrod3          = Color{205, 149,  12};
        constexpr auto DarkGoldenrod4          = Color{139, 101,   8};
        constexpr auto RosyBrown               = Color{188, 143, 143};
        constexpr auto RosyBrown1              = Color{255, 193, 193};
        constexpr auto RosyBrown2              = Color{238, 180, 180};
        constexpr auto RosyBrown3              = Color{205, 155, 155};
        constexpr auto RosyBrown4              = Color{139, 105, 105};
        constexpr auto IndianRed               = Color{205,  92,  92};
        constexpr auto IndianRed1              = Color{255, 106, 106};
        constexpr auto IndianRed2              = Color{238,  99,  99};
        constexpr auto IndianRed3              = Color{205,  85,  85};
        constexpr auto IndianRed4              = Color{139,  58,  58};
        constexpr auto Sienna                  = Color{160,  82,  45};
        constexpr auto Sienna1                 = Color{255, 130,  71};
        constexpr auto Sienna2                 = Color{238, 121,  66};
        constexpr auto Sienna3                 = Color{205, 104,  57};
        constexpr auto Sienna4                 = Color{139,  71,  38};
        constexpr auto Burlywood               = Color{222, 184, 135};
        constexpr auto Burlywood1              = Color{255, 211, 155};
        constexpr auto Burlywood2              = Color{238, 197, 145};
        constexpr auto Burlywood3              = Color{205, 170, 125};
        constexpr auto Burlywood4              = Color{139, 115,  85};
        constexpr auto Wheat                   = Color{245, 222, 179};
        constexpr auto Wheat1                  = Color{255, 231, 186};
        constexpr auto Wheat2                  = Color{238, 216, 174};
        constexpr auto Wheat3                  = Color{205, 186, 150};
        constexpr auto Wheat4                  = Color{139, 126, 102};
        constexpr auto Tan                     = Color{210, 180, 140};
        constexpr auto Tan1                    = Color{255, 165,  79};
        constexpr auto Tan2                    = Color{238, 154,  73};
        constexpr auto Tan3                    = Color{205, 133,  63};
        constexpr auto Tan4                    = Color{139,  90,  43};
        constexpr auto Chocolate               = Color{210, 105,  30};
        constexpr auto Chocolate1              = Color{255, 127,  36};
        constexpr auto Chocolate2              = Color{238, 118,  33};
        constexpr auto Chocolate3              = Color{205, 102,  29};
        constexpr auto Chocolate4              = Color{139,  69,  19};
        constexpr auto Firebrick               = Color{178,  34,  34};
        constexpr auto Firebrick1              = Color{255,  48,  48};
        constexpr auto Firebrick2              = Color{238,  44,  44};
        constexpr auto Firebrick3              = Color{205,  38,  38};
        constexpr auto Firebrick4              = Color{139,  26,  26};
        constexpr auto Brown                   = Color{165,  42,  42};
        constexpr auto Brown1                  = Color{255,  64,  64};
        constexpr auto Brown2                  = Color{238,  59,  59};
        constexpr auto Brown3                  = Color{205,  51,  51};
        constexpr auto Brown4                  = Color{139,  35,  35};
        constexpr auto Salmon                  = Color{250, 128, 114};
        constexpr auto Salmon1                 = Color{255, 140, 105};
        constexpr auto Salmon2                 = Color{238, 130,  98};
        constexpr auto Salmon3                 = Color{205, 112,  84};
        constexpr auto Salmon4                 = Color{139,  76,  57};
        constexpr auto LightSalmon             = Color{255, 160, 122};
        constexpr auto LightSalmon1            = LightSalmon;
        constexpr auto LightSalmon2            = Color{238, 149, 114};
        constexpr auto LightSalmon3            = Color{205, 129,  98};
        constexpr auto LightSalmon4            = Color{139,  87,  66};
        constexpr auto Orange                  = Color{255, 165,   0};
        constexpr auto Orange1                 = Orange;
        constexpr auto Orange2                 = Color{238, 154,   0};
        constexpr auto Orange3                 = Color{205, 133,   0};
        constexpr auto Orange4                 = Color{139,  90,   0};
        constexpr auto DarkOrange              = Color{255, 140,   0};
        constexpr auto DarkOrange1             = Color{255, 127,   0};
        constexpr auto DarkOrange2             = Color{238, 118,   0};
        constexpr auto DarkOrange3             = Color{205, 102,   0};
        constexpr auto DarkOrange4             = Color{139,  69,   0};
        constexpr auto Coral                   = Color{255, 127,  80};
        constexpr auto Coral1                  = Color{255, 114,  86};
        constexpr auto Coral2                  = Color{238, 106,  80};
        constexpr auto Coral3                  = Color{205,  91,  69};
        constexpr auto Coral4                  = Color{139,  62,  47};
        constexpr auto Tomato                  = Color{255,  99,  71};
        constexpr auto Tomato1                 = Tomato;
        constexpr auto Tomato2                 = Color{238,  92,  66};
        constexpr auto Tomato3                 = Color{205,  79,  57};
        constexpr auto Tomato4                 = Color{139,  54,  38};
        constexpr auto OrangeRed               = Color{255,  69,   0};
        constexpr auto OrangeRed1              = OrangeRed;
        constexpr auto OrangeRed2              = Color{238,  64,   0};
        constexpr auto OrangeRed3              = Color{205,  55,   0};
        constexpr auto OrangeRed4              = Color{139,  37,   0};
        constexpr auto Red                     = Color{255,   0,   0};
        constexpr auto Red1                    = Red;
        constexpr auto Red2                    = Color{238,   0,   0};
        constexpr auto Red3                    = Color{205,   0,   0};
        constexpr auto Red4                    = Color{139,   0,   0};
        constexpr auto DeepPink1               = Color{255,  20, 147};
        constexpr auto DeepPink2               = Color{238,  18, 137};
        constexpr auto DeepPink3               = Color{205,  16, 118};
        constexpr auto DeepPink4               = Color{139,  10,  80};
        constexpr auto HotPink                 = Color{255, 105, 180};
        constexpr auto HotPink1                = Color{255, 110, 180};
        constexpr auto HotPink2                = Color{238, 106, 167};
        constexpr auto HotPink3                = Color{205,  96, 144};
        constexpr auto HotPink4                = Color{139,  58,  98};
        constexpr auto Pink                    = Color{255, 192, 203};
        constexpr auto Pink1                   = Color{255, 181, 197};
        constexpr auto Pink2                   = Color{238, 169, 184};
        constexpr auto Pink3                   = Color{205, 145, 158};
        constexpr auto Pink4                   = Color{139,  99, 108};
        constexpr auto LightPink               = Color{255, 182, 193};
        constexpr auto LightPink1              = Color{255, 174, 185};
        constexpr auto LightPink2              = Color{238, 162, 173};
        constexpr auto LightPink3              = Color{205, 140, 149};
        constexpr auto LightPink4              = Color{139,  95, 101};
        constexpr auto PaleVioletRed           = Color{219, 112, 147};
        constexpr auto PaleVioletRed1          = Color{255, 130, 171};
        constexpr auto PaleVioletRed2          = Color{238, 121, 159};
        constexpr auto PaleVioletRed3          = Color{205, 104, 137};
        constexpr auto PaleVioletRed4          = Color{139,  71,  93};
        constexpr auto Maroon                  = Color{176,  48,  96};
        constexpr auto Maroon1                 = Color{255,  52, 179};
        constexpr auto Maroon2                 = Color{238,  48, 167};
        constexpr auto Maroon3                 = Color{205,  41, 144};
        constexpr auto Maroon4                 = Color{139,  28,  98};
        constexpr auto VioletRed               = Color{208,  32, 144};
        constexpr auto VioletRed1              = Color{255,  62, 150};
        constexpr auto VioletRed2              = Color{238,  58, 140};
        constexpr auto VioletRed3              = Color{205,  50, 120};
        constexpr auto VioletRed4              = Color{139,  34,  82};
        constexpr auto Magenta                 = Fuchsia;
        constexpr auto Magenta1                = Magenta;
        constexpr auto Magenta2                = Color{238,   0, 238};
        constexpr auto Magenta3                = Color{205,   0, 205};
        constexpr auto Magenta4                = Color{139,   0, 139};
        constexpr auto Orchid                  = Color{218, 112, 214};
        constexpr auto Orchid1                 = Color{255, 131, 250};
        constexpr auto Orchid2                 = Color{238, 122, 233};
        constexpr auto Orchid3                 = Color{205, 105, 201};
        constexpr auto Orchid4                 = Color{139,  71, 137};
        constexpr auto Plum                    = Color{221, 160, 221};
        constexpr auto Plum1                   = Color{255, 187, 255};
        constexpr auto Plum2                   = Color{238, 174, 238};
        constexpr auto Plum3                   = Color{205, 150, 205};
        constexpr auto Plum4                   = Color{139, 102, 139};
        constexpr auto MediumOrchid            = Color{186,  85, 211};
        constexpr auto MediumOrchid1           = Color{224, 102, 255};
        constexpr auto MediumOrchid2           = Color{209,  95, 238};
        constexpr auto MediumOrchid3           = Color{180,  82, 205};
        constexpr auto MediumOrchid4           = Color{122,  55, 139};
        constexpr auto DarkOrchid              = Color{153,  50, 204};
        constexpr auto DarkOrchid1             = Color{191,  62, 255};
        constexpr auto DarkOrchid2             = Color{178,  58, 238};
        constexpr auto DarkOrchid3             = Color{154,  50, 205};
        constexpr auto DarkOrchid4             = Color{104,  34, 139};
        constexpr auto Purple                  = Color{160,  32, 240};
        constexpr auto Purple1                 = Color{155,  48, 255};
        constexpr auto Purple2                 = Color{145,  44, 238};
        constexpr auto Purple3                 = Color{125,  38, 205};
        constexpr auto Purple4                 = Color{ 85,  26, 139};
        constexpr auto MediumPurple            = Color{147, 112, 219};
        constexpr auto MediumPurple1           = Color{171, 130, 255};
        constexpr auto MediumPurple2           = Color{159, 121, 238};
        constexpr auto MediumPurple3           = Color{137, 104, 205};
        constexpr auto MediumPurple4           = Color{ 93,  71, 139};
        constexpr auto Thistle                 = Color{216, 191, 216};
        constexpr auto Thistle1                = White;
        constexpr auto Thistle2                = Color{238, 210, 238};
        constexpr auto Thistle3                = Color{205, 181, 205};
        constexpr auto Thistle4                = Color{139, 123, 139};
        constexpr auto Gray0                   = Black;
        constexpr auto Gray1                   = Color{  3,   3,   3};
        constexpr auto Gray2                   = Color{  5,   5,   5};
        constexpr auto Gray3                   = Color{  8,   8,   8};
        constexpr auto Gray4                   = Color{ 10,  10,  10};
        constexpr auto Gray5                   = Color{ 13,  13,  13};
        constexpr auto Gray6                   = Color{ 15,  15,  15};
        constexpr auto Gray7                   = Color{ 18,  18,  18};
        constexpr auto Gray8                   = Color{ 20,  20,  20};
        constexpr auto Gray9                   = Color{ 23,  23,  23};
        constexpr auto Gray10                  = Color{ 26,  26,  26};
        constexpr auto Gray11                  = Color{ 28,  28,  28};
        constexpr auto Gray12                  = Color{ 31,  31,  31};
        constexpr auto Gray13                  = Color{ 33,  33,  33};
        constexpr auto Gray14                  = Color{ 36,  36,  36};
        constexpr auto Gray15                  = Color{ 38,  38,  38};
        constexpr auto Gray16                  = Color{ 41,  41,  41};
        constexpr auto Gray17                  = Color{ 43,  43,  43};
        constexpr auto Gray18                  = Color{ 46,  46,  46};
        constexpr auto Gray19                  = Color{ 48,  48,  48};
        constexpr auto Gray20                  = Color{ 51,  51,  51};
        constexpr auto Gray21                  = Color{ 54,  54,  54};
        constexpr auto Gray22                  = Color{ 56,  56,  56};
        constexpr auto Gray23                  = Color{ 59,  59,  59};
        constexpr auto Gray24                  = Color{ 61,  61,  61};
        constexpr auto Gray25                  = Color{ 64,  64,  64};
        constexpr auto Gray26                  = Color{ 66,  66,  66};
        constexpr auto Gray27                  = Color{ 69,  69,  69};
        constexpr auto Gray28                  = Color{ 71,  71,  71};
        constexpr auto Gray29                  = Color{ 74,  74,  74};
        constexpr auto Gray30                  = Color{ 77,  77,  77};
        constexpr auto Gray31                  = Color{ 79,  79,  79};
        constexpr auto Gray32                  = Color{ 82,  82,  82};
        constexpr auto Gray33                  = Color{ 84,  84,  84};
        constexpr auto Gray34                  = Color{ 87,  87,  87};
        constexpr auto Gray35                  = Color{ 89,  89,  89};
        constexpr auto Gray36                  = Color{ 92,  92,  92};
        constexpr auto Gray37                  = Color{ 94,  94,  94};
        constexpr auto Gray38                  = Color{ 97,  97,  97};
        constexpr auto Gray39                  = Color{ 99,  99,  99};
        constexpr auto Gray40                  = Color{102, 102, 102};
        constexpr auto Gray41                  = Color{105, 105, 105};
        constexpr auto Gray42                  = Color{107, 107, 107};
        constexpr auto Gray43                  = Color{110, 110, 110};
        constexpr auto Gray44                  = Color{112, 112, 112};
        constexpr auto Gray45                  = Color{115, 115, 115};
        constexpr auto Gray46                  = Color{117, 117, 117};
        constexpr auto Gray47                  = Color{120, 120, 120};
        constexpr auto Gray48                  = Color{122, 122, 122};
        constexpr auto Gray49                  = Color{125, 125, 125};
        constexpr auto Gray50                  = Color{127, 127, 127};
        constexpr auto Gray51                  = Color{130, 130, 130};
        constexpr auto Gray52                  = Color{133, 133, 133};
        constexpr auto Gray53                  = Color{135, 135, 135};
        constexpr auto Gray54                  = Color{138, 138, 138};
        constexpr auto Gray55                  = Color{140, 140, 140};
        constexpr auto Gray56                  = Color{143, 143, 143};
        constexpr auto Gray57                  = Color{145, 145, 145};
        constexpr auto Gray58                  = Color{148, 148, 148};
        constexpr auto Gray59                  = Color{150, 150, 150};
        constexpr auto Gray60                  = Color{153, 153, 153};
        constexpr auto Gray61                  = Color{156, 156, 156};
        constexpr auto Gray62                  = Color{158, 158, 158};
        constexpr auto Gray63                  = Color{161, 161, 161};
        constexpr auto Gray64                  = Color{163, 163, 163};
        constexpr auto Gray65                  = Color{166, 166, 166};
        constexpr auto Gray66                  = Color{168, 168, 168};
        constexpr auto Gray67                  = Color{171, 171, 171};
        constexpr auto Gray68                  = Color{173, 173, 173};
        constexpr auto Gray69                  = Color{176, 176, 176};
        constexpr auto Gray70                  = Color{179, 179, 179};
        constexpr auto Gray71                  = Color{181, 181, 181};
        constexpr auto Gray72                  = Color{184, 184, 184};
        constexpr auto Gray73                  = Color{186, 186, 186};
        constexpr auto Gray74                  = Color{189, 189, 189};
        constexpr auto Gray75                  = Color{191, 191, 191};
        constexpr auto Gray76                  = Color{194, 194, 194};
        constexpr auto Gray77                  = Color{196, 196, 196};
        constexpr auto Gray78                  = Color{199, 199, 199};
        constexpr auto Gray79                  = Color{201, 201, 201};
        constexpr auto Gray80                  = Color{204, 204, 204};
        constexpr auto Gray81                  = Color{207, 207, 207};
        constexpr auto Gray82                  = Color{209, 209, 209};
        constexpr auto Gray83                  = Color{212, 212, 212};
        constexpr auto Gray84                  = Color{214, 214, 214};
        constexpr auto Gray85                  = Color{217, 217, 217};
        constexpr auto Gray86                  = Color{219, 219, 219};
        constexpr auto Gray87                  = Color{222, 222, 222};
        constexpr auto Gray88                  = Color{224, 224, 224};
        constexpr auto Gray89                  = Color{227, 227, 227};
        constexpr auto Gray90                  = Color{229, 229, 229};
        constexpr auto Gray91                  = Color{232, 232, 232};
        constexpr auto Gray92                  = Color{235, 235, 235};
        constexpr auto Gray93                  = Color{237, 237, 237};
        constexpr auto Gray94                  = Color{240, 240, 240};
        constexpr auto Gray95                  = Color{242, 242, 242};
        constexpr auto Gray96                  = Color{245, 245, 245};
        constexpr auto Gray97                  = Color{247, 247, 247};
        constexpr auto Gray98                  = Color{250, 250, 250};
        constexpr auto Gray99                  = Color{252, 252, 252};
        constexpr auto Gray100                 = White;
        constexpr auto Grey0                   = Gray0;
        constexpr auto Grey1                   = Gray1;
        constexpr auto Grey2                   = Gray2;
        constexpr auto Grey3                   = Gray3;
        constexpr auto Grey4                   = Gray4;
        constexpr auto Grey5                   = Gray5;
        constexpr auto Grey6                   = Gray6;
        constexpr auto Grey7                   = Gray7;
        constexpr auto Grey8                   = Gray8;
        constexpr auto Grey9                   = Gray9;
        constexpr auto Grey10                  = Gray10;
        constexpr auto Grey11                  = Gray11;
        constexpr auto Grey12                  = Gray12;
        constexpr auto Grey13                  = Gray13;
        constexpr auto Grey14                  = Gray14;
        constexpr auto Grey15                  = Gray15;
        constexpr auto Grey16                  = Gray16;
        constexpr auto Grey17                  = Gray17;
        constexpr auto Grey18                  = Gray18;
        constexpr auto Grey19                  = Gray19;
        constexpr auto Grey20                  = Gray20;
        constexpr auto Grey21                  = Gray21;
        constexpr auto Grey22                  = Gray22;
        constexpr auto Grey23                  = Gray23;
        constexpr auto Grey24                  = Gray24;
        constexpr auto Grey25                  = Gray25;
        constexpr auto Grey26                  = Gray26;
        constexpr auto Grey27                  = Gray27;
        constexpr auto Grey28                  = Gray28;
        constexpr auto Grey29                  = Gray29;
        constexpr auto Grey30                  = Gray30;
        constexpr auto Grey31                  = Gray31;
        constexpr auto Grey32                  = Gray32;
        constexpr auto Grey33                  = Gray33;
        constexpr auto Grey34                  = Gray34;
        constexpr auto Grey35                  = Gray35;
        constexpr auto Grey36                  = Gray36;
        constexpr auto Grey37                  = Gray37;
        constexpr auto Grey38                  = Gray38;
        constexpr auto Grey39                  = Gray39;
        constexpr auto Grey40                  = Gray40;
        constexpr auto Grey41                  = Gray41;
        constexpr auto Grey42                  = Gray42;
        constexpr auto Grey43                  = Gray43;
        constexpr auto Grey44                  = Gray44;
        constexpr auto Grey45                  = Gray45;
        constexpr auto Grey46                  = Gray46;
        constexpr auto Grey47                  = Gray47;
        constexpr auto Grey48                  = Gray48;
        constexpr auto Grey49                  = Gray49;
        constexpr auto Grey50                  = Gray50;
        constexpr auto Grey51                  = Gray51;
        constexpr auto Grey52                  = Gray52;
        constexpr auto Grey53                  = Gray53;
        constexpr auto Grey54                  = Gray54;
        constexpr auto Grey55                  = Gray55;
        constexpr auto Grey56                  = Gray56;
        constexpr auto Grey57                  = Gray57;
        constexpr auto Grey58                  = Gray58;
        constexpr auto Grey59                  = Gray59;
        constexpr auto Grey60                  = Gray60;
        constexpr auto Grey61                  = Gray61;
        constexpr auto Grey62                  = Gray62;
        constexpr auto Grey63                  = Gray63;
        constexpr auto Grey64                  = Gray64;
        constexpr auto Grey65                  = Gray65;
        constexpr auto Grey66                  = Gray66;
        constexpr auto Grey67                  = Gray67;
        constexpr auto Grey68                  = Gray68;
        constexpr auto Grey69                  = Gray69;
        constexpr auto Grey70                  = Gray70;
        constexpr auto Grey71                  = Gray71;
        constexpr auto Grey72                  = Gray72;
        constexpr auto Grey73                  = Gray73;
        constexpr auto Grey74                  = Gray74;
        constexpr auto Grey75                  = Gray75;
        constexpr auto Grey76                  = Gray76;
        constexpr auto Grey77                  = Gray77;
        constexpr auto Grey78                  = Gray78;
        constexpr auto Grey79                  = Gray79;
        constexpr auto Grey80                  = Gray80;
        constexpr auto Grey81                  = Gray81;
        constexpr auto Grey82                  = Gray82;
        constexpr auto Grey83                  = Gray83;
        constexpr auto Grey84                  = Gray84;
        constexpr auto Grey85                  = Gray85;
        constexpr auto Grey86                  = Gray86;
        constexpr auto Grey87                  = Gray87;
        constexpr auto Grey88                  = Gray88;
        constexpr auto Grey89                  = Gray89;
        constexpr auto Grey90                  = Gray90;
        constexpr auto Grey91                  = Gray91;
        constexpr auto Grey92                  = Gray92;
        constexpr auto Grey93                  = Gray93;
        constexpr auto Grey94                  = Gray94;
        constexpr auto Grey95                  = Gray95;
        constexpr auto Grey96                  = Gray96;
        constexpr auto Grey97                  = Gray97;
        constexpr auto Grey98                  = Gray98;
        constexpr auto Grey99                  = Gray99;
        constexpr auto Grey100                 = Gray100;
        constexpr auto DarkGray                = Color{169, 169, 169};
        constexpr auto DarkGrey                = DarkGray;
        constexpr auto DarkBlue                = Color{  0,   0, 139};
        constexpr auto DarkCyan                = Color{  0, 139, 139};
        constexpr auto DarkMagenta             = Color{139,   0, 139};
        constexpr auto DarkRed                 = Color{139,   0,   0};
        constexpr auto LightGreen              = Color{144, 238, 144};
        constexpr auto Crimson                 = Color{220,  20,  60};
        constexpr auto Indigo                  = Color{ 75,   0, 130};
        constexpr auto Olive                   = Color{128, 128,   0};
        constexpr auto RebeccaPurple           = Color{102,  51, 153};
        constexpr auto Silver                  = Color{192, 192, 192};
        constexpr auto Teal                    = Color{  0, 128, 128};
    }
}

module : private;
