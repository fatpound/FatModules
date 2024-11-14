module;

#define FATPOUND_FULL_WIN_TARGETED

#include <FatWin32.hpp>

#include <gdiplus.h>

#pragma comment(lib, "gdiplus")

module FatPound.Win32.GDI_Plus.Manager;

namespace fatpound::win32::gdi_plus
{
	Manager::Manager() noexcept
	{
		if (s_ref_count_ == 0)
		{
			::Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			::Gdiplus::GdiplusStartup(&s_gdiPlus_token_, &gdiplusStartupInput, nullptr);
		}

		++s_ref_count_;
	}
	Manager::~Manager() noexcept
	{
		--s_ref_count_;

		if (s_ref_count_ == 0)
		{
			::Gdiplus::GdiplusShutdown(s_gdiPlus_token_);
		}
	}
}