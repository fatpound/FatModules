module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:ShaderResource;

import FatPound.Win32.D3D11.Graphics.ResourcePack;
import FatPound.Win32.D3D11.Factory;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class ShaderResource final
	{
	public:
		explicit ShaderResource() = delete;
		explicit ShaderResource(const ShaderResource& src) = delete;
		explicit ShaderResource(ShaderResource&& src) = delete;

		auto operator = (const ShaderResource& src) -> ShaderResource& = delete;
		auto operator = (ShaderResource&& src)      -> ShaderResource& = delete;
		~ShaderResource() noexcept = delete;


	public:
		template <bool ForFramework = true>
		static void SetDefault(GraphicsResourcePack& gfxResPack, const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions, const UINT msaaCount, const UINT msaaQuality)
		{
			const auto& t2dDesc = factory::Texture2D::CreateDESC<ForFramework>(gfxDimensions, msaaCount, msaaQuality);
			factory::Texture2D::Create(gfxResPack, t2dDesc);

			::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pSysBufferTextureView_ = nullptr;

			const auto& srvDesc = factory::ShaderResourceView::CreateDESC(t2dDesc.Format, msaaCount);
			factory::ShaderResourceView::Create(gfxResPack, pSysBufferTextureView_, srvDesc);

			gfxResPack.m_pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView_.GetAddressOf());
		}


	protected:


	private:
	};
}