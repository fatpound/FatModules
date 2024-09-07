module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:RenderTarget;

import FatPound.Win32.D3D11.Graphics.ResourcePack;
import FatPound.Win32.D3D11.Factory;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class RenderTarget final
	{
	public:
		explicit RenderTarget() = delete;
		explicit RenderTarget(const RenderTarget& src) = delete;
		explicit RenderTarget(RenderTarget&& src) = delete;

		auto operator = (const RenderTarget& src) -> RenderTarget& = delete;
		auto operator = (RenderTarget&& src)      -> RenderTarget& = delete;
		~RenderTarget() noexcept = delete;


	public:
		template <bool ForFramework = false>
		static void SetDefault(GraphicsResourcePack& gfxResPack, const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions, const UINT msaaCount, const UINT msaaQuality)
		{
			factory::RenderTargetView::Create(gfxResPack);

			::Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D = nullptr;

			const auto& descTex2D = factory::Texture2D::CreateDESC(gfxDimensions, msaaCount, msaaQuality);
			factory::Texture2D::Create(gfxResPack, pTexture2D, descTex2D);

			if constexpr (not ForFramework)
			{
				const auto& descDSV = factory::DepthStencilView::CreateDESC(msaaCount);
				factory::DepthStencilView::Create(gfxResPack, pTexture2D, descDSV);
			}

			gfxResPack.m_pImmediateContext->OMSetRenderTargets(1u, gfxResPack.m_pTarget.GetAddressOf(), gfxResPack.m_pDSV.Get());
		}


	protected:


	private:
	};
}