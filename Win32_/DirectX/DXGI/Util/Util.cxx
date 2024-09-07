module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.DXGI.Util;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::dxgi::util
{
    auto GetFactory(ID3D11Device* const pDevice) -> ::wrl::ComPtr<IDXGIFactory>
    {
        ::wrl::ComPtr<IDXGIDevice> pDXGIDevice{};
        pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        ::wrl::ComPtr<IDXGIAdapter> pDXGIAdapter{};
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        ::wrl::ComPtr<IDXGIFactory> pDXGIFactory{};
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        return pDXGIFactory;
    }
}