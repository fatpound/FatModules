module;

#if FAT_BUILDING_WITH_MSVC
#include <FatWin32.hpp>
#endif

export module FatPound.Win32.WndClassEx;

#if FAT_BUILDING_WITH_MSVC

import std;

using std::string_literals::operator ""s;

export namespace fatpound::win32
{
    class WndClassEx final
    {
    public:
        explicit WndClassEx(const std::wstring& clsName = L"#fat->pound.Default.Window.Class#"s);

        explicit WndClassEx()                      = delete;
        explicit WndClassEx(const WndClassEx&)     = delete;
        explicit WndClassEx(WndClassEx&&) noexcept = delete;

        auto operator = (const WndClassEx&)     -> WndClassEx& = delete;
        auto operator = (WndClassEx&&) noexcept -> WndClassEx& = delete;
        ~WndClassEx() noexcept;


    public:
        auto GetAtom()     const noexcept -> ATOM;
        auto GetInstance() const noexcept -> HINSTANCE;


    protected:


    private:
        static auto CALLBACK HandleMsgSetup_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT;
        static auto CALLBACK HandleMsgThunk_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT;
        static auto ForwardMsg_(class IWindow* const pWnd, const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT;


    private:
        HINSTANCE m_hInstance_;
        ATOM m_atom_;
    };
}

#endif
