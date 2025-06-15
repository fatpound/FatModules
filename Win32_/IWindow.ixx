module;

export module FatPound.Win32.IWindow;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <Win32_/WinAPI.hxx>;

import std;

export namespace fatpound::win32
{
    /// @brief Abstract interface for windowing with multithreading support
    ///
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
        virtual auto HandleMsg_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT = 0;


    private:
    };
    
    /// @brief Manages the registration and unregistration of a window class (WNDCLASSEX) in the Windows API, while providing custom WndProc setup functions
    ///
    class IWindow::ClassEx
    {
    public:
        explicit ClassEx(const WNDCLASSEX& wcx)
            :
            m_hInstance_(wcx.hInstance),
            m_atom_(::RegisterClassEx(&wcx))
        {
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
            ClassEx(CreateDefaultWNDCLASSEX_<>(ModuleHandleOf(nullptr), clsName))
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
        template <typename Wnd = IWindow> static auto CreateDefaultWNDCLASSEX_(const HINSTANCE& hInst, const wchar_t* const clsName, const UINT& style = CS_OWNDC) noexcept -> WNDCLASSEX
        {
            return
            {
                .cbSize        = sizeof(WNDCLASSEX),
                .style         = style,
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
            // There is no way to pass a member function pointer for a custom Window class' WndProc to Window Creation.
            // One can only pass a function pointer which is type of => LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM)
            // 
            // There are few options for this. I will use SetWindowLongPtr for that. But first, the Window class object's address ('this' pointer) is required
            // 
            // Microsoft Documentation says:
            // The last and optional parameter of CreateWindowEx:
            // 
            // [in, optional] lpParam
            // Type: LPVOID
            // 
            // Pointer to a value to be passed to the window through the CREATESTRUCT structure (lpCreateParams member) pointed to by the lParam param of the WM_CREATE message.
            // This message is sent to the created window by this function before it returns.
            // 
            // That parameter will store 'this' pointer of whichever custom Window class object is creating the window, in the hWnd
            // 
            // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexw
            // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-createstructw
            // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-create
            // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-nccreate
            // 
            // WM_CREATE is sent before CreateWindowEx returns. And WndProc receives it (it starts immediately)
            // but, WM_NCCREATE (non-client area create) is sent BEFORE the WM_CREATE message is sent.
            // So, this function will receive WM_NCCREATE "first" (see the end of this function)
            // I've tested, it ran well. So here it is:

            if (msg == WM_NCCREATE)
            {
#ifdef UNICODE
    #define CREATESTRUCT_t CREATESTRUCTW
#else
    #define CREATESTRUCT_t CREATESTRUCTA
#endif
                Wnd* const pWnd = static_cast<Wnd*>(reinterpret_cast<CREATESTRUCT_t*>(lParam)->lpCreateParams);
#undef CREATESTRUCT_t

                
                // This function Changes an attribute of the specified window. The function also sets a value at the specified offset in the extra window memory.
                // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlongptrw
                // lets set it to an attribute of our hWnd
                // user data is fine => "This data is intended for use by the application that created the window. Its value is initially zero."
                ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

#pragma warning (push)
#pragma warning (disable : 5039)
                // https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-c5000-through-c5199?view=msvc-170
                // 
                // Then, set the new WndProc function's (HandleMsgThunk_) address
                ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&ClassEx::HandleMsgThunk_<Wnd>));
#pragma warning (pop)


                // now its time to see the new WndProc in work
                //
                return HandleMsgThunk_<Wnd>(hWnd, msg, wParam, lParam);
            }

            // If there is a message before WM_NCCREATE OR between it and WM_CREATE (and Microsoft did not document it)
            // DefWindowProc can handle it
            // Otherwise, the creation message is processed above and this function returns.

            return ::DefWindowProc(hWnd, msg, wParam, lParam);
        }
        template <typename Wnd = IWindow> static auto CALLBACK HandleMsgThunk_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            // Get 'userdata' which is a pointer to our custom Window class, from the hWnd
            // Then use that pointer and just call the member function

            Wnd* const pWnd = reinterpret_cast<Wnd*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

            if constexpr (std::same_as<Wnd, IWindow>)
            {
                return ForwardMsg_(pWnd, hWnd, msg, wParam, lParam);
            }
            else
            {
                return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
            }
        }


    protected:
        HINSTANCE m_hInstance_{};
        ATOM      m_atom_{};


    private:
        static auto ForwardMsg_(IWindow* const pWnd, const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
        }
    };

    using WndClassEx = IWindow::ClassEx;
}

#endif
