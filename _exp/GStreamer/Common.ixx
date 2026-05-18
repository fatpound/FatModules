module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hxx"
#endif

export module FatX.GStreamer.Common;

#ifdef FATX_WITH_GSTREAMER

import std;

export namespace fatx::gstreamer
{
    template <typename T>
    using UniqueGstPtr = std::unique_ptr<T, decltype([](T* const ptr) noexcept -> void { gst_object_unref(ptr); })>;

    inline auto CreateBin(const std::string& name) noexcept -> GstElement*
    {
        auto* const ptr = gst_bin_new(name.c_str());

        if (ptr == nullptr)
        {
            g_printerr("Could NOT create GStreamer bin %s!", name.c_str());
        }

        return ptr;
    }

    inline auto CreatePlugin(const std::string& factoryName, const std::string& name) noexcept -> GstElement*
    {
        auto* const ptr = gst_element_factory_make(factoryName.c_str(), name.c_str());

        if (ptr == nullptr)
        {
            g_printerr("Could NOT create GStreamer plugin '%s' of type '%s'\n", factoryName.c_str(), name.c_str());
        }

        return ptr;
    }

    inline void LinkElements(GstElement* const src, GstElement* const dest) noexcept
    {
        g_print("Linking element %s => %s ... ", gst_element_get_name(src), gst_element_get_name(dest));

        if (gst_element_link(src, dest) == FALSE)
        {
            g_printerr("[FAILED]\n");
            return;
        }

        g_print("[DONE]\n");
    }

    inline void LinkPads(GstPad* const src, GstPad* const dest) noexcept
    {
        g_print("Linking pad %s => %s ... ", gst_pad_get_name(src), gst_pad_get_name(dest));

        if (GST_PAD_LINK_FAILED(gst_pad_link(src, dest)))
        {
            g_printerr("[FAILED]\n");
            return;
        }

        g_print("[DONE]\n");
    }

    inline void PrintErrorMsg(GstMessage* const msg) noexcept
    {
        GError* err{};
        gchar* debug_info{};

        gst_message_parse_error(msg, &err, &debug_info);
        g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
        g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
        g_clear_error(&err);
        g_free(debug_info);
    }

    class SmartGstPad final
    {
    public:
        SmartGstPad(GstElement* const owner, GstPad* const pad) noexcept
            :
            m_pOwner_(owner),
            m_pPad_(pad)
        {

        }

        SmartGstPad() noexcept          = default;
        SmartGstPad(const SmartGstPad&) = delete;
        SmartGstPad(SmartGstPad&& other) noexcept
            :
            m_pOwner_(other.m_pOwner_),
            m_pPad_(std::move(other.m_pPad_))
        {
            other.m_pOwner_ = nullptr;
        }

        auto operator = (const SmartGstPad&)           -> SmartGstPad& = delete;
        auto operator = (SmartGstPad&& other) noexcept -> SmartGstPad&
        {
            if (this not_eq &other)
            {
                Reset();

                m_pOwner_       = other.m_pOwner_;
                m_pPad_         = std::move(other.m_pPad_);
                other.m_pOwner_ = nullptr;
            }

            return *this;
        }
        ~SmartGstPad() noexcept
        {
            Reset();
        }


    public:
        [[nodiscard]] auto Get() const noexcept -> GstPad*
        {
            return m_pPad_.get();
        }

        [[nodiscard]] operator bool() const noexcept
        {
            return m_pPad_ not_eq nullptr;
        }

        void Reset() noexcept
        {
            if ((m_pOwner_ not_eq nullptr) and (m_pPad_ not_eq nullptr))
            {
                gst_element_release_request_pad(m_pOwner_, m_pPad_.get());
                m_pOwner_ = nullptr;
            }
        }


    protected:


    private:
        GstElement*           m_pOwner_{};
        UniqueGstPtr<GstPad>  m_pPad_{};
    };
}

#endif

// module : private;
