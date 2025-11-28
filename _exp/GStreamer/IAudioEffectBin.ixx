module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hxx"
#endif

export module FatX.GStreamer.IAudioEffectBin;

#ifdef FATX_WITH_GSTREAMER

export namespace fatx::gstreamer
{
    class IAudioEffectBin
    {
    public:
        IAudioEffectBin() noexcept                  = default;
        IAudioEffectBin(const IAudioEffectBin&)     = default;
        IAudioEffectBin(IAudioEffectBin&&) noexcept = default;

        auto operator = (const IAudioEffectBin&)     -> IAudioEffectBin& = default;
        auto operator = (IAudioEffectBin&&) noexcept -> IAudioEffectBin& = default;
        virtual ~IAudioEffectBin() noexcept                              = default;


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
