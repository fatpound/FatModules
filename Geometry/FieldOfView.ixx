module;

#include <_macros/STL.hxx>

export module FatPound.Geometry.FieldOfView;

import std;

export namespace fatpound::geometry
{
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto HFOV_To_VFOV(const U& hFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(hFovRad / 2.0) / aspectRatio));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto VFOV_To_HFOV(const U& vFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(vFovRad / 2.0) * aspectRatio));
    }

    template <std::floating_point T = float, std::convertible_to<T> U>
    CX_MATH26 auto CalculateFocalLength(const U& fovRad, const U& sensorSize) noexcept -> T
    {
        return static_cast<T>((sensorSize / 2.0) / std::tan(fovRad / 2.0));
    }
}

// module : private;
