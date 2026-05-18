module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hxx"
#endif

export module FatX.GStreamer.IAudioEffect;

#ifdef FATX_WITH_GSTREAMER

export namespace fatx::gstreamer
{
    class IAudioEffect
    {
    public:
        IAudioEffect() noexcept               = default;
        IAudioEffect(const IAudioEffect&)     = default;
        IAudioEffect(IAudioEffect&&) noexcept = default;

        auto operator = (const IAudioEffect&)     -> IAudioEffect& = default;
        auto operator = (IAudioEffect&&) noexcept -> IAudioEffect& = default;
        virtual ~IAudioEffect() noexcept                           = default;


    public:
        [[nodiscard]] virtual auto GetBin     () const -> GstElement* = 0;
        [[nodiscard]] virtual auto GetSinkPad () const -> GstPad*     = 0;
        [[nodiscard]] virtual auto GetSrcPad  () const -> GstPad*     = 0;


    protected:


    private:
    };
}

#endif

// module : private;
