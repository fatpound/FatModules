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
    template
    <
        ::std::unsigned_integral U,
        ::std::floating_point    FP = float
    >
    FAT_CMATH_CONSTEXPR23
    auto HourMinuteHandAngle(U hours, U minutes) -> FP
    {
        hours   %= 12;
        minutes %= 60;

        const auto angle = std::fabs((11 * minutes - 60 * hours) / 2);

        return (angle > 180) ? (360 - angle) : angle;
    }
}

module : private;