#pragma once

#define NAMESPACE_FATPOUND            ::fatpound      

#define FATSPACE                      NAMESPACE_FATPOUND

#define FATSPACE_AUTOMATA             ::fatpound::automata
#define FATSPACE_COLORS               ::fatpound::colors
#define FATSPACE_CONCURRENCY          ::fatpound::concurrency
#define FATSPACE_MATH                 ::fatpound::math
#define FATSPACE_WIN32                ::fatpound::win32
#define FATSPACE_UTIL                 ::fatpound::util

#define FATSPACE_UTIL_TIME            FATSPACE_UTIL::time
#define FATSPACE_UTIL_IO              FATSPACE_UTIL::io
#define FATSPACE_UTIL_GFX             FATSPACE_UTIL::gfx

// these will be refactored later
#define FATSPACE_D2D                  FATSPACE_WIN32::d2d
#define FATSPACE_D3D11                FATSPACE_WIN32::d3d11
#define FATSPACE_DIRECTX              FATSPACE_WIN32::directx
#define FATSPACE_DXGI                 FATSPACE_WIN32::dxgi
#define FATSPACE_VISUAL               FATSPACE_D3D11::visual
#define FATSPACE_PIPELINE             FATSPACE_D3D11::pipeline
#define FATSPACE_PIPELINE_ELEMENT     FATSPACE_PIPELINE::element
#define FATSPACE_PIPELINE_RESOURCE    FATSPACE_PIPELINE::resource
#define FATSPACE_PIPELINE_SYSTEM      FATSPACE_PIPELINE::system