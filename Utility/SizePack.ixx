module;

export module FatPound.Utility.SizePack;

import std;

export namespace fatpound::utility
{
    struct alignas(16) SizePack
    {
        std::size_t   m_width{};
        std::size_t   m_height{};
    };
}

// module : private;
