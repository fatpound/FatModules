module;

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
        return { HexDigits[(value >> 4U) bitand 0x0FU], HexDigits[value bitand 0x0FU] };
    }
}

module : private;
