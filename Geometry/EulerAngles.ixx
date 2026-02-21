module;

#include <_macros/STL.hxx>

export module FatPound.Geometry.EulerAngles;

import FatPound.Geometry.AngularConv;
import std;

export namespace fatpound::geometry
{
    template <std::floating_point T = float> CX_MATH26 auto CalculateYaw_Rad   (const T& fwd, const T& hrz) noexcept -> T
    {
        return std::atan2(hrz, fwd);
    }
    template <std::floating_point T = float> CX_MATH26 auto CalculatePitch_Rad (const T& fwd, const T& vrt) noexcept -> T
    {
        return std::atan2(vrt, fwd);
    }
    template <std::floating_point T = float> CX_MATH26 auto CalculateRoll_Rad  (const T& hrz, const T& vrt) noexcept -> T
    {
        return std::atan2(vrt, hrz);
    }
    template <std::floating_point T = float> CX_MATH26 auto CalculateYaw_Deg   (const T& fwd, const T& hrz) noexcept -> T
    {
        return RadToDeg<>(CalculateYaw_Rad<>(fwd, hrz));
    }
    template <std::floating_point T = float> CX_MATH26 auto CalculatePitch_Deg (const T& fwd, const T& vrt) noexcept -> T
    {
        return RadToDeg<>(CalculatePitch_Rad<>(fwd, vrt));
    }
    template <std::floating_point T = float> CX_MATH26 auto CalculateRoll_Deg  (const T& hrz, const T& vrt) noexcept -> T
    {
        return RadToDeg<>(CalculateRoll_Rad<>(hrz, vrt));
    }
}

// module : private;
