module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:SwapChain;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Win32.DXGI;

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
        template <bool ForFramework = false>
        static auto CreateDESC(
                const HWND hWnd,
                const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions,
                [[maybe_unused]] const UINT msaaCount,
                [[maybe_unused]] const UINT msaaQuality
            )
            noexcept -> DXGI_SWAP_CHAIN_DESC
        {
            DXGI_SWAP_CHAIN_DESC desc = {};
            desc.BufferDesc.Width = gfxDimensions.m_width;
            desc.BufferDesc.Height = gfxDimensions.m_height;
            desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
            desc.BufferDesc.RefreshRate.Numerator = 0u;
            desc.BufferDesc.RefreshRate.Denominator = 0u;
            desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            desc.BufferCount = 1u;
            desc.OutputWindow = hWnd;
            desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            desc.Flags = 0u;

            if constexpr (ForFramework)
            {
                desc.SampleDesc.Count = 1u;
                desc.SampleDesc.Quality = 0u;
            }
            else
            {
                desc.SampleDesc.Count = msaaCount;
                desc.SampleDesc.Quality = msaaQuality - 1u;
            }

            if constexpr (IN_RELEASE)
            {
                desc.Windowed = false;
            }
            else
            {
                desc.Windowed = true;
            }

            return desc;
        }


    public:
        static auto CreateDESC(
            const HWND hWnd,
            const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions,
            const UINT msaaCount,
            const UINT msaaQuality
        ) 
        noexcept -> DXGI_SWAP_CHAIN_DESC;

        static void Create(GraphicsResourcePack& gfxResPack, DXGI_SWAP_CHAIN_DESC& desc);

        static void Create(
            ID3D11Device* const pDevice,
            DXGI_SWAP_CHAIN_DESC& desc,
            ::Microsoft::WRL::ComPtr<IDXGISwapChain>& pSwapChain
        );


    protected:


    private:
    };
}