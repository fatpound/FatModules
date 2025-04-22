module;

export module FatPound.IO.KeyEvent;

import std;

export namespace fatpound::io
{
    struct alignas(2) KeyEvent final
    {
        enum struct Type : std::uint8_t
        {
            Press,
            Release,

            Invalid
        };

        Type type{ Type::Invalid };
        
        std::underlying_type_t<Type> code{};
    };
}

module : private;
