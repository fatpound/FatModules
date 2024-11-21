module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Core.Device;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::core
{
    void Create_Device(
        ::Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
        ::Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pImmediateContext);

    void Create_Device(CGfxResPack auto& gfxResPack)
    {
        Create_Device(gfxResPack.m_pDevice, gfxResPack.m_pImmediateContext);
    }
}