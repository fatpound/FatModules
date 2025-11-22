module;

#ifdef FATX_WITH_GSTREAMER
#include "FatGst.hpp"
#endif

export module FatX.GStreamer.Manager;

#ifdef FATX_WITH_GSTREAMER

export namespace fatx::gstreamer
{
    class Manager final
    {
    public:
        explicit Manager(int& argc, char**& argv) noexcept
        {
            gst_init(&argc, &argv);
        }
        explicit Manager(const Manager&)     = default;
        explicit Manager(Manager&&) noexcept = default;

        auto operator = (const Manager&)     -> Manager& = default;
        auto operator = (Manager&&) noexcept -> Manager& = default;
        ~Manager() noexcept
        {
            gst_deinit();
        }


    protected:


    private:
    };
}

#endif

// module : private;
