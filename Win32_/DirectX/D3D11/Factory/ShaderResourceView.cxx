module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:ShaderResourceView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void ShaderResourceView::Create(
            const GraphicsResourcePack& gfxResPack,
            D3D11_SHADER_RESOURCE_VIEW_DESC desc,
            ::wrl::ComPtr<ID3D11ShaderResourceView>& pSysBufferTextureView
        )
    {
        Create(
            gfxResPack.m_pDevice.Get(),
            gfxResPack.m_pSysBufferTexture.Get(),
            desc,
            pSysBufferTextureView
        );
    }

    void ShaderResourceView::Create(
            ID3D11Device* const pDevice,
            ID3D11Texture2D* pSysBufferTexture,
            D3D11_SHADER_RESOURCE_VIEW_DESC desc,
            ::wrl::ComPtr<ID3D11ShaderResourceView>& pSysBufferTextureView
        )
    {
        const auto& hr = pDevice->CreateShaderResourceView(pSysBufferTexture, &desc, &pSysBufferTextureView);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create ShaderResourceView!");
        }
    }
}