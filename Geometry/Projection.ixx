module;

export module FatPound.Geometry.Projection;

import std;

export namespace fatpound::geometry
{
    template <std::floating_point T = float>
    constexpr auto UnprojectPixelCoordinate(const T& pixelCoord, const T& centerCoord, const T& pixelDepth, const T& focalLength) noexcept -> T
    {
        return (pixelCoord - centerCoord) * pixelDepth / focalLength;
    }
}

// module : private;
