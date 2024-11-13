module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:DepthStencilView;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class DepthStencilView final
    {
    public:
        explicit DepthStencilView() = delete;
        explicit DepthStencilView(const DepthStencilView& src) = delete;
        explicit DepthStencilView(DepthStencilView&& src) = delete;

        auto operator = (const DepthStencilView& src) -> DepthStencilView& = delete;
        auto operator = (DepthStencilView&& src)      -> DepthStencilView& = delete;
        ~DepthStencilView() noexcept = delete;


    public:
        static constexpr auto CreateDESC(const UINT msaaCount) noexcept -> D3D11_DEPTH_STENCIL_VIEW_DESC
        {
            D3D11_DEPTH_STENCIL_VIEW_DESC desc{};
            desc.Format = DXGI_FORMAT_D32_FLOAT;

            if (msaaCount == 1u)
            {
                desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
                desc.Texture2D.MipSlice = 0u;
            }
            else
            {
                desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
                desc.Texture2D.MipSlice = 1u;
            }

            return desc;
        }


    public:
        static void Create(
            GraphicsResourcePack& gfxResPack,
            const ::Microsoft::WRL::ComPtr<ID3D11Texture2D>& pDepthStencil,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& desc);

        static void Create(
            ID3D11Device* const pDevice,
            const ::Microsoft::WRL::ComPtr<ID3D11Texture2D>& pDepthStencil,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& desc,
            ::Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& pDSV);


    protected:


    private:
    };
}