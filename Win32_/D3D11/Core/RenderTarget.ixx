module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Core.RenderTarget;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;
import FatPound.Win32.D3D11.Core.DepthStencil;
import FatPound.Win32.D3D11.Resource.Texture2D;

import std;

export namespace fatpound::win32::d3d11::core
{
    class RenderTarget : public Bindable
    {
    public:
        explicit RenderTarget(ID3D11Device* const pDevice, const resource::Texture2D& tex2d)
        {
            if (FAILED(pDevice->CreateRenderTargetView(tex2d.GetBuffer(), nullptr, &m_pRTV_)))
            {
                throw std::runtime_error("Could NOT create RenderTargetView!");
            }
        }
        explicit RenderTarget(
            ID3D11Device* const pDevice,
            const resource::Texture2D& rtvTex2d,
            const resource::Texture2D& dsvTex2d,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc)
            :
            RenderTarget(pDevice, rtvTex2d)
        {
            m_depth_stencil_.emplace(pDevice, dsvTex2d, dsvDesc);
        }

        explicit RenderTarget()                        = default;
        explicit RenderTarget(const RenderTarget&)     = delete;
        explicit RenderTarget(RenderTarget&&) noexcept = default;

        auto operator = (const RenderTarget&)     -> RenderTarget& = delete;
        auto operator = (RenderTarget&&) noexcept -> RenderTarget& = default;
        virtual ~RenderTarget() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override
        {
            pImmediateContext->OMSetRenderTargets(
                1U,
                m_pRTV_.GetAddressOf(),
                GetDSView()
            );
        }


    public:
        auto GetView   () const noexcept -> ID3D11RenderTargetView*
        {
            return m_pRTV_.Get();
        }
        auto GetDSView () const noexcept -> ID3D11DepthStencilView*
        {
            return HasDepthStencil() ? m_depth_stencil_->GetView() : nullptr;
        }

        auto HasDepthStencil () const noexcept -> bool
        {
            return m_depth_stencil_.has_value();
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView>   m_pRTV_;
        std::optional<DepthStencil>                      m_depth_stencil_;


    private:
    };
}

#endif

// module : private;
