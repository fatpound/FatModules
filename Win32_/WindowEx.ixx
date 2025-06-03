module;

#if FAT_BUILDING_WITH_MSVC
    #include <FatNamespaces.hxx>
    #include <FatMacros.hxx>
    #include <FatWin32_Macros.hxx>

    #ifdef __INTELLISENSE__
        #include <FatWin32.hpp>
    #endif

    #include <DirectXMath.h>
#endif

export module FatPound.Win32.WindowEx;

#if FAT_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <FatWin32.hxx>;
#endif

import FatPound.Concurrency;
import FatPound.IO;
import FatPound.Traits.Bitwise;
import FatPound.Utility.Gfx.SizePack;
import FatPound.Win32.IWindow;

#ifdef __INTELLISENSE__
    import FatPound.Win32.Common;
#endif

import std;

namespace dx = DirectX;

using FATSPACE_UTILITY_GFX::SizePack;

export namespace fatpound::win32
{
    class WindowEx : public IWindow
    {
    public:
        explicit WindowEx(
            std::shared_ptr<WndClassEx>            pWndClassEx,
            const std::wstring                     title,
            const SizePack                         clientDimensions,
            std::shared_ptr<io::Keyboard>          pKeyboard         = std::make_shared<io::Keyboard>(),
            std::shared_ptr<io::Mouse>             pMouse            = std::make_shared<io::Mouse>(),
            const std::optional<dx::XMINT2>        position          = std::nullopt,
            const DWORD                            styles            = WS_VISIBLE bitor FAT_WNDSTYLE_EX,
            const DWORD                            exStyles          = {})
            :
            m_pKeyboard{ std::move<>(pKeyboard) },
            m_pMouse{ std::move<>(pMouse) },
            m_pWndClassEx_{ std::move<>(pWndClassEx) },
            mc_client_size_{ .m_width = clientDimensions.m_width, .m_height = clientDimensions.m_height },
            /////////////////////
#pragma region (thread w/o C4355)
#pragma warning (push)
#pragma warning (disable : 4355)
            m_msg_jthread_{ &WindowEx::MessageKernel_, this }
#pragma warning (pop)
#pragma endregion
        {
            auto future = DispatchTaskToQueue_<false>(
                [=, this]() -> void
                {
#if IN_DEBUG or IS_GFX_FRAMEWORK

                    RECT rect
                    {
                        .left   = 0L,
                        .top    = 0L,
                        .right  = rect.left + static_cast<LONG>(mc_client_size_.m_width),
                        .bottom = rect.top  + static_cast<LONG>(mc_client_size_.m_height)
                    };

                    if (const auto& retval = ::AdjustWindowRectEx(&rect, styles, false, exStyles); retval == 0)
                    {
                        throw std::runtime_error("Error occured when adjusting RECT");
                    }

#endif
                    
                    m_hWnd_ = ::CreateWindowEx(
                        exStyles,
                        MAKEINTATOM(m_pWndClassEx_->GetAtom()),
                        title.c_str(),
                        styles,
                        position.has_value() ? position->x : CW_USEDEFAULT,
                        position.has_value() ? position->y : CW_USEDEFAULT,

#if IN_DEBUG or IS_GFX_FRAMEWORK

                        rect.right  - rect.left,
                        rect.bottom - rect.top,
#else
                        static_cast<LONG>(mc_client_size_.m_width),
                        static_cast<LONG>(mc_client_size_.m_height),

#endif

                        nullptr,
                        nullptr,
                        ModuleHandleOf(),
                        this
                    );

                    if (m_hWnd_ == nullptr)
                    {
                        throw std::runtime_error("Error occured when creating HWND!");
                    }
                }
            );

            m_start_signal_.release();

            future.get();
        }

        explicit WindowEx()                    = delete;
        explicit WindowEx(const WindowEx&)     = delete;
        explicit WindowEx(WindowEx&&) noexcept = delete;

        auto operator = (const WindowEx&)     -> WindowEx& = delete;
        auto operator = (WindowEx&&) noexcept -> WindowEx& = delete;
        virtual ~WindowEx() noexcept(false) override
        {
            [[maybe_unused]]
            const auto future = DispatchTaskToQueue_<>(
                [this]() noexcept -> void
                {
                    [[maybe_unused]]
                    const auto&& retval = ::DestroyWindow(m_hWnd_);
                }
            );
        }


