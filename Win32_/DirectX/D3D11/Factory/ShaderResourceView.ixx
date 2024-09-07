module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:ShaderResourceView;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class ShaderResourceView final
    {
    public:
        explicit ShaderResourceView() = delete;
        explicit ShaderResourceView(const ShaderResourceView& src) = delete;
        explicit ShaderResourceView(ShaderResourceView&& src) = delete;

        auto operator = (const ShaderResourceView& src) -> ShaderResourceView& = delete;
        auto operator = (ShaderResourceView&& src)      -> ShaderResourceView& = delete;
        ~ShaderResourceView() noexcept = delete;


    public:
        static constexpr auto CreateDESC(const DXGI_FORMAT format, const UINT msaaCount) noexcept -> D3D11_SHADER_RESOURCE_VIEW_DESC
        {
            D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
            desc.Format = format;
            desc.Texture2D.MipLevels = 1u;

            if (msaaCount == 1u)
            {
                desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            }
            else
            {
                desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
            }

            return desc;
        }


    public:
        static void Create(
            const GraphicsResourcePack& gfxResPack,
            ::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pSysBufferTextureView,
            D3D11_SHADER_RESOURCE_VIEW_DESC desc
        );


    protected:


    private:
    };
}