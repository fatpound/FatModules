module;

#include <FatSTL_Macros.hxx>

export module FatPound.Utility.Common;

#if FAT_BUILDING_WITH_MSVC

import <FatWin32.hxx>;

#endif

import std;

export namespace fatpound::utility
{
    constexpr std::string_view         BinDigits = "01";
    constexpr std::string_view         OctDigits = "01234567";
    constexpr std::string_view         DecDigits = "0123456789";
    constexpr std::string_view         HexDigits = "0123456789ABCDEF";

    constexpr std::string_view      BinaryDigits = BinDigits;
    constexpr std::string_view       OctalDigits = OctDigits;
    constexpr std::string_view     DecimalDigits = DecDigits;
    constexpr std::string_view HexadecimalDigits = HexDigits;

#if FAT_BUILDING_WITH_MSVC

    auto ToWString(const std::string& str) -> std::wstring
    {
        std::wstring wstr(str.size(), '\0');

        ::MultiByteToWideChar(
            CP_UTF8,
            0,
            str.c_str(),
            static_cast<int>(str.size()),
            wstr.data(),
            static_cast<int>(wstr.size())
        );

        return wstr;
    }

#endif

    auto ToHexString(const std::uint8_t& value) -> std::string
    {
        return
        {
            HexDigits[static_cast<unsigned int>(value >> 4U) bitand 0x0FU],
            HexDigits[value bitand 0x0FU]
        };
    }

    template <std::floating_point FP = double, std::integral T>
    CX_MATH23
    auto ClockHandsAngle(T hours, T minutes) noexcept -> FP
    {
        if constexpr (std::signed_integral<T>)
        {
            hours   = std::abs(hours);
            minutes = std::abs(minutes);
        }

        hours   %= 12;
        minutes %= 60;

        const auto angle = std::fabs(static_cast<FP>((11 * minutes) - (60 * hours)) / static_cast<FP>(2.0));

        return (angle > 180) ? static_cast<FP>(360 - angle) : angle;
    }
    
    constexpr auto StrRev(const std::string& str) -> std::string
    {
        auto revstr = str;

        std::ranges::reverse(revstr);

        return revstr;
    }

    constexpr void StrSet(std::string& str, const char ch)
    {
        std::ranges::fill(str, ch);
    }
}

module : private;
