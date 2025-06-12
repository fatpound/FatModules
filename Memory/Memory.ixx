module;

#include <cstdlib>

#if defined(_MSVC_STL_VERSION) or FAT_BUILDING_ON_WINDOWS
    #define FAT_MEMORY_ALIGNED_ALLOCATOR _aligned_malloc
    #define FAT_MEMORY_ALIGNED_FREER     _aligned_free
#else
    #define FAT_MEMORY_ALIGNED_ALLOCATOR std::aligned_alloc
    #define FAT_MEMORY_ALIGNED_FREER     std::free
#endif

export module FatPound.Memory;

import FatPound.Traits.Extents;

import std;

namespace fatpound::memory
{
    template <typename T>
    struct AlignedUPtr
    {
        using ptr_type = std::unique_ptr<T, decltype(&FAT_MEMORY_ALIGNED_FREER)>;
    };

    template <typename T>
    struct AlignedUPtr<T[]>
    {
        using ptr_type = std::unique_ptr<T[], decltype(&FAT_MEMORY_ALIGNED_FREER)>;
    };
}

export namespace fatpound::memory
{
    template <typename T>
    using AlignedUniquePtr = AlignedUPtr<T>::ptr_type;

    template <typename T>
    auto AlignedAlloc(const std::size_t& alignBytes, const std::size_t& size) -> T*
    {
        if (auto* const ptr = static_cast<T*>(
#if defined(_MSVC_STL_VERSION) or FAT_BUILDING_ON_WINDOWS
            FAT_MEMORY_ALIGNED_ALLOCATOR(size * sizeof(T), alignBytes)
#else
            FAT_MEMORY_ALIGNED_ALLOCATOR(alignBytes, size * sizeof(T))
#endif
            ))
        {
            return ptr;
        }

        throw std::runtime_error{ "Aligned allocation failed!" };
    }

    void AlignedFree(void* const ptr) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-no-malloc, hicpp-no-malloc)
        FAT_MEMORY_ALIGNED_FREER(ptr);
        // NOLINTEND(cppcoreguidelines-no-malloc, hicpp-no-malloc)
    }

    template <traits::Array T>
    auto MakeAlignedUniquePtr(const std::size_t& alignBytes, const std::size_t& size)
    {
        return AlignedUniquePtr<T>(AlignedAlloc<std::remove_all_extents_t<T>>(alignBytes, size), &FAT_MEMORY_ALIGNED_FREER);
    }

    template <typename T>
    auto MakeAlignedUniquePtr(const std::size_t& alignBytes)
    {
        return AlignedUniquePtr<T>(AlignedAlloc<T>(alignBytes, 1U), &FAT_MEMORY_ALIGNED_FREER);
    }
}

module : private;
