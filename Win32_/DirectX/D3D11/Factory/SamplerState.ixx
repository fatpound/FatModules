module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:SamplerState;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class SamplerState final
    {
    public:
        explicit SamplerState() = delete;
        explicit SamplerState(const SamplerState& src) = delete;
        explicit SamplerState(SamplerState&& src) = delete;

        auto operator = (const SamplerState& src) -> SamplerState& = delete;
        auto operator = (SamplerState&& src)      -> SamplerState& = delete;
        ~SamplerState() noexcept = delete;


    public:
        static constexpr auto CreateDESC() noexcept -> D3D11_SAMPLER_DESC
        {
            D3D11_SAMPLER_DESC desc{};
            desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
            desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
            desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
            desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
            desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
            desc.MinLOD = 0.0f;
            desc.MaxLOD = D3D11_FLOAT32_MAX;

            return desc;
        }


    public:
        static void Create(
            const GraphicsResourcePack& gfxResPack,
            D3D11_SAMPLER_DESC desc,
            ::Microsoft::WRL::ComPtr<ID3D11SamplerState>& pSamplerState
        );

        static void Create(
            ID3D11Device* const pDevice,
            D3D11_SAMPLER_DESC desc,
            ::Microsoft::WRL::ComPtr<ID3D11SamplerState>& pSamplerState
        );


    protected:


    private:
    };
}