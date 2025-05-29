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
    auto HourMinuteHandAngle(T hours, T minutes) noexcept -> FP
    {
        if constexpr (std::signed_integral<T>)
        {
            if (hours < 0)
            {
                hours = -hours;
            }

            if (minutes < 0)
            {
                minutes = -minutes;
            }
        }

        hours   %= 12;
        minutes %= 60;

        const auto& angle = std::fabs(static_cast<FP>((11 * minutes) - (60 * hours)) / static_cast<FP>(2.0));

        return (angle > 180) ? static_cast<FP>(360 - angle) : angle;
    }
}

module : private;
