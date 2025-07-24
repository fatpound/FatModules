module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Compiler.hxx>
    #include <_macros/Namespaces.hxx>

    #pragma comment(lib, "d3d11")
    #pragma comment(lib, "D3DCompiler")
#endif

export module FatPound.Win32.D3D11.Graphics;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <d3d11_4.h>;
import <d3dcompiler.h>;

import FatPound.Colors.ARGB;
import FatPound.Traits.Bitwise;
import FatPound.Utility.Surface;
import FatPound.Utility.Gfx;
import FatPound.Win32.D3D11.Pipeline;
import FatPound.Win32.DXGI.Common;
import FatPound.Win32.WRL.Common;

import std;

using FATSPACE_UTILITY_GFX::SizePack;

export namespace fatpound::win32::d3d11
{
    /// @brief A graphics management class template that configures rendering behavior based on the Framework template parameter
    /// 
    /// @tparam Framework: A boolean value that determines whether to use framework-specific graphics resources and behavior. Defaults to false
    /// 
    template <bool Framework = false>
    class Graphics final
    {
        static constexpr auto NotFramework         = not Framework;
        static constexpr auto RasterizationEnabled = NotFramework;

        using ResourcePack_t   = std::conditional_t<Framework, FATSPACE_UTILITY_GFX::FrameworkResourcePack, FATSPACE_UTILITY_GFX::ResourcePack>;
        using FullScreenQuad_t = utility::gfx::FullScreenQuad; // for Framework
        using Surface_t        = utility::Surface;             // for Framework
        using Color_t          = Surface_t::Color_t;           // for Framework

    public:
        using Float_t = float;


    public:
        explicit Graphics(const HWND& hWnd, const SizePack& dimensions)
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
        explicit Graphics(const HWND& hWnd, const SizePack& dimensions,          const std::wstring& VShaderPath, const std::wstring& PShaderPath) requires(Framework)
            :
            m_res_pack_(dimensions),
            mc_hWnd_(hWnd),
            mc_dimensions_{ dimensions }
        {
            InitCommon_();
            InitFramework_(VShaderPath, PShaderPath);
        }
        explicit Graphics(const HWND& hWnd, std::unique_ptr<Surface_t> pSurface, const std::wstring& VShaderPath, const std::wstring& PShaderPath) requires(Framework)
            :
            Graphics(hWnd, pSurface->GetSizePack(), VShaderPath, PShaderPath)
        {
            BindSurface(std::move<>(pSurface));
        }

        explicit Graphics()                    = delete;
        explicit Graphics(const Graphics&)     = delete;
        explicit Graphics(Graphics&&) noexcept = delete;

        auto operator = (const Graphics&)     -> Graphics& = delete;
        auto operator = (Graphics&&) noexcept -> Graphics& = delete;
        ~Graphics() noexcept                               = default;
        ~Graphics() noexcept requires(Framework)
        {
            if (GetImmediateContext() not_eq nullptr)
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
        template <traits::IntegralOrFloating T> [[nodiscard]] constexpr auto GetWidth () const noexcept -> T
        {
            return static_cast<T>(mc_dimensions_.m_width);
        }
        template <traits::IntegralOrFloating T> [[nodiscard]] constexpr auto GetHeight() const noexcept -> T
        {
            return static_cast<T>(mc_dimensions_.m_height);
        }

        template <std::integral T> [[nodiscard]] FATLIB_FORCEINLINE auto GetPixel(const T& x, const T& y) const -> Color_t               requires(Framework)
        {
            return m_res_pack_.m_surface.template GetPixel<>(x, y);
        }
        template <std::integral T>               FATLIB_FORCEINLINE void PutPixel(const T& x, const T& y, const Color_t& color) noexcept requires(Framework)
        {
            m_res_pack_.m_surface.template PutPixel<>(x, y, color);
        }

        template <bool FullBlack = true, Float_t red = 1.0F, Float_t green = 1.0F, Float_t blue = 1.0F, Float_t alpha = 1.0F>
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
            void* const ptr = std::memset(
                m_res_pack_.m_surface,
                GrayToneValue,
                GetWidth<UINT>() * GetHeight<UINT>() * sizeof(Color_t)
            );
        }

