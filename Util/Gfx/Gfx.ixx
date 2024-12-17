module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Util.Gfx;

export import FatPound.Util.Gfx.FullScreenQuad;
export import FatPound.Util.Gfx.ResourcePack;

import std;

export namespace fatpound::util::gfx
{
    template <typename T>
    concept ConGfxResPack = ::std::same_as<T, ResourcePack> or ::std::same_as<T, FrameworkResourcePack>;

    auto GetDXGIFactory(ID3D11Device* const pDevice) -> ::Microsoft::WRL::ComPtr<IDXGIFactory>;

    void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND hWnd, UINT& flag);
}