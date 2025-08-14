module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Resource.SBuffer;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;

import std;

export namespace fatpound::win32::d3d11::resource
{
    template <typename T>
    class SBuffer : public Bindable
    {
    public:
        explicit SBuffer(ID3D11Device* const pDevice, ID3D11DeviceContext* const pImmediateContext, const D3D11_BUFFER_DESC& bufDesc, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc, const std::vector<T>& structures)
        {
            {
                Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
                 
                {
                    const D3D11_SUBRESOURCE_DATA initData
                    {
                        .pSysMem          = structures.data(),
                        .SysMemPitch      = {},
                        .SysMemSlicePitch = {}
                    };

                    if (FAILED(pDevice->CreateBuffer(&bufDesc, &initData, &pBuffer)))
                    {
                        throw std::runtime_error("Could NOT create SBuffer!");
                    }
                }

                if (FAILED(pDevice->CreateShaderResourceView(pBuffer.Get(), &srvDesc, &m_pShaderResourceView_)))
                {
                    throw std::runtime_error("Could NOT create ShaderResourceView!");
                }
            }

            pImmediateContext->VSSetShaderResources(0U, 1U, m_pShaderResourceView_.GetAddressOf());
        }

        explicit SBuffer()                   = delete;
        explicit SBuffer(const SBuffer&)     = delete;
        explicit SBuffer(SBuffer&&) noexcept = delete;

        auto operator = (const SBuffer&)     -> SBuffer& = delete;
        auto operator = (SBuffer&&) noexcept -> SBuffer& = delete;
        virtual ~SBuffer() noexcept override             = default;


    protected:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  m_pShaderResourceView_;


    private:
    };
}

#endif

// module : private;
