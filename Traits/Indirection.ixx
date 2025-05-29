module;

#include <FatMacros.hxx>

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

module : private;

#ifdef IN_DEBUG

namespace fatpound::traits
{
    class FAT_EBCO ___unused___ final
    {
        explicit ___unused___()                        = delete;
        explicit ___unused___(const ___unused___&)     = delete;
        explicit ___unused___(___unused___&&) noexcept = delete;

        auto operator = (const ___unused___&)     -> ___unused___& = delete;
        auto operator = (___unused___&&) noexcept -> ___unused___& = delete;
        ~___unused___() noexcept                                   = delete;
        
        //********************//

        void foo();

        int val;

        static_assert(MemberFunctionPointer<decltype(&___unused___::foo)>);
        static_assert(  MemberObjectPointer<decltype(&___unused___::val)>);
        static_assert(        MemberPointer<decltype(&___unused___::foo)>);
        static_assert(              Pointer<decltype(&___unused___::foo)>);
        static_assert(              Pointer<decltype(&___unused___::val)>);
        static_assert(not  NonMemberPointer<decltype(&___unused___::foo)>);
        static_assert(not  NonMemberPointer<decltype(&___unused___::val)>);
    };
}

#endif
