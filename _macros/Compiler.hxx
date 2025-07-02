#pragma once

#if defined(_MSC_VER)
    #define FATLIB_FORCEINLINE __forceinline
#elif defined(__INTEL_LLVM_COMPILER)
    #define FATLIB_FORCEINLINE __inline
#elif defined(__clang__)
    #define FATLIB_FORCEINLINE [[clang::always_inline]] inline
#elif defined(__GNUC__)
    #define FATLIB_FORCEINLINE [[gnu::always_inline]] inline
#else
    #error unsupported compiler detected
#endif

#ifdef _MSC_VER
    #define FATLIB_EBCO __declspec(empty_bases)
#else
    #define FATLIB_EBCO
#endif
