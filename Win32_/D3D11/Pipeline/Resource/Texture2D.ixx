module;

#include <FatNamespaces.hpp>
#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource.Texture2D;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Util.Surface;

import std;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <bool ForFramework>
    class Texture2D final
    {
    public:
        Texture2D(ID3D11Device* const pDevice, const UINT width, const UINT height, const UINT msaaCount, const UINT msaaQuality, std::shared_ptr<FATSPACE_UTIL::Surface> pSurface = {})
        {
            D3D11_TEXTURE2D_DESC texDesc{};
            texDesc.Width = width;
            texDesc.Height = height;
            texDesc.MipLevels = 1u;
            texDesc.ArraySize = 1u;

            if constexpr (ForFramework)
            {
                texDesc.SampleDesc.Count = 1;
                texDesc.SampleDesc.Quality = 0;
                texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                texDesc.Usage = D3D11_USAGE_DYNAMIC;
                texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            }
            else
            {
                texDesc.SampleDesc.Count = msaaCount;
                texDesc.SampleDesc.Quality = msaaQuality - 1u;
                texDesc.Format = DXGI_FORMAT_D32_FLOAT;
                texDesc.Usage = D3D11_USAGE_DEFAULT;
                texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            }

            ::Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;

            const D3D11_SUBRESOURCE_DATA* pSubresourceData{};

            if (pSurface not_eq nullptr)
            {
                D3D11_SUBRESOURCE_DATA sd{};
                sd.pSysMem = *pSurface;
                sd.SysMemPitch = pSurface->GetPitch<>();

                pSubresourceData = &sd;
            }

            const auto& hr = pDevice->CreateTexture2D(&texDesc, pSubresourceData, &m_pTexture2D_);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("Could NOT create Texture2D!");
            }
        }


    public:
        auto Get() const -> ID3D11Texture2D*
        {
            return m_pTexture2D_.Get();
        }


    protected:


    private:
        ::Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture2D_;
    };
}

module : private;