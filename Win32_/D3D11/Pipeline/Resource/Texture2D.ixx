module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.Texture2D;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Utility.Surface;
import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::pipeline
{
    class Texture2D final : public Bindable
    {
    public:
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, std::shared_ptr<FATSPACE_UTILITY::Surface> pSurface)
        {
            wrl::ComPtr<ID3D11Texture2D> pTex2d;

            if (pSurface not_eq nullptr)
            {
                const D3D11_SUBRESOURCE_DATA sd
                {
                    .pSysMem          = *pSurface,
                    .SysMemPitch      =  pSurface->GetPitch<UINT>(),
                    .SysMemSlicePitch = {}
                };

                if (const auto& hr = pDevice->CreateTexture2D(&tex2dDesc, &sd, &pTex2d);
                    FAILED(hr))
                {
                    throw std::runtime_error("Could NOT create Texture2D!");
                }
            }
            else
            {
                throw std::runtime_error("pSurface is empty!");
            }

            if (const auto& hr = pDevice->CreateShaderResourceView(pTex2d.Get(), &srvDesc, &m_pSRV_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create ShaderResourceView!");
            }
        }
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, wrl::ComPtr<ID3D11Texture2D>& pTex2d)
        {
            if (const auto& hr = pDevice->CreateTexture2D(&tex2dDesc, nullptr, &pTex2d);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create Texture2D!");
            }

            if (const auto& hr = pDevice->CreateShaderResourceView(pTex2d.Get(), &srvDesc, &m_pSRV_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create ShaderResourceView!");
            }
        }

        explicit Texture2D()                     = delete;
        explicit Texture2D(const Texture2D&)     = delete;
        explicit Texture2D(Texture2D&&) noexcept = delete;

        auto operator = (const Texture2D&)     -> Texture2D& = delete;
        auto operator = (Texture2D&&) noexcept -> Texture2D& = delete;
        virtual ~Texture2D() noexcept override final         = default;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final
        {
            pImmediateContext->PSSetShaderResources(0U, 1U, m_pSRV_.GetAddressOf());
        }


    protected:


    private:
        wrl::ComPtr<ID3D11ShaderResourceView>  m_pSRV_;
    };
}

#endif

module : private;
