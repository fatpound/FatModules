#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#define FAT_THROW_HRX_IF_FAILED(hrcall, notestring)                                \
    {                                                                              \
        if (const auto& hr = (hrcall); FAILED(hr))                                 \
        {                                                                          \
            throw fatpound::win32::HrException(hr, notestring "\nCode: " #hrcall); \
        }                                                                          \
    }

#endif
