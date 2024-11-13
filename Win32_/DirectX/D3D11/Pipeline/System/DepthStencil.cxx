module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:DepthStencil;

import FatPound.Win32.D3D11.Factory;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
	void DepthStencil::SetState_FatDefault(const GraphicsResourcePack& gfxResPack)
	{
		SetState_FatDefault(gfxResPack.m_pDevice.Get(), gfxResPack.m_pImmediateContext.Get());
	}

	void DepthStencil::SetState_FatDefault(
			ID3D11Device* const pDevice,
			ID3D11DeviceContext* const pImmediateContext)
	{
		::wrl::ComPtr<ID3D11DepthStencilState> pDSState{};

		{
			const auto& descDSS = factory::DepthStencilState::CreateDESC();
			factory::DepthStencilState::Create(pDevice, descDSS, pDSState);
		}

		pImmediateContext->OMSetDepthStencilState(pDSState.Get(), 1u);
	}
}