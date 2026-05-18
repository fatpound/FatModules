module;

export module FatPound.Win32.HrException;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <Win32_/WinAPI.hxx>;
import std;

export namespace fatpound::win32
{
    class HrException : public std::runtime_error
    {
    public:
        HrException(const HRESULT& hr, const std::string& note, const std::source_location& loc = std::source_location::current())
            :
            std::runtime_error("WinAPI Exception!"),
            m_hr_(hr)
        {
            m_message_ = std::format<>(
                "WinAPI Exception!\n"
                "Error Code: {:#010x}\n"
                "Description: {}\n"
                "Note: {}\n"
                "File: {}\n"
                "Line: {}\n"
                "Function: {}",
                static_cast<unsigned int>(m_hr_),
                std::system_category().message(hr),
                note,
                loc.file_name(),
                loc.line(),
                loc.function_name()
            );
        }


    public:
        [[nodiscard]]
        virtual auto what() const noexcept -> const char* override
        {
            return m_message_.c_str();
        }


    public:
        [[nodiscard]]
        auto GetErrorCode() const noexcept -> HRESULT
        {
            return m_hr_;
        }


    protected:
        std::string   m_message_;
        HRESULT       m_hr_;

        
    private:
    };
}

#endif

// module : private;
