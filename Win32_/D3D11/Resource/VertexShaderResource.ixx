module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Resource.VertexShaderResource;

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
    class VertexShaderResource : public Bindable, public ShaderResource
    {
    public:
        explicit VertexShaderResource(ID3D11Device* const pDevice, ID3D11Buffer* const d3dbuf, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U)
            :
            ShaderResource(pDevice, d3dbuf, srvDesc, startSlot)
        {

        }

        explicit VertexShaderResource()                                = delete;
        explicit VertexShaderResource(const VertexShaderResource&)     = delete;
        explicit VertexShaderResource(VertexShaderResource&&) noexcept = default;

        auto operator = (const VertexShaderResource&)     -> VertexShaderResource& = delete;
        auto operator = (VertexShaderResource&&) noexcept -> VertexShaderResource& = default;
        virtual ~VertexShaderResource() noexcept override                          = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override
        {
            pImmediateContext->VSSetShaderResources(m_start_slot_, 1U, m_pSRV_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif

// module : private;
