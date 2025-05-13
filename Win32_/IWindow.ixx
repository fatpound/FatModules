module;

#ifdef __INTELLISENSE__
    #include <FatWin32.hpp>
#endif

export module FatPound.Win32.IWindow;

#if FAT_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <Windows.h>;
#endif

import FatPound.Win32.Common;

import std;

export namespace fatpound::win32
{
    class IWindow
    {
    public:
        class ClassEx;


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
    
    class IWindow::ClassEx final
    {
    public:
        explicit ClassEx(const WNDCLASSEX& wcx)
        {
            m_atom_ = ::RegisterClassEx(&wcx);

            if (m_atom_ == 0)
            {
                throw std::runtime_error{
                    "ATOM could not be created!\n\n"
                    "You should check ClassEx::lpszClassName\n"
                    "It should have a unique name. If that's not the problem\n"
                    "Then check other parameters too."
                };
            }
        }
        explicit ClassEx(const std::wstring& wstr)
            :
            ClassEx(wstr.c_str())
        {

        }
        explicit ClassEx(const wchar_t* const clsName = L"#fatpound.Default.IWindow.ClassEx#")
            :
            ClassEx(CreateDefaultWNDCLASSEX_(m_hInstance_ = ModuleHandleOf(nullptr), clsName))
        {

        }

        explicit ClassEx(const ClassEx&)     = delete;
        explicit ClassEx(ClassEx&&) noexcept = delete;

        auto operator = (const ClassEx&)     -> ClassEx& = delete;
        auto operator = (ClassEx&&) noexcept -> ClassEx& = delete;
        ~ClassEx() noexcept
        {
            [[maybe_unused]]
            const auto&& retval = ::UnregisterClass(MAKEINTATOM(m_atom_), m_hInstance_);
        }


    public:
        auto GetAtom()     const noexcept -> ATOM
        {
            return m_atom_;
        }
        auto GetInstance() const noexcept -> HINSTANCE
        {
            return m_hInstance_;
        }


    protected:


    private:
        static auto CreateDefaultWNDCLASSEX_(const HINSTANCE& hInst, const wchar_t* const clsName) noexcept -> WNDCLASSEX
        {
            return
            {
                .cbSize        = sizeof(WNDCLASSEX),
                .style         = CS_OWNDC,
                .lpfnWndProc   = &ClassEx::HandleMsgSetup_,
                .cbClsExtra    = 0,
                .cbWndExtra    = 0,
                .hInstance     = hInst,
                .hIcon         = nullptr,
                .hCursor       = ::LoadCursor(nullptr, IDC_ARROW),
                .hbrBackground = nullptr,
                .lpszMenuName  = nullptr,
                .lpszClassName = clsName,
                .hIconSm       = nullptr
            };
        }

        static auto CALLBACK HandleMsgSetup_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            if (msg == WM_NCCREATE)
            {
                IWindow* const pWnd = static_cast<IWindow*>(reinterpret_cast<CREATESTRUCT_t*>(lParam)->lpCreateParams);

                ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

#pragma warning (push)
#pragma warning (disable : 5039)
                ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&ClassEx::HandleMsgThunk_));
#pragma warning (pop)

                return ForwardMsg_(pWnd, hWnd, msg, wParam, lParam);
            }

            return ::DefWindowProc(hWnd, msg, wParam, lParam);
        }
        static auto CALLBACK HandleMsgThunk_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            IWindow* const pWnd = reinterpret_cast<IWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

            return ForwardMsg_(pWnd, hWnd, msg, wParam, lParam);
        }
        static auto ForwardMsg_(IWindow* const pWnd, const HWND hWnd, const UINT msg, const ::WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            return pWnd->HandleMessage_(hWnd, msg, wParam, lParam);
        }


    private:
        HINSTANCE m_hInstance_{};
        ATOM      m_atom_{};
    };

    using WndClassEx = IWindow::ClassEx;
}

#endif
