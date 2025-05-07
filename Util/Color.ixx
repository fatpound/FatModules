module;

#include <FatDefines.hpp>

export module FatPound.Util.Color;

import std;

export namespace fatpound::util
{
    class [[nodiscard]] Color final
    {
    public:
        constexpr Color(const std::uint32_t& xrgb, const std::uint32_t& alpha = 0xFF'00'00'00U) noexcept
            :
            m_dword(xrgb bitor alpha)
        {

        }
        constexpr Color(const std::uint32_t&  red, const std::uint32_t& green, const std::uint32_t& blue, const std::uint32_t& alpha = 0xFF'00'00'00U) noexcept
            :
            Color((red << 16U) bitor (green << 8U) bitor blue, alpha)
        {

        }
        constexpr Color(const std::uint8_t&   red, const std::uint8_t&  green, const std::uint8_t&  blue, const std::uint8_t&  alpha = 0xFFU) noexcept
            :
            Color(static_cast<std::uint32_t>(red), static_cast<std::uint32_t>(green), static_cast<std::uint32_t>(blue), static_cast<std::uint32_t>(alpha))
        {
            
        }
        constexpr Color(const Color& col, const std::uint8_t& alpha) noexcept
            :
            Color(col.m_dword, static_cast<std::uint32_t>(alpha))
        {

        }

        constexpr Color()                 = default;
        constexpr Color(const Color&)     = default;
        constexpr Color(Color&&) noexcept = default;

        constexpr auto operator = (const Color&)     -> Color& = default;
        constexpr auto operator = (Color&&) noexcept -> Color& = default;
        constexpr ~Color() noexcept                            = default;


    public:
        auto operator <=> (const Color&) const noexcept -> bool = delete;
        auto operator ==  (const Color&) const noexcept -> bool = default;

        // NOLINTBEGIN(google-explicit-constructor, hicpp-explicit-conversions)
        operator std::uint32_t () const noexcept
        {
            return m_dword;
        }
        // NOLINTEND(google-explicit-constructor, hicpp-explicit-conversions)


    public:
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetA() const noexcept -> unsigned char
        {
            return m_dword >> 24U;
        }
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetR() const noexcept -> unsigned char
        {
            return (m_dword >> 16U) bitand 0xFFU;
        }
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetG() const noexcept -> unsigned char
        {
            return (m_dword >> 8U) bitand 0xFFU;
        }
        [[nodiscard]] FAT_FORCEINLINE constexpr auto GetB() const noexcept -> unsigned char
        {
            return m_dword bitand 0xFFU;
        }

        FAT_FORCEINLINE void SetA(const std::uint8_t& alpha) noexcept
        {
            m_dword = ((m_dword bitand 0x00'FF'FF'FFU) bitor (static_cast<std::uint32_t>(alpha) << 24U));
        }
        FAT_FORCEINLINE void SetR(const std::uint8_t& red) noexcept
        {
            m_dword = ((m_dword bitand 0xFF'00'FF'FFU) bitor (static_cast<std::uint32_t>(red) << 16U));
        }
        FAT_FORCEINLINE void SetG(const std::uint8_t& green) noexcept
        {
            m_dword = ((m_dword bitand 0xFF'FF'00'FFU) bitor (static_cast<std::uint32_t>(green) << 8U));
        }
        FAT_FORCEINLINE void SetB(const std::uint8_t& blue) noexcept
        {
            m_dword = ((m_dword bitand 0xFF'FF'FF'00U) bitor static_cast<std::uint32_t>(blue));
        }


    public:
        std::uint32_t m_dword = std::numeric_limits<decltype(m_dword)>::max();
        

    protected:


    private:
    };
}

export namespace fatpound::colors
{
    using namespace util;

    // This namespace contains Microsoft-style colors. (count: 140) (Direct2D version 1)
    // Lime => 0x00FF00, Green => 0x008000, LimeGreen => 0x32CD32
    // 
    // Alpha value: 0xFF

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
    constexpr Color Cyan                 = 0x00FFFF;
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
    constexpr Color Magenta              = 0xFF00FF;
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
}

module : private;
