module;

#include <FatWin32.hpp>

#include <mfapi.h>

module FatPound.Win32.WMF.Manager;

namespace fatpound::win32::wmf
{
	Manager::Manager()
	{
		const auto hr = ::MFStartup(MF_VERSION);
			
		if (FAILED(hr))
		{
			throw std::runtime_error("Failed to initialize Media Foundation.");
		}
	}
	Manager::~Manager() noexcept
	{
		::MFShutdown();
	}
}