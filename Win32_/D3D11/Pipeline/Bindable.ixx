module;

export module FatPound.Win32.D3D11.Pipeline.Bindable;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <d3d11.h>;

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
