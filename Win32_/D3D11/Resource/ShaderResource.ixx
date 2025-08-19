module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/Win32.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Resource.ShaderResource;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;
import FatPound.Win32.D3D11.Resource.Texture2D;

import std;

export namespace fatpound::win32::d3d11::resource
{
    class ShaderResource : public Bindable
    {
    public:
        explicit ShaderResource(ID3D11Device* const pDevice, const Texture2D& tex2d, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U)
            :
            m_start_slot_(startSlot)
        {
            if (FAILED(pDevice->CreateShaderResourceView(tex2d.GetBuffer(), &srvDesc, &m_pSRV_)))
            {
                throw std::runtime_error("Could NOT create ShaderResourceView!");
            }
        }

        explicit ShaderResource()                          = delete;
        explicit ShaderResource(const ShaderResource&)     = delete;
        explicit ShaderResource(ShaderResource&&) noexcept = default;

        auto operator = (const ShaderResource&)     -> ShaderResource& = delete;
        auto operator = (ShaderResource&&) noexcept -> ShaderResource& = default;
        virtual ~ShaderResource() noexcept override                    = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override
        {
            pImmediateContext->PSSetShaderResources(m_start_slot_, 1U, m_pSRV_.GetAddressOf());
        }


    public:
        auto GetView() const noexcept -> ID3D11ShaderResourceView*
        {
            return m_pSRV_.Get();
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>   m_pSRV_;
        UINT                                               m_start_slot_{};


    private:
    };
}

#endif

// module : private;
