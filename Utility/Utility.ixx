module;

#include <FatSTL_Macros.hxx>

export module FatPound.Utility;

export import FatPound.Utility.Gfx;

export import FatPound.Utility.Color;
export import FatPound.Utility.Common;
export import FatPound.Utility.Surface;
export import FatPound.Utility.Timer;
export import FatPound.Utility.ViewXM;

import std;

export namespace fatpound::utility
{
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
}

module : private;
