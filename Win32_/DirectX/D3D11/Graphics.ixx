module;

#include <FatWin32.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "D3DCompiler")

export module FatPound.Win32.D3D11.Graphics;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Win32.D3D11.Core;
import FatPound.Win32.D3D11.Pipeline;
import FatPound.Win32.D3D11.Visual;
import FatPound.Win32.D3D11.Factory;

import FatPound.Win32.DXGI;

import FatPound.Math;
import FatPound.Util;

import std;

namespace dx = DirectX;
namespace wrl = Microsoft::WRL;

using FATSPACE_UTIL::Color;
using FATSPACE_UTIL::ScreenSizeInfo;

export namespace fatpound::win32::d3d11
{
    template <bool Framework = false>
    class Graphics final
    {
        using float_t = float;

    public:
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions)
            :
            mc_dimensions_{ dimensions }
        {
            InitCommon_(hWnd);
            
            if constexpr (scx_rasterizationEnabled_)
            {
                pipeline::system::Rasterizer::SetState_FatDefault(m_res_pack_);
            }
        }
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions) requires(Framework)
            :
            mc_dimensions_{ dimensions }
        {
            InitCommon_(hWnd);

            pipeline::system::ShaderResource::SetView_FatDefault<Framework>(m_res_pack_, mc_dimensions_, m_msaa_count_, m_msaa_quality_);
            pipeline::system::Sampler::SetState_FatDefault(m_res_pack_);

            m_res_pack_.m_pSysBuffer = static_cast<Color*>(::_aligned_malloc(sizeof(Color) * mc_dimensions_.m_width * mc_dimensions_.m_height, 16u));

            if (m_res_pack_.m_pSysBuffer == nullptr) [[unlikely]]
            {
                throw std::runtime_error("Could NOT allocate memory for sysBuffer");
            }
            
            InitFramework_();
        }

        explicit Graphics() = delete;
        explicit Graphics(const Graphics& src) = delete;
        explicit Graphics(Graphics&& src) = delete;

        auto operator = (const Graphics& src) -> Graphics& = delete;
        auto operator = (Graphics&& src)      -> Graphics& = delete;
        ~Graphics() noexcept = default;
        ~Graphics() noexcept requires(Framework)
        {
            if (m_res_pack_.m_pSysBuffer not_eq nullptr) [[likely]]
            {
                ::_aligned_free(m_res_pack_.m_pSysBuffer);
                m_res_pack_.m_pSysBuffer = nullptr;
            }

            if (m_res_pack_.m_pImmediateContext not_eq nullptr) [[likely]]
            {
                try
                {
                    m_res_pack_.m_pImmediateContext->ClearState();
                }
                catch (...)
                {
                    OutputDebugString(L"COM Exception caught in Graphics<Framework> destructor!\n");
                }
            }
        }


    public:
        template <float_t red, float_t green, float_t blue, float_t alpha = 1.0f>
        void FillWithSolidColor() requires(not Framework)
        {
            ClearBuffer_<red, green, blue, alpha>();
        }

        template <std::floating_point T = float_t>
        void FillWithSolidColor(const T red, const T green, const T blue, const T alpha = static_cast<T>(1.0)) requires(not Framework)
        {
            ClearBuffer_(red, green, blue, alpha);
        }


    public:
        auto GetDevice() noexcept -> ID3D11Device*
        {
            return m_res_pack_.m_pDevice.Get();
        }
        auto GetImmediateContext() noexcept -> ID3D11DeviceContext*
        {
            return m_res_pack_.m_pImmediateContext.Get();
        }

        void BeginFrame()
        {
            ClearBuffer_<0.0f, 0.0f, 0.25f>();
        }
        void BeginFrame() noexcept requires(Framework)
        {
            std::memset(
                static_cast<void*>(m_res_pack_.m_pSysBuffer),
                0u,
                sizeof(Color) * mc_dimensions_.m_width * mc_dimensions_.m_height
            );
        }
        void EndFrame()
        {
            Present_<>();
        }
        void EndFrame() requires(Framework)
        {
            MapSubresource_();

            CopySysbufferToMappedSubresource_();

            GetImmediateContext()->Unmap(m_res_pack_.m_pSysBufferTexture.Get(), 0u);
            GetImmediateContext()->Draw(6u, 0u);

            Present_<>();
        }

        void PutPixel(const int x, const int y, const Color color) noexcept requires(Framework)
        {
            assert(x >= 0);
            assert(x < static_cast<int>(mc_dimensions_.m_width));
            assert(y >= 0);
            assert(y < static_cast<int>(mc_dimensions_.m_height));

            m_res_pack_.m_pSysBuffer[mc_dimensions_.m_width * y + x] = color;
        }


    public:
        template <FATSPACE_MATH::number_set::Rational Q>
        auto GetWidth() const noexcept
        {
            return static_cast<Q>(mc_dimensions_.m_width);
        }

        template <FATSPACE_MATH::number_set::Rational Q>
        auto GetHeight() const noexcept
        {
            return static_cast<Q>(mc_dimensions_.m_height);
        }


    protected:


    private:
        template <float_t red = 0.0f, float_t green = 0.0f, float_t blue = 0.0f, float_t alpha = 1.0f>
        void ClearBuffer_() requires(not Framework)
        {
            constexpr std::array<const float_t, 4> colors{ red, green, blue, alpha };

            m_res_pack_.m_pImmediateContext->ClearRenderTargetView(m_res_pack_.m_pRTV.Get(), colors.data());
            m_res_pack_.m_pImmediateContext->ClearDepthStencilView(m_res_pack_.m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }

        template <std::floating_point T = float_t>
        void ClearBuffer_(const T red, const T green, const T blue, const T alpha = static_cast<T>(1.0)) requires(not Framework)
        {
            const std::array<const T, 4> colors{ red, green, blue, alpha };

            m_res_pack_.m_pImmediateContext->ClearRenderTargetView(m_res_pack_.m_pRTV.Get(), colors.data());
            m_res_pack_.m_pImmediateContext->ClearDepthStencilView(m_res_pack_.m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }

        template <bool VSynced = true>
        void Present_()
        {
            const auto& hr = m_res_pack_.m_pSwapChain->Present(static_cast<UINT>(VSynced), 0u);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::exception("SwapChain could NOT Present!");;
            }
        }

        void InitFrameworkBinds_(auto& binds) requires(Framework)
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


    private:
        void InitCommon_(const HWND hWnd)
        {
            core::Device::Create(m_res_pack_);

            InitMSAA_Settings_();

            {
                auto&& scdesc = factory::SwapChain::CreateDESC<Framework>(hWnd, mc_dimensions_, m_msaa_count_, m_msaa_quality_);
                factory::SwapChain::Create(m_res_pack_, scdesc);
            }
            
            ToggleAltEnterMode_();

            pipeline::system::RenderTarget::Set_FatDefault<Framework>(m_res_pack_, mc_dimensions_, m_msaa_count_, m_msaa_quality_);
            pipeline::system::Viewport::Set_FatDefault(m_res_pack_, mc_dimensions_);
        }
        void InitFramework_() requires(Framework)
        {
            std::vector<std::unique_ptr<FATSPACE_PIPELINE::Bindable>> binds;

            InitFrameworkBinds_(binds);

            auto* const pImmediateContext = GetImmediateContext();

            for (auto& bindable : binds)
            {
                bindable->Bind(pImmediateContext);
            }
        }
        void InitMSAA_Settings_()
        {
            constexpr std::array<const UINT, 4> msaa_counts{ 32u, 16u, 8u, 4u };

            for (auto i = 0u; i < msaa_counts.size(); ++i)
            {
                m_res_pack_.m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, msaa_counts[i], &m_msaa_quality_);

                if (m_msaa_quality_ > 0)
                {
                    m_msaa_count_ = msaa_counts[i];

                    break;
                }
            }

            if (m_msaa_quality_ <= 0)
            {
                throw std::runtime_error{ "MSAA Quality is NOT valid!" };
            }
        }

        void ToggleAltEnterMode_()
        {
            static UINT flag{};

            static constexpr auto magicVal = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);
            
            if ((flag bitand magicVal) not_eq 0u)
            {
                flag and_eq (compl magicVal);
            }
            else
            {
                flag or_eq magicVal;
            }

            DXGI_SWAP_CHAIN_DESC scdesc{};
            m_res_pack_.m_pSwapChain->GetDesc(&scdesc);

            FATSPACE_DXGI::util::GetFactory(GetDevice())->MakeWindowAssociation(scdesc.OutputWindow, flag);
        }

        void MapSubresource_() requires(Framework)
        {
            const auto& hr = GetImmediateContext()->Map(
                m_res_pack_.m_pSysBufferTexture.Get(),
                0u,
                D3D11_MAP_WRITE_DISCARD,
                0u,
                &m_res_pack_.m_mappedSysBufferTexture
            );

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::exception("Could NOT Map the ImmediateContext!");
            }
        }
        void CopySysbufferToMappedSubresource_() requires(Framework)
        {
            Color* const pDst = static_cast<Color*>(m_res_pack_.m_mappedSysBufferTexture.pData);

            const auto dstPitch = m_res_pack_.m_mappedSysBufferTexture.RowPitch / sizeof(Color);
            const auto srcPitch = mc_dimensions_.m_width;
            const auto rowBytes = srcPitch * sizeof(Color);

            for (auto y = 0u; y < mc_dimensions_.m_height; ++y)
            {
                std::memcpy(
                    static_cast<void*>(&pDst[y * dstPitch]),
                    static_cast<void*>(&m_res_pack_.m_pSysBuffer[y * srcPitch]),
                    rowBytes
                );
            }
        }


    private:
        static constexpr auto scx_rasterizationEnabled_ = std::bool_constant<not Framework>::value;


    private:
        GraphicsResourcePack m_res_pack_{};
        
        const ScreenSizeInfo mc_dimensions_;

        UINT m_msaa_count_{};
        UINT m_msaa_quality_{};
    };
}