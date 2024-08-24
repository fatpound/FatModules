module;

#include <FatWin32_.hpp>

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
        Graphics(HWND hWnd, const NAMESPACE_UTIL::ScreenSizeInfo& dimensions);

        Graphics() = delete;
        Graphics(const Graphics& src) = delete;
        Graphics(Graphics&& src) = delete;

        Graphics& operator = (const Graphics& src) = delete;
        Graphics& operator = (Graphics&& src) = delete;
        ~Graphics() noexcept = default;


    public:
        void BeginFrame() noexcept;
        void EndFrame() noexcept;

        void DrawLine(const D2D1_POINT_2F p0, const D2D1_POINT_2F p1) noexcept;
        void DrawLine(const D2D1_POINT_2F p0, const D2D1_POINT_2F p1, const D2D1_COLOR_F color) noexcept;

        void DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F color) noexcept;
        void DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F color, DirectX::XMMATRIX transform) noexcept;


    public:
        const std::size_t width_;
        const std::size_t height_;


    protected:


    private:
        void ClearScreen_(float r, float g, float b) noexcept;
        
        
    private:
        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> pRenderTarget_   = nullptr;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>  pBrush_          = nullptr;
    };
}