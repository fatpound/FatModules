module;

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Sampler;

import FatPound.Win32.D3D11.Graphics.ResourcePack;
import FatPound.Win32.D3D11.Factory;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class Sampler final
	{
	public:
		explicit Sampler() = delete;
		explicit Sampler(const Sampler& src) = delete;
		explicit Sampler(Sampler&& src) = delete;

		auto operator = (const Sampler& src) -> Sampler& = delete;
		auto operator = (Sampler&& src)      -> Sampler& = delete;
		~Sampler() noexcept = delete;


	public:
		static void SetState_FatDefault(const CGfxResPack auto& gfxResPack)
		{
			SetState_FatDefault(gfxResPack.m_pDevice.Get(), gfxResPack.m_pImmediateContext.Get());
		}


	public:
		static void SetState_FatDefault(
			ID3D11Device* const pDevice,
			ID3D11DeviceContext* const pImmediateContext);


	protected:


	private:
	};
}