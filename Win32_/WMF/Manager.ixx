module;

#include <FatWin32.hpp>

#include <mfapi.h>

export module FatPound.Win32.WMF.Manager;

import std;

export namespace fatpound::win32::wmf
{
    class Manager final
    {
    public:
        explicit Manager()
        {
            const auto hr = ::MFStartup(MF_VERSION);

            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to initialize Media Foundation!");
            }
        }
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept
        {
            ::MFShutdown();
        }


    protected:


    private:
    };
}

module : private;