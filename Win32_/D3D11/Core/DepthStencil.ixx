module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Core.DepthStencil;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Win32.D3D11.Resource.Texture2D;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::core
{
    class DepthStencil
    {
    public:
        explicit DepthStencil(ID3D11Device* const pDevice, const resource::Texture2D& tex2d, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc)
        {
            if (FAILED(pDevice->CreateDepthStencilView(tex2d.GetBuffer(), &dsvDesc, &m_pDSV_)))
            {
                throw std::runtime_error("Could NOT create DepthStencilView!");
            }
        }

        explicit DepthStencil()                        = default;
        explicit DepthStencil(const DepthStencil&)     = delete;
        explicit DepthStencil(DepthStencil&&) noexcept = default;

        auto operator = (const DepthStencil&)     -> DepthStencil& = delete;
        auto operator = (DepthStencil&&) noexcept -> DepthStencil& = default;
        ~DepthStencil() noexcept                                   = default;


    public:
        auto GetView() const noexcept -> ID3D11DepthStencilView*
        {
            return m_pDSV_.Get();
        }


    protected:
        wrl::ComPtr<ID3D11DepthStencilView>  m_pDSV_;


    private:
    };
}

#endif

// module : private;
