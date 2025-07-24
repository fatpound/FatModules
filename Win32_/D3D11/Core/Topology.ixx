module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11_4.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Core.Topology;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
#endif

import FatPound.Win32.D3D11.Bindable;

export namespace fatpound::win32::d3d11::core
{
    class Topology : public Bindable
    {
    public:
        explicit Topology(const D3D11_PRIMITIVE_TOPOLOGY& type) noexcept
            :
            m_type_(type)
        {

        }

        explicit Topology()                    = delete;
        explicit Topology(const Topology&)     = delete;
        explicit Topology(Topology&&) noexcept = delete;

        auto operator = (const Topology&)     -> Topology& = delete;
        auto operator = (Topology&&) noexcept -> Topology& = delete;
        virtual ~Topology() noexcept override              = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->IASetPrimitiveTopology(m_type_);
        }


    protected:
        D3D11_PRIMITIVE_TOPOLOGY  m_type_;


    private:
    };
}

#endif

// module : private;
