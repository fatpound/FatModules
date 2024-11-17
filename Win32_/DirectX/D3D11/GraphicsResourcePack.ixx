module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

#define GFX_RES_PACK_COMMON \
::Microsoft::WRL::ComPtr<::IDXGISwapChain>         m_pSwapChain{};\
::Microsoft::WRL::ComPtr<::ID3D11Device>           m_pDevice{};\
::Microsoft::WRL::ComPtr<::ID3D11DeviceContext>    m_pImmediateContext{};\
::Microsoft::WRL::ComPtr<::ID3D11RenderTargetView> m_pRTV{};\
::Microsoft::WRL::ComPtr<::ID3D11DepthStencilView> m_pDSV{};\

export module FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Util.Color;
import FatPound.Util.ScreenSizeInfo;
import FatPound.Util.Surface;

import std;

export namespace fatpound::win32::d3d11
{
    struct GraphicsResourcePack final
    {
        GFX_RES_PACK_COMMON
    };

    struct GraphicsFrameworkResourcePack final
    {
        GFX_RES_PACK_COMMON

        ::Microsoft::WRL::ComPtr<::ID3D11Texture2D> m_pSysBufferTexture{};

        ::D3D11_MAPPED_SUBRESOURCE m_mappedSysBufferTexture{};

        FATSPACE_UTIL::Surface m_surface;

        GraphicsFrameworkResourcePack(const FATSPACE_UTIL::ScreenSizeInfo& dimensions)
            :
            m_surface(dimensions)
        {
            
        }
    };

    template <typename T>
    concept CGfxResPack = ::std::same_as<T, GraphicsResourcePack> or ::std::same_as<T, GraphicsFrameworkResourcePack>;
}