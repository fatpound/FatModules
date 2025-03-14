module;

#if defined(_MSC_VER)
#include <cstdlib>
#ifndef FAT_MEMORY_ALIGNED_ALLOCATE_WITH
    #define FAT_MEMORY_ALIGNED_ALLOCATE_WITH(align, size) (::_aligned_malloc(size, align))
#endif
#ifndef FAT_MEMORY_ALIGNED_FREER
    #define FAT_MEMORY_ALIGNED_FREER ::_aligned_free
#endif
#else
#ifndef FAT_MEMORY_ALIGNED_ALLOCATE_WITH
    #define FAT_MEMORY_ALIGNED_ALLOCATE_WITH(align, size) (::std::aligned_alloc(align, size))
#endif
#ifndef FAT_MEMORY_ALIGNED_FREER
    #define FAT_MEMORY_ALIGNED_FREER ::std::free
#endif
#endif

export module FatPound.Memory;

import std;

export namespace fatpound::memory
{
    template <typename T>
    auto AlignedAlloc(const std::size_t& alignBytes, const std::size_t& size) -> T*
    {
        if (auto* const ptr = static_cast<T*>(FAT_MEMORY_ALIGNED_ALLOCATE_WITH(alignBytes, (size * sizeof(T)))))
        {
            return ptr;
        }
        else
        {
            throw std::runtime_error{ "Aligned allocation failed!" };
        }
    }

    template <typename T>
    struct AlignedUniquePtr
    {
        using ptr_type = std::unique_ptr<T, decltype(&FAT_MEMORY_ALIGNED_FREER)>;

        static auto Make(const std::size_t& alignBytes) -> ptr_type
        {
            return ptr_type{ AlignedAlloc<T>(alignBytes, 1), &std::free };
        }
    };
    
    template <typename T>
    struct AlignedUniquePtr<T[]>
    {
        using ptr_type = std::unique_ptr<T[], decltype(&FAT_MEMORY_ALIGNED_FREER)>;

        static auto Make(const std::size_t& alignBytes, const std::size_t& size) -> ptr_type
        {
            return ptr_type{ AlignedAlloc<T>(alignBytes, size), &std::free };
        }
    };

    template <typename T>
    using AlignedUniquePtr_t = AlignedUniquePtr<T>::ptr_type;
}

module : private;
