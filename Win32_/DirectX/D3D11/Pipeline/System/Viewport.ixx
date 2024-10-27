module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Viewport;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class Viewport final
	{
	public:
		explicit Viewport() = delete;
		explicit Viewport(const Viewport& src) = delete;
		explicit Viewport(Viewport&& src) = delete;

		auto operator = (const Viewport& src) -> Viewport& = delete;
		auto operator = (Viewport&& src)      -> Viewport& = delete;
		~Viewport() noexcept = delete;


	public:
		static void Set_FatDefault(const GraphicsResourcePack& gfxResPack, const FATSPACE_UTIL::ScreenSizeInfo gfxDimensions);

		static void Set_FatDefault(ID3D11DeviceContext* const pImmediateContext, const FATSPACE_UTIL::ScreenSizeInfo gfxDimensions);


	protected:


	private:
	};
}