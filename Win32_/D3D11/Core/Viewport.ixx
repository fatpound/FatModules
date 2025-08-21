module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <d3d11_4.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Core.Viewport;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
#endif

import FatPound.Win32.D3D11.Bindable;

export namespace fatpound::win32::d3d11::core
{
    class Viewport : public Bindable
    {
    public:
        explicit Viewport(const D3D11_VIEWPORT& vp) noexcept
            :
            m_vp_(vp)
        {
            
        }

        explicit Viewport()                    = delete;
        explicit Viewport(const Viewport&)     = delete;
        explicit Viewport(Viewport&&) noexcept = default;

        auto operator = (const Viewport&)     -> Viewport& = delete;
        auto operator = (Viewport&&) noexcept -> Viewport& = default;
        virtual ~Viewport() noexcept override              = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->RSSetViewports(1U, &m_vp_);
        }


    protected:
        D3D11_VIEWPORT  m_vp_;


    private:
    };
}

#endif

// module : private;
