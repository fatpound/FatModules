module;

#include <_macros/STL.hxx>

export module FatPound.Geometry.FieldOfView;

import FatPound.Math.Multiplicative;
import FatPound.Geometry.Common;

import std;

export namespace fatpound::geometry
{
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto HFOV(const U& sensorWidth,    const U& focalLength) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(sensorWidth * 0.5 / focalLength));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto VFOV(const U& sensorHeight,   const U& focalLength) noexcept -> T
    {
        return HFOV<T>(sensorHeight, focalLength);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto DFOV(const U& sensorDiagonal, const U& focalLength) noexcept -> T
    {
        return HFOV<T>(sensorDiagonal, focalLength);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto DFOV(const U& sensorWidth, const U& sensorHeight, const U& focalLength) noexcept -> T
    {
        return DFOV<T>(Hypotenuse<>(sensorWidth, sensorHeight), focalLength);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto DFOV_(const U& hFovRad, const U& vFovRad) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(Hypotenuse<>(std::tan(hFovRad * 0.5), std::tan(vFovRad * 0.5))));
    }

    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto HFOV_To_VFOV(const U& hFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(hFovRad * 0.5) / aspectRatio));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto HFOV_To_DFOV(const U& hFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(hFovRad * 0.5) * std::sqrt(1.0 + 1.0 / math::Square<>(aspectRatio))));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto VFOV_To_HFOV(const U& vFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(vFovRad * 0.5) * aspectRatio));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto VFOV_To_DFOV(const U& vFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(vFovRad * 0.5) * std::sqrt(1.0 + math::Square<>(aspectRatio))));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto DFOV_To_HFOV(const U& dFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(dFovRad * 0.5) / std::sqrt(1.0 + 1.0 / math::Square<>(aspectRatio))));
    }
    template <std::floating_point T = float, std::convertible_to<T> U> CX_MATH26 auto DFOV_To_VFOV(const U& dFovRad, const U& aspectRatio) noexcept -> T
    {
        return static_cast<T>(2.0 * std::atan(std::tan(dFovRad * 0.5) / std::sqrt(1.0 + math::Square<>(aspectRatio))));
    }

    template <std::floating_point T = float, std::convertible_to<T> U>
    CX_MATH26 auto FocalLength(const U& fovRad, const U& sensorSize) noexcept -> T
    {
        return static_cast<T>((sensorSize * 0.5) / std::tan(fovRad * 0.5));
    }
}

// module : private;
