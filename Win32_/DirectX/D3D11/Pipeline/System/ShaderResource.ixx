module;

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:ShaderResource;

import FatPound.Win32.D3D11.Graphics.ResourcePack;
import FatPound.Win32.D3D11.Factory;

import FatPound.Util;

import std;

namespace wrl = Microsoft::WRL;

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
		static void SetView_FatDefault(GraphicsResourcePack& gfxResPack, const FATSPACE_UTIL::ScreenSizeInfo gfxDimensions, const UINT msaaCount, const UINT msaaQuality)
		{
			SetView_FatDefault<ForFramework>(
				gfxResPack.m_pDevice.Get(),
				gfxResPack.m_pImmediateContext.Get(),
				gfxResPack.m_pSysBufferTexture,
				gfxDimensions,
				msaaCount,
				msaaQuality
			);
		}

		template <bool ForFramework = true>
		static void SetView_FatDefault(
				ID3D11Device* const pDevice,
				ID3D11DeviceContext* const pImmediateContext,
				::wrl::ComPtr<ID3D11Texture2D>& pSysBufferTexture,
				const FATSPACE_UTIL::ScreenSizeInfo gfxDimensions,
				const UINT msaaCount,
				const UINT msaaQuality
			)
		{
			::wrl::ComPtr<ID3D11ShaderResourceView> pSysBufferTextureView{};

			{
				const auto& t2dDesc = factory::Texture2D::CreateDESC<ForFramework>(gfxDimensions, msaaCount, msaaQuality);
				factory::Texture2D::Create(pDevice, t2dDesc, pSysBufferTexture);

				const auto& srvDesc = factory::ShaderResourceView::CreateDESC<ForFramework>(t2dDesc.Format, msaaCount);
				factory::ShaderResourceView::Create(pDevice, pSysBufferTexture.Get(), srvDesc, pSysBufferTextureView);
			}

			pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView.GetAddressOf());
		}


	protected:


	private:
	};
}