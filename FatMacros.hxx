#pragma once

#define IS_GFX_FRAMEWORK  false
#define WITH_EXPERIMENTAL false

#if defined(_MSC_VER)
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

#define FAT_EXTERNAL_WARNINGS 26432 26434 26439 26440 26447 26457 26460 26461 26462 26465 26477 26494 26495 26496 26497 26814 26849 6269 4127 4365 4946 5219
