module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:DepthStencilState;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class DepthStencilState final
    {
    public:
        explicit DepthStencilState() = delete;
        explicit DepthStencilState(const DepthStencilState& src) = delete;
        explicit DepthStencilState(DepthStencilState&& src) = delete;

        auto operator = (const DepthStencilState& src) -> DepthStencilState& = delete;
        auto operator = (DepthStencilState&& src)      -> DepthStencilState& = delete;
        ~DepthStencilState() noexcept = delete;


    public:
        static constexpr auto CreateDESC() noexcept -> D3D11_DEPTH_STENCIL_DESC
        {
            D3D11_DEPTH_STENCIL_DESC desc{};
            desc.DepthEnable = true;
            desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
            desc.DepthFunc = D3D11_COMPARISON_LESS;

            return desc;
        }


    public:
        static void Create(
            const GraphicsResourcePack& gfxResPack,
            const D3D11_DEPTH_STENCIL_DESC& desc,
            ::Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& pDSState);

        static void Create(
            ID3D11Device* const pDevice,
            const D3D11_DEPTH_STENCIL_DESC& desc,
            ::Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& pDSState);


    protected:


    private:
    };
}