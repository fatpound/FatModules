module;

export module FatPound.Traits;

export import FatPound.Traits.Bitwise;
export import FatPound.Traits.Callable;

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
