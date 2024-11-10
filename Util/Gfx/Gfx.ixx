module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Util.Gfx;

export import FatPound.Util.Gfx.FullScreenQuad;

export namespace fatpound::util::gfx
{
    auto GetDXGIFactory(ID3D11Device* const pDevice) -> ::Microsoft::WRL::ComPtr<IDXGIFactory>;

    void ToggleDXGI_AltEnterMode(ID3D11Device* const pDevice, const HWND hWnd, UINT& flag);
}