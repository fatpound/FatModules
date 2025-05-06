module;

export module FatPound.Traits.UdtKinds;

import std;

export namespace fatpound::traits
{
    template <typename T>
    concept ClassOrStruct = std::is_class_v<T>;

    template <typename T>
    concept Union = std::is_union_v<T>;

    template <typename T>
    concept ScopedEnum = std::is_scoped_enum_v<T>;

    template <typename T>
    concept Enum = std::is_enum_v<T>; // or ScopedEnum<T>
}

module : private;
