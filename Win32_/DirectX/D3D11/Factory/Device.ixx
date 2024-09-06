module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

export module FatPound.Win32.D3D11.Factory:Device;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class Device final
    {
    public:
        explicit Device() = delete;
        explicit Device(const Device& src) = delete;
        explicit Device(Device&& src) = delete;

        Device& operator = (const Device& src) = delete;
        Device& operator = (Device&& src) = delete;
        ~Device() noexcept = delete;


    public:
        static void Create(GraphicsResourcePack& gfxResPack);


    protected:


    private:
    };
}