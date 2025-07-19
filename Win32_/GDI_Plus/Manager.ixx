module;

#pragma comment(lib, "gdiplus")

export module FatPound.Win32.GDI_Plus.Manager;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <Win32_/WinAPI.hxx>;

import std;

export namespace fatpound::win32::gdi_plus
{
    /// @brief Manages the initialization and shutdown of the GDI+ library using reference counting.
    ///        Ensures GDI+ is started once and properly shut down when no longer needed
    ///
    class Manager final
    {
    public:
        explicit Manager()
        {
            if (s_ref_count_ == 0)
            {
                const Gdiplus::GdiplusStartupInput gdiplusStartupInput;

                const auto& status = Gdiplus::GdiplusStartup(&s_gdiPlus_token_, &gdiplusStartupInput, nullptr);

                if (status not_eq Gdiplus::Ok)
                {
                    throw std::runtime_error("GDI+ initialization failed");
                }
            }

            ++s_ref_count_;
        }
        explicit Manager(const Manager&)     = delete;
        explicit Manager(Manager&&) noexcept = delete;

        auto operator = (const Manager&)     -> Manager& = delete;
        auto operator = (Manager&&) noexcept -> Manager& = delete;
        ~Manager() noexcept
        {
            --s_ref_count_;

            if (s_ref_count_ == 0)
            {
                Gdiplus::GdiplusShutdown(s_gdiPlus_token_);
            }
        }


    protected:


    private:
        inline static ULONG_PTR      s_gdiPlus_token_{};
        inline static unsigned int   s_ref_count_{};
    };
}

#endif

// module : private;
