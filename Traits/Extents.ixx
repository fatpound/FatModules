module;

export module FatPound.Traits.Extents;

import std;

export namespace fatpound::traits
{
    template <typename T>
    concept BoundedArray = std::is_bounded_array_v<T>;

    template <typename T>
    concept UnboundedArray = std::is_unbounded_array_v<T>;

    template <typename T>
    concept Array = std::is_array_v<T>; // or BoundedArray<T> or UnboundedArray<T>
}

// module : private;
