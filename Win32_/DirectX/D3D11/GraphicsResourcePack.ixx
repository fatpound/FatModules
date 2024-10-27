module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11
{
    struct GraphicsResourcePack final
    {
        ::Microsoft::WRL::ComPtr<IDXGISwapChain>         m_pSwapChain{};
        ::Microsoft::WRL::ComPtr<ID3D11Device>           m_pDevice{};
        ::Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_pImmediateContext{};
        ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRTV{};
        ::Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDSV{};

        ::Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pSysBufferTexture{};

        D3D11_MAPPED_SUBRESOURCE m_mappedSysBufferTexture{};

        FATSPACE_UTIL::Color* m_pSysBuffer{};
    };
}