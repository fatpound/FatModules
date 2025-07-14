module;

export module FatPound.Utility.Gfx.SizePack;

import std;

export namespace fatpound::utility::gfx
{
    struct alignas(16) SizePack final
    {
        std::size_t   m_width{};
        std::size_t   m_height{};
    };
}

module : private;
