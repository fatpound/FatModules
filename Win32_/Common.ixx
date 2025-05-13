module;

#ifdef __INTELLISENSE__
    #if FAT_BUILDING_WITH_MSVC
    
    #ifndef FATPOUND_FULL_WIN_TARGETED
        #define FATPOUND_FULL_WIN_TARGETED
    #endif
    
    #include <FatWin32_Settings.hpp>
    #undef FATPOUND_FULL_WIN_TARGETED
    #include <Windows.h>
    // #include <ntdef.h>  // for UNICODE_STRING
    // #include <winDNS.h> // for QWORD
    
    #endif
#endif

export module FatPound.Win32.Common;

#if FAT_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <Windows.h>;
#endif

import std;

export namespace fatpound::win32
{
#ifdef UNICODE
    using CREATESTRUCT_t = ::CREATESTRUCTW;
    using STR_t          = ::LPCWSTR;
#else
    using CREATESTRUCT_t = ::CREATESTRUCTA;
    using STR_t          = ::LPCSTR;
#endif

    using ::ATOM;
    using ::BOOL;
    using ::BOOLEAN;
    using ::BYTE;
    using ::CCHAR;
    using ::CHAR;
    using ::COLORREF;
    using ::DWORD;
    using ::DWORDLONG;
    using ::DWORD_PTR;
    using ::DWORD32;
    using ::DWORD64;
    using ::FLOAT;
    using ::HACCEL;
    using ::HALF_PTR;
    using ::HANDLE;
    using ::HBITMAP;
    using ::HBRUSH;
    using ::HCOLORSPACE;
    using ::HCONV;
    using ::HCONVLIST;
    using ::HCURSOR;
    using ::HDC;
    using ::HDDEDATA;
    using ::HDESK;
    using ::HDROP;
    using ::HDWP;
    using ::HENHMETAFILE;
    using ::HFILE;
    using ::HFONT;
    using ::HGDIOBJ;
    using ::HGLOBAL;
    using ::HHOOK;
    using ::HICON;
    using ::HINSTANCE;
    using ::HKEY;
    using ::HKL;
    using ::HLOCAL;
    using ::HMENU;
    using ::HMETAFILE;
    using ::HMODULE;
    using ::HMONITOR;
    using ::HPALETTE;
    using ::HPEN;
    using ::HRESULT;
    using ::HRGN;
    using ::HRSRC;
    using ::HSZ;
    using ::HWINSTA;
    using ::HWND;
    using ::INT;
    using ::INT_PTR;
    using ::INT8;
    using ::INT16;
    using ::INT32;
    using ::INT64;
    using ::LANGID;
    using ::LCID;
    using ::LCTYPE;
    using ::LGRPID;
    using ::LONG;
    using ::LONGLONG;
    using ::LONG_PTR;
    using ::LONG32;
    using ::LONG64;
    using ::LPARAM;
    using ::LPBOOL;
    using ::LPBYTE;
    using ::LPCOLORREF;
    using ::LPCSTR;
    using ::LPCTSTR;
    using ::LPCVOID;
    using ::LPCWSTR;
    using ::LPDWORD;
    using ::LPHANDLE;
    using ::LPINT;
    using ::LPLONG;
    using ::LPSTR;
    using ::LPTSTR;
    using ::LPVOID;
    using ::LPWORD;
    using ::LPWSTR;
    using ::LRESULT;
    using ::PBOOL;
    using ::PBOOLEAN;
    using ::PBYTE;
    using ::PCHAR;
    using ::PCSTR;
    using ::PCTSTR;
    using ::PCWSTR;
    using ::PDWORD;
    using ::PDWORDLONG;
    using ::PDWORD_PTR;
    using ::PDWORD32;
    using ::PDWORD64;
    using ::PFLOAT;
    using ::PHALF_PTR;
    using ::PHANDLE;
    using ::PHKEY;
    using ::PINT;
    using ::PINT_PTR;
    using ::PINT8;
    using ::PINT16;
    using ::PINT32;
    using ::PINT64;
    using ::PLCID;
    using ::PLONG;
    using ::PLONGLONG;
    using ::PLONG_PTR;
    using ::PLONG32;
    using ::PLONG64;
    using ::PSHORT;
    using ::PSIZE_T;
    using ::PSSIZE_T;
    using ::PSTR;
    using ::PTBYTE;
    using ::PTCHAR;
    using ::PTSTR;
    using ::PUCHAR;
    using ::PUHALF_PTR;
    using ::PUINT;
    using ::PUINT_PTR;
    using ::PUINT8;
    using ::PUINT16;
    using ::PUINT32;
    using ::PUINT64;
    using ::PULONG;
    using ::PULONGLONG;
    using ::PULONG_PTR;
    using ::PULONG32;
    using ::PULONG64;
    using ::PUSHORT;
    using ::PVOID;
    using ::PWCHAR;
    using ::PWORD;
    using ::PWSTR;
//  using ::QWORD;
    using ::SC_HANDLE;
    using ::SC_LOCK;
    using ::SERVICE_STATUS_HANDLE;
    using ::SHORT;
    using ::SIZE_T;
    using ::SSIZE_T;
    using ::TBYTE;
    using ::TCHAR;
    using ::UCHAR;
    using ::UHALF_PTR;
    using ::UINT;
    using ::UINT_PTR;
    using ::UINT8;
    using ::UINT16;
    using ::UINT32;
    using ::UINT64;
    using ::ULONG;
    using ::ULONGLONG;
    using ::ULONG_PTR;
    using ::ULONG32;
    using ::ULONG64;
//  using ::UNICODE_STRING;
    using ::USHORT;
    using ::USN;
    using ::WCHAR;
    using ::WORD;
    using ::WPARAM;
    
    using ::WNDCLASSEX;

    auto ModuleHandleOf(const STR_t& cstr = nullptr) -> HINSTANCE
    {
        if (const auto& hInstance{ ::GetModuleHandle(cstr) }; hInstance not_eq nullptr)
        {
            return hInstance;
        }

        throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
    }
}

#endif

module : private;