    public:
        virtual auto SetTitle  (const std::wstring& title) -> std::future<void> override final
        {
            auto future = DispatchTaskToQueue_<>(
                [=, this]() noexcept -> void
                {
                    [[maybe_unused]]
                    const auto&& retval = ::SetWindowText(m_hWnd_, title.c_str());
                }
            );

            return future;
        }
        virtual auto GetHandle () const noexcept -> HWND override final
        {
            return m_hWnd_;
        }
        virtual auto IsClosing () const noexcept -> bool override final
        {
            return m_is_closing_;
        }


    public:
        template <traits::IntegralOrFloating T> FAT_FORCEINLINE auto GetClientWidth  () const noexcept -> T
        {
            return static_cast<T>(mc_client_size_.m_width);
        }
        template <traits::IntegralOrFloating T> FAT_FORCEINLINE auto GetClientHeight () const noexcept -> T
        {
            return static_cast<T>(mc_client_size_.m_height);
        }


    public:
        std::shared_ptr<io::Keyboard> m_pKeyboard;
        std::shared_ptr<io::Mouse>    m_pMouse;


    protected:
        template <bool Notify = true, typename F, typename... Args>
        requires std::invocable<F, Args...>
        auto DispatchTaskToQueue_(F&& function, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
        {
            auto future = m_tasks_.Push<>(std::forward<F>(function), std::forward<Args>(args)...);

            if constexpr (Notify)
            {
                NotifyTaskDispatch_();
            }

            return future;
        }


    protected:
        virtual auto HandleMessage_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT override
        {
            switch (msg)
            {
            case WM_MOUSEMOVE:
                Process_WM_MOUSEMOVE_(wParam, lParam);
                return 0;

            case WM_LBUTTONDOWN:
                Process_WM_LBUTTONDOWN_();
                return 0;

            case WM_LBUTTONUP:
                Process_WM_LBUTTONUP_();
                return 0;

            case WM_RBUTTONDOWN:
                Process_WM_RBUTTONDOWN_();
                return 0;

            case WM_RBUTTONUP:
                Process_WM_RBUTTONUP_();
                return 0;

            case WM_MBUTTONDOWN:
                Process_WM_MBUTTONDOWN_();
                return 0;

            case WM_MBUTTONUP:
                Process_WM_MBUTTONUP_();
                return 0;

            case WM_MOUSEWHEEL:
                Process_WM_MOUSEWHEEL_(GET_WHEEL_DELTA_WPARAM(wParam));
                return 0;

            case WM_KILLFOCUS:
                Process_WM_KILLFOCUS_();
                return 0;

            case WM_KEYDOWN: [[fallthrough]];
            case WM_SYSKEYDOWN:
                Process_WM_SYSKEYDOWN_(wParam, lParam);
                break;

            case WM_KEYUP: [[fallthrough]];
            case WM_SYSKEYUP:
                Process_WM_SYSKEYUP_(wParam);
                break;

            case WM_CHAR:
                Process_WM_CHAR_(wParam);
                break;

            case WM_CLOSE:
                m_is_closing_ = true;
                break;

            case WM_DESTROY:
                m_hWnd_ = nullptr;
                ::PostQuitMessage(0);
                break;

            case scx_customTaskMsgId_:
                m_tasks_.ExecuteFirstAndPopOff();
                return 0;

            // this also controls window movement
            case WM_SYSCOMMAND:
                Process_WM_SYSCOMMAND_(wParam);
                break;

            default:
                break;
            }

            return ::DefWindowProc(hWnd, msg, wParam, lParam);
        }


    protected:
        FAT_FORCEINLINE void Process_WM_MOUSEMOVE_  (const WPARAM& wParam, const LPARAM& lParam)
        {
            const POINTS pt = MAKEPOINTS(lParam);

            if (pt.x >= 0
                and pt.x < GetClientWidth<SHORT>()
                and pt.y >= 0
                and pt.y < GetClientHeight<SHORT>()
                )
            {
                m_pMouse->AddMouseMoveEvent(pt.x, pt.y);

                if (not m_pMouse->IsInWindow())
                {
                    ::SetCapture(m_hWnd_);
                    m_pMouse->AddMouseEnterEvent();
                }
            }
            else
            {
                if (wParam bitand (MK_LBUTTON bitor MK_RBUTTON))
                {
                    m_pMouse->AddMouseMoveEvent(pt.x, pt.y);
                }
                else
                {
                    ::ReleaseCapture();
                    m_pMouse->AddMouseLeaveEvent();
                }
            }
        }
        FAT_FORCEINLINE void Process_WM_LBUTTONDOWN_()
        {
            m_pMouse->AddLeftPressEvent();
        }
        FAT_FORCEINLINE void Process_WM_LBUTTONUP_  ()
        {
            m_pMouse->AddLeftReleaseEvent();
        }
        FAT_FORCEINLINE void Process_WM_RBUTTONDOWN_()
        {
            m_pMouse->AddRightPressEvent();
        }
        FAT_FORCEINLINE void Process_WM_RBUTTONUP_  ()
        {
            m_pMouse->AddRightReleaseEvent();
        }
        FAT_FORCEINLINE void Process_WM_MBUTTONDOWN_()
        {
            m_pMouse->AddWheelPressEvent();
        }
        FAT_FORCEINLINE void Process_WM_MBUTTONUP_  ()
        {
            m_pMouse->AddWheelReleaseEvent();
        }
        FAT_FORCEINLINE void Process_WM_MOUSEWHEEL_ (const int& delta)
        {
            m_pMouse->ProcessWheelDelta(delta);
        }

        FAT_FORCEINLINE void Process_WM_KILLFOCUS_ () noexcept
        {
            m_pKeyboard->ClearKeyStateBitset();
        }
        FAT_FORCEINLINE void Process_WM_KEYDOWN_   (const WPARAM& wParam, const LPARAM& lParam)
        {
            Process_WM_SYSKEYDOWN_(wParam, lParam);
        }
        FAT_FORCEINLINE void Process_WM_SYSKEYDOWN_(const WPARAM& wParam, const LPARAM& lParam)
        {
            if ((not (lParam bitand 0x40000000)) or m_pKeyboard->AutoRepeatIsEnabled())
            {
                m_pKeyboard->AddKeyPressEvent(static_cast<unsigned char>(wParam));
            }
        }
        FAT_FORCEINLINE void Process_WM_KEYUP_     (const WPARAM& wParam)
        {
            Process_WM_SYSKEYUP_(wParam);
        }
        FAT_FORCEINLINE void Process_WM_SYSKEYUP_  (const WPARAM& wParam)
        {
            m_pKeyboard->AddKeyReleaseEvent(static_cast<unsigned char>(wParam));
        }
        FAT_FORCEINLINE void Process_WM_CHAR_      (const WPARAM& wParam)
        {
            m_pKeyboard->AddChar(static_cast<unsigned char>(wParam));
        }
        FAT_FORCEINLINE void Process_WM_SYSCOMMAND_(const WPARAM& wParam) noexcept
        {
            if ((wParam bitand 0xFFF0U) == SC_CLOSE)
            {
                ::PostMessage(m_hWnd_, WM_CLOSE, 0, 0);
            }
        }


    protected:
        static constexpr UINT scx_customTaskMsgId_ = WM_USER;


    protected:
        FATSPACE_CONCURRENCY::TaskQueue m_tasks_;
        std::shared_ptr<WndClassEx>     m_pWndClassEx_;
        const SizePack                  mc_client_size_;

        HWND                            m_hWnd_{};

        std::atomic_bool                m_is_closing_{};
        std::binary_semaphore           m_start_signal_{ 0 };
        std::jthread                    m_msg_jthread_;


    private:
        void NotifyTaskDispatch_() const
        {
            if (const auto& retval = ::PostMessage(m_hWnd_, scx_customTaskMsgId_, 0U, 0); retval == 0)
            {
                throw std::runtime_error{ "Failed to post task notification message!" };
            }
        }
        void MessageKernel_()
        {
            m_start_signal_.acquire();
            m_tasks_.ExecuteFirstAndPopOff();

            MSG msg{};

            while (::GetMessage(&msg, m_hWnd_, 0U, 0U) not_eq 0)
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
    };
}

#endif

module : private;
