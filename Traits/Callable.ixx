module;

#include <FatDefines.hpp>

export module FatPound.Traits.Callable;

import std;

export namespace fatpound::traits
{
    template <typename T>
    struct FAT_EBCO FunctionInfo;
    
    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(Args...)>
    {
        using Return_t      = R;
        using Callable_t    = R(Args...);
        using CallablePtr_t = R(*)(Args...);
        using TupleOfArgs_t = std::tuple<Args...>;

        template <std::size_t N>
        using Nth_Argument_t = std::tuple_element<N, TupleOfArgs_t>::type;

        static constexpr auto arity = sizeof...(Args);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(*)(Args...)> : virtual FunctionInfo<R(Args...)>
    {
        
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using Class_t = std::conditional_t<std::is_class_v<C>, C, void>;
        using Union_t = std::conditional_t<std::is_union_v<C>, C, void>;

        using CallablePtr_t                   = R(C::*)(Args...);
        using CallablePtr_t_no_cvrn           = R(C::*)(Args...); // removing all cvr-n but pointer cv qualifiers
        using CallablePtr_t_no_cvrn_no_ptr_cv = R(C::*)(Args...); // removing all cvr-n

        static constexpr bool is_const_qualified{};
        static constexpr bool is_volatile_qualified{};
        static constexpr bool is_lvalue_reference_qualified{};
        static constexpr bool is_rvalue_reference_qualified{};
        static constexpr bool is_not_reference_qualified{ true };
        static constexpr bool is_noexcept_specified{};
    };

    /////////////////////////////////////////////////////////////////////////////
    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) const;

        static constexpr bool is_const_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) volatile;

        static constexpr bool is_volatile_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) &> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) &;

        static constexpr bool is_lvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) &&> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) &&;

        static constexpr bool is_rvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) noexcept> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t = R(C::*)(Args...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };
    /////////////////////////////////////////////////////////////////////////////

#define MEM_FUNCPTR_TYPE(PQUAL) R(C::* PQUAL)(Args...)

#define V_INHERIT(PQUAL, FQS) virtual FunctionInfo< MEM_FUNCPTR_TYPE(PQUAL) FQS >

#define FAT_FUNC_INFO_GENERATOR1(PQUAL, ...)                         \
template <typename C, typename R, typename... Args>                  \
struct FAT_EBCO FunctionInfo< MEM_FUNCPTR_TYPE(PQUAL) __VA_ARGS__ >

#define FAT_FUNC_INFO_GENERATOR2(PQUAL, ...)                         \
    :                                                                \
    __VA_ARGS__                                                      
                                                                     
#define FAT_FUNC_INFO_GENERATOR3(PQUAL, ...)                         \
{                                                                    \
    using CallablePtr_t = MEM_FUNCPTR_TYPE(PQUAL) __VA_ARGS__;       \
};

#define FAT_FUNC_INFO_GENERATOR(PQUAL)                                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile)                                                                                        \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile))                                                   \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile)                                                                                        \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const &)                                                                                               \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &))                                                          \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const &)                                                                                               \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const &&)                                                                                              \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &&))                                                         \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const &&)                                                                                              \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile &)                                                                                            \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &))                                                       \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile &)                                                                                            \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile &&)                                                                                           \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&))                                                      \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile &&)                                                                                           \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile &)                                                                                      \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &))                              \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile &)                                                                                      \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile &&)                                                                                     \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&))                             \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile &&)                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const noexcept)                                                                                        \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, noexcept))                                                   \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const noexcept)                                                                                        \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile noexcept)                                                                                     \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, noexcept))                                                \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile noexcept)                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile noexcept)                                                                               \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, noexcept))                       \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile noexcept)                                                                               \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const & noexcept)                                                                                      \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                              \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const & noexcept)                                                                                      \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const && noexcept)                                                                                     \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                             \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const && noexcept)                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile & noexcept)                                                                                   \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                           \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile & noexcept)                                                                                   \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile && noexcept)                                                                                  \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                          \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile && noexcept)                                                                                  \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile & noexcept)                                                                             \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))  \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile & noexcept)                                                                             \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile && noexcept)                                                                            \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept)) \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile && noexcept)

#pragma warning (push)
#pragma warning (disable : 4003)
    FAT_FUNC_INFO_GENERATOR()
#pragma warning (pop)

    /// with cvr-qualified (member function) pointers

#define FAT_FUNC_INFO_GENERATOR4(PQUAL, FQS)                                                              \
    template <typename C, typename R, typename... Args>                                                   \
    struct FAT_EBCO FunctionInfo<R(C::* PQUAL)(Args...) FQS> : virtual FunctionInfo<R(C::*)(Args...) FQS> \
    {                                                                                                     \
        using CallablePtr_t         = R(C::* PQUAL)(Args...) FQS;                                         \
        using CallablePtr_t_no_cvrn = R(C::* PQUAL)(Args...);                                             \
    };

#define FAT_FUNC_INFO_GENERATOR_BASE(PQUAL)  \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, const)    \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, volatile) \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, &)        \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, &&)       \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, noexcept)

    FAT_FUNC_INFO_GENERATOR_BASE(const)
    FAT_FUNC_INFO_GENERATOR(const)

    FAT_FUNC_INFO_GENERATOR_BASE(volatile)
    FAT_FUNC_INFO_GENERATOR(volatile)

    FAT_FUNC_INFO_GENERATOR_BASE(const volatile)
    FAT_FUNC_INFO_GENERATOR(const volatile)

#undef FAT_FUNC_INFO_GENERATOR4
#undef FAT_FUNC_INFO_GENERATOR_CVPTR
#undef FAT_FUNC_INFO_GENERATOR3
#undef FAT_FUNC_INFO_GENERATOR2
#undef FAT_FUNC_INFO_GENERATOR1
#undef FAT_FUNC_INFO_GENERATOR
#undef V_INHERIT
#undef MEM_FUNCPTR_TYPE

    template <typename T>
    concept Callable = std::invocable<T>;

    template <typename T>
    concept Functor = Callable<T> and std::is_object_v<T> and (std::is_class_v<T> or std::is_union_v<T>);
}

module : private;
