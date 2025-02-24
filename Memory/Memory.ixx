module;

#include <cstdlib>

export module FatPound.Memory;

import std;

export namespace fatpound::memory
{
    template <typename T>
    auto AlignedAlloc(const std::size_t alignBytes, const std::size_t size) -> T*
    {
        if (auto* const ptr = static_cast<T*>(::_aligned_malloc(size * sizeof(T), alignBytes)); ptr == nullptr)
        {
            throw std::runtime_error{"::_aligned_malloc failed!"};
        }
        else
        {
            return ptr;
        }
    }

    template <typename T>
    struct AlignedUniquePtr
    {
        using ptr_type = std::unique_ptr<T, decltype(&::_aligned_free)>;

        static auto Make(const std::size_t alignBytes) -> ptr_type
        {
            return ptr_type{ AlignedAlloc<T>(alignBytes, 1z), &::_aligned_free };
        }
    };

    template <typename T>
    struct AlignedUniquePtr<T[]>
    {
        using ptr_type = std::unique_ptr<T[], decltype(&::_aligned_free)>;

        static auto Make(const std::size_t alignBytes, const std::size_t size) -> ptr_type
        {
            return ptr_type{ AlignedAlloc<T>(alignBytes, size), &::_aligned_free };
        }
    };

    template <typename T>
    using AlignedUniquePtr_t = AlignedUniquePtr<T>::ptr_type;
}

module : private;