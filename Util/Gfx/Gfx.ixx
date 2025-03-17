module;

#if FAT_BUILD_ONLY_WITH_MSVC
#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

export module FatPound.Util.Gfx;

export import FatPound.Util.Gfx.FullScreenQuad;
export import FatPound.Util.Gfx.ResourcePack;
export import FatPound.Util.Gfx.SizePack;

#if FAT_BUILD_ONLY_WITH_MSVC

namespace wrl = Microsoft::WRL;

export namespace fatpound::util::gfx
{
    auto GetDXGIFactory(ID3D11Device* const pDevice) -> ::Microsoft::WRL::ComPtr<IDXGIFactory>
    {
        auto pDXGIDevice = ::wrl::ComPtr<IDXGIDevice>{};
        pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        auto pDXGIAdapter = ::wrl::ComPtr<IDXGIAdapter>{};
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        auto pDXGIFactory = ::wrl::ComPtr<IDXGIFactory>{};
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        return pDXGIFactory;
    }

    void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND hWnd, UINT& flag)
    {
        static constexpr auto magicVal = static_cast<UINT>(DXGI_MWA_NO_ALT_ENTER);

        if ((flag bitand magicVal) not_eq 0u)
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
