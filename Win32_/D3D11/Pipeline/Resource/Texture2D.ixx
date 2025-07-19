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
    class Texture2D
    {
    public:
        explicit Texture2D(IDXGISwapChain* const pSwapChain)
        {
            if (FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_pTex2d_)))
            {
                throw std::runtime_error("Could NOT get the buffer from SwapChain!");
            }
        }
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc, std::shared_ptr<FATSPACE_UTILITY::Surface> pSurface)
        {
            if (pSurface not_eq nullptr)
            {
                const D3D11_SUBRESOURCE_DATA sd
                {
                    .pSysMem          = *pSurface,
                    .SysMemPitch      =  pSurface->GetPitch<UINT>(),
                    .SysMemSlicePitch = {}
                };

                if (FAILED(pDevice->CreateTexture2D(&tex2dDesc, &sd, &m_pTex2d_)))
                {
                    throw std::runtime_error("Could NOT create Texture2D!");
                }
            }
            else
            {
                throw std::runtime_error("pSurface is empty!");
            }
        }
        explicit Texture2D(ID3D11Device* const pDevice, const D3D11_TEXTURE2D_DESC& tex2dDesc)
        {
            if (FAILED(pDevice->CreateTexture2D(&tex2dDesc, nullptr, &m_pTex2d_)))
            {
                throw std::runtime_error("Could NOT create Texture2D!");
            }
        }

        explicit Texture2D()                     = default;
        explicit Texture2D(const Texture2D&)     = delete;
        explicit Texture2D(Texture2D&&) noexcept = delete;

        auto operator = (const Texture2D&)     -> Texture2D& = delete;
        auto operator = (Texture2D&&) noexcept -> Texture2D& = default;
        ~Texture2D() noexcept                                = default;


    public:
        auto GetBuffer() const noexcept -> ID3D11Texture2D*
        {
            return m_pTex2d_.Get();
        }


    protected:
        wrl::ComPtr<ID3D11Texture2D>  m_pTex2d_;


    private:
    };
}

#endif

// module : private;
