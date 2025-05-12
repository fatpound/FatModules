module;

export module FatPound.Traits.Formation;

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

    template <typename T>
    concept Instantiable = requires()
    {
        requires std::is_object_v<T>; // or ClassOrStruct<T> or Union<T> or ScopedEnum<T> or Enum<T>

        T{};
    };
}

module : private;
