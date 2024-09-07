module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:SwapChain;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void SwapChain::Create(GraphicsResourcePack& gfxResPack, DXGI_SWAP_CHAIN_DESC& desc)
    {
        Create(gfxResPack.m_pDevice.Get(), desc, gfxResPack.m_pSwapChain);
    }

    void SwapChain::Create(
            ID3D11Device* const pDevice,
            DXGI_SWAP_CHAIN_DESC& desc,
            ::wrl::ComPtr<IDXGISwapChain>& pSwapChain
        )
    {
        ::wrl::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
        pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        ::wrl::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        ::wrl::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        const auto& hr = pDXGIFactory->CreateSwapChain(
            pDevice,
            &desc,
            pSwapChain.GetAddressOf()
        );

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Direct3D SwapChain!");
        }
    }
}