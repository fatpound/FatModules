#pragma once

#ifdef FATX_WITH_GSTREAMER

#include <_misc/FatCodex/Macros/ExternalWarnings_MSVC.hpp>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : MSVC_EXWARN_GST)
#endif

#include <gst/gst.h>

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#endif
