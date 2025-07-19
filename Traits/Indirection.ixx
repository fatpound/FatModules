module;

#include <_macros/Compiler.hxx>

export module FatPound.Traits.Indirection;

import std;

export namespace fatpound::traits
{
    template <typename T>
    concept MemberPointer = std::is_member_pointer_v<T>;

    template <typename T>
    concept MemberFunctionPointer = std::is_member_function_pointer_v<T>;

    template <typename T>
    concept MemberObjectPointer = MemberPointer<T> and not MemberFunctionPointer<T>;

    template <typename T>
    concept NonMemberPointer = std::is_pointer_v<T>; // not MemberPointer<T>

    template <typename T>
    concept Pointer = NonMemberPointer<T> or MemberPointer<T> or MemberFunctionPointer<T> or MemberObjectPointer<T>;

    template <typename T>
    concept LValueReference = std::is_lvalue_reference_v<T>;

    template <typename T>
    concept RValueReference = std::is_rvalue_reference_v<T>;

    template <typename T>
    concept Reference = std::is_reference_v<T>; // LValueReference<T> or RValueReference<T>
}

// module : private;

#ifdef IN_DEBUG

namespace fatpound::traits
{
    struct FATLIB_EBCO _unused_ final
    {
        explicit _unused_()                    = delete;
        explicit _unused_(const _unused_&)     = delete;
        explicit _unused_(_unused_&&) noexcept = delete;

        auto operator = (const _unused_&)     -> _unused_& = delete;
        auto operator = (_unused_&&) noexcept -> _unused_& = delete;
        ~_unused_() noexcept                               = delete;
        
        //********************//

        void foo();

        int val;

        static_assert(MemberFunctionPointer<decltype(&_unused_::foo)>);
        static_assert(  MemberObjectPointer<decltype(&_unused_::val)>);
        static_assert(        MemberPointer<decltype(&_unused_::foo)>);
        static_assert(        MemberPointer<decltype(&_unused_::val)>);
        static_assert(              Pointer<decltype(&_unused_::foo)>);
        static_assert(              Pointer<decltype(&_unused_::val)>);
        static_assert(not  NonMemberPointer<decltype(&_unused_::foo)>);
        static_assert(not  NonMemberPointer<decltype(&_unused_::val)>);
    };
}

#endif
