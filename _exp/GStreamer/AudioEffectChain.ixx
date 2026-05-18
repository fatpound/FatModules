module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hxx"
#endif

export module FatX.GStreamer.AudioEffectChain;

#ifdef FATX_WITH_GSTREAMER

export import FatX.GStreamer.IEffectChain;
import FatX.GStreamer.Common;
import FatX.GStreamer.IAudioEffect;

import std;

export namespace fatx::gstreamer
{
    class AudioEffectChain final : public IEffectChain
    {
    public:
        explicit AudioEffectChain() noexcept
            :
            m_pBin_(CreateBin("audio_effect_chain"))
        {

        }

        AudioEffectChain(const AudioEffectChain&)     = delete;
        AudioEffectChain(AudioEffectChain&&) noexcept = delete;

        auto operator = (const AudioEffectChain&)     -> AudioEffectChain& = delete;
        auto operator = (AudioEffectChain&&) noexcept -> AudioEffectChain& = delete;
        virtual ~AudioEffectChain() noexcept = default;


    public:
        [[nodiscard]] auto GetBin() const noexcept -> GstElement* override
        {
            return m_pBin_;
        }
        [[nodiscard]] auto GetSinkPad() const noexcept -> GstPad* override
        {
            return gst_element_get_static_pad(m_pBin_, "sink");
        }
        [[nodiscard]] auto GetSrcPad() const noexcept -> GstPad* override
        {
            return gst_element_get_static_pad(m_pBin_, "src");
        }
        [[nodiscard]] auto Count() const noexcept -> std::size_t override
        {
            return m_effects_.size();
        }

        virtual void Add(std::shared_ptr<IAudioEffect> pEffect) noexcept override final
        {
            if (pEffect == nullptr)
            {
                g_printerr(__func__);
                g_printerr(": null effect, ignoring.\n");

                return;
            }

            if (m_pBin_ == nullptr)
            {
                g_printerr(__func__);
                g_printerr(": chain bin does not exist.\n");

                return;
            }

            auto* const pEffectBin = pEffect->GetBin();

            if (gst_bin_add(GST_BIN(m_pBin_), pEffectBin) == FALSE)
            {
                g_printerr(__func__);
                g_printerr(": could not add effect bin '%s' to chain.\n", gst_element_get_name(pEffectBin));

                return;
            }

            if (not m_effects_.empty())
            {
                const auto prevSrc  = UniqueGstPtr<GstPad>{ m_effects_.back()->GetSrcPad() };
                const auto currSink = UniqueGstPtr<GstPad>{ pEffect->GetSinkPad() };

                if (const auto& ret = gst_pad_link(prevSrc.get(), currSink.get()); GST_PAD_LINK_FAILED(ret))
                {
                    g_printerr(__func__);
                    g_printerr(": failed to link effect bins in chain.\n");

                    gst_bin_remove(GST_BIN(m_pBin_), pEffectBin);

                    return;
                }
            }

            m_effects_.push_back(std::move(pEffect));

            RewireGhostPads_();

            g_print("Effect '%s' added to chain (count: %zu)\n", gst_element_get_name(pEffectBin), m_effects_.size());
        }


    protected:


    private:
        void RewireGhostPads_() const noexcept
        {
            if (m_effects_.empty() or m_pBin_ == nullptr)
            {
                return;
            }

            if (auto* const existing_sink = gst_element_get_static_pad(m_pBin_, "sink"); existing_sink not_eq nullptr)
            {
                gst_element_remove_pad(m_pBin_, existing_sink);
                gst_object_unref(existing_sink);
            }

            if (auto* const existing_src = gst_element_get_static_pad(m_pBin_, "src"); existing_src not_eq nullptr)
            {
                gst_element_remove_pad(m_pBin_, existing_src);
                gst_object_unref(existing_src);
            }

            {
                const auto innerSink = UniqueGstPtr<GstPad>{ m_effects_.front()->GetSinkPad() };
                auto* const ghostSink = gst_ghost_pad_new("sink", innerSink.get());
                gst_element_add_pad(m_pBin_, ghostSink);
            }

            {
                const auto innerSrc = UniqueGstPtr<GstPad>{ m_effects_.back()->GetSrcPad() };
                auto* const ghostSrc = gst_ghost_pad_new("src", innerSrc.get());
                gst_element_add_pad(m_pBin_, ghostSrc);
            }
        }


    private:
        GstElement*                                  m_pBin_{};
        std::vector<std::shared_ptr<IAudioEffect>>   m_effects_{};
    };
}

#endif

// module : private;
