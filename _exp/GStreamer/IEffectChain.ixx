module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hxx"
#endif

export module FatX.GStreamer.IEffectChain;

#ifdef FATX_WITH_GSTREAMER

import FatX.GStreamer.IAudioEffect;
import std;

export namespace fatx::gstreamer
{
    class IEffectChain
    {
    public:
        IEffectChain() noexcept                   = default;
        IEffectChain(const IEffectChain&)         = delete;
        IEffectChain(IEffectChain&&)    noexcept  = delete;

        auto operator = (const IEffectChain&)     -> IEffectChain& = delete;
        auto operator = (IEffectChain&&) noexcept -> IEffectChain& = delete;
        virtual ~IEffectChain() noexcept                           = default;


    public:
        [[nodiscard]] virtual auto GetBin     () const noexcept -> GstElement* = 0;
        [[nodiscard]] virtual auto GetSinkPad () const noexcept -> GstPad*     = 0;
        [[nodiscard]] virtual auto GetSrcPad  () const noexcept -> GstPad*     = 0;
        [[nodiscard]] virtual auto Count      () const noexcept -> std::size_t = 0;

        virtual void Add(std::shared_ptr<IAudioEffect> pEffect) noexcept = 0;


    protected:


    private:
    };
}

#endif

// module : private;
