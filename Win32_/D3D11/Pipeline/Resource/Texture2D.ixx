module;

#if FAT_BUILDING_WITH_MSVC
#include <FatNamespaces.hpp>

#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

export module FatPound.Win32.D3D11.Pipeline.Resource.Texture2D;

#if FAT_BUILDING_WITH_MSVC

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Util.Surface;

import std;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    class Texture2D final : public Bindable
    {
    public:
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, std::shared_ptr<FATSPACE_UTIL::Surface> pSurface = {})
        {
            ::Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;

            {
                const D3D11_SUBRESOURCE_DATA sd
                {
                    .pSysMem     = *pSurface,
                    .SysMemPitch =  pSurface->GetPitch<UINT>()
                };

                if (const auto& hr = pDevice->CreateTexture2D(
                    &tex2dDesc,
                    sd.pSysMem not_eq nullptr ? &sd : nullptr,
                    &pTexture); FAILED(hr))
                {
                    throw std::runtime_error("Could NOT create Texture2D!");
                }
            }

            if (const auto& hr = pDevice->CreateShaderResourceView(pTexture.Get(), &srvDesc, &m_pSRV_); FAILED(hr))
            {
                throw std::runtime_error("Could NOT create ShaderResourceView!");
            }
        }

        explicit Texture2D()                     = delete;
        explicit Texture2D(const Texture2D&)     = delete;
        explicit Texture2D(Texture2D&&) noexcept = delete;

        auto operator = (const Texture2D&)     -> Texture2D& = delete;
        auto operator = (Texture2D&&) noexcept -> Texture2D& = delete;
        virtual ~Texture2D() noexcept final                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final
        {
            pImmediateContext->PSSetShaderResources(0, 1, m_pSRV_.GetAddressOf());
        }


    protected:


    private:
        ::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV_;
    };
}

#endif

module : private;
