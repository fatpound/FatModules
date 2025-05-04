#pragma once

// fat->pound

#define IS_GFX_FRAMEWORK  false
#define WITH_EXPERIMENTAL false

#if   defined(_MSC_VER) or defined(_MSC_FULL_VER)
    #define FAT_FORCEINLINE __forceinline
#elif defined(__INTEL_LLVM_COMPILER)
    #define FAT_FORCEINLINE __inline
#elif defined(__clang__)
    #define FAT_FORCEINLINE [[clang::always_inline]] inline
#elif defined(__GNUC__)
    #define FAT_FORCEINLINE [[gnu::always_inline]] inline
#else
    #error unsupported compiler detected
#endif

#ifdef _MSC_VER
    #define FAT_EBCO __declspec(empty_bases)
#else
    #define FAT_EBCO
#endif

#include <version>

#ifdef __cpp_lib_constexpr_cmath
#if    __cpp_lib_constexpr_cmath == 202202L
    #ifndef FAT_CMATH_CONSTEXPR23
    #define FAT_CMATH_CONSTEXPR23 constexpr
    #endif
#elif  __cpp_lib_constexpr_cmath == 202306L
    #ifndef FAT_CMATH_CONSTEXPR26
    #define FAT_CMATH_CONSTEXPR26 constexpr
    #endif
#endif
#else
    #ifndef FAT_CMATH_CONSTEXPR23
    #define FAT_CMATH_CONSTEXPR23
    #endif
    #ifndef FAT_CMATH_CONSTEXPR26
    #define FAT_CMATH_CONSTEXPR26
    #endif
#endif

#define FAT_EXTERNAL_WARNINGS 26432 26434 26439 26440 26447 26457 26460 26461 26462 26465 26477 26494 26495 26496 26497 26814 26849 6269 4127 4365 4946 5219
