module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.DXGI.Util;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::dxgi::util
{
    auto GetFactory(ID3D11Device* const pDevice) -> ::wrl::ComPtr<IDXGIFactory>
    {
        auto pDXGIDevice = ::wrl::ComPtr<IDXGIDevice>{};
        pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        auto pDXGIAdapter = ::wrl::ComPtr<IDXGIAdapter>{};
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        auto pDXGIFactory = ::wrl::ComPtr<IDXGIFactory>{};
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        return pDXGIFactory;
    }
}