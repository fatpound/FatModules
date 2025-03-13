#pragma once

// fat->pound

#define IS_GFX_FRAMEWORK  false
#define WITH_EXPERIMENTAL false

#if   defined(_MSC_VER) or defined(_MSC_FULL_VER)
    #define FAT_FORCEINLINE __forceinline
#elif defined(__INTEL_LLVM_COMPILER)
    #define FAT_FORCEINLINE __inline
#elif defined(__clang__)
    #define FAT_FORCEINLINE [[gnu::always_inline]] [[gnu::gnu_inline]] inline
#elif defined(__GNUC__)
    #define FAT_FORCEINLINE [[gnu::always_inline]] inline
#else
    #error unsupported compiler detected
#endif

#include <version>

#if   __cpp_lib_constexpr_cmath == 202202L
    #ifndef FAT_CMATH_CONSTEXPR23
    #define FAT_CMATH_CONSTEXPR23 constexpr
    #endif
#elif __cpp_lib_constexpr_cmath == 202306L
    #ifndef FAT_CMATH_CONSTEXPR26
    #define FAT_CMATH_CONSTEXPR26 constexpr
    #endif
#else
    #ifndef FAT_CMATH_CONSTEXPR23
    #define FAT_CMATH_CONSTEXPR23
    #endif
    #ifndef FAT_CMATH_CONSTEXPR26
    #define FAT_CMATH_CONSTEXPR26
    #endif
#endif
