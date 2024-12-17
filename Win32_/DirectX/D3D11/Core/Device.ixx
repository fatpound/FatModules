module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Core.Device;

import FatPound.Util.Gfx;

import std;

export namespace fatpound::win32::d3d11::core
{
    void Create_Device(FATSPACE_UTIL_GFX::ResourcePack& gfxResPack);

    void Create_Device(
        ::Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
        ::Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pImmediateContext);
}