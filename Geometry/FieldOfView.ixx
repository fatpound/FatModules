module;

#include <_macros/STL.hxx>

export module FatPound.Geometry.FieldOfView;

import std;

export namespace fatpound::geometry
{
    template <std::floating_point T = float> CX_MATH26 auto HFOV_To_VFOV(const T& hFovRad, const T& aspectRatio) noexcept -> T
    {
        return 2.0 * std::atan(std::tan(hFovRad / 2.0) / aspectRatio);
    }
    template <std::floating_point T = float> CX_MATH26 auto VFOV_To_HFOV(const T& vFovRad, const T& aspectRatio) noexcept -> T
    {
        return 2.0 * std::atan(std::tan(vFovRad / 2.0) * aspectRatio);
    }

    template <std::floating_point T = float>
    CX_MATH26 auto CalculateFocalLength(const T& fovRad, const T& sensorSize) noexcept -> T
    {
        return (sensorSize / 2.0) / std::tan(fovRad / 2.0);
    }
}

// module : private;
