module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory.RenderTargetView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void Create_RenderTargetView(FATSPACE_UTIL_GFX::ResourcePack& gfxResPack)
    {
        Create_RenderTargetView(
            gfxResPack.m_pSwapChain.Get(),
            gfxResPack.m_pDevice.Get(),
            gfxResPack.m_pRTV
        );
    }

    void Create_RenderTargetView(
        IDXGISwapChain* const pSwapChain,
        ID3D11Device* const pDevice,
        ::wrl::ComPtr<ID3D11RenderTargetView>& pRenderTargetView)
    {
        ::wrl::ComPtr<ID3D11Texture2D> pBackBufferTexture{};

        HRESULT hr;

        hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBufferTexture);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT get the buffer from SwapChain!");
        }

        hr = pDevice->CreateRenderTargetView(pBackBufferTexture.Get(), nullptr, &pRenderTargetView);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RenderTargetView!");
        }
    }
}