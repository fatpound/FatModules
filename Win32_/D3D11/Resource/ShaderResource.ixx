module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
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

import std;

export namespace fatpound::win32::d3d11::resource
{
    class ShaderResource
    {
    public:
        explicit ShaderResource(ID3D11Device* const pDevice, ID3D11Resource* const d3dres, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const UINT& startSlot = 0U)
            :
            m_start_slot_(startSlot)
        {
            if (FAILED(pDevice->CreateShaderResourceView(d3dres, &srvDesc, &m_pSRV_)))
            {
                throw std::runtime_error("Could NOT create ShaderResourceView!");
            }
        }

        explicit ShaderResource()                          = delete;
        explicit ShaderResource(const ShaderResource&)     = delete;
        explicit ShaderResource(ShaderResource&&) noexcept = default;

        auto operator = (const ShaderResource&)     -> ShaderResource& = delete;
        auto operator = (ShaderResource&&) noexcept -> ShaderResource& = default;
        ~ShaderResource() noexcept                                     = default;


    public:
        auto GetView() const noexcept -> ID3D11ShaderResourceView*
        {
            return m_pSRV_.Get();
        }
        auto GetAddressOfView() const noexcept -> ID3D11ShaderResourceView* const*
        {
            return m_pSRV_.GetAddressOf();
        }

        auto GetStartSlot() const noexcept -> UINT
        {
            return m_start_slot_;
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>   m_pSRV_;
        UINT                                               m_start_slot_{};


    private:
    };
}

#endif

// module : private;
