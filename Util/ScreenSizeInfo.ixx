module;

export module FatPound.Util.ScreenSizeInfo;

export namespace fatpound::util
{
    struct alignas(8) ScreenSizeInfo final
    {
        unsigned int m_width{};
        unsigned int m_height{};
    };
}

module : private;