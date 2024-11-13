module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:Rasterizer;

import FatPound.Win32.D3D11.Factory;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
    void Rasterizer::SetState_FatDefault(const GraphicsResourcePack& gfxResPack)
    {
        SetState_FatDefault(gfxResPack.m_pDevice.Get(), gfxResPack.m_pImmediateContext.Get());
    }

    void Rasterizer::SetState_FatDefault(
            ID3D11Device* const pDevice,
            ID3D11DeviceContext* const pImmediateContext)
    {
        ::wrl::ComPtr<ID3D11RasterizerState> pRasterizerState{};

        {
            const auto& descRS = factory::RasterizerState::CreateDESC();
            factory::RasterizerState::Create(pDevice, descRS, pRasterizerState);
        }

        pImmediateContext->RSSetState(pRasterizerState.Get());
    }
}