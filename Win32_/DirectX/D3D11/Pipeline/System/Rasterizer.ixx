module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Rasterizer;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class Rasterizer final
	{
	public:
		explicit Rasterizer() = delete;
		explicit Rasterizer(const Rasterizer& src) = delete;
		explicit Rasterizer(Rasterizer&& src) = delete;

		auto operator = (const Rasterizer& src) -> Rasterizer& = delete;
		auto operator = (Rasterizer&& src)      -> Rasterizer& = delete;
		~Rasterizer() noexcept = delete;


	public:
		static void SetState_FatDefault(const GraphicsResourcePack& gfxResPack);

		static void SetState_FatDefault(
			ID3D11Device* const pDevice,
			ID3D11DeviceContext* const pImmediateContext
		);


	protected:


	private:
	};
}