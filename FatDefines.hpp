#pragma once

#include <version>

#ifndef FAT_CMATH_CONSTEXPR23
#ifdef __cpp_lib_constexpr_cmath
#define FAT_CMATH_CONSTEXPR23 constexpr
#else
#define FAT_CMATH_CONSTEXPR23
#endif // __cpp_lib_constexpr_cmath
#endif // FAT_CMATH_CONSTEXPR23

#define IS_GFX_FRAMEWORK  false
#define WITH_EXPERIMENTAL false
