module;

#if FAT_BUILDING_WITH_MSVC
    #include <combaseapi.h>
#endif

export module FatPound.Win32.COM.Manager;

#if FAT_BUILDING_WITH_MSVC

import std;

export namespace fatpound::win32::com
{
    class Manager final
    {
    public:
        explicit Manager(const DWORD initFlags = COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)
        {
            const auto hr = ::CoInitializeEx(nullptr, initFlags);

            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to initialize COM!");
            }
        }

        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept
        {
            ::CoUninitialize();
        }


    protected:


    private:
    };
}

#endif

module : private;
