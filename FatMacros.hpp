#pragma once

#include <version>

#ifdef __cpp_lib_constexpr_cmath
#define FAT_CMATH_CONSTEXPR23 constexpr
#else
#define FAT_CMATH_CONSTEXPR23
#endif // DEBUG

#define IS_FRAMEWORK false