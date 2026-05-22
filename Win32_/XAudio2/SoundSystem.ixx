module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <xaudio2.h>
        #include <wrl.h>
    #endif

    #include <_macros/Win.hxx>
    #include <cassert>
#endif

export module FatPound.Win32.XAudio2.SoundSystem;

#ifdef FATLIB_BUILDING_WITH_MSVC

export import FatPound.Win32.HrException;
import FatPound.Win32.MF.SourceReader;

#ifndef __INTELLISENSE__
    import <Win32_/WinAPI.hxx>;
    import <wrl.h>;
#endif

import std;

export namespace fatpound::win32::xaudio2
{
    class SoundSystem final
    {
        class Channel_;

    public:
        class Sound final
        {
            friend Channel_;

        public:
            explicit Sound(const std::wstring& filePath, const WAVEFORMATEX& format)
                :
                m_format_(format)
            {
                mf::SourceReader{ filePath }.ReadAudioPCM(m_pcm_data_, m_format_);
            }

            explicit Sound()                 = delete;
            explicit Sound(const Sound&)     = delete;
            explicit Sound(Sound&&) noexcept = delete;

            auto operator = (const Sound&)     -> Sound& = delete;
            auto operator = (Sound&&) noexcept -> Sound& = delete;
            ~Sound()
            {
                {
                    const std::lock_guard lg{ m_mtx_ };
    
                    for (auto& pChan : m_active_channel_ptrs_)
                    {
                        pChan->Stop();
                    }
                }

                bool allChannelsAreDeactivated{};   

                do
                {
                    const std::lock_guard lg{ m_mtx_ };

                    allChannelsAreDeactivated = (m_active_channel_ptrs_.size() == 0);
                }
                while (not allChannelsAreDeactivated);
            }


        public:
            auto GetData   () const noexcept -> std::span<const std::byte>
            {
                return m_pcm_data_;
            }
            auto GetFormat () const noexcept -> WAVEFORMATEX
            {
                return m_format_;
            }

            void Play(SoundSystem& sys, const float volume = 1.0F, const float freqMod = 1.0F)
            {
                sys.PlaySound(*this, volume, freqMod);
            }


        protected:


        private:
            void AddChannel_    (Channel_& channel)
            {
                const std::lock_guard lg{ m_mtx_ };

                m_active_channel_ptrs_.push_back(&channel);
            }
            void RemoveChannel_ (Channel_& channel)
            {
                const std::lock_guard lg{ m_mtx_ };

                m_active_channel_ptrs_.erase(std::ranges::find(m_active_channel_ptrs_, &channel));
            }


        private:
            std::vector<std::byte>   m_pcm_data_{};
            WAVEFORMATEX             m_format_{};
            std::vector<Channel_*>   m_active_channel_ptrs_;

            std::mutex               m_mtx_;
        };


    public:
        explicit SoundSystem(const WAVEFORMATEX& masterFormat = S_DefaultFormat_())
            :
            m_master_voice_format_{ masterFormat },
#ifdef _MSC_VER
    #pragma region (C4355 'this' warning)
    #pragma warning (push)
    #pragma warning (disable : 4355)
#endif
            m_voice_callback_(*this)
#ifdef _MSC_VER
    #pragma warning (pop)
    #pragma endregion
#endif
        {
            FAT_THROW_HRX_IF_FAILED(XAudio2Create(&m_pXAudio2_, 0U, XAUDIO2_USE_DEFAULT_PROCESSOR), "Failed to create XAudio2 Engine!");
            FAT_THROW_HRX_IF_FAILED(m_pXAudio2_->CreateMasteringVoice(&m_pMasterVoice_),            "Failed to create XAudio2 Mastering Voice!");

            for (std::size_t i{}; i < scx_channel_count_; ++i)
            {
                m_idle_channel_ptrs_.push_back(std::make_unique<Channel_>(*this));
            }
        }
        explicit SoundSystem(const SoundSystem&)     = delete;
        explicit SoundSystem(SoundSystem&&) noexcept = delete;

        auto operator = (const SoundSystem&)     -> SoundSystem& = delete;
        auto operator = (SoundSystem&&) noexcept -> SoundSystem& = delete;
        ~SoundSystem() noexcept
        {
            if (m_pMasterVoice_ not_eq nullptr)
            {
                m_pMasterVoice_->DestroyVoice();
                m_pMasterVoice_ = nullptr;
            }
        }


    public:
        auto GetMasterFormat() const noexcept -> WAVEFORMATEX
        {
            return m_master_voice_format_;
        }
        
        void PlaySound(Sound& sound, const float volume, const float freqMod)
        {
            const std::lock_guard lg{ m_mtx_ };

            if (m_idle_channel_ptrs_.size() > 0)
            {
                m_active_channel_ptrs_.push_back(std::move(m_idle_channel_ptrs_.back()));
                m_idle_channel_ptrs_.pop_back();
                m_active_channel_ptrs_.back()->Play(sound, volume, freqMod);
            }
        }
        void SetMasterVolume(const float volume) noexcept
        {
            if (m_pMasterVoice_ not_eq nullptr)
            {
                m_pMasterVoice_->SetVolume(volume);
            }
        }


    protected:


    private:
        class VoiceCallback_ final : public IXAudio2VoiceCallback
        {
        public:
            explicit VoiceCallback_(SoundSystem& sys) noexcept
                :
                m_sys_(sys)
            {

            }

            explicit VoiceCallback_()                          = delete;
            explicit VoiceCallback_(const VoiceCallback_&)     = delete;
            explicit VoiceCallback_(VoiceCallback_&&) noexcept = delete;

