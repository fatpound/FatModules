module;

#include <FatWin32_.hpp>

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

using NAMESPACE_UTIL::Color;
using NAMESPACE_UTIL::ScreenSizeInfo;

export namespace fatpound::win32::d3d11
{
    template <bool Framework = false>
    class Graphics final
    {
        using float_t = float;

    public:
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions)
            :
            m_dimensions_{ dimensions }
        {
            InitCommon_(hWnd);
            
            if constexpr (s_rasterizationEnabled_)
            {
                pipeline::system::Rasterizer::SetState_FatDefault(m_res_pack_);
            }
        }
        explicit Graphics(const HWND hWnd, const ScreenSizeInfo& dimensions) requires(Framework)
            :
            m_dimensions_{ dimensions }
        {
            InitCommon_(hWnd);

            pipeline::system::ShaderResource::SetView_Default<Framework>(m_res_pack_, m_dimensions_, m_msaa_count_, m_msaa_quality_);
            pipeline::system::Sampler::SetState_FatDefault(m_res_pack_);

            m_res_pack_.m_pSysBuffer = static_cast<Color*>(_aligned_malloc(sizeof(Color) * m_dimensions_.m_width * m_dimensions_.m_height, 16u));

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
        ~Graphics() noexcept(false) requires(Framework)
        {
            if (m_res_pack_.m_pSysBuffer not_eq nullptr) [[likely]]
            {
                _aligned_free(m_res_pack_.m_pSysBuffer);
                m_res_pack_.m_pSysBuffer = nullptr;
            }

            if (m_res_pack_.m_pImmediateContext not_eq nullptr) [[likely]]
            {
                m_res_pack_.m_pImmediateContext->ClearState();
            }
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
            std::memset(static_cast<void*>(m_res_pack_.m_pSysBuffer), 0u, sizeof(Color) * m_dimensions_.m_width * m_dimensions_.m_height);
        }
        void EndFrame()
        {
            Present_<>();
        }
        void EndFrame() requires(Framework)
        {
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
            
            {
                Color* const pDst = static_cast<Color*>(m_res_pack_.m_mappedSysBufferTexture.pData);

                const auto dstPitch = m_res_pack_.m_mappedSysBufferTexture.RowPitch / sizeof(Color);
                const auto srcPitch = m_dimensions_.m_width;
                const auto rowBytes = srcPitch * sizeof(Color);

                for (auto y = 0u; y < m_dimensions_.m_height; ++y)
                {
                    std::memcpy(
                        static_cast<void*>(&pDst[y * dstPitch]),
                        static_cast<void*>(&m_res_pack_.m_pSysBuffer[y * srcPitch]),
                        rowBytes
                    );
                }
            }

            GetImmediateContext()->Unmap(m_res_pack_.m_pSysBufferTexture.Get(), 0u);
            GetImmediateContext()->Draw(6u, 0u);

            Present_<>();
        }

        void FillWithSolidColor(const float_t red, const float_t green, const float_t blue, const float_t alpha = 1.0f) requires(not Framework)
        {
            ClearBuffer_(red, green, blue, alpha);
        }
        void PutPixel(const int x, const int y, const Color color) noexcept requires(Framework)
        {
            assert(x >= 0);
            assert(x < static_cast<int>(m_dimensions_.m_width));
            assert(y >= 0);
            assert(y < static_cast<int>(m_dimensions_.m_height));

            m_res_pack_.m_pSysBuffer[m_dimensions_.m_width * y + x] = color;
        }


    public:
        template <NAMESPACE_MATH_CONCEPTS::number_set::Rational Q>
        auto GetWidth() const noexcept
        {
            return static_cast<Q>(m_dimensions_.m_width);
        }

        template <NAMESPACE_MATH_CONCEPTS::number_set::Rational Q>
        auto GetHeight() const noexcept
        {
            return static_cast<Q>(m_dimensions_.m_height);
        }


    protected:


    private:
        struct FullScreenQuad_ final
        {
            struct Vertex final
            {
                float x;
                float y;
                float z;

                float u;
                float v;
            };

            inline static const std::vector<Vertex> vertices =
            {
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f,  1.0f,  0.5f,  1.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f,  1.0f,  0.5f,  0.0f,  0.0f },
                Vertex{  1.0f, -1.0f,  0.5f,  1.0f,  1.0f },
                Vertex{ -1.0f, -1.0f,  0.5f,  0.0f,  1.0f }
            };
        };


    private:
        static void InitFrameworkBinds_(auto& binds) requires(Framework)
        {
            auto pVS = std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexShader>(GetDevice(), L"..\\FatModules\\VSFrameBuffer.cso");
            auto pBlob = pVS->GetBytecode();

            binds.push_back(std::move(pVS));
            binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::PixelShader>(GetDevice(), L"..\\FatModules\\PSFrameBuffer.cso"));
            binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::VertexBuffer>(GetDevice(), FullScreenQuad_::vertices));
            binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> iedesc =
            {
                {
                    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                }
            };

            binds.push_back(std::make_unique<NAMESPACE_PIPELINE::element::InputLayout>(GetDevice(), iedesc, pBlob));
        }


    private:
        template <
            float_t red   = 0.0f,
            float_t green = 0.0f,
            float_t blue  = 0.0f,
            float_t alpha = 1.0f
        >
        void ClearBuffer_() requires(not Framework)
        {
            constexpr std::array<const float_t, 4> colors{ red, green, blue, alpha };

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


    private:
        void InitCommon_(const HWND hWnd)
        {
            core::Device::Create(m_res_pack_);

            InitMSAA_Settings_();

            {
                auto&& scdesc = factory::SwapChain::CreateDESC<Framework>(hWnd, m_dimensions_, m_msaa_count_, m_msaa_quality_);
                factory::SwapChain::Create(m_res_pack_, scdesc);
            }
            
            ToggleAltEnterMode_();

            pipeline::system::RenderTarget::Set_FatDefault<Framework>(m_res_pack_, m_dimensions_, m_msaa_count_, m_msaa_quality_);
            pipeline::system::Viewport::Set_FatDefault(m_res_pack_, m_dimensions_);
        }
        void InitFramework_() requires(Framework)
        {
            std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> binds;

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

            static constexpr auto magic_value = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

            if ((flag bitand magic_value) not_eq 0u)
            {
                flag and_eq ~magic_value;
            }
            else
            {
                flag or_eq magic_value;
            }

            DXGI_SWAP_CHAIN_DESC desc{};
            m_res_pack_.m_pSwapChain->GetDesc(&desc);

            const auto& hWnd = desc.OutputWindow;

            NAMESPACE_DXGI::util::GetFactory(GetDevice())->MakeWindowAssociation(hWnd, flag);
        }
        
        void ClearBuffer_(const float_t red, const float_t green, const float_t blue, const float_t alpha = 1.0f) requires(not Framework)
        {
            const std::array<const float_t, 4> colors{ red, green, blue, alpha };

            m_res_pack_.m_pImmediateContext->ClearRenderTargetView(m_res_pack_.m_pRTV.Get(), colors.data());
            m_res_pack_.m_pImmediateContext->ClearDepthStencilView(m_res_pack_.m_pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }


    private:
        GraphicsResourcePack m_res_pack_{};

        const ScreenSizeInfo m_dimensions_{};

        UINT m_msaa_count_{};
        UINT m_msaa_quality_{};

        static constexpr auto s_rasterizationEnabled_ = std::conditional_t<Framework, std::false_type, std::true_type>::value;
    };
}