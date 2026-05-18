module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <mfapi.h>
    #endif

    #include <_macros/Win.hxx>
#endif

export module FatPound.Win32.MF.Manager;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <Win32_/WinAPI.hxx>;
#endif

import FatPound.Win32.HrException;
import std;

export namespace fatpound::win32::mf
{
    class Manager final
    {
    public:
        explicit Manager()
        {
            FAT_THROW_HRX_IF_FAILED(MFStartup(MF_VERSION), "Failed to initialize Microsoft Media Foundation!");
        }
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept
        {
            MFShutdown();
        }


    protected:


    private:
    };
}

#endif

// module : private;
