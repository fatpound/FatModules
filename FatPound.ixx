module;

export module FatPound;

export import FatPound.Automata;
export import FatPound.Bitwise;
export import FatPound.Concurrency;
export import FatPound.DSA;
export import FatPound.File;
export import FatPound.IO;
export import FatPound.Math;
export import FatPound.Memory;
export import FatPound.Random;
export import FatPound.Util;

#if FAT_BUILDING_WITH_MSVC
export import FatPound.Win32;
#endif

module : private;
