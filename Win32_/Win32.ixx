module;

export module FatPound.Win32;

#ifdef FATLIB_BUILDING_WITH_MSVC

export import FatPound.Win32.COM;
export import FatPound.Win32.D2D;
export import FatPound.Win32.D3D11;
export import FatPound.Win32.DXGI;
export import FatPound.Win32.GDI_Plus;
export import FatPound.Win32.MF;
export import FatPound.Win32.XAudio2;

export import FatPound.Win32.Core;
export import FatPound.Win32.Common;
export import FatPound.Win32.IWindow;
export import FatPound.Win32.WindowEx;

#endif

// module : private;
