module;

#include <FatDefines.hpp>

export module FatPound.Util.Color;

import std;

export namespace fatpound
{
    namespace util
    {
        class [[nodiscard]] Color final
        {
        public:
            constexpr explicit Color(const std::uint8_t&  red, const std::uint8_t&  green, const std::uint8_t&  blue, const std::uint8_t& alpha = 0xFFU)
                :
                m_dword{(static_cast<std::uint32_t>(alpha) << 24U)
                    bitor (static_cast<std::uint32_t>(red) << 16U)
                    bitor (static_cast<std::uint32_t>(green) << 8U)
                    bitor (static_cast<std::uint32_t>(blue))}
            {
                
            }
            constexpr explicit Color(const std::uint32_t& red, const std::uint32_t& green, const std::uint32_t& blue)
                :
                Color(static_cast<std::uint8_t>(red), static_cast<std::uint8_t>(green), static_cast<std::uint8_t>(blue))
            {

            }
            constexpr explicit Color(const std::uint32_t& num)
                :
                m_dword(num bitor 0xFF'00'00'00U)
            {

            }
            constexpr explicit Color(const Color& col, const std::uint8_t& alpha)
                :
                Color((static_cast<std::uint32_t>(alpha) << 24U) bitor col.m_dword)
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

            // NOLINTBEGIN(google-explicit-constructor, hicpp-explicit-conversions)
            operator std::uint32_t () const noexcept
            {
                return m_dword;
            }
            // NOLINTEND(google-explicit-constructor, hicpp-explicit-conversions)


        public:
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetA() const -> unsigned char
            {
                return m_dword >> 24U;
            }
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetR() const -> unsigned char
            {
                return (m_dword >> 16U) bitand 0xFFU;
            }
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetG() const -> unsigned char
            {
                return (m_dword >> 8U) bitand 0xFFU;
            }
            [[nodiscard]] FAT_FORCEINLINE constexpr auto GetB() const -> unsigned char
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

    namespace colors
    {
        constexpr auto MakeRGB(const std::uint8_t& red, const std::uint8_t& green, const std::uint8_t& blue) -> util::Color
        {
            return util::Color{
                (static_cast<std::uint32_t>(red) << 16U)
                bitor (static_cast<std::uint32_t>(green) << 8U)
                bitor static_cast<std::uint32_t>(blue)
            };
        }

        constexpr auto Black     = MakeRGB(  0U,   0U,   0U);
        constexpr auto Gray      = MakeRGB(128U, 128U, 128U);
        constexpr auto LightGray = MakeRGB(192U, 192U, 192U);
        constexpr auto White     = MakeRGB(255U, 255U, 255U);

        constexpr auto Red       = MakeRGB(255U,   0U,   0U);
        constexpr auto Green     = MakeRGB(  0U, 255U,   0U);
        constexpr auto Blue      = MakeRGB(  0U,   0U, 255U);
        constexpr auto Yellow    = MakeRGB(255U, 255U,   0U);
        constexpr auto Cyan      = MakeRGB(  0U, 255U, 255U);
        constexpr auto Magenta   = MakeRGB(255U,   0U, 255U);
    }
}

module : private;
