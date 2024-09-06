module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:SwapChain;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    auto SwapChain::CreateDESC(
            const HWND hWnd,
            const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions,
            const UINT msaaCount,
            const UINT msaaQuality
        )
        noexcept -> DXGI_SWAP_CHAIN_DESC
    {
        DXGI_SWAP_CHAIN_DESC desc = {};
        desc.BufferDesc.Width = gfxDimensions.m_width;
        desc.BufferDesc.Height = gfxDimensions.m_height;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.RefreshRate.Numerator = 0u;
        desc.BufferDesc.RefreshRate.Denominator = 0u;
        desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.SampleDesc.Count = msaaCount;
        desc.SampleDesc.Quality = msaaQuality - 1u;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = 1u;
        desc.OutputWindow = hWnd;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        desc.Flags = 0u;

        if constexpr (IN_RELEASE)
        {
            desc.Windowed = false;
        }
        else
        {
            desc.Windowed = true;
        }

        return desc;
    }

    void SwapChain::Create(GraphicsResourcePack& gfxResPack, DXGI_SWAP_CHAIN_DESC& desc)
    {
        ::wrl::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
        gfxResPack.m_pDevice->QueryInterface(__uuidof(IDXGIDevice), &pDXGIDevice);

        ::wrl::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
        pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &pDXGIAdapter);

        ::wrl::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), &pDXGIFactory);

        const auto& hr = pDXGIFactory->CreateSwapChain(
            gfxResPack.m_pDevice.Get(),
            &desc,
            gfxResPack.m_pSwapChain.GetAddressOf()
        );

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Direct3D SwapChain!");
        }
    }
}