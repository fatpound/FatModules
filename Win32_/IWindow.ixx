module;

export module FatPound.Win32.IWindow;

#if FAT_BUILDING_WITH_MSVC

import <FatWin32.hxx>;

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
        virtual auto SetTitle  (const std::wstring& title) -> std::future<void> = 0;
        virtual auto GetHandle () const noexcept           -> HWND              = 0;
        virtual auto IsClosing () const noexcept           -> bool              = 0;


    protected:
        virtual auto HandleMessage_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT = 0;


    private:
    };
    
    class IWindow::ClassEx
    {
    public:
        explicit ClassEx(const WNDCLASSEX& wcx)
        {
            m_atom_ = ::RegisterClassEx(&wcx);

            if (m_atom_ == 0)
            {
                throw std::runtime_error { "ATOM could not be created!\n" "Consider checking WNDCLASSEX::lpszClassName" };
            }
        }
        explicit ClassEx(const std::wstring& wstr)
            :
            ClassEx(wstr.c_str())
        {

        }
        explicit ClassEx(const wchar_t* const clsName = L"#fatpound.Default.IWindow.ClassEx#")
            :
            ClassEx(CreateDefaultWNDCLASSEX_<>(m_hInstance_ = ModuleHandleOf(nullptr), clsName))
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
        auto GetAtom     () const noexcept -> ATOM
        {
            return m_atom_;
        }
        auto GetInstance () const noexcept -> HINSTANCE
        {
            return m_hInstance_;
        }


    protected:
        template <typename Wnd = IWindow> static auto CreateDefaultWNDCLASSEX_(const HINSTANCE& hInst, const wchar_t* const clsName) noexcept -> WNDCLASSEX
        {
            return
            {
                .cbSize        = sizeof(WNDCLASSEX),
                .style         = CS_OWNDC,
                .lpfnWndProc   = &ClassEx::HandleMsgSetup_<Wnd>,
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

        template <typename Wnd = IWindow> static auto CALLBACK HandleMsgSetup_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            if (msg == WM_NCCREATE)
            {
#ifdef UNICODE
    #define CREATESTRUCT_t CREATESTRUCTW
#else
    #define CREATESTRUCT_t CREATESTRUCTA
#endif
                Wnd* const pWnd = static_cast<Wnd*>(reinterpret_cast<CREATESTRUCT_t*>(lParam)->lpCreateParams);
#undef CREATESTRUCT_t

                ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

#pragma warning (push)
#pragma warning (disable : 5039)
                ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&ClassEx::HandleMsgThunk_<Wnd>));
#pragma warning (pop)

                if constexpr (std::same_as<Wnd, IWindow>)
                {
                    return ForwardMsg_(pWnd, hWnd, msg, wParam, lParam);
                }
                else
                {
                    return pWnd->HandleMessage_(hWnd, msg, wParam, lParam);
                }
            }

            return ::DefWindowProc(hWnd, msg, wParam, lParam);
        }
        template <typename Wnd = IWindow> static auto CALLBACK HandleMsgThunk_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            Wnd* const pWnd = reinterpret_cast<Wnd*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

            if constexpr (std::same_as<Wnd, IWindow>)
            {
                return ForwardMsg_(pWnd, hWnd, msg, wParam, lParam);
            }
            else
            {
                return pWnd->HandleMessage_(hWnd, msg, wParam, lParam);
            }
        }


    protected:
        HINSTANCE m_hInstance_{};
        ATOM      m_atom_{};


    private:
        static auto ForwardMsg_(IWindow* const pWnd, const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            return pWnd->HandleMessage_(hWnd, msg, wParam, lParam);
        }
    };

    using WndClassEx = IWindow::ClassEx;
}

#endif
