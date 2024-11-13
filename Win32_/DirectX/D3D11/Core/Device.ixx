module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Core:Device;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::core
{
    class Device final
    {
    public:
        explicit Device() = delete;
        explicit Device(const Device& src) = delete;
        explicit Device(Device&& src) = delete;

        auto operator = (const Device& src) -> Device& = delete;
        auto operator = (Device&& src)      -> Device& = delete;
        ~Device() noexcept = delete;


    public:
        static void Create(CGfxResPack auto& gfxResPack)
        {
            Create(gfxResPack.m_pDevice, gfxResPack.m_pImmediateContext);
        }


    public:
        static void Create(
            ::Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
            ::Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pImmediateContext);


    protected:


    private:
    };
}