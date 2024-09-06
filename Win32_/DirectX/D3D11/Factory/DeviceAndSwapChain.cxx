module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DeviceAndSwapChain;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void DeviceAndSwapChain::Create(GraphicsResourcePack& gfxResPack, const DXGI_SWAP_CHAIN_DESC& desc)
    {
        static constinit UINT swapCreateFlags;

        if constexpr (IN_RELEASE)
        {
            swapCreateFlags = 0u;
        }
        else
        {
            swapCreateFlags = D3D11_CREATE_DEVICE_DEBUG;
        }

        D3D_FEATURE_LEVEL featureLevel{};

        const auto hr = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            swapCreateFlags,
            nullptr,
            0u,
            D3D11_SDK_VERSION,
            &desc,
            &gfxResPack.m_pSwapChain,
            &gfxResPack.m_pDevice,
            &featureLevel,
            &gfxResPack.m_pImmediateContext
        );

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create the Device and SwapChain!");
        }

        if (featureLevel not_eq D3D_FEATURE_LEVEL_11_0)
        {
            throw std::runtime_error("Direct3D Feature Level 11 is unsupported!");
        }
    }
}