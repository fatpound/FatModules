module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory.ShaderResourceView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void Create_ShaderResourceView(
        const FATSPACE_UTIL_GFX::FrameworkResourcePack& gfxFwkResPack,
        D3D11_SHADER_RESOURCE_VIEW_DESC desc,
        ::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pSysBufferTextureView)
    {
        Create_ShaderResourceView(
            gfxFwkResPack.m_pDevice.Get(),
            gfxFwkResPack.m_pSysBufferTexture.Get(),
            desc,
            pSysBufferTextureView
        );
    }

    void Create_ShaderResourceView(
        ID3D11Device* const pDevice,
        ID3D11Texture2D* pSysBufferTexture,
        D3D11_SHADER_RESOURCE_VIEW_DESC desc,
        ::wrl::ComPtr<ID3D11ShaderResourceView>& pSysBufferTextureView)
    {
        const auto& hr = pDevice->CreateShaderResourceView(pSysBufferTexture, &desc, &pSysBufferTextureView);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create ShaderResourceView!");
        }
    }
}