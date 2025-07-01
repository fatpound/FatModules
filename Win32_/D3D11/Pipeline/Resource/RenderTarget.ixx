module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.RenderTarget;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Pipeline.Texture2D;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::pipeline
{
    class RenderTarget : public Bindable
    {
    public:
        explicit RenderTarget(ID3D11Device* const pDevice, const Texture2D& tex2d)
        {
            if (FAILED(pDevice->CreateRenderTargetView(tex2d.GetBuffer(), nullptr, &m_pRTV_)))
            {
                throw std::runtime_error("Could NOT create RenderTargetView!");
            }
        }

        explicit RenderTarget()                        = default;
        explicit RenderTarget(const RenderTarget&)     = delete;
        explicit RenderTarget(RenderTarget&&) noexcept = delete;

        auto operator = (const RenderTarget&)     -> RenderTarget& = delete;
        auto operator = (RenderTarget&&) noexcept -> RenderTarget& = default;
        virtual ~RenderTarget() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override
        {
            pImmediateContext->OMSetRenderTargets(1U, m_pRTV_.GetAddressOf(), nullptr);
        }


    public:
        auto GetView() const noexcept -> ID3D11RenderTargetView*
        {
            return m_pRTV_.Get();
        }

        void BindWithDepthStencilView(ID3D11DeviceContext* pImmediateContext, ID3D11DepthStencilView* const pDSV)
        {
            pImmediateContext->OMSetRenderTargets(1U, m_pRTV_.GetAddressOf(), pDSV);
        }


    protected:
        wrl::ComPtr<ID3D11RenderTargetView>  m_pRTV_;


    private:
    };
}

#endif

module : private;
