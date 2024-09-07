module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:RenderTargetView;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class RenderTargetView final
    {
    public:
        explicit RenderTargetView() = delete;
        explicit RenderTargetView(const RenderTargetView& src) = delete;
        explicit RenderTargetView(RenderTargetView&& src) = delete;

        auto operator = (const RenderTargetView& src) -> RenderTargetView& = delete;
        auto operator = (RenderTargetView&& src)      -> RenderTargetView& = delete;
        ~RenderTargetView() noexcept = delete;


    public:
        static void Create(GraphicsResourcePack& gfxResPack);

        static void Create(
            IDXGISwapChain* const pSwapChain,
            ID3D11Device* const pDevice,
            ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& pRenderTargetView
        );


    protected:


    private:
    };
}