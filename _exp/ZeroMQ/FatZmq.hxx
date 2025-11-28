#pragma once

#include <_misc/FatCodex/Macros/ExternalWarnings_MSVC.hpp>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : MSVC_EXWARN_CPPZMQ)
#endif

#include <zmq.hpp>

#ifdef _MSC_VER
#pragma warning (pop)
#pragma comment(lib, "iphlpapi")
#endif
