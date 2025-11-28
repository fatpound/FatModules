module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Resource.PixelShaderResource;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;
import FatPound.Win32.D3D11.Resource.Texture2D;
import FatPound.Win32.D3D11.Resource.ShaderResource;

export namespace fatpound::win32::d3d11::resource
{
    class PixelShaderResource : public Bindable, public ShaderResource
    {
    public:
        explicit PixelShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U)
            :
            ShaderResource(pDevice, tex2d.GetBuffer(), srvDesc, startSlot)
        {

        }

        explicit PixelShaderResource()                               = delete;
        explicit PixelShaderResource(const PixelShaderResource&)     = delete;
        explicit PixelShaderResource(PixelShaderResource&&) noexcept = default;

        auto operator = (const PixelShaderResource&)     -> PixelShaderResource& = delete;
        auto operator = (PixelShaderResource&&) noexcept -> PixelShaderResource& = default;
        virtual ~PixelShaderResource() noexcept override                         = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override
        {
            pImmediateContext->PSSetShaderResources(m_start_slot_, 1U, m_pSRV_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif

// module : private;
