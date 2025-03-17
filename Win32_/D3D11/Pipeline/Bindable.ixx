module;

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)
#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

export module FatPound.Win32.D3D11.Pipeline.Bindable;

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)

export namespace fatpound::win32::d3d11::pipeline
{
    class Bindable
    {
    public:
        explicit Bindable()                    = default;
        explicit Bindable(const Bindable&)     = default;
        explicit Bindable(Bindable&&) noexcept = default;

        auto operator = (const Bindable&)     -> Bindable& = default;
        auto operator = (Bindable&&) noexcept -> Bindable& = default;
        virtual ~Bindable() noexcept                       = default;
        

    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) = 0;


    protected:


    private:
    };
}

#endif

module : private;
