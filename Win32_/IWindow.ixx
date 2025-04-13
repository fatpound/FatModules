module;

#if FAT_BUILDING_WITH_MSVC
#include <FatWin32.hpp>
#endif

export module FatPound.Win32.IWindow;

#if FAT_BUILDING_WITH_MSVC

import FatPound.Win32.WndClassEx;

import std;

export namespace fatpound::win32
{
    class IWindow
    {
        friend WndClassEx;

    public:
        explicit IWindow()                   = default;
        explicit IWindow(const IWindow&)     = delete;
        explicit IWindow(IWindow&&) noexcept = delete;

        auto operator = (const IWindow&)     -> IWindow& = delete;
        auto operator = (IWindow&&) noexcept -> IWindow& = delete;
        virtual ~IWindow() noexcept(false)               = default;


    public:
        virtual auto SetTitle(const std::wstring& title) -> std::future<void> = 0;

        virtual auto GetHandle() const noexcept -> HWND = 0;

        virtual auto IsClosing() const noexcept -> bool = 0;


    protected:
        virtual auto HandleMessage_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT = 0;


    private:
    };
}

#endif

module : private;
