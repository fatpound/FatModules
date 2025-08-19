module;

export module FatPound.Win32.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

export import FatPound.Win32.Core;
import std;

export namespace fatpound::win32
{
    auto ModuleHandleOfA(const LPCSTR  cstr = nullptr) -> HINSTANCE
    {
        if (const auto& hInstance{ GetModuleHandleA(cstr) }; hInstance not_eq nullptr)
        {
            return hInstance;
        }

        throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
    }
    auto ModuleHandleOfW(const LPCWSTR cstr = nullptr) -> HINSTANCE
    {
        if (const auto& hInstance{ GetModuleHandleW(cstr) }; hInstance not_eq nullptr)
        {
            return hInstance;
        }

        throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
    }



    /// @brief Retrieves a module handle for the specified module name, or throws an exception if the handle cannot be obtained
    /// 
    /// @param cstr: A pointer to a null-terminated string specifying the module name. If nullptr, returns a handle to the file used to create the calling process
    /// 
    /// @return HINSTANCE if successful
    /// 
    auto ModuleHandleOf(const std::conditional_t<UNICODE, LPCWSTR, LPCSTR>& cstr = nullptr) -> HINSTANCE
    {
#ifdef UNICODE
        return ModuleHandleOfW(cstr);
#else
        return ModuleHandleOfA(cstr);
#endif
    }
}

#endif

// module : private;
