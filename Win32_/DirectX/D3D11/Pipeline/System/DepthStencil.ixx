module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:DepthStencil;

import FatPound.Win32.D3D11.Graphics.ResourcePack;
import FatPound.Win32.D3D11.Factory;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class DepthStencil final
	{
	public:
		explicit DepthStencil() = delete;
		explicit DepthStencil(const DepthStencil& src) = delete;
		explicit DepthStencil(DepthStencil&& src) = delete;

		auto operator = (const DepthStencil& src) -> DepthStencil& = delete;
		auto operator = (DepthStencil&& src)      -> DepthStencil& = delete;
		~DepthStencil() noexcept = delete;


	public:
		static void SetState_FatDefault(const GraphicsResourcePack& gfxResPack);

		static void SetState_FatDefault(
			ID3D11Device* const pDevice,
			ID3D11DeviceContext* const pImmediateContext);


	protected:


	private:
	};
}