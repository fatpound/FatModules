#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <_misc/FatCodex/Macros/ExternalWarnings_MSVC.hpp>

#pragma warning (push)
#pragma warning (disable : MSVC_EXWARN_GST)
#endif

#include <gst/gst.h>

#ifdef FATLIB_BUILDING_WITH_MSVC
#pragma warning (pop)
#endif
