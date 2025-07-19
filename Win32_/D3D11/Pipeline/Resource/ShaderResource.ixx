module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.ShaderResource;

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
    class ShaderResource : public Bindable
    {
    public:
        explicit ShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc)
        {
            if (FAILED(pDevice->CreateShaderResourceView(tex2d.GetBuffer(), &srvDesc, &m_pSRV_)))
            {
                throw std::runtime_error("Could NOT create ShaderResourceView!");
            }
        }

        explicit ShaderResource()                          = delete;
        explicit ShaderResource(const ShaderResource&)     = delete;
        explicit ShaderResource(ShaderResource&&) noexcept = delete;

        auto operator = (const ShaderResource&)     -> ShaderResource& = delete;
        auto operator = (ShaderResource&&) noexcept -> ShaderResource& = delete;
        virtual ~ShaderResource() noexcept override                    = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override
        {
            pImmediateContext->PSSetShaderResources(0U, 1U, m_pSRV_.GetAddressOf());
        }


    public:
        auto GetView() const noexcept -> ID3D11ShaderResourceView*
        {
            return m_pSRV_.Get();
        }


    protected:
        wrl::ComPtr<ID3D11ShaderResourceView>  m_pSRV_;


    private:
    };
}

#endif

// module : private;
