module;

#define FATPOUND_FULL_WIN_TARGETED

#include <FatWin32.hpp>

#include <gdiplus.h>

#undef FATPOUND_FULL_WIN_TARGETED

#pragma comment(lib, "gdiplus")

export module FatPound.Win32.GDI_Plus.Manager;

export namespace fatpound::win32::gdi_plus
{
    class Manager final
    {
    public:
        Manager() noexcept
        {
            if (s_ref_count_ == 0)
            {
                ::Gdiplus::GdiplusStartupInput gdiplusStartupInput;
                ::Gdiplus::GdiplusStartup(&s_gdiPlus_token_, &gdiplusStartupInput, nullptr);
            }

            ++s_ref_count_;
        }
        Manager(const Manager& src) = delete;
        Manager(Manager&& src) = delete;

        auto operator = (const Manager& src) -> Manager& = delete;
        auto operator = (Manager&& src)      -> Manager& = delete;
        ~Manager() noexcept
        {
            --s_ref_count_;

            if (s_ref_count_ == 0)
            {
                ::Gdiplus::GdiplusShutdown(s_gdiPlus_token_);
            }
        }


    protected:


    private:
        inline static ::ULONG_PTR s_gdiPlus_token_{};

        inline static int s_ref_count_{};
    };
}

module : private;