module;

#include <FatWin32.hpp>

#include <combaseapi.h>

module FatPound.Win32.COM.Manager;

namespace fatpound::win32::com
{
	Manager::Manager(const DWORD initFlags)
	{
		const auto hr = ::CoInitializeEx(nullptr, initFlags);
			
		if (FAILED(hr))
		{
			throw std::runtime_error("Failed to initialize Media Foundation.");
		}
	}
	Manager::~Manager() noexcept
	{
		::CoUninitialize();
	}
}