            auto operator = (const VoiceCallback_&)     -> VoiceCallback_& = delete;
            auto operator = (VoiceCallback_&&) noexcept -> VoiceCallback_& = delete;
            virtual ~VoiceCallback_() noexcept                             = default;

        public:
            virtual void STDMETHODCALLTYPE OnVoiceProcessingPassStart ([[maybe_unused]] UINT32 BytesRequired)                                       noexcept override final
            {

            }
            virtual void STDMETHODCALLTYPE OnVoiceProcessingPassEnd   ()                                                                            noexcept override final
            {

            }
            virtual void STDMETHODCALLTYPE OnStreamEnd                ()                                                                            noexcept override final
            {

            }
            virtual void STDMETHODCALLTYPE OnBufferStart              ([[maybe_unused]] void*       pBufferContext)                                 noexcept override final
            {

            }
            virtual void STDMETHODCALLTYPE OnBufferEnd                (                 void* const pBufferContext)                                          override final
            {
                auto& channel = *reinterpret_cast<Channel_*>(pBufferContext);

                channel.Stop();
                channel.RemoveFromSoundList();

                m_sys_.DeactivateChannel_(channel);
            }
            virtual void STDMETHODCALLTYPE OnLoopEnd                  ([[maybe_unused]] void*       pBufferContext)                                 noexcept override final
            {

            }
            virtual void STDMETHODCALLTYPE OnVoiceError               ([[maybe_unused]] void*       pBufferContext, [[maybe_unused]] HRESULT Error) noexcept override final
            {

            }

        protected:

        private:
            SoundSystem& m_sys_;
        };
        class Channel_       final
        {
            friend VoiceCallback_;

        public:
            explicit Channel_(SoundSystem& sys)
            {
                ZeroMemory(&m_xabuf_, sizeof(m_xabuf_));

                m_xabuf_.pContext = this;
                
                const auto& format = sys.GetMasterFormat();
                
                FAT_THROW_HRX_IF_FAILED(
                    sys.m_pXAudio2_->CreateSourceVoice(&m_pSourceVoice_, &format, 0U, XAUDIO2_DEFAULT_FREQ_RATIO, &sys.m_voice_callback_),
                    "Failed to create XAudio2 Source Voice!"
                );
            }

            explicit Channel_()                    = delete;
            explicit Channel_(const Channel_&)     = default;
            explicit Channel_(Channel_&&) noexcept = default;

            auto operator = (const Channel_&)     -> Channel_& = default;
            auto operator = (Channel_&&) noexcept -> Channel_& = default;
            ~Channel_() noexcept
            {
                assert((m_pSound_ == nullptr));

                if (m_pSourceVoice_ not_eq nullptr)
                {
                    m_pSourceVoice_->DestroyVoice();
                    m_pSourceVoice_ = nullptr;
                }
            }

        public:
            void Play(Sound& sound, const float volume, const float freqMod)
            {
                assert(((m_pSourceVoice_ not_eq nullptr) and (m_pSound_ == nullptr)));

                sound.AddChannel_(*this);

                m_pSound_ = &sound;
                m_xabuf_.pAudioData = reinterpret_cast<const BYTE*>(sound.GetData().data());
                m_xabuf_.AudioBytes = static_cast<UINT32>(sound.GetData().size());

                m_pSourceVoice_->SubmitSourceBuffer(&m_xabuf_);
                m_pSourceVoice_->SetFrequencyRatio(freqMod);
                m_pSourceVoice_->SetVolume(volume);
                m_pSourceVoice_->Start();
            }
            void Stop() noexcept
            {
                assert((m_pSourceVoice_ not_eq nullptr)); // and (m_pSound_ not_eq nullptr)

                m_pSourceVoice_->Stop();
                m_pSourceVoice_->FlushSourceBuffers();
            }

        protected:

        private:
            void RemoveFromSoundList()
            {
                m_pSound_->RemoveChannel_(*this);
                m_pSound_ = nullptr;
            }

        private:
            XAUDIO2_BUFFER         m_xabuf_{};
            IXAudio2SourceVoice*   m_pSourceVoice_{};
            Sound*                 m_pSound_{};
        };


    private:
        static constexpr auto S_DefaultFormat_() noexcept -> WAVEFORMATEX
        {
            return
            {
                .wFormatTag      = WAVE_FORMAT_PCM,
                .nChannels       = 2,
                .nSamplesPerSec  = 44100,
                .nAvgBytesPerSec = 44100 * 2 * 24 / 8,
                .nBlockAlign     = static_cast<WORD>(2 * 24 / 8),
                .wBitsPerSample  = 24,
                .cbSize          = 0U
            };
        }


    private:
        void DeactivateChannel_(Channel_& channel)
        {
            const std::lock_guard lg{ m_mtx_ };

            auto iter = std::ranges::find_if(
                m_active_channel_ptrs_,
                [&channel](const auto& pChan)
                {
                    return pChan.get() == &channel;
                }
            );

            if (iter not_eq m_active_channel_ptrs_.end())
            {
                m_idle_channel_ptrs_.push_back(std::move<>(*iter));
                m_active_channel_ptrs_.erase(iter);
            }
        }


    private:
        static constexpr auto                    scx_channel_count_{ 64UZ };

        Microsoft::WRL::ComPtr<IXAudio2>         m_pXAudio2_;
        IXAudio2MasteringVoice*                  m_pMasterVoice_{};
        WAVEFORMATEX                             m_master_voice_format_;

        std::vector<std::unique_ptr<Channel_>>   m_idle_channel_ptrs_;
        std::vector<std::unique_ptr<Channel_>>   m_active_channel_ptrs_;

        std::mutex                               m_mtx_;

        VoiceCallback_                           m_voice_callback_;
    };

    using Sound = SoundSystem::Sound;
}

#endif

// module : private;
