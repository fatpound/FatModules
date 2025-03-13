module;

#include <FatDefines.hpp>

export module FatPound.Util.Color;

import std;

export namespace fatpound
{
    namespace util
    {
        class Color final
        {
        public:
            constexpr explicit Color(const ::std::uint8_t&  red, const ::std::uint8_t&  green, const ::std::uint8_t&  blue, const ::std::uint8_t&  alpha = 0xFFu)
                :
                Color(static_cast<::std::uint32_t>(red), static_cast<::std::uint32_t>(green), static_cast<::std::uint32_t>(blue), static_cast<::std::uint32_t>(alpha))
            {
                
            }
            constexpr explicit Color(const ::std::uint32_t& red, const ::std::uint32_t& green, const ::std::uint32_t& blue, const ::std::uint32_t& alpha = 0xFFu)
                :
                m_dword{ (alpha << 24u) bitor (red << 16u) bitor (green << 8u) bitor blue }
            {

            }
            constexpr explicit Color(const ::std::uint32_t& num, const ::std::uint8_t& alpha)
                :
                Color(num, static_cast<::std::uint32_t>(alpha))
            {

            }
            constexpr explicit Color(const ::std::uint32_t& num, const ::std::uint32_t& alpha)
                :
                Color(num bitor (alpha << 24u))
            {

            }
            constexpr explicit Color(const ::std::uint32_t& num)
                :
                m_dword(num)
            {

            }
            constexpr explicit Color(const Color& col, const ::std::uint8_t& alpha)
                :
                Color(col.m_dword, alpha)
            {

            }

            constexpr explicit Color()        = default;
            constexpr Color(const Color&)     = default;
            constexpr Color(Color&&) noexcept = default;

            constexpr auto operator = (const Color&)     -> Color& = default;
            constexpr auto operator = (Color&&) noexcept -> Color& = default;
            constexpr ~Color() noexcept                            = default;


        public:
            auto operator <=> (const Color&) const -> bool = delete;
            auto operator ==  (const Color&) const -> bool = default;

            operator ::std::uint32_t () const noexcept
            {
                return m_dword;
            }


        public:
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetA() const -> ::std::uint8_t
            {
                return m_dword >> 24u;
            }
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetR() const -> ::std::uint8_t
            {
                return (m_dword >> 16u) bitand 0xFFu;
            }
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetG() const -> ::std::uint8_t
            {
                return (m_dword >> 8u) bitand 0xFFu;
            }
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetB() const -> ::std::uint8_t
            {
                return m_dword bitand 0xFFu;
            }

            FAT_FORCEINLINE void SetA(const ::std::uint8_t& alpha) noexcept
            {
                m_dword = ((m_dword bitand 0x00'FF'FF'FFu) bitor (static_cast<::std::uint32_t>(alpha) << 24u));
            }
            FAT_FORCEINLINE void SetR(const ::std::uint8_t&   red) noexcept
            {
                m_dword = ((m_dword bitand 0xFF'00'FF'FFu) bitor (static_cast<::std::uint32_t>(red) << 16u));
            }
            FAT_FORCEINLINE void SetG(const ::std::uint8_t& green) noexcept
            {
                m_dword = ((m_dword bitand 0xFF'FF'00'FFu) bitor (static_cast<::std::uint32_t>(green) << 8u));
            }
            FAT_FORCEINLINE void SetB(const ::std::uint8_t&  blue) noexcept
            {
                m_dword = ((m_dword bitand 0xFF'FF'FF'00u) bitor static_cast<::std::uint32_t>(blue));
            }


        public:
            ::std::uint32_t m_dword = 0xFF'FF'FF'FFu;


        protected:


        private:
        };
    }

    namespace colors
    {
        constexpr auto MakeRGB(const ::std::uint8_t& red, const ::std::uint8_t& green, const ::std::uint8_t& blue) -> util::Color
        {
            return util::Color{
                (static_cast<::std::uint32_t>(red)   << 16u) bitor
                (static_cast<::std::uint32_t>(green) <<  8u) bitor
                 static_cast<::std::uint32_t>(blue)
            };
        }

        constexpr auto Black     = MakeRGB(  0u,   0u,   0u);
        constexpr auto Gray      = MakeRGB(128u, 128u, 128u);
        constexpr auto LightGray = MakeRGB(192u, 192u, 192u);
        constexpr auto White     = MakeRGB(255u, 255u, 255u);

        constexpr auto Red       = MakeRGB(255u,   0u,   0u);
        constexpr auto Green     = MakeRGB(  0u, 255u,   0u);
        constexpr auto Blue      = MakeRGB(  0u,   0u, 255u);
        constexpr auto Yellow    = MakeRGB(255u, 255u,   0u);
        constexpr auto Cyan      = MakeRGB(  0u, 255u, 255u);
        constexpr auto Magenta   = MakeRGB(255u,   0u, 255u);
    }
}

module : private;