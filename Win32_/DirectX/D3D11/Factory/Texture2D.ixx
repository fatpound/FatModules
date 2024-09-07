module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:Texture2D;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class Texture2D final
    {
    public:
        explicit Texture2D() = delete;
        explicit Texture2D(const Texture2D& src) = delete;
        explicit Texture2D(Texture2D&& src) = delete;

        auto operator = (const Texture2D& src) -> Texture2D& = delete;
        auto operator = (Texture2D&& src)      -> Texture2D& = delete;
        ~Texture2D() noexcept = delete;


    public:
        template <bool ForShaderResource = false>
        static constexpr auto CreateDESC(
                const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions,
                const UINT msaaCount,
                const UINT msaaQuality
            )
            noexcept -> D3D11_TEXTURE2D_DESC
        {
            D3D11_TEXTURE2D_DESC desc = {};
            desc.Width = gfxDimensions.m_width;
            desc.Height = gfxDimensions.m_height;
            desc.MipLevels = 1u;
            desc.ArraySize = 1u;
            desc.SampleDesc.Count = msaaCount;
            desc.SampleDesc.Quality = msaaQuality - 1u;

            if constexpr (ForShaderResource)
            {
                desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                desc.Usage = D3D11_USAGE_DYNAMIC;
                desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            }
            else
            {
                desc.Format = DXGI_FORMAT_D32_FLOAT;
                desc.Usage = D3D11_USAGE_DEFAULT;
                desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            }

            return desc;
        }


    public:
        static void Create(GraphicsResourcePack& gfxResPack, const D3D11_TEXTURE2D_DESC& desc);

        static void Create(
            ID3D11Device* const pDevice,
            const D3D11_TEXTURE2D_DESC& desc,
            ::Microsoft::WRL::ComPtr<ID3D11Texture2D>& pTexture2D
        );


    protected:


    private:
    };
}