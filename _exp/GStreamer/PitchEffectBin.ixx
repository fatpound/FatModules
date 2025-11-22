module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hpp"
#endif

export module FatX.GStreamer.PitchEffectBin;

#ifdef FATX_WITH_GSTREAMER

import FatX.GStreamer.Common;
import FatX.GStreamer.IAudioEffectBin;
import FatX.GStreamer.Pipeline;

export namespace fatx::gstreamer
{
    class PitchEffectBin : public IAudioEffectBin
    {
    public:
        PitchEffectBin() noexcept
            :
            m_pBin_(CreateBin("pitch_bin")),
            m_pValve_(CreatePlugin("valve", "valve_pitch")),
            m_pPitch_(CreatePlugin("pitch", "pitch"))
        {
            gst_bin_add_many(GST_BIN(m_pBin_), m_pValve_, m_pPitch_, nullptr);

            LinkElements(m_pValve_, m_pPitch_);

            const auto sinkpad = UniqueGstPtr<GstPad>{ gst_element_get_static_pad(m_pValve_, "sink") };
            const auto srcpad  = UniqueGstPtr<GstPad>{ gst_element_get_static_pad(m_pPitch_, "src") };

            gst_element_add_pad(m_pBin_, gst_ghost_pad_new("sink", sinkpad.get()));
            gst_element_add_pad(m_pBin_, gst_ghost_pad_new("src", srcpad.get()));
        }
        PitchEffectBin(const PitchEffectBin&)     = default;
        PitchEffectBin(PitchEffectBin&&) noexcept = default;

        auto operator = (const PitchEffectBin&)     -> PitchEffectBin& = default;
        auto operator = (PitchEffectBin&&) noexcept -> PitchEffectBin& = default;
        virtual ~PitchEffectBin() noexcept                             = default;


    public:
        [[nodiscard]] virtual auto GetBin     () const noexcept -> GstElement* override
        {
            return m_pBin_;
        }
        [[nodiscard]] virtual auto GetSinkPad () const noexcept -> GstPad* override
        {
            return gst_element_get_static_pad(m_pBin_, "sink");
        }
        [[nodiscard]] virtual auto GetSrcPad  () const noexcept -> GstPad* override
        {
            return gst_element_get_static_pad(m_pBin_, "src");
        }


    public:
        void SetPitchAsync(Pipeline& pipeline, const double newPitch) noexcept
        {
            pipeline.RunFunc(
                [pPitch = this->m_pPitch_, newPitch]() noexcept -> void
                {
                    if (pPitch not_eq nullptr)
                    {
                        g_object_set(G_OBJECT(pPitch), "pitch", newPitch, nullptr);
                    }
                }
            );
        }


    protected:


    private:
        GstElement*   m_pBin_{};
        GstElement*   m_pValve_{};
        GstElement*   m_pPitch_{};
    };
}

#endif

// module : private;
