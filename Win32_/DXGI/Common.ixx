module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.DXGI.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import FatPound.Win32.WRL.Common;
#else
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::dxgi
{
    auto GetFactoryFromDevice(ID3D11Device* const pDevice) -> wrl::ComPtr<IDXGIFactory>
    {
        auto pDXGIDevice = wrl::ComPtr<IDXGIDevice>{};

        pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        auto pDXGIAdapter = wrl::ComPtr<IDXGIAdapter>{};
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        auto pDXGIFactory = wrl::ComPtr<IDXGIFactory>{};
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        return pDXGIFactory;
    }

    void ToggleAltEnterMode(ID3D11Device* const pDevice, const HWND& hWnd, UINT& flag)
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

        GetFactoryFromDevice(pDevice)->MakeWindowAssociation(hWnd, flag);
    }
}

#endif

module : private;
