module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <mfapi.h>
        #include <mfidl.h>
        #include <mfreadwrite.h>
        #include <wrl.h>
    #endif

    #include <_macros/Win.hxx>
#endif

export module FatPound.Win32.MF.SourceReader;

#ifdef FATLIB_BUILDING_WITH_MSVC

import FatPound.Win32.HrException;

#ifndef __INTELLISENSE__
    import <Win32_/WinAPI.hxx>;
    import <wrl.h>;
#endif

import std;

export namespace fatpound::win32::mf
{
    class SourceReader final
    {
        enum class ReadingMode
        {
            Audio = MF_SOURCE_READER_FIRST_AUDIO_STREAM,
            Video = MF_SOURCE_READER_FIRST_VIDEO_STREAM
        };
        
    public:
        explicit SourceReader(const std::wstring& filePath)
        {
            const auto& hr = MFCreateSourceReaderFromURL(filePath.c_str(), nullptr, &m_pReader_); // Synchronous

            if (FAILED(hr))
            {
                throw HrException(hr, "Failed to create MF Source Reader for file!");
            }
        }

        explicit SourceReader()                        = delete;
        explicit SourceReader(const SourceReader&)     = delete;
        explicit SourceReader(SourceReader&&) noexcept = default;
        
        auto operator = (const SourceReader&)     -> SourceReader& = delete;
        auto operator = (SourceReader&&) noexcept -> SourceReader& = default;
        ~SourceReader() noexcept                                   = default;


    public:
        [[nodiscard]]
        auto GetWaveformatOfAudioFile() -> WAVEFORMATEX
        {
            WAVEFORMATEX* pWaveFormat{};

            {
                Microsoft::WRL::ComPtr<IMFMediaType> pUncompressedAudioType;

                FAT_THROW_HRX_IF_FAILED(m_pReader_->GetCurrentMediaType(static_cast<DWORD>(ReadingMode::Audio), &pUncompressedAudioType), "Failed to get uncompressed media type!");

                UINT32 cbFormat{};

                FAT_THROW_HRX_IF_FAILED(MFCreateWaveFormatExFromMFMediaType(pUncompressedAudioType.Get(), &pWaveFormat, &cbFormat),       "Failed to extract WAVEFORMATEX!");
            }

            std::unique_ptr<WAVEFORMATEX, decltype(&CoTaskMemFree)> formatGuard{ pWaveFormat, &CoTaskMemFree };

            return *pWaveFormat;
        }

        void ReadAudioPCM(std::vector<std::byte>& outPcmData, const std::optional<WAVEFORMATEX> targetFormat = std::nullopt) // assumes pcmData is empty
        {
            SelectStream_(ReadingMode::Audio);
            SetOutputFormatToPCM_(targetFormat);

            Microsoft::WRL::ComPtr<IMFSample>      pSample;
            Microsoft::WRL::ComPtr<IMFMediaBuffer> pBuffer;

            while (true)
            {
                DWORD dwFlags{};

                FAT_THROW_HRX_IF_FAILED(
                    m_pReader_->ReadSample(static_cast<DWORD>(ReadingMode::Audio), 0, nullptr, &dwFlags, nullptr, &pSample),
                    "Failed to read audio sample!"
                );

                if (dwFlags bitand MF_SOURCE_READERF_ENDOFSTREAM)
                {
                    break;
                }

                if (pSample == nullptr)
                {
                    continue;
                }

                FAT_THROW_HRX_IF_FAILED(pSample->ConvertToContiguousBuffer(&pBuffer), "Failed to convert sample to contiguous buffer!");

                struct MediaBufferLockGuard final
                {
                    IMFMediaBuffer* const m_pBuffer;
                    BYTE*                 m_pAudioData{};
                    DWORD                 m_cbBuffer{};

                    explicit MediaBufferLockGuard(IMFMediaBuffer* const buffer)
                        :
                        m_pBuffer(buffer)
                    {
                        FAT_THROW_HRX_IF_FAILED(m_pBuffer->Lock(&m_pAudioData, nullptr, &m_cbBuffer), "Failed to lock media buffer!");
                    }

                    explicit MediaBufferLockGuard()                                = delete;
                    explicit MediaBufferLockGuard(const MediaBufferLockGuard&)     = delete;
                    explicit MediaBufferLockGuard(MediaBufferLockGuard&&) noexcept = delete;

                    auto operator = (const MediaBufferLockGuard&)     -> MediaBufferLockGuard& = delete;
                    auto operator = (MediaBufferLockGuard&&) noexcept -> MediaBufferLockGuard& = delete;
                    ~MediaBufferLockGuard() noexcept
                    {
                        m_pBuffer->Unlock();
                    }
                };

                MediaBufferLockGuard lgbuf{ pBuffer.Get() };

                auto* const pByteData = reinterpret_cast<std::byte*>(lgbuf.m_pAudioData);
                outPcmData.insert(outPcmData.end(), pByteData, pByteData + lgbuf.m_cbBuffer);
            }

            if (outPcmData.empty())
            {
                throw std::runtime_error("Audio data is empty after reading!");
            }
        }


    protected:


    private:
        void SelectStream_(const ReadingMode mode)
        {
            m_pReader_->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_ALL_STREAMS), FALSE);
            m_pReader_->SetStreamSelection(static_cast<DWORD>(mode), TRUE);
        }
        void SetOutputFormatToPCM_(const std::optional<WAVEFORMATEX> targetFormat)
        {
            Microsoft::WRL::ComPtr<IMFMediaType> pMediaType;

            FAT_THROW_HRX_IF_FAILED(MFCreateMediaType(&pMediaType), "Failed to create target media type!");

            pMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
            pMediaType->SetGUID(MF_MT_SUBTYPE,    MFAudioFormat_PCM);

            if (targetFormat.has_value())
            {
                const auto& blockAlign  = static_cast<UINT32>((targetFormat->nChannels * targetFormat->wBitsPerSample) / 8);
                const auto& bytesPerSec = static_cast<UINT32>(blockAlign * targetFormat->nSamplesPerSec);

                pMediaType->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS,         targetFormat->nChannels);
                pMediaType->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND,   targetFormat->nSamplesPerSec);
                pMediaType->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE,      targetFormat->wBitsPerSample);
                pMediaType->SetUINT32(MF_MT_AUDIO_BLOCK_ALIGNMENT,      blockAlign);
                pMediaType->SetUINT32(MF_MT_AUDIO_AVG_BYTES_PER_SECOND, bytesPerSec);
            //  pMediaType->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT,    TRUE);
            }

            FAT_THROW_HRX_IF_FAILED(
                m_pReader_->SetCurrentMediaType(static_cast<DWORD>(ReadingMode::Audio), nullptr, pMediaType.Get()),
                "MF cannot resample to the requested target format!"
            );
        }


    private:
        Microsoft::WRL::ComPtr<IMFSourceReader> m_pReader_;
    };
}

#endif

// module : private;
