module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Compiler.hxx>

    #include <Win32_/FatWin.hpp>
    #include <d2d1_3.h>

    #ifdef __INTELLISENSE__
        #include <wrl.h>
    #endif

    #include <DirectXMath.h>

    #pragma comment(lib, "d2d1")
#endif

export module FatPound.Win32.D2D.Graphics;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    // import <Win32_/WinAPI.hxx>;
    import <wrl.h>;
#endif

import FatPound.Traits.Bitwise;
import FatPound.Utility.SizePack;

import std;

export namespace fatpound::win32::d2d
{
    /// @brief The Graphics class provides a wrapper for Direct2D rendering operations on a window, including drawing lines and polylines, clearing the screen, and managing the drawing frame lifecycle
    ///
    class Graphics final
    {
    public:
        using Color_t = D2D1_COLOR_F;
        using Point_t = D2D1_POINT_2F;
        

    public:
        explicit Graphics(const HWND& hWnd, const utility::SizePack& dimensions)
            :
            mc_dimensions_(dimensions)
        {
            Microsoft::WRL::ComPtr<ID2D1Factory> pFactory;
            
            if (FAILED(D2D1CreateFactory<ID2D1Factory>(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
            {
                throw std::runtime_error("A problem occured when creating the D2D1 factory!");
            }

            if (FAILED(pFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(GetWidth<UINT32>(), GetHeight<UINT32>())),
                &m_pRenderTarget_)))
            {
                throw std::runtime_error("A problem occured when creating the HwndRenderTarget!");
            }

            if (FAILED(m_pRenderTarget_->CreateSolidColorBrush(Color_t{ D2D1::ColorF::White }, &m_pSolidBrush_)))
            {
                throw std::runtime_error("Could NOT create SolidColorBrush!");
            }
        }

        explicit Graphics()                    = delete;
        explicit Graphics(const Graphics&)     = delete;
        explicit Graphics(Graphics&&) noexcept = delete;

        auto operator = (const Graphics&)     -> Graphics& = delete;
        auto operator = (Graphics&&) noexcept -> Graphics& = delete;
        ~Graphics() noexcept                               = default;


    public:
        template <traits::IntegralOrFloating T> FATLIB_FORCEINLINE constexpr auto GetWidth()  const noexcept -> T
        {
            return static_cast<T>(mc_dimensions_.m_width);
        }
        template <traits::IntegralOrFloating T> FATLIB_FORCEINLINE constexpr auto GetHeight() const noexcept -> T
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

        template <float r = 0.0F, float g = 0.0F, float b = 0.0F, float a = 1.0F>
        void ClearScreen() noexcept
        {
            m_pRenderTarget_->Clear(Color_t{ r, g, b, a });
        }


    public:
        auto GetSolidBrushColor() const noexcept -> Color_t
        {
            return m_pSolidBrush_->GetColor();
        }
        void SetSolidBrushColor(const Color_t& color) noexcept
        {
            m_pSolidBrush_->SetColor(color);
        }

        void DrawLine(const Point_t& p0, const Point_t& p1) noexcept
        {
            m_pRenderTarget_->DrawLine(p0, p1, m_pSolidBrush_.Get());
        }
        void DrawLine(const Point_t& p0, const Point_t& p1, const Color_t& color) noexcept
        {
            SetSolidBrushColor(color);

            DrawLine(p0, p1);
        }
        void DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices) noexcept
        {
            for (std::size_t i{}; i < vertices.size(); ++i)
            {
                const auto& current = vertices[i];
                const auto& next    = vertices[(i + 1U) % vertices.size()];

                DrawLine(
                    D2D1::Point2F(current.x, current.y),
                    D2D1::Point2F(next.x, next.y)
                );
            }
        }
        void DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const Color_t& color) noexcept
        {
            SetSolidBrushColor(color);

            DrawClosedPolyLine(vertices);
        }
        void DrawClosedPolyLine(const std::vector<DirectX::XMFLOAT2>& vertices, const Color_t& color, const DirectX::XMMATRIX& transform) noexcept
        {
            SetSolidBrushColor(color);

            std::vector<DirectX::XMFLOAT2> transformed_vertices;
            transformed_vertices.reserve(vertices.size());

            for (const auto& vertex : vertices)
            {
                auto vec = DirectX::XMLoadFloat2(&vertex);
                vec = DirectX::XMVector2TransformCoord(vec, transform);

                DirectX::XMFLOAT2 transformed;
                DirectX::XMStoreFloat2(&transformed, vec);

                transformed_vertices.push_back(transformed);
            }

            DrawClosedPolyLine(transformed_vertices, color);
        }

        void ClearScreen(const float& r, const float& g, const float& b, const float& a = 1.0F) noexcept
        {
            m_pRenderTarget_->Clear(Color_t{ r, g, b, a });
        }
        void EndFrame() noexcept
        {
            m_pRenderTarget_->EndDraw();
        }


    protected:
        
        
    private:
        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>   m_pRenderTarget_;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>    m_pSolidBrush_;

        const utility::SizePack                         mc_dimensions_;
    };
}

#endif

// module : private;
