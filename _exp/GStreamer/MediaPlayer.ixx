module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hxx"
#endif

export module FatX.GStreamer.MediaPlayer;

#ifdef FATX_WITH_GSTREAMER

import FatX.GStreamer.AudioPitchEffect;
import FatX.GStreamer.AudioEffectChain;
import FatX.GStreamer.Pipeline;

import std;

export namespace fatx::gstreamer
{
    class MediaPlayer
    {
    public:
        explicit MediaPlayer()
            :
            m_pPitchEffect_(std::make_shared<AudioPitchEffect>()),
            m_pipeline_(MakeEffectChain_())
        {
            g_print("Starting MediaPlayer...\n");
        }
        explicit MediaPlayer(const MediaPlayer&)     = delete;
        explicit MediaPlayer(MediaPlayer&&) noexcept = delete;

        auto operator = (const MediaPlayer&)     -> MediaPlayer& = delete;
        auto operator = (MediaPlayer&&) noexcept -> MediaPlayer& = delete;
        ~MediaPlayer() noexcept
        {
            g_print("Shutting down MediaPlayer...\n");
        }


    public:
        auto QueryPosition () const noexcept -> std::size_t
        {
            return m_pipeline_.QueryPosition();
        }
        auto QueryDuration () const noexcept -> std::size_t
        {
            return m_pipeline_.QueryDuration();
        }
        auto IsPlaying     () const noexcept -> bool
        {
            return m_pipeline_.IsPlaying();
        }

        void LoadAudio     (const std::string& uriPath) noexcept
        {
            m_pipeline_.LoadAudio(uriPath);
        }
        void Play          () noexcept
        {
            m_pipeline_.Play();
        }
        void Pause         () noexcept
        {
            m_pipeline_.Pause();
        }
        void Seek          (const std::size_t& pos) noexcept
        {
            m_pipeline_.Seek(pos);
        }
        void SetPitchValue (const double val) noexcept
        {
            if (m_pPitchEffect_.use_count() > 1L)
            {
                m_pPitchEffect_->SetPitchAsync(m_pipeline_, val);
            }
        }

        void SetStateChangedCallback (std::function<void(bool)> callback)
        {
            m_pipeline_.SetStateChangedCallback(callback);
        }
        void SetMediaChangedCallback (std::function<void()>     callback)
        {
            m_pipeline_.SetMediaChangedCallback(callback);
        }


    protected:


    private:
        auto MakeEffectChain_() const noexcept -> std::unique_ptr<IEffectChain>
        {
            auto chain = std::make_unique<AudioEffectChain>();
            chain->Add(m_pPitchEffect_);

            return chain;
        }


    private:
        std::shared_ptr<AudioPitchEffect>   m_pPitchEffect_;
        Pipeline                            m_pipeline_;
    };
}

#endif

// module : private;
