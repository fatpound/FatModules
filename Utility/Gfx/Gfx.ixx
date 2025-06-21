module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <wrl.h>
        #include <d3d11.h>
    #endif
#endif

export module FatPound.Utility.Gfx;

export import FatPound.Utility.Gfx.FullScreenQuad;
export import FatPound.Utility.Gfx.ResourcePack;
export import FatPound.Utility.Gfx.SizePack;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <d3d11.h>;

#ifndef __INTELLISENSE__
    import FatPound.Win32.WRL.Common;
#else
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::utility::gfx
{
    auto GetDXGIFactory(ID3D11Device* const pDevice) -> wrl::ComPtr<IDXGIFactory>
    {
        auto pDXGIDevice = wrl::ComPtr<IDXGIDevice>{};

        pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        auto pDXGIAdapter = wrl::ComPtr<IDXGIAdapter>{};
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        auto pDXGIFactory = wrl::ComPtr<IDXGIFactory>{};
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        return pDXGIFactory;
    }

    void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND& hWnd, UINT& flag)
    {
        static constexpr auto magicVal = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

        if ((flag bitand magicVal) not_eq 0U)
        {
            flag and_eq (compl magicVal);
        }
        else
        {
            flag or_eq magicVal;
        }

        GetDXGIFactory(pDevice)->MakeWindowAssociation(hWnd, flag);
    }
}

#endif

module : private;
