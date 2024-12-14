module;

export module FatPound.Win32.WMF.Manager;

import std;

export namespace fatpound::win32::wmf
{
    class Manager final
    {
    public:
        Manager();
        Manager(const Manager& src) = delete;
        Manager(Manager&& src) = delete;

        auto operator = (const Manager& src) -> Manager& = delete;
        auto operator = (Manager&& src)      -> Manager& = delete;
        ~Manager() noexcept;


    protected:


    private:
    };
}