module;

#if FAT_BUILDING_WITH_MSVC
#include <FatNamespaces.hpp>
#include <FatDefines.hpp>

#include <FatWin32.hpp>
#include <d2d1.h>
#include <wrl.h>

#include <DirectXMath.h>

#pragma comment(lib, "d2d1")
#endif

export module FatPound.Win32.D2D.Graphics;

#if FAT_BUILDING_WITH_MSVC

import FatPound.Bitwise.Concepts;
import FatPound.Util.Gfx.SizePack;

import std;

namespace dx = DirectX;

export namespace fatpound::win32::d2d
{
    class Graphics final
    {
    public:
        explicit Graphics(const HWND hWnd, const FATSPACE_UTIL_GFX::SizePack& dimensions)
            :
            mc_dimensions_(dimensions)
        {
            ::Microsoft::WRL::ComPtr<ID2D1Factory> pFactory;

            {
                const auto& hr = ::D2D1CreateFactory<ID2D1Factory>(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

                if (FAILED(hr))
                {
                    throw std::runtime_error("A problem occured when creating the D2D1 factory!");
                }
            }

            {
                const auto& hr = pFactory->CreateHwndRenderTarget(
                    ::D2D1::RenderTargetProperties(),
                    ::D2D1::HwndRenderTargetProperties(hWnd, ::D2D1::SizeU(GetWidth<UINT32>(), GetHeight<UINT32>())),
                    &m_pRenderTarget_
                );

                if (FAILED(hr))
                {
                    throw std::runtime_error("A problem occured when creating the HwndRenderTarget!");
                }
            }
        }

        explicit Graphics()                    = delete;
        explicit Graphics(const Graphics&)     = delete;
        explicit Graphics(Graphics&&) noexcept = delete;

        auto operator = (const Graphics&)     -> Graphics& = delete;
        auto operator = (Graphics&&) noexcept -> Graphics& = delete;
        ~Graphics() noexcept                               = default;


    public:
        template <bitwise::Integral_Or_Floating T> FAT_FORCEINLINE constexpr auto GetWidth()  const noexcept -> T
        {
            return static_cast<T>(mc_dimensions_.m_width);
        }
        template <bitwise::Integral_Or_Floating T> FAT_FORCEINLINE constexpr auto GetHeight() const noexcept -> T
        {
            return static_cast<T>(mc_dimensions_.m_height);
        }

        template <bool Clear = true>
        void BeginFrame() noexcept
        {
            m_pRenderTarget_->BeginDraw();

            if constexpr (Clear)
            {
                ClearScreen<>();
            }
        }

        template <float r = 0.0F, float g = 0.0F, float b = 0.0F>
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
        void DrawClosedPolyLine(const std::vector<::dx::XMFLOAT2>& vertices, const D2D1_COLOR_F& color) noexcept
        {
            m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

            for (std::size_t i{}; i < vertices.size(); ++i)
            {
                const auto& current = vertices[i];
                const auto& next = vertices[(i + 1U) % vertices.size()];

                DrawLine(
                    ::D2D1::Point2F(current.x, current.y),
                    ::D2D1::Point2F(next.x, next.y)
                );
            }
        }
        void DrawClosedPolyLine(const std::vector<::dx::XMFLOAT2>& vertices, const D2D1_COLOR_F& color, ::dx::XMMATRIX transform) noexcept
        {
            m_pRenderTarget_->CreateSolidColorBrush(color, &m_pBrush_);

            for (std::size_t i = 1U; i < vertices.size() + 1U; ++i)
            {
                const auto& vec0 = ::dx::XMVector2TransformCoord(::dx::XMLoadFloat2(&vertices[i - 1U]), transform);
                const auto& vec1 = ::dx::XMVector2TransformCoord(::dx::XMLoadFloat2(&vertices[i % vertices.size()]), transform);

                ::dx::XMFLOAT2 transformed0;
                ::dx::XMFLOAT2 transformed1;
                ::dx::XMStoreFloat2(&transformed0, vec0);
                ::dx::XMStoreFloat2(&transformed1, vec1);

                DrawLine(
                    ::D2D1::Point2F(transformed0.x, transformed0.y),
                    ::D2D1::Point2F(transformed1.x, transformed1.y)
                );
            }
        }

        void EndFrame() noexcept
        {
            m_pRenderTarget_->EndDraw();
        }


    protected:
        
        
    private:
        ::Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget_;
        ::Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>  m_pBrush_;

        const FATSPACE_UTIL_GFX::SizePack               mc_dimensions_;
    };
}

#endif

module : private;
