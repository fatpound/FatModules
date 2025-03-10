module;

#include <FatNamespaces.hpp>
#include <FatMacros.hpp>

export module FatPound.Util;

export import FatPound.Util.Gfx;

export import FatPound.Util.Color;
export import FatPound.Util.Surface;
export import FatPound.Util.Gfx.SizePack;
export import FatPound.Util.Timer;
export import FatPound.Util.ViewXM;

import FatPound.Math.Numbers.Sets;

import std;

export namespace fatpound::util
{
    template <FATSPACE_NUMBERS::Natural N, FATSPACE_NUMBERS::Floating F = float>
    FAT_CMATH_CONSTEXPR23
    auto HourMinuteHandAngle(N hours, N minutes) -> F
    {
        hours   %= 12;
        minutes %= 60;

        const auto angle = std::fabs((11 * minutes - 60 * hours) / 2);

        return (angle > 180) ? (360 - angle) : angle;
    }
}

module : private;