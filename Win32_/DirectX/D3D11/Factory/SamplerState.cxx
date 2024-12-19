module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory.SamplerState;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void Create_SamplerState(
        const FATSPACE_UTIL_GFX::ResourcePack& gfxResPack,
        D3D11_SAMPLER_DESC desc,
        ::Microsoft::WRL::ComPtr<ID3D11SamplerState>& pSamplerState)
    {
        Create_SamplerState(gfxResPack.m_pDevice.Get(), desc, pSamplerState);
    }

    void Create_SamplerState(
        ID3D11Device* const pDevice,
        D3D11_SAMPLER_DESC desc,
        ::wrl::ComPtr<ID3D11SamplerState>& pSamplerState)
    {
        const auto& hr = pDevice->CreateSamplerState(&desc, &pSamplerState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create SamplerState");
        }
    }
}