        template <bool VSynced = true>
        void EndFrame()
        {
            if constexpr (Framework)
            {
                MapSubresource_();
                CopySysbufferToMappedSubresource_();
                UnMapSubresourceAndDraw_();
            }

            if (FAILED(GetSwapChain()->Present(static_cast<UINT>(VSynced), 0U)))
            {
                throw std::runtime_error("SwapChain could NOT Present!");
            }
        }

        template <Float_t red = 0.0F, Float_t green = 0.0F, Float_t blue = 0.0F, Float_t alpha = 1.0F>
        void FillWithSolidColor() requires(NotFramework)
        {
            {
                constexpr std::array<const Float_t, 4> colors{ red, green, blue, alpha };

                GetImmediateContext()->ClearRenderTargetView(GetRenderTargetView(), colors.data());
            }

            GetImmediateContext()->ClearDepthStencilView(GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0F, 0U);
        }

        template <std::floating_point T = Float_t>
        void FillWithSolidColor(const T& red, const T& green, const T& blue, const T& alpha = static_cast<T>(1.0)) requires(NotFramework)
        {
            {
                const std::array<const T, 4> colors{ red, green, blue, alpha };

                GetImmediateContext()->ClearRenderTargetView(GetRenderTargetView(), colors.data());
            }

            GetImmediateContext()->ClearDepthStencilView(GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0F, 0U);
        }


    public:
        auto GetSurface() noexcept -> Surface_t*
        {
            return m_pSurface_.get();
        }

        auto GetHwnd             () const noexcept -> HWND
        {
            return mc_hWnd_;
        }
        auto GetSwapChain        () const noexcept -> IDXGISwapChain*
        {
            return m_res_pack_.m_pSwapChain.Get();
        }
        auto GetDevice           () const noexcept -> ID3D11Device*
        {
            return m_res_pack_.m_pDevice.Get();
        }
        auto GetImmediateContext () const noexcept -> ID3D11DeviceContext*
        {
            return m_res_pack_.m_pImmediateContext.Get();
        }
        auto GetRenderTargetView () const noexcept -> ID3D11RenderTargetView*
        {
            return m_res_pack_.m_render_target.GetView();
        }
        auto GetDepthStencilView () const noexcept -> ID3D11DepthStencilView* requires(NotFramework)
        {
            return m_res_pack_.m_depth_stencil.GetView();
        }
        auto GetSysbufferTexture () const noexcept -> ID3D11Texture2D*        requires(Framework)
        {
            return m_res_pack_.m_sysbufferTex2d.GetBuffer();
        }

        auto GetMSAACount        () const noexcept
        {
            return m_msaa_count_;
        }
        auto GetMSAAQuality      () const noexcept
        {
            return m_msaa_quality_;
        }

        void BindSurface(std::unique_ptr<Surface_t> pSurface) requires(Framework)
        {
            if (m_pSurface_ not_eq nullptr)
            {
                m_pSurface_->Reset();
            }

            m_pSurface_ = std::move<>(pSurface);
        }
        void CopySurfaceToSysbuffer()                         requires(Framework)
        {
            if (const void* const pSrc = *m_pSurface_; pSrc not_eq nullptr)
            {
                std::memcpy(
                    m_res_pack_.m_surface,
                    pSrc,
                    GetWidth<UINT>() * GetHeight<UINT>() * sizeof(Color_t)
                );
            }
        }


    protected:


    private:
        void InitCommon_                       ()
        {
            InitDevice_();
            InitMSAA_Settings_();
            InitSwapChain_();
            InitRenderTarget_();
            InitViewport_();

            ToggleAltEnterMode_();
        }
        void InitFramework_                    (const std::wstring& VShaderPath, const std::wstring& PShaderPath) requires(Framework)
        {
            InitFrameworkBackbufferTexture_();
            InitFrameworkBackbufferSampler_();

            std::vector<std::unique_ptr<pipeline::Bindable>> binds;

            {
                {
                    wrl::ComPtr<ID3DBlob> pVSBlob;

                    if (FAILED(D3DReadFileToBlob(VShaderPath.c_str(), &pVSBlob)))
                    {
                        throw std::runtime_error("CANNOT read file to D3D Blob!");
                    }

                    binds.push_back(std::make_unique<pipeline::VertexShader>(GetDevice(), pVSBlob));

                    const std::vector<D3D11_INPUT_ELEMENT_DESC> iedesc
                    {
                        {
                            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                        }
                    };

                    binds.push_back(std::make_unique<pipeline::InputLayout>(GetDevice(), iedesc, pVSBlob));
                }

                binds.push_back(std::make_unique<pipeline::PixelShader>(GetDevice(), PShaderPath));

                {
                    const auto& vertices = FullScreenQuad_t::S_GenerateVertices();

                    const D3D11_BUFFER_DESC bd
                    {
                        .ByteWidth           = static_cast<UINT>(vertices.size() * sizeof(FullScreenQuad_t::Vertex)),
                        .Usage               = D3D11_USAGE_DEFAULT,
                        .BindFlags           = D3D11_BIND_VERTEX_BUFFER,
                        .CPUAccessFlags      = 0U,
                        .MiscFlags           = 0U,
                        .StructureByteStride = sizeof(FullScreenQuad_t::Vertex)
                    };

                    binds.push_back(std::make_unique<pipeline::VertexBuffer>(GetDevice(), bd, vertices));
                }

                binds.push_back(std::make_unique<pipeline::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
            }

            for (auto& bindable : binds)
            {
                bindable->Bind(GetImmediateContext());
            }
        }
        void InitFrameworkBackbufferTexture_   () requires(Framework)
        {
            const D3D11_TEXTURE2D_DESC tex2dDesc
            {
                .Width          = GetWidth<UINT>(),
                .Height         = GetHeight<UINT>(),
                .MipLevels      = 1U,
                .ArraySize      = 1U,
                .Format         = DXGI_FORMAT_B8G8R8A8_UNORM,
                .SampleDesc     =
                                {
                                    .Count   = 1U,
                                    .Quality = 0U
                                },
                .Usage          = D3D11_USAGE_DYNAMIC,
                .BindFlags      = D3D11_BIND_SHADER_RESOURCE,
                .CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags      = 0U
            };

            const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc
            {
                .Format        = tex2dDesc.Format,
                .ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D,
                .Texture2D     =
                               {
                                   .MostDetailedMip = {},
                                   .MipLevels       = tex2dDesc.MipLevels
                               }
            };

            m_res_pack_.m_sysbufferTex2d = pipeline::Texture2D{ GetDevice(), tex2dDesc };

            pipeline::ShaderResource{ GetDevice(), m_res_pack_.m_sysbufferTex2d, srvDesc }.Bind(GetImmediateContext());
        }
        void InitFrameworkBackbufferSampler_   () requires(Framework)
        {
            const D3D11_SAMPLER_DESC sDesc
            {
                .Filter         = D3D11_FILTER_MIN_MAG_MIP_POINT,
                .AddressU       = D3D11_TEXTURE_ADDRESS_CLAMP,
                .AddressV       = D3D11_TEXTURE_ADDRESS_CLAMP,
                .AddressW       = D3D11_TEXTURE_ADDRESS_CLAMP,
                .MipLODBias     = {},
                .MaxAnisotropy  = {},
                .ComparisonFunc = D3D11_COMPARISON_NEVER,
                .BorderColor    = {},
                .MinLOD         = 0.0F,
                .MaxLOD         = D3D11_FLOAT32_MAX
            };

            pipeline::Sampler{ GetDevice(), sDesc }.Bind(GetImmediateContext());
        }
        void InitDevice_                       ()
        {
            D3D_FEATURE_LEVEL featureLevel{};

            if (const auto& hr = D3D11CreateDevice(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
#ifdef IN_RELEASE
                0U,
#else
                D3D11_CREATE_DEVICE_DEBUG,
#endif
                nullptr,
                0U,
                D3D11_SDK_VERSION,
                &m_res_pack_.m_pDevice,
                &featureLevel,
                &m_res_pack_.m_pImmediateContext);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create Direct3D Device!");
            }

            if (featureLevel not_eq D3D_FEATURE_LEVEL_11_0)
            {
                throw std::runtime_error("Direct3D Feature Level 11 is unsupported!");
            }
        }
        void InitMSAA_Settings_                ()
        {
            {
                constexpr std::array<const UINT, 4> msaa_counts{ 32U, 16U, 8U, 4U };

                for (const auto& count : msaa_counts)
                {
                    m_res_pack_.m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, count, &m_msaa_quality_);

                    if (m_msaa_quality_ > 0)
                    {
                        m_msaa_count_ = count;

                        break;
                    }
                }
            }

            if (m_msaa_quality_ <= 0)
            {
                throw std::runtime_error{ "MSAA Quality is NOT valid!" };
            }
        }
        void InitSwapChain_                    ()
        {
            DXGI_SWAP_CHAIN_DESC scDesc
            {
                .BufferDesc   =
                              {
                                  .Width            = GetWidth<UINT>(),
                                  .Height           = GetHeight<UINT>(),
                                  .RefreshRate      =
                                                    {
                                                        .Numerator   = 0U,
                                                        .Denominator = 0U,
                                                    },
                                  .Format           = DXGI_FORMAT_B8G8R8A8_UNORM,
                                  .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
                                  .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
                              },
                .SampleDesc   =
                              {
                                  .Count            = (Framework ? 1U : GetMSAACount()),
                                  .Quality          = (Framework ? 0U : GetMSAAQuality() - 1U)
                              },
                .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
                .BufferCount  = 2U,
                .OutputWindow = GetHwnd(),

#ifdef IN_RELEASE
                .Windowed     = Framework,
#else
                .Windowed     = true,
#endif

                .SwapEffect   = DXGI_SWAP_EFFECT_DISCARD,
                .Flags        = 0U
            };

            if (FAILED(dxgi::GetFactoryFromDevice(GetDevice())->CreateSwapChain(
                GetDevice(),
                &scDesc,
                m_res_pack_.m_pSwapChain.GetAddressOf())))
            {
                throw std::runtime_error("Could NOT create DXGI SwapChain!");
            }
        }
        void InitRenderTarget_                 ()
        {
            m_res_pack_.m_render_target = pipeline::RenderTarget{ GetDevice(), pipeline::Texture2D{ GetSwapChain() } };

            if constexpr (NotFramework)
            {
                const D3D11_TEXTURE2D_DESC tex2dDesc
                {
                    .Width          = GetWidth<UINT>(),
                    .Height         = GetHeight<UINT>(),
                    .MipLevels      = 1U,
                    .ArraySize      = 1U,
                    .Format         = DXGI_FORMAT_D32_FLOAT,
                    .SampleDesc     =
                                    {
                                        .Count   = GetMSAACount(),
                                        .Quality = GetMSAAQuality() - 1U
                                    },
                    .Usage          = D3D11_USAGE_DEFAULT,
                    .BindFlags      = D3D11_BIND_DEPTH_STENCIL,
                    .CPUAccessFlags = {},
                    .MiscFlags      = {}
                };

                const D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc
                {
                    .Format        = DXGI_FORMAT_D32_FLOAT,
                    .ViewDimension = (m_msaa_count_ == 1U) ? D3D11_DSV_DIMENSION_TEXTURE2D : D3D11_DSV_DIMENSION_TEXTURE2DMS,
                    .Flags         = {},
                    .Texture2D     =
                                   {
                                       .MipSlice = (m_msaa_count_ == 1U) ? 0U : 1U
                                   }
                };

                m_res_pack_.m_depth_stencil = pipeline::DepthStencil{ GetDevice(), pipeline::Texture2D{ GetDevice(), tex2dDesc }, dsvDesc };
                m_res_pack_.m_render_target.BindWithDepthStencilView(GetImmediateContext(), GetDepthStencilView());
            }
            else
            {
                m_res_pack_.m_render_target.Bind(GetImmediateContext());
            }
        }
        void InitViewport_                     ()
        {
            const D3D11_VIEWPORT vp
            {
                .TopLeftX = 0.0F,
                .TopLeftY = 0.0F,
                .Width    = GetWidth<FLOAT>(),
                .Height   = GetHeight<FLOAT>(),
                .MinDepth = 0.0F,
                .MaxDepth = 1.0F
            };

            pipeline::Viewport{ vp }.Bind(GetImmediateContext());
        }
        void InitRasterizer_                   () requires(NotFramework)
        {
            const D3D11_RASTERIZER_DESC rDesc
            {
                .FillMode              = D3D11_FILL_SOLID,
                .CullMode              = D3D11_CULL_BACK,
                .FrontCounterClockwise = false,
                .DepthBias             = 0,
                .DepthBiasClamp        = 0.0F,
                .SlopeScaledDepthBias  = 0.0F,
                .DepthClipEnable       = true,
                .ScissorEnable         = false,
                .MultisampleEnable     = true,
                .AntialiasedLineEnable = true
            };

            pipeline::Rasterizer{ GetDevice(), rDesc }.Bind(GetImmediateContext());
        }

        void MapSubresource_                   () requires(Framework)
        {
            if (FAILED(GetImmediateContext()->Map(
                GetSysbufferTexture(),
                0U,
                D3D11_MAP_WRITE_DISCARD,
                0U,
                &m_res_pack_.m_mappedSysbufferTex2d)))
            {
                throw std::runtime_error("Could NOT Map the ImmediateContext!");
            }
        }
        void CopySysbufferToMappedSubresource_ () requires(Framework)
        {
            auto* const pDst = static_cast<Color_t*>(m_res_pack_.m_mappedSysbufferTex2d.pData);

            const auto dstPitch = m_res_pack_.m_mappedSysbufferTex2d.RowPitch / sizeof(Color_t);
            const auto srcPitch = mc_dimensions_.m_width;
            const auto rowBytes = srcPitch * sizeof(Color_t);

            for (auto y = 0U; y < mc_dimensions_.m_height; ++y)
            {
                std::memcpy(
                    static_cast<void*>(&pDst[y * dstPitch]),
                    static_cast<void*>(&m_res_pack_.m_surface[y * srcPitch]),
                    rowBytes
                );
            }
        }
        void UnMapSubresourceAndDraw_          () requires(Framework)
        {
            GetImmediateContext()->Unmap(GetSysbufferTexture(), 0U);
            GetImmediateContext()->Draw(6U, 0U);
        }

        void ToggleAltEnterMode_()
        {
            dxgi::ToggleAltEnterMode(GetDevice(), GetHwnd(), m_dxgi_mode_);
        }


    private:
        ResourcePack_t               m_res_pack_{};

        const HWND                   mc_hWnd_;
        const SizePack               mc_dimensions_;

        UINT                         m_msaa_count_{};
        UINT                         m_msaa_quality_{};
        UINT                         m_dxgi_mode_{};

        std::unique_ptr<Surface_t>   m_pSurface_;
    };
}

#endif

// module : private;
