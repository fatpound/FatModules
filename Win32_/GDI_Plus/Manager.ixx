module;

#include <FatWin32.hpp>

export module FatPound.Win32.GDI_Plus.Manager;

export namespace fatpound::win32::gdi_plus
{
	class Manager final
	{
	public:
		Manager() noexcept;
		Manager(const Manager& src) = delete;
		Manager(Manager&& src) = delete;

		auto operator = (const Manager& src) -> Manager& = delete;
		auto operator = (Manager&& src)      -> Manager& = delete;
		~Manager() noexcept;


	protected:


	private:
		inline static ::ULONG_PTR s_gdiPlus_token_{};

		inline static int s_ref_count_{};
	};
}