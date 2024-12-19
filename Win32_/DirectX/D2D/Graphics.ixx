module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

#include <d2d1.h>

#include <wrl.h>

export module FatPound.Win32.D2D.Graphics;

import FatPound.Util;

import std;

export namespace fatpound::win32::d2d
{
    class Graphics final
    {
    public:
        explicit Graphics(const HWND hWnd, const FATSPACE_UTIL::ScreenSizeInfo& dimensions);

        explicit Graphics() = delete;
        explicit Graphics(const Graphics& src) = delete;
        explicit Graphics(Graphics&& src) = delete;

        auto operator = (const Graphics& src) -> Graphics& = delete;
        auto operator = (Graphics&& src)      -> Graphics& = delete;
        ~Graphics() noexcept = default;


    public:
        template <bool Clear = true>
        void BeginFrame() noexcept
        {
            m_pRenderTarget_->BeginDraw();

            if constexpr (Clear)
            {
                ClearScreen<>();
            }
        }

        template <float r = 0.0f, float g = 0.0f, float b = 0.0f>
        void ClearScreen() noexcept
        {
            m_pRenderTarget_->Clear(::D2D1::ColorF(r, g, b));
        }


    public:
        void ClearScreen(const float r, const float g, const float b) noexcept;

        void DrawLine(const D2D1_POINT_2F p0, const D2D1_POINT_2F p1) noexcept;
        void DrawLine(const D2D1_POINT_2F p0, const D2D1_POINT_2F p1, const D2D1_COLOR_F color) noexcept;
        void DrawClosedPolyLine(const std::vector<::DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F color) noexcept;
        void DrawClosedPolyLine(const std::vector<::DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F color, ::DirectX::XMMATRIX transform) noexcept;

        void EndFrame() noexcept;


    public:
        const std::size_t mc_width;
        const std::size_t mc_height;


    protected:
        
        
    private:
        ::Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget_;
        ::Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>  m_pBrush_;
    };
}