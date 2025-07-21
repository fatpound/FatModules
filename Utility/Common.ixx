module;

#include <_macros/STL.hxx>

export module FatPound.Utility.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC
    import <Win32_/WinAPI.hxx>;
#endif

import FatPound.Traits.Bitwise;

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



    /// @brief Calculates the smallest angle between the hour and minute hands of a clock for a given time
    /// 
    /// @tparam      FP: The floating-point type used for the result (defaults to double). Must satisfy std::floating_point
    /// @tparam       T: The integral type of the input parameters. Must satisfy std::integral
    /// 
    ///  @param   hours: The hour value (0-23) representing the current hour
    ///  @param minutes: The minute value (0-59) representing the current minute
    /// 
    /// @return The smallest angle (in degrees) between the hour and minute hands, as a value of type FP
    /// 
    template <std::floating_point FP = double, std::integral T>
    CX_MATH23 auto ClockHandsAngle(T hours, T minutes) noexcept -> FP
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



    /// @brief Maps a value from one range to another using linear interpolation
    /// 
    /// @tparam        T: The numeric type of the values, constrained to integral or floating-point types
    /// 
    ///  @param    value: The value to map from the source range to the target range
    ///  @param  fromLow: The lower bound of the source range
    ///  @param fromHigh: The upper bound of the source range
    ///  @param    toLow: The lower bound of the target range
    ///  @param   toHigh: The upper bound of the target range
    /// 
    /// @return The value mapped to the target range
    /// 
    template <traits::IntegralOrFloating T>
    constexpr auto Map(const T& value, const T& fromLow, const T& fromHigh, const T& toLow, const T& toHigh) -> T
    {
        return ((value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow)) + toLow;
    }
    


    template <std::integral T>
    void ParseLineToIntegralVector(const std::string& line, std::vector<T>& vec)
    {
        vec.reserve(line.length() / 2U + 1);

        std::stringstream ss(line);

        T value{};

        while (ss >> value)
        {
            vec.push_back(value);
        }
    }



    template <std::integral T>
    auto ParseLineToIntegralVector(const std::string& line) -> std::vector<T>
    {
        std::vector<T> vec;

        ParseLineToIntegralVector<>(line, vec);

        return vec;
    }



    template <std::integral T>
    auto ParseLineToIntegralVector(const std::ifstream& ifs) -> std::vector<T>
    {
        std::string line;
        std::getline<>(ifs, line);

        return ParseLineToIntegralVector<T>(line);
    }



    template <std::integral T>
    void ParseLineToIntegralVector(const std::ifstream& ifs, std::vector<T>& vec)
    {
        std::string line;
        std::getline<>(ifs, line);

        ParseLineToIntegralVector<>(line, vec);
    }



    /// @brief Returns a new string with the characters of the input string in reverse order
    /// 
    /// @param str: The input string to be reversed
    /// 
    /// @return A new string containing the characters of the input string in reverse order
    /// 
    constexpr auto StrRev(const std::string& str) -> std::string
    {
        auto revstr = str;

        std::ranges::reverse(revstr);

        return revstr;
    }


    
    /// @brief Sets all characters in a string to the specified character
    /// 
    /// @param str: The string whose characters will be set
    /// @param  ch: The character to assign to each position in the string
    /// 
    constexpr void StrSet(std::string& str, const char ch)
    {
        std::ranges::fill(str, ch);
    }



#ifdef FATLIB_BUILDING_WITH_MSVC

    auto To_WString(const std::string& str) -> std::wstring
    {
        if (str.empty())
        {
            return {};
        }

        const auto& required_size = MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            str.c_str(),
            static_cast<int>(str.size()),
            nullptr,
            0
        );

        if (required_size == 0)
        {
            throw std::runtime_error("Failed to calculate required size for string conversion!");
        }

        std::wstring wstr(static_cast<std::size_t>(required_size), L'\0');

        const auto& bytes_written = MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            str.c_str(),
            static_cast<int>(str.size()),
            wstr.data(),
            required_size
        );

        if (bytes_written == 0)
        {
            throw std::runtime_error("Failed to convert string to wstring!");
        }

        return wstr;
    }

#endif



    /// @brief Converts an 8-bit unsigned integer to its two-character hexadecimal string representation
    /// 
    /// @param value: The 8-bit unsigned integer to convert to a hexadecimal string
    /// 
    /// @return A string containing the two-character hexadecimal representation of the input value
    /// 
    auto ToHexString(const std::uint8_t& value) -> std::string
    {
        return
        {
            HexDigits[static_cast<unsigned int>(value >> 4U) bitand 0x0FU],
            HexDigits[value bitand 0x0FU]
        };
    }
}

// module : private;
