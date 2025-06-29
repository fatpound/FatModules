module;

export module FatPound.Utility.Gfx.SizePack;

import std;

export namespace fatpound::utility::gfx
{
    struct alignas(8) SizePack final
    {
        std::uint32_t   m_width{};
        std::uint32_t   m_height{};
    };
}

module : private;
