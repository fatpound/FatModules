module;

#include <FatWin32_Settings.hpp>

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
		static void SetDefault(const GraphicsResourcePack& gfxResPack);


	protected:


	private:
	};
}