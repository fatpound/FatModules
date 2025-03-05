module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")

export module FatPound.Win32.D3D11.Graphics;

import FatPound.Win32.D3D11.Pipeline;
import FatPound.Win32.D3D11.Visual;

import FatPound.Math;
import FatPound.Util;

import std;

namespace dx  = DirectX;
namespace wrl = Microsoft::WRL;

using FATSPACE_UTIL::Color;
using FATSPACE_UTIL::Surface;
using FATSPACE_UTIL::ScreenSizeInfo;

export namespace fatpound::win32::d3d11
{
    template <bool Framework = false>
    class Graphics final
    {
        static constexpr auto NotFramework = std::bool_constant<not Framework>::value;
        static constexpr auto RasterizationEnabled = NotFramework;

        using ResourcePack_t = ::std::conditional_t<Framework, FATSPACE_UTIL_GFX::FrameworkResourcePack, FATSPACE_UTIL_GFX::ResourcePack>;
        using float_t = float;

    public:
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions)
            :
            mc_hWnd_(hWnd),
            mc_dimensions_{ dimensions }
        {
            InitCommon_();
            
            if constexpr (RasterizationEnabled)
            {
                InitRasterizer_();
            }
        }
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions)  requires(Framework)
            :
            m_res_pack_(dimensions),
            mc_hWnd_(hWnd),
            mc_dimensions_{ dimensions }
        {
            InitCommon_();
            InitFramework_();
        }
        explicit Graphics(const HWND hWnd, std::unique_ptr<Surface> pSurface) requires(Framework)
            :
            Graphics(hWnd, pSurface->GetScreenSizeInfo())
        {
            BindSurface(std::move(pSurface));
        }

        explicit Graphics()                    = delete;
        explicit Graphics(const Graphics&)     = delete;
        explicit Graphics(Graphics&&) noexcept = delete;

        auto operator = (const Graphics&)     -> Graphics& = delete;
        auto operator = (Graphics&&) noexcept -> Graphics& = delete;
        ~Graphics() noexcept                               = default;
        ~Graphics() noexcept requires(Framework)
        {
            if (GetImmediateContext() not_eq nullptr) [[likely]]
            {
                try
                {
                    GetImmediateContext()->ClearState();
                }
                catch (...)
                {
                    OutputDebugString(L"COM Exception caught in Graphics<Framework> destructor!\n");
                }
            }
        }


    public:
        template <FATSPACE_MATH::numbers::Rational Q> constexpr auto GetWidth()  const noexcept
        {
            return static_cast<Q>(mc_dimensions_.m_width);
        }
        template <FATSPACE_MATH::numbers::Rational Q> constexpr auto GetHeight() const noexcept
        {
            return static_cast<Q>(mc_dimensions_.m_height);
        }

        template <bool FullBlack = true, float_t red = 1.0f, float_t green = 1.0f, float_t blue = 1.0f, float_t alpha = 1.0f>
        void BeginFrame() requires(NotFramework)
        {
            if constexpr (FullBlack)
            {
                FillWithSolidColor<>();
            }
            else
            {
                FillWithSolidColor<red, green, blue, alpha>();
            }
        }

        template <int GrayToneValue = 0>
        void BeginFrame() noexcept requires(Framework)
        {
            [[maybe_unused]]
            void* const ptr = ::std::memset(
                m_res_pack_.m_surface,
                GrayToneValue,
                sizeof(Color) * GetWidth<UINT>() * GetHeight<UINT>()
            );
        }

        template <bool VSynced = true>
        void EndFrame()
        {
            if constexpr (Framework)
            {
                MapSubresource_();
                CopySysbufferToMappedSubresource_();

                GetImmediateContext()->Unmap(GetSysbufferTexture(), 0u);
                GetImmediateContext()->Draw(6u, 0u);
            }

            const auto& hr = GetSwapChain()->Present(static_cast<UINT>(VSynced), 0u);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("SwapChain could NOT Present!");;
            }
        }

        template <float_t red = 0.0f, float_t green = 0.0f, float_t blue = 0.0f, float_t alpha = 1.0f>
        void FillWithSolidColor() requires(NotFramework)
        {
            constexpr std::array<const float_t, 4> colors{ red, green, blue, alpha };

            GetImmediateContext()->ClearRenderTargetView(GetRenderTargetView(), colors.data());
            GetImmediateContext()->ClearDepthStencilView(GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }

        template <std::floating_point T = float_t>
        void FillWithSolidColor(const T red, const T green, const T blue, const T alpha = static_cast<T>(1.0)) requires(NotFramework)
        {
            const std::array<const T, 4> colors{ red, green, blue, alpha };

            GetImmediateContext()->ClearRenderTargetView(GetRenderTargetView(), colors.data());
            GetImmediateContext()->ClearDepthStencilView(GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }


    public:
        auto GetSurface() -> Surface*
        {
            return m_pSurface_.get();
        }

        auto GetHwnd() const noexcept -> HWND
        {
            return mc_hWnd_;
        }
        auto GetDevice() const noexcept -> ID3D11Device*
        {
            return m_res_pack_.m_pDevice.Get();
        }
        auto GetSwapChain() const -> IDXGISwapChain*
        {
            return m_res_pack_.m_pSwapChain.Get();
        }
        auto GetImmediateContext() const noexcept -> ID3D11DeviceContext*
        {
            return m_res_pack_.m_pImmediateContext.Get();
        }
        auto GetRenderTargetView() const noexcept -> ID3D11RenderTargetView*
        {
            return m_res_pack_.m_pRTV.Get();
        }
        auto GetDepthStencilView() const noexcept -> ID3D11DepthStencilView*
        {
            return m_res_pack_.m_pDSV.Get();
        }
        auto GetSysbufferTexture() const noexcept -> ID3D11Texture2D* requires(Framework)
        {
            return m_res_pack_.m_pSysbufferTex2d.Get();
        }

        auto GetMSAACount() const noexcept
        {
            return m_msaa_count_;
        }
        auto GetMSAAQuality() const noexcept
        {
            return m_msaa_quality_;
        }

        void BindSurface(std::unique_ptr<Surface> pSurface) requires(Framework)
        {
            if (m_pSurface_ not_eq nullptr)
            {
                m_pSurface_->Clear();
            }

            m_pSurface_ = std::move(pSurface);
        }
        void CopySurfaceToSysbuffer() requires(Framework)
        {
            if (const void* const pSrc = *m_pSurface_)
            {
                ::std::memcpy(
                    m_res_pack_.m_surface,
                    pSrc,
                    sizeof(Color) * GetWidth<UINT>() * GetHeight<UINT>()
                );
            }
        }

        void PutPixel(const int x, const int y, const Color color) noexcept requires(Framework)
        {
            assert(x >= 0);
            assert(x < GetWidth<int>());
            assert(y >= 0);
            assert(y < GetHeight<int>());

            m_res_pack_.m_surface.PutPixel(x, y, color);
        }


    protected:


    private:
        void InitCommon_()
        {
            InitDevice_();
            InitMSAA_Settings_();
            InitSwapChain_();
            InitRenderTarget_();
            InitViewport_();

            ToggleAltEnterMode_();
        }
        void InitFramework_() requires(Framework)
        {
            InitFrameworkBackbuffer_();

            std::vector<std::unique_ptr<FATSPACE_PIPELINE::Bindable>> binds;

            {
                auto pVS = std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexShader>(GetDevice(), L"..\\FatModules\\VSFrameBuffer.cso");
                auto pBlob = pVS->GetBytecode();

                binds.push_back(std::move(pVS));
                binds.push_back(std::make_unique<FATSPACE_PIPELINE_ELEMENT::PixelShader>(GetDevice(), L"..\\FatModules\\PSFrameBuffer.cso"));
                binds.push_back(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(GetDevice(), FATSPACE_UTIL_GFX::FullScreenQuad::sc_vertices));
                binds.push_back(std::make_unique<FATSPACE_PIPELINE_ELEMENT::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

                const std::vector<D3D11_INPUT_ELEMENT_DESC> iedesc =
                {
                    {
                        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                    }
                };

                binds.push_back(std::make_unique<FATSPACE_PIPELINE_ELEMENT::InputLayout>(GetDevice(), iedesc, pBlob));
            }

            auto* const pImmediateContext = GetImmediateContext();

            for (auto& bindable : binds)
            {
                bindable->Bind(pImmediateContext);
            }
        }
        void InitFrameworkBackbuffer_() requires(Framework)
        {
            D3D11_TEXTURE2D_DESC texDesc{
                .Width              = GetWidth<UINT>(),
                .Height             = GetHeight<UINT>(),
                .MipLevels          = 1u,
                .ArraySize          = 1u,
                .Format             = DXGI_FORMAT_B8G8R8A8_UNORM,
                .SampleDesc         = {
                                        .Count = 1u,
                                        .Quality = 0u 
                                    },
                .Usage              = D3D11_USAGE_DYNAMIC,
                .BindFlags          = D3D11_BIND_SHADER_RESOURCE,
                .CPUAccessFlags     = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags          = 0u
            };

            {
                const auto& hr = GetDevice()->CreateTexture2D(&texDesc, nullptr, m_res_pack_.m_pSysbufferTex2d.GetAddressOf());

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT create Texture2D!");
                }
            }

            ::wrl::ComPtr<ID3D11ShaderResourceView> pSRV;

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{
                .Format              = texDesc.Format,
                .ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D,
                .Texture2D           = { .MipLevels = texDesc.MipLevels }
            };

            {
                const auto& hr = GetDevice()->CreateShaderResourceView(GetSysbufferTexture(), &srvDesc, pSRV.GetAddressOf());

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT create ShaderResourceView!");
                }
            }

            GetImmediateContext()->PSSetShaderResources(0u, 1u, pSRV.GetAddressOf());

            {
                ::wrl::ComPtr<ID3D11SamplerState> pSS;

                D3D11_SAMPLER_DESC sDesc{
                    .Filter = D3D11_FILTER_MIN_MAG_MIP_POINT,
                    .AddressU = D3D11_TEXTURE_ADDRESS_CLAMP,
                    .AddressV = D3D11_TEXTURE_ADDRESS_CLAMP,
                    .AddressW = D3D11_TEXTURE_ADDRESS_CLAMP,
                    .ComparisonFunc = D3D11_COMPARISON_NEVER,
                    .MinLOD = 0.0f,
                    .MaxLOD = D3D11_FLOAT32_MAX
                };

                const auto& hr = GetDevice()->CreateSamplerState(&sDesc, pSS.GetAddressOf());

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT create SamplerState");
                }

                GetImmediateContext()->PSSetSamplers(0, 1, pSS.GetAddressOf());
            }
        }
        void InitDevice_()
        {
            static constinit UINT swapCreateFlags;

            if constexpr (IN_RELEASE)
            {
                swapCreateFlags = 0u;
            }
            else
            {
                swapCreateFlags = D3D11_CREATE_DEVICE_DEBUG;
            }

            D3D_FEATURE_LEVEL featureLevel{};

            const auto& hr = ::D3D11CreateDevice(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                swapCreateFlags,
                nullptr,
                0u,
                D3D11_SDK_VERSION,
                &m_res_pack_.m_pDevice,
                &featureLevel,
                &m_res_pack_.m_pImmediateContext
            );

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("Could NOT create Direct3D Device!");
            }

            if (featureLevel not_eq D3D_FEATURE_LEVEL_11_0)
            {
                throw std::runtime_error("Direct3D Feature Level 11 is unsupported!");
            }
        }
        void InitMSAA_Settings_()
        {
            constexpr std::array<const UINT, 4> msaa_counts{ 32u, 16u, 8u, 4u };

            for (const auto& count : msaa_counts)
            {
                m_res_pack_.m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, count, &m_msaa_quality_);

                if (m_msaa_quality_ > 0)
                {
                    m_msaa_count_ = count;

                    break;
                }
            }

            if (m_msaa_quality_ <= 0)
            {
                throw std::runtime_error{ "MSAA Quality is NOT valid!" };
            }
        }
        void InitSwapChain_()
        {
            DXGI_SWAP_CHAIN_DESC scDesc{
                .BufferDesc   = {
                                 .Width            = GetWidth<UINT>(),
                                 .Height           = GetHeight<UINT>(),
                                 .RefreshRate      = {
                                                      .Numerator = 0u,
                                                      .Denominator = 0u,
                                                   },
                                 .Format           = DXGI_FORMAT_B8G8R8A8_UNORM,
                                 .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
                                 .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
                              },
                .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
                .BufferCount  = 1u,
                .OutputWindow = GetHwnd(),
                .SwapEffect   = DXGI_SWAP_EFFECT_DISCARD,
                .Flags        = 0u
            };

            if constexpr (Framework)
            {
                scDesc.SampleDesc.Count   = 1u;
                scDesc.SampleDesc.Quality = 0u;
            }
            else
            {
                scDesc.SampleDesc.Count   = m_msaa_count_;
                scDesc.SampleDesc.Quality = m_msaa_quality_ - 1u;
            }

            if constexpr (IN_RELEASE and NotFramework)
            {
                scDesc.Windowed = false;
            }
            else
            {
                scDesc.Windowed = true;
            }

            const auto& hr = FATSPACE_UTIL::gfx::GetDXGIFactory(GetDevice())->CreateSwapChain(
                GetDevice(),
                &scDesc,
                m_res_pack_.m_pSwapChain.GetAddressOf()
            );

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("Could NOT create Direct3D SwapChain!");
            }
        }
        void InitRenderTarget_()
        {
            ::Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBufferTexture2D{};

            {
                const auto& hr = GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBufferTexture2D);

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT get the buffer from SwapChain!");
                }
            }

            {
                const auto& hr = GetDevice()->CreateRenderTargetView(pBackBufferTexture2D.Get(), nullptr, &m_res_pack_.m_pRTV);

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT create RenderTargetView!");
                }
            }

            if constexpr (NotFramework)
            {
                ::wrl::ComPtr<ID3D11Texture2D> pTexture2d;

                D3D11_TEXTURE2D_DESC tex2dDesc{
                    .Width      = GetWidth<UINT>(),
                    .Height     = GetHeight<UINT>(),
                    .MipLevels  = 1u,
                    .ArraySize  = 1u,
                    .Format     = DXGI_FORMAT_D32_FLOAT,
                    .SampleDesc = {
                                    .Count   = GetMSAACount(),
                                    .Quality = GetMSAAQuality() - 1u
                                },
                    .Usage      = D3D11_USAGE_DEFAULT,
                    .BindFlags  = D3D11_BIND_DEPTH_STENCIL
                };

                D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{ .Format = DXGI_FORMAT_D32_FLOAT };

                if (m_msaa_count_ == 1u)
                {
                    dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
                    dsvDesc.Texture2D.MipSlice = 0u;
                }
                else
                {
                    dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2DMS;
                    dsvDesc.Texture2D.MipSlice = 1u;
                }

                {
                    const auto& hr = GetDevice()->CreateTexture2D(&tex2dDesc, nullptr, pTexture2d.GetAddressOf());

                    if (FAILED(hr)) [[unlikely]]
                    {
                        throw std::runtime_error("Could NOT create Texture2D!");
                    }
                }

                {
                    const auto& hr = GetDevice()->CreateDepthStencilView(pTexture2d.Get(), &dsvDesc, &m_res_pack_.m_pDSV);

                    if (FAILED(hr)) [[unlikely]]
                    {
                        throw std::runtime_error("Could NOT create DepthStencilView!");
                    }
                }
            }

            GetImmediateContext()->OMSetRenderTargets(1u, m_res_pack_.m_pRTV.GetAddressOf(), GetDepthStencilView());
        }
        void InitViewport_()
        {
            const D3D11_VIEWPORT vp{
                .TopLeftX = 0.0f,
                .TopLeftY = 0.0f,
                .Width    = GetWidth<FLOAT>(),
                .Height   = GetHeight<FLOAT>(),
                .MinDepth = 0.0f,
                .MaxDepth = 1.0f
            };

            GetImmediateContext()->RSSetViewports(1u, &vp);
        }
        void InitRasterizer_() requires(NotFramework)
        {
            D3D11_RASTERIZER_DESC rDesc{
                .FillMode              = D3D11_FILL_SOLID,
                .CullMode              = D3D11_CULL_BACK,
                .FrontCounterClockwise = false,
                .DepthBias             = 0,
                .DepthBiasClamp        = 0.0f,
                .SlopeScaledDepthBias  = 0.0f,
                .DepthClipEnable       = true,
                .ScissorEnable         = false,
                .MultisampleEnable     = true,
                .AntialiasedLineEnable = true
            };

            ::wrl::ComPtr<ID3D11RasterizerState> m_pRasterizerState_;

            {
                const auto& hr = GetDevice()->CreateRasterizerState(&rDesc, &m_pRasterizerState_);

                if (FAILED(hr)) [[unlikely]]
                {
                    throw std::runtime_error("Could NOT create RasterizerState!");
                }
            }

            GetImmediateContext()->RSSetState(m_pRasterizerState_.Get());
        }

        void MapSubresource_() requires(Framework)
        {
            const auto& hr = GetImmediateContext()->Map(
                GetSysbufferTexture(),
                0u,
                D3D11_MAP_WRITE_DISCARD,
                0u,
                &m_res_pack_.m_mappedSysbufferTex2d
            );

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("Could NOT Map the ImmediateContext!");
            }
        }
        void CopySysbufferToMappedSubresource_() requires(Framework)
        {
            Color* const pDst = static_cast<Color*>(m_res_pack_.m_mappedSysbufferTex2d.pData);

            const auto dstPitch = m_res_pack_.m_mappedSysbufferTex2d.RowPitch / sizeof(Color);
            const auto srcPitch = mc_dimensions_.m_width;
            const auto rowBytes = srcPitch * sizeof(Color);

            for (auto y = 0u; y < mc_dimensions_.m_height; ++y)
            {
                std::memcpy(
                    static_cast<void*>(&pDst[y * dstPitch]),
                    static_cast<void*>(&m_res_pack_.m_surface[y * srcPitch]),
                    rowBytes
                );
            }
        }

        void ToggleAltEnterMode_()
        {
            FATSPACE_UTIL::gfx::ToggleDXGI_AltEnterMode(GetDevice(), GetHwnd(), m_dxgi_mode_);
        }


    private:
        ResourcePack_t m_res_pack_{};

        const HWND mc_hWnd_;
        
        const ScreenSizeInfo mc_dimensions_;

        UINT m_msaa_count_{};
        UINT m_msaa_quality_{};

        UINT m_dxgi_mode_{};

        std::unique_ptr<Surface> m_pSurface_;
    };
}

module : private;