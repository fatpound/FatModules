module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory.Texture2D;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void Create_Texture2D(FATSPACE_UTIL_GFX::FrameworkResourcePack& gfxFwkResPack, const D3D11_TEXTURE2D_DESC& desc)
    {
        Create_Texture2D(gfxFwkResPack.m_pDevice.Get(), desc, gfxFwkResPack.m_pSysBufferTexture);
    }

    void Create_Texture2D(
        ID3D11Device* const pDevice,
        const D3D11_TEXTURE2D_DESC& desc,
        ::wrl::ComPtr<ID3D11Texture2D>& pSysBufferTexture)
    {
        const auto& hr = pDevice->CreateTexture2D(&desc, nullptr, &pSysBufferTexture);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Texture2D!");
        }
    }
}