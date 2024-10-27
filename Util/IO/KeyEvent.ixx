module;

export module FatPound.Util.IO.KeyEvent;

import std;

export namespace fatpound::util::io
{
    struct KeyEvent final
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