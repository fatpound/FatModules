module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

#include <d2d1.h>

#include <wrl.h>

#define SOFT_COLOR_EFFECT false

#pragma comment(lib, "d2d1")

export module FatPound.Win32.D2D.Graphics;

import FatPound.Util;

import std;

namespace dx = DirectX;

export namespace fatpound::win32::d2d
{
    class Graphics final
    {
    public:
        explicit Graphics(const HWND hWnd, const FATSPACE_UTIL::ScreenSizeInfo& dimensions)
            :
            mc_width(dimensions.m_width),
            mc_height(dimensions.m_height)
        {
            HRESULT hr{};

            ::Microsoft::WRL::ComPtr<ID2D1Factory> pFactory{};

            hr = ::D2D1CreateFactory<ID2D1Factory>(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("A problem occured when creating the Factory!");
            }

            RECT rect{};
            ::GetClientRect(hWnd, &rect);

            hr = pFactory->CreateHwndRenderTarget(
                ::D2D1::RenderTargetProperties(),
                ::D2D1::HwndRenderTargetProperties(hWnd, ::D2D1::SizeU(static_cast<UINT32>(rect.right), static_cast<UINT32>(rect.bottom))),
                &m_pRenderTarget_
            );

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("A problem occured when creating the HwndRenderTarget!");
            }
        }

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
        void ClearScreen(const float r, const float g, const float b) noexcept
        {
            m_pRenderTarget_->Clear(::D2D1::ColorF(r, g, b));
        }

        void DrawLine(const D2D1_POINT_2F p0, const D2D1_POINT_2F p1) noexcept
        {
            m_pRenderTarget_->DrawLine(p0, p1, m_pBrush_.Get());
        }
        void DrawLine(const D2D1_POINT_2F p0, const D2D1_POINT_2F p1, const D2D1_COLOR_F color) noexcept
        {
            m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

            m_pRenderTarget_->DrawLine(p0, p1, m_pBrush_.Get());
        }
        void DrawClosedPolyLine(const std::vector<::DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F color) noexcept
        {
            m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

            for (std::size_t i = 0u; i < vertices.size(); ++i)
            {
                const auto& current = vertices[i];
                const auto& next = vertices[(i + 1u) % vertices.size()];

                DrawLine(
                    D2D1::Point2F(current.x, current.y),
                    D2D1::Point2F(next.x, next.y)
                );
            }
        }
        void DrawClosedPolyLine(const std::vector<::DirectX::XMFLOAT2>& vertices, const D2D1_COLOR_F color, ::DirectX::XMMATRIX transform) noexcept
        {
            m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

            for (std::size_t i = 1u; i < vertices.size() + 1u; ++i)
            {
                const auto& vec0 = ::dx::XMVector2TransformCoord(::dx::XMLoadFloat2(&vertices[i - 1u]), transform);
                const auto& vec1 = ::dx::XMVector2TransformCoord(::dx::XMLoadFloat2(&vertices[i % vertices.size()]), transform);

                ::dx::XMFLOAT2 transformed0;
                ::dx::XMFLOAT2 transformed1;
                ::dx::XMStoreFloat2(&transformed0, vec0);
                ::dx::XMStoreFloat2(&transformed1, vec1);

                DrawLine(
                    D2D1::Point2F(transformed0.x, transformed0.y),
                    D2D1::Point2F(transformed1.x, transformed1.y)
                );
            }
        }

        void EndFrame() noexcept
        {
            m_pRenderTarget_->EndDraw();
        }


    public:
        const std::size_t mc_width;
        const std::size_t mc_height;


    protected:
        
        
    private:
        ::Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget_;
        ::Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>  m_pBrush_;
    };
}

module : private;