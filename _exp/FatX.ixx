module;

export module FatX;

#ifdef FATX_WITH_GSTREAMER
export import FatX.GStreamer;
#endif

#ifdef FATX_WITH_OPENCV
export import FatX.OpenCV;
#endif

#ifdef FATX_WITH_ZEROMQ
export import FatX.ZeroMQ;
#endif

// module : private;
