#pragma once

#include <_misc/FatCodex/Macros/ExternalWarnings_MSVC.hpp>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : MSVC_EXWARN_OPENCV)
#endif

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#ifdef _MSC_VER
#pragma warning (pop)
#endif
