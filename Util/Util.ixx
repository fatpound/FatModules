module;

#include <FatNamespaces.hpp>
#include <FatDefines.hpp>

export module FatPound.Util;

export import FatPound.Util.Gfx;

export import FatPound.Util.Color;
export import FatPound.Util.Common;
export import FatPound.Util.Surface;
export import FatPound.Util.Timer;
export import FatPound.Util.ViewXM;

import std;

export namespace fatpound::util
{
    template <::std::floating_point FP = float, ::std::integral I>
    FAT_CMATH_CONSTEXPR23
    auto HourMinuteHandAngle(I hours, I minutes) -> FP
    {
        if constexpr (::std::signed_integral<I>)
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

        const auto& angle = ::std::fabs(static_cast<FP>(11 * minutes - 60 * hours) / static_cast<FP>(2));

        return (angle > 180) ? static_cast<FP>(360 - angle) : angle;
    }
}

module : private;
