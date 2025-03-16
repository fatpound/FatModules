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
    auto AlignedAlloc(const ::std::size_t& alignBytes, const ::std::size_t& size) -> T*
    {
        if (auto* const ptr = static_cast<T*>(FAT_MEMORY_ALIGNED_ALLOCATE_WITH(alignBytes, (size * sizeof(T)))))
        {
            return ptr;
        }
        else
        {
            throw ::std::runtime_error{ "Aligned allocation failed!" };
        }
    }

    namespace details
    {
        template <typename T>
        struct AlignedUPtr
        {
            using ptr_type = ::std::unique_ptr<T,   decltype(&FAT_MEMORY_ALIGNED_FREER)>;
        };

        template <typename T>
        struct AlignedUPtr<T[]>
        {
            using ptr_type = ::std::unique_ptr<T[], decltype(&FAT_MEMORY_ALIGNED_FREER)>;
        };
    }

    template <typename T>
    using AlignedUniquePtr = details::AlignedUPtr<T>::ptr_type;

    template <typename T>
    auto MakeAlignedUniquePtr(const ::std::size_t& alignBytes, [[maybe_unused]] const ::std::size_t& size)
    {
        if constexpr (::std::is_array_v<T>)
        {
            return AlignedUniquePtr<T>(AlignedAlloc<::std::remove_all_extents_t<T>>(alignBytes, size), &FAT_MEMORY_ALIGNED_FREER);
        }
        else
        {
            return AlignedUniquePtr<T>(AlignedAlloc<T>(alignBytes, 1u), &FAT_MEMORY_ALIGNED_FREER);
        }
    }
}

module : private;
