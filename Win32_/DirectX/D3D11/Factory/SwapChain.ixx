module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

export module FatPound.Win32.D3D11.Factory:SwapChain;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class SwapChain final
    {
    public:
        explicit SwapChain() = delete;
        explicit SwapChain(const SwapChain& src) = delete;
        explicit SwapChain(SwapChain&& src) = delete;

        auto operator = (const SwapChain& src) -> SwapChain& = delete;
        auto operator = (SwapChain&& src)      -> SwapChain& = delete;
        ~SwapChain() noexcept = delete;


    public:
        static auto CreateDESC(
            const HWND hWnd,
            const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions,
            const UINT msaaCount,
            const UINT msaaQuality
        ) 
        noexcept -> DXGI_SWAP_CHAIN_DESC;

        static void Create(GraphicsResourcePack& gfxResPack, DXGI_SWAP_CHAIN_DESC& desc);


    protected:


    private:
    };
}