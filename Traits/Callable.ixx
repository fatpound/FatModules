module;

#include <FatMacros.hxx>

export module FatPound.Traits.Callable;

import FatPound.Traits.Formation;

import std;

export namespace fatpound::traits
{
    template <typename T>
    struct FAT_EBCO FunctionInfo;
    
    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(Args...)>
    {
        using Return_t       = R;
        using Callable_t     = R(Args...);
        using CallableDecl_t = R(Args...);
        using CallablePtr_t  = R(*)(Args...);
        using TupleOfArgs_t  = std::tuple<Args...>;

        template <std::size_t N>
        using Nth_Argument_t = std::tuple_element<N, TupleOfArgs_t>::type;

        static constexpr auto fixed_arity = sizeof...(Args);
        static constexpr bool is_variadic{};
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(Args..., ...)> : virtual FunctionInfo<R(Args...)>
    {
        using Callable_t     = R(Args..., ...);
        using CallableDecl_t = R(Args..., ...);
        using CallablePtr_t  = R(*)(Args..., ...);

        static constexpr bool is_variadic = true;
    };

    // (cv-qualified ptr bases)

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(*)(Args...)> : virtual FunctionInfo<R(Args...)>
    {
        using CallablePtr_t_no_ptr_cv = R(*)(Args...);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using CallablePtr_t = R(* const)(Args...);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* volatile)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using CallablePtr_t = R(* volatile)(Args...);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const volatile)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using CallablePtr_t = R(* const volatile)(Args...);
    };

    // noexcept specializations

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(*)(Args...) noexcept>
        :
        virtual FunctionInfo<R(*)(Args...)>,
        virtual FunctionInfo<R(Args...) noexcept>
    {
        using CallablePtr_t           = R(*)(Args...) noexcept;
        using CallablePtr_t_no_ptr_cv = R(*)(Args...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const)(Args...) noexcept> : virtual FunctionInfo<R(*)(Args...) noexcept>
    {
        using Callable_t     = R(Args...) noexcept;
        using CallableDecl_t = R(Args...) noexcept;
        using CallablePtr_t  = R(* const)(Args...) noexcept;
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* volatile)(Args...) noexcept> : virtual FunctionInfo<R(*)(Args...) noexcept>
    {
        using Callable_t     = R(Args...) noexcept;
        using CallableDecl_t = R(Args...) noexcept;
        using CallablePtr_t  = R(* volatile)(Args...) noexcept;
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const volatile)(Args...) noexcept> : virtual FunctionInfo<R(*)(Args...) noexcept>
    {
        using Callable_t     = R(Args...) noexcept;
        using CallableDecl_t = R(Args...) noexcept;
        using CallablePtr_t  = R(* const volatile)(Args...) noexcept;
    };

    // cv-qualified ptr bases (variadic)

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(*)(Args..., ...)> : virtual FunctionInfo<R(Args..., ...)>
    {
        using CallablePtr_t_no_ptr_cv = R(*)(Args..., ...);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const)(Args..., ...)> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using CallablePtr_t = R(* const)(Args..., ...);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* volatile)(Args..., ...)> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using CallablePtr_t = R(* volatile)(Args..., ...);
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const volatile)(Args..., ...)> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using CallablePtr_t = R(* const volatile)(Args..., ...);
    };

    // noexcept specializations

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(*)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using Callable_t              = R(Args..., ...) noexcept;
        using CallablePtr_t           = R(*)(Args..., ...) noexcept;
        using CallablePtr_t_no_ptr_cv = R(*)(Args..., ...) noexcept;
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...) noexcept>
    {
        using Callable_t    = R(Args..., ...) noexcept;
        using CallablePtr_t = R(* const)(Args..., ...) noexcept;
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* volatile)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...) noexcept>
    {
        using Callable_t    = R(Args..., ...) noexcept;
        using CallablePtr_t = R(* volatile)(Args..., ...) noexcept;
    };

    template <typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(* const volatile)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...) noexcept>
    {
        using Callable_t    = R(Args..., ...) noexcept;
        using CallablePtr_t = R(* const volatile)(Args..., ...) noexcept;
    };

    //////////////////////////////////
    // member function specializations

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using Class_t = std::conditional_t<std::is_class_v<C>, C, void>;
        using Union_t = std::conditional_t<std::is_union_v<C>, C, void>;

        using Callable_t                      = void;
        using CallableDecl_t                  = R(Args...);
        using CallablePtr_t                   = R(C::*)(Args...);
        using CallablePtr_t_no_ptr_cv         = R(C::*)(Args...); // removing pointer cv qualifiers
        using CallablePtr_t_no_cvrn           = R(C::*)(Args...); // removing all cvr-n but pointer cv qualifiers
        using CallablePtr_t_no_cvrn_no_ptr_cv = R(C::*)(Args...); // removing all cvr-n

        static constexpr bool is_const_qualified{};
        static constexpr bool is_volatile_qualified{};
        static constexpr bool is_lvalue_reference_qualified{};
        static constexpr bool is_rvalue_reference_qualified{};
        static constexpr bool is_not_reference_qualified{ true };
        static constexpr bool is_noexcept_specified{};
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args..., ...)>
        :
        virtual FunctionInfo<R(C::*)(Args...)>,
        virtual FunctionInfo<R(Args..., ...)>
    {
        using Callable_t                      = void;
        using CallableDecl_t                  = R(Args..., ...);
        using CallablePtr_t                   = R(C::*)(Args..., ...);
        using CallablePtr_t_no_ptr_cv         = R(C::*)(Args..., ...); // removing pointer cv qualifiers
        using CallablePtr_t_no_cvrn           = R(C::*)(Args..., ...); // removing all cvr-n but pointer cv qualifiers
        using CallablePtr_t_no_cvrn_no_ptr_cv = R(C::*)(Args..., ...); // removing all cvr-n
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args...)> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t         = R(C::* const)(Args...);
        using CallablePtr_t_no_cvrn = R(C::* const)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args...)> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t         = R(C::* volatile)(Args...);
        using CallablePtr_t_no_cvrn = R(C::* volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args...)>
        :
        virtual FunctionInfo<R(C::* const)(Args...)>,
        virtual FunctionInfo<R(C::* volatile)(Args...)>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args...);
        using CallablePtr_t_no_cvrn = R(C::* const volatile)(Args...);
    };

    ///////////////////////////
    // variadic specializations

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const)(Args..., ...)> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallablePtr_t         = R(C::* const)(Args..., ...);
        using CallablePtr_t_no_cvrn = R(C::* const)(Args..., ...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* volatile)(Args..., ...)> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallablePtr_t         = R(C::* volatile)(Args..., ...);
        using CallablePtr_t_no_cvrn = R(C::* volatile)(Args..., ...);
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::* const volatile)(Args..., ...)>
        :
        virtual FunctionInfo<R(C::* const)(Args..., ...)>,
        virtual FunctionInfo<R(C::* volatile)(Args..., ...)>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args..., ...);
        using CallablePtr_t_no_cvrn = R(C::* const volatile)(Args..., ...);
    };

    /////////////////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) const> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) const;
        using CallablePtr_t           = R(C::*)(Args...) const;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args...) const;

        static constexpr bool is_const_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) volatile> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) volatile;
        using CallablePtr_t           = R(C::*)(Args...) volatile;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args...) volatile;

        static constexpr bool is_volatile_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) &> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) &;
        using CallablePtr_t           = R(C::*)(Args...) &;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args...) &;

        static constexpr bool is_lvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) &&> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) &&;
        using CallablePtr_t           = R(C::*)(Args...) &&;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args...) &&;

        static constexpr bool is_rvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args...) noexcept> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) noexcept;
        using CallablePtr_t           = R(C::*)(Args...) noexcept;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };

    ///////////////////////////
    // variadic specializations

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args..., ...) const> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) const;
        using CallablePtr_t           = R(C::*)(Args..., ...) const;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args..., ...) const;

        static constexpr bool is_const_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args..., ...) volatile> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) volatile;
        using CallablePtr_t           = R(C::*)(Args..., ...) volatile;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args..., ...) volatile;

        static constexpr bool is_volatile_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args..., ...) &> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) &;
        using CallablePtr_t           = R(C::*)(Args..., ...) &;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args..., ...) &;

        static constexpr bool is_lvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args..., ...) &&> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) &&;
        using CallablePtr_t           = R(C::*)(Args..., ...) &&;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args..., ...) &&;

        static constexpr bool is_rvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FAT_EBCO FunctionInfo<R(C::*)(Args..., ...) noexcept> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) noexcept;
        using CallablePtr_t           = R(C::*)(Args..., ...) noexcept;
        using CallablePtr_t_no_ptr_cv = R(C::*)(Args..., ...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };
    /////////////////////////////////////////////////////////////////////////////

#define MEM_FUNCDECL_TYPE R(Args...)
#define MEM_FUNCDECL_TYPE_VARIADIC R(Args..., ...)

#define MEM_FUNCPTR_TYPE(PQUAL) R(C::* PQUAL )(Args...)
#define MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) R(C::* PQUAL )(Args..., ...)

#define V_INHERIT(PQUAL, FQS) virtual FunctionInfo< MEM_FUNCPTR_TYPE(PQUAL) FQS >
#define V_INHERIT_VARIADIC(PQUAL, FQS) virtual FunctionInfo< MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) FQS >

#define FAT_FUNC_INFO_GENERATOR1(PQUAL, ...)                         \
template <typename C, typename R, typename... Args>                  \
struct FAT_EBCO FunctionInfo< MEM_FUNCPTR_TYPE(PQUAL) __VA_ARGS__ >

#define FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, ...)                \
template <typename C, typename R, typename... Args>                  \
struct FAT_EBCO FunctionInfo< MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) __VA_ARGS__ >

#define FAT_FUNC_INFO_GENERATOR2(PQUAL, ...)                         \
    :                                                                \
    __VA_ARGS__                                                      

#define FAT_FUNC_INFO_GENERATOR3(PQUAL, ...)                                  \
{                                                                             \
    using CallableDecl_t          = MEM_FUNCDECL_TYPE       __VA_ARGS__;      \
    using CallablePtr_t           = MEM_FUNCPTR_TYPE(PQUAL) __VA_ARGS__;      \
    using CallablePtr_t_no_ptr_cv = MEM_FUNCPTR_TYPE()      __VA_ARGS__;      \
    using CallablePtr_t_no_cvrn   = MEM_FUNCPTR_TYPE(PQUAL);                  \
};

#define FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, ...)                              \
{                                                                                  \
    using CallableDecl_t          = MEM_FUNCDECL_TYPE_VARIADIC       __VA_ARGS__;  \
    using CallablePtr_t           = MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) __VA_ARGS__;  \
    using CallablePtr_t_no_ptr_cv = MEM_FUNCPTR_TYPE_VARIADIC()      __VA_ARGS__;  \
    using CallablePtr_t_no_cvrn   = MEM_FUNCPTR_TYPE_VARIADIC(PQUAL);              \
};

#define FAT_FUNC_INFO_GENERATOR(PQUAL)                                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const &)                                                                                               \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &))                                                          \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const &)                                                                                               \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const &&)                                                                                              \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &&))                                                         \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const &&)                                                                                              \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const noexcept)                                                                                        \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, noexcept))                                                   \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const noexcept)                                                                                        \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const & noexcept)                                                                                      \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                              \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const & noexcept)                                                                                      \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const && noexcept)                                                                                     \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                             \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const && noexcept)                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile &)                                                                                            \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &))                                                       \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile &)                                                                                            \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile &&)                                                                                           \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&))                                                      \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile &&)                                                                                           \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile noexcept)                                                                                     \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, noexcept))                                                \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile noexcept)                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile & noexcept)                                                                                   \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                           \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile & noexcept)                                                                                   \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, volatile && noexcept)                                                                                  \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                          \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, volatile && noexcept)                                                                                  \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile)                                                                                        \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile))                                                   \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile)                                                                                        \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile &)                                                                                      \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &))                              \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile &)                                                                                      \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile &&)                                                                                     \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&))                             \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile &&)                                                                                     \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile noexcept)                                                                               \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, noexcept))                       \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile noexcept)                                                                               \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile & noexcept)                                                                             \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))  \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile & noexcept)                                                                             \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, const volatile && noexcept)                                                                            \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept)) \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, const volatile && noexcept)                                                                            \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, & noexcept)                                                                                            \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                                                       \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, & noexcept)                                                                                            \
                                                                                                                                           \
    FAT_FUNC_INFO_GENERATOR1(PQUAL, && noexcept)                                                                                           \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                                                      \
    FAT_FUNC_INFO_GENERATOR3(PQUAL, && noexcept)                                                                                           \

#define FAT_FUNC_INFO_GENERATOR_VARIADIC(PQUAL)                                                                                            \
                                                                                                                                            \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const &)                                                                                        \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &))                                           \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const &)                                                                                          \
                                                                                                                                                \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const &&)                                                                                           \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &&))                                              \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const &&)                                                                                             \
                                                                                                                                                    \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const noexcept)                                                                                         \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, noexcept))                                            \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const noexcept)                                                                                           \
                                                                                                                                                        \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const & noexcept)                                                                                           \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))                  \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const & noexcept)                                                                                             \
                                                                                                                                                            \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const && noexcept)                                                                                              \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept))                     \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const && noexcept)                                                                                                \
                                                                                                                                                                \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile &)                                                                                                         \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &))                                                            \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile &)                                                                                                           \
                                                                                                                                                                    \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile &&)                                                                                                            \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&))                                                               \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile &&)                                                                                                              \
                                                                                                                                                                        \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile noexcept)                                                                                                          \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, noexcept))                                                             \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile noexcept)                                                                                                            \
                                                                                                                                                                            \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile & noexcept)                                                                                                            \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))                                   \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile & noexcept)                                                                                                              \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile && noexcept)                                                                                                             \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept))                                   \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile && noexcept)                                                                                                             \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile)                                                                                                                   \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile))                                                                     \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile)                                                                                                                   \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile &)                                                                                                                 \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &))                                       \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile &)                                                                                                                 \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile &&)                                                                                                                \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&))                                      \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile &&)                                                                                                                \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile noexcept)                                                                                                          \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, noexcept))                                \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile noexcept)                                                                                                          \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile & noexcept)                                                                                                        \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))  \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile & noexcept)                                                                                                        \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile && noexcept)                                                                                                       \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept)) \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile && noexcept)                                                                                                       \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, & noexcept)                                                                                                                       \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))                                                                         \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, & noexcept)                                                                                                                       \
                                                                                                                                                                               \
    FAT_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, && noexcept)                                                                                                                      \
    FAT_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept))                                                                        \
    FAT_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, && noexcept)

#pragma warning (push)
#pragma warning (disable : 4003)
    FAT_FUNC_INFO_GENERATOR()
    FAT_FUNC_INFO_GENERATOR_VARIADIC()
#pragma warning (pop)

    // with cv-qualified (member function) pointers

#define FAT_FUNC_INFO_GENERATOR4(PQUAL, FQS)                        \
    template <typename C, typename R, typename... Args>             \
    struct FAT_EBCO FunctionInfo<R(C::* PQUAL)(Args...) FQS>        \
        :                                                           \
        virtual FunctionInfo<R(C::* PQUAL)(Args...)>,               \
        virtual FunctionInfo<R(C::*      )(Args...) FQS>            \
    {                                                               \
        using CallablePtr_t           = R(C::* PQUAL)(Args...) FQS; \
        using CallablePtr_t_no_ptr_cv = R(C::*      )(Args...) FQS; \
        using CallablePtr_t_no_cvrn   = R(C::* PQUAL)(Args...);     \
    };

#define FAT_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, FQS)                    \
    template <typename C, typename R, typename... Args>                  \
    struct FAT_EBCO FunctionInfo<R(C::* PQUAL)(Args..., ...) FQS>        \
        :                                                                \
        virtual FunctionInfo<R(C::* PQUAL)(Args..., ...)>,               \
        virtual FunctionInfo<R(C::*      )(Args..., ...) FQS>            \
    {                                                                    \
        using CallablePtr_t           = R(C::* PQUAL)(Args..., ...) FQS; \
        using CallablePtr_t_no_ptr_cv = R(C::*      )(Args..., ...) FQS; \
        using CallablePtr_t_no_cvrn   = R(C::* PQUAL)(Args..., ...);     \
    };

#define FAT_FUNC_INFO_GENERATOR_BASE(PQUAL)   \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, const)    \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, volatile) \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, &)        \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, &&)       \
    FAT_FUNC_INFO_GENERATOR4(PQUAL, noexcept)

#define FAT_FUNC_INFO_GENERATOR_BASE_VARIADIC(PQUAL)   \
    FAT_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, const)    \
    FAT_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, volatile) \
    FAT_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, &)        \
    FAT_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, &&)       \
    FAT_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, noexcept)

    FAT_FUNC_INFO_GENERATOR_BASE(const)
    FAT_FUNC_INFO_GENERATOR(const)

    FAT_FUNC_INFO_GENERATOR_BASE(volatile)
    FAT_FUNC_INFO_GENERATOR(volatile)

    FAT_FUNC_INFO_GENERATOR_BASE(const volatile)
    FAT_FUNC_INFO_GENERATOR(const volatile)

    FAT_FUNC_INFO_GENERATOR_BASE_VARIADIC(const)
    FAT_FUNC_INFO_GENERATOR_VARIADIC(const)

    FAT_FUNC_INFO_GENERATOR_BASE_VARIADIC(volatile)
    FAT_FUNC_INFO_GENERATOR_VARIADIC(volatile)

    FAT_FUNC_INFO_GENERATOR_BASE_VARIADIC(const volatile)
    FAT_FUNC_INFO_GENERATOR_VARIADIC(const volatile)

#undef FAT_FUNC_INFO_GENERATOR_BASE
#undef FAT_FUNC_INFO_GENERATOR_BASE_VARIADIC
#undef FAT_FUNC_INFO_GENERATOR4
#undef FAT_FUNC_INFO_GENERATOR4_VARIADIC
#undef FAT_FUNC_INFO_GENERATOR_CVPTR
#undef FAT_FUNC_INFO_GENERATOR3
#undef FAT_FUNC_INFO_GENERATOR3_VARIADIC
#undef FAT_FUNC_INFO_GENERATOR2
#undef FAT_FUNC_INFO_GENERATOR1
#undef FAT_FUNC_INFO_GENERATOR1_VARIADIC
#undef FAT_FUNC_INFO_GENERATOR
#undef FAT_FUNC_INFO_GENERATOR_VARIADIC
#undef V_INHERIT
#undef V_INHERIT_VARIADIC
#undef MEM_FUNCPTR_TYPE
#undef MEM_FUNCPTR_TYPE_VARIADIC
#undef MEM_FUNCDECL_TYPE
#undef MEM_FUNCDECL_TYPE_VARIADIC

    template <typename T>
    concept Function = std::is_function_v<T>;

    template <typename T>
    concept HasFCallOperator = (ClassOrStruct<T> or Union<T>) and requires()
    {
        &T::operator ();
    };

    template <typename T>
    concept Functor = Instantiable<T> and not Function<T> and requires(T t)
    {
        t();
    };

    template <typename T>
    concept Callable = Function<T> or Functor<T>;
}

module : private;

#ifdef IN_DEBUG

namespace fatpound::traits
{
    // static assertion tests for lambdas

    static_assert(        not Function<decltype([]{})>);
    static_assert(             Functor<decltype([]{})>);
    static_assert(    HasFCallOperator<decltype([]{})>);
    static_assert(            Callable<decltype([]{})>);

    static_assert(    FunctionInfo<decltype(&decltype([]()          {})::operator ())>::is_const_qualified);
    static_assert(not FunctionInfo<decltype(&decltype([]() mutable  {})::operator ())>::is_const_qualified);
    static_assert(not FunctionInfo<decltype(&decltype([]()          {})::operator ())>::is_volatile_qualified);
    
    static_assert(not FunctionInfo<decltype(&decltype([]()          {})::operator ())>::is_lvalue_reference_qualified);
    static_assert(not FunctionInfo<decltype(&decltype([]()          {})::operator ())>::is_rvalue_reference_qualified);
    static_assert(    FunctionInfo<decltype(&decltype([]()          {})::operator ())>::is_not_reference_qualified);
    
    static_assert(not FunctionInfo<decltype(&decltype([]()          {})::operator ())>::is_noexcept_specified);
    static_assert(    FunctionInfo<decltype(&decltype([]() noexcept {})::operator ())>::is_noexcept_specified);
    
    static_assert(not FunctionInfo<decltype(&decltype([]()          {})::operator ())>::is_variadic);
    static_assert(    FunctionInfo<decltype(&decltype([](...)       {})::operator ())>::is_variadic);

    //////////////////////////////////

    struct FAT_EBCO ___unused___ final
    {
        explicit ___unused___()                        = delete;
        explicit ___unused___(const ___unused___&)     = delete;
        explicit ___unused___(___unused___&&) noexcept = delete;

        auto operator = (const ___unused___&)     -> ___unused___& = delete;
        auto operator = (___unused___&&) noexcept -> ___unused___& = delete;
        ~___unused___() noexcept                                   = delete;
        
        //********************//

        auto operator () () -> int;

        static_assert(HasFCallOperator<               ___unused___>);
        static_assert(HasFCallOperator<const          ___unused___>);
        static_assert(HasFCallOperator<      volatile ___unused___>);
        static_assert(HasFCallOperator<const volatile ___unused___>);


#define FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(ret_t, funcname, PQUAL, FQS, cons, vol, lref, rref, nonref, noexc, vary, ...)                                                                                                                                                                                                                                                     \
                                                                                                                                                                                                                                                                                                                                                                                      \
        ret_t funcname ( __VA_ARGS__ ) FQS;                                                                                                                                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                                                                                      \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::Class_t,                         ___unused___>,                                     " Class_t"                         " check failed!");                                                                                                                                                \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::Callable_t,                      void>,                                             " Callable_t"                      " check failed!");                                                                                                                                                \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::CallableDecl_t,                  void( __VA_ARGS__ ) FQS >,                         " CallableDecl_t"                  " check failed!");                                                                                                                                                \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::CallablePtr_t,                   void(___unused___::* PQUAL )( __VA_ARGS__ ) FQS>,  " CallablePtr_t"                   " check failed!");                                                                                                                                                \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::CallablePtr_t_no_ptr_cv,         void(___unused___::*       )( __VA_ARGS__ ) FQS >, " CallablePtr_t_no_ptr_cv"         " check failed!");                                                                                                                                                \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::CallablePtr_t_no_cvrn,           void(___unused___::* PQUAL )( __VA_ARGS__ )>,      " CallablePtr_t_no_cvrn"           " check failed!");                                                                                                                                                \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::CallablePtr_t_no_cvrn_no_ptr_cv, void(___unused___::*       )( __VA_ARGS__ )>,      " CallablePtr_t_no_cvrn_no_ptr_cv" " check failed!");                                                                                                                                                \
                                                                                                                                                                                                                                                                                                                                                                                      \
        static_assert(        cons FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::is_const_qualified,            "   cons qual check ==> " #ret_t " (::* " #PQUAL " to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);   \
        static_assert(         vol FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::is_volatile_qualified,         "    vol qual check ==> " #ret_t " (::* " #PQUAL " to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);   \
        static_assert(        lref FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::is_lvalue_reference_qualified, "   lref qual check ==> " #ret_t " (::* " #PQUAL " to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);   \
        static_assert(        rref FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::is_rvalue_reference_qualified, "   rref qual check ==> " #ret_t " (::* " #PQUAL " to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);   \
        static_assert(      nonref FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::is_not_reference_qualified,    " nonref qual check ==> " #ret_t " (::* " #PQUAL " to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);   \
        static_assert(       noexc FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::is_noexcept_specified,         "  noexc qual check ==> " #ret_t " (::* " #PQUAL " to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);   \
        static_assert(        vary FunctionInfo< PQUAL decltype(&___unused___:: funcname )>::is_variadic,                   "   vary func check ==> " #ret_t " (::* " #PQUAL " to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);



        ///////////////////////////////////////////   ret_t,  funcname,            PQUAL,                          FQS,  cons,  vol, lref,   rref, nonref, noexc,  vary,  parameters       
                                                                                       
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo00,                 ,                             ,   not,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo01,                 ,                       const ,      ,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo02,                 ,                    volatile ,   not,     ,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo03,                 ,                           & ,   not,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo04,                 ,                          && ,   not,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo05,                 ,                    noexcept ,   not,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo06,                 ,                    const  & ,      ,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo07,                 ,                    const && ,      ,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo08,                 ,              const noexcept ,      ,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo09,                 ,            const & noexcept ,      ,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo10,                 ,           const && noexcept ,      ,  not,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo11,                 ,                 volatile  & ,   not,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo12,                 ,                 volatile && ,   not,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo13,                 ,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo14,                 ,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo15,                 ,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo16,                 ,           const volatile  & ,      ,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo17,                 ,           const volatile && ,      ,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo18,                 ,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo19,                 ,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo20,                 ,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo21,                 ,                  & noexcept ,   not,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo22,                 ,                 && noexcept ,   not,  not,  not,       ,    not,      ,   not,             )
                                                                                  
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo23,            const,                             ,   not,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo24,            const,                       const ,      ,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo25,            const,                    volatile ,   not,     ,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo26,            const,                           & ,   not,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo27,            const,                          && ,   not,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo28,            const,                    noexcept ,   not,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo29,            const,                    const  & ,      ,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo30,            const,                    const && ,      ,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo31,            const,              const noexcept ,      ,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo32,            const,            const & noexcept ,      ,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo33,            const,           const && noexcept ,      ,  not,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo34,            const,                 volatile  & ,   not,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo35,            const,                 volatile && ,   not,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo36,            const,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo37,            const,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo38,            const,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo39,            const,           const volatile  & ,      ,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo40,            const,           const volatile && ,      ,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo41,            const,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo42,            const,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo43,            const,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo44,            const,                  & noexcept ,   not,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo45,            const,                 && noexcept ,   not,  not,  not,       ,    not,      ,   not,             )
                                                                               
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo46,         volatile,                             ,   not,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo47,         volatile,                       const ,      ,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo48,         volatile,                    volatile ,   not,     ,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo49,         volatile,                           & ,   not,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo50,         volatile,                          && ,   not,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo51,         volatile,                    noexcept ,   not,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo52,         volatile,                    const  & ,      ,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo53,         volatile,                    const && ,      ,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo54,         volatile,              const noexcept ,      ,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo55,         volatile,            const & noexcept ,      ,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo56,         volatile,           const && noexcept ,      ,  not,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo57,         volatile,                 volatile  & ,   not,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo58,         volatile,                 volatile && ,   not,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo59,         volatile,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo60,         volatile,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo61,         volatile,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo62,         volatile,           const volatile  & ,      ,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo63,         volatile,           const volatile && ,      ,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo64,         volatile,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo65,         volatile,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo66,         volatile,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo67,         volatile,                  & noexcept ,   not,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo68,         volatile,                 && noexcept ,   not,  not,  not,       ,    not,      ,   not,             )

        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo69,   const volatile,                             ,   not,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo70,   const volatile,                       const ,      ,  not,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo71,   const volatile,                    volatile ,   not,     ,  not,    not,       ,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo72,   const volatile,                           & ,   not,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo73,   const volatile,                          && ,   not,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo74,   const volatile,                    noexcept ,   not,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo75,   const volatile,                    const  & ,      ,  not,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo76,   const volatile,                    const && ,      ,  not,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo77,   const volatile,              const noexcept ,      ,  not,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo78,   const volatile,            const & noexcept ,      ,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo79,   const volatile,           const && noexcept ,      ,  not,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo80,   const volatile,                 volatile  & ,   not,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo81,   const volatile,                 volatile && ,   not,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo82,   const volatile,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo83,   const volatile,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo84,   const volatile,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo85,   const volatile,           const volatile  & ,      ,     ,     ,    not,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo86,   const volatile,           const volatile && ,      ,     ,  not,       ,    not,   not,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo87,   const volatile,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo88,   const volatile,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo89,   const volatile,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo90,   const volatile,                  & noexcept ,   not,  not,     ,    not,    not,      ,   not,             )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     foo91,   const volatile,                 && noexcept ,   not,  not,  not,       ,    not,      ,   not,             )

        // variadic specializiation tests

        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar00,                 ,                             ,   not,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar01,                 ,                       const ,      ,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar02,                 ,                    volatile ,   not,     ,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar03,                 ,                           & ,   not,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar04,                 ,                          && ,   not,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar05,                 ,                    noexcept ,   not,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar06,                 ,                    const  & ,      ,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar07,                 ,                    const && ,      ,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar08,                 ,              const noexcept ,      ,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar09,                 ,            const & noexcept ,      ,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar10,                 ,           const && noexcept ,      ,  not,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar11,                 ,                 volatile  & ,   not,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar12,                 ,                 volatile && ,   not,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar13,                 ,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar14,                 ,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar15,                 ,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar16,                 ,           const volatile  & ,      ,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar17,                 ,           const volatile && ,      ,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar18,                 ,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar19,                 ,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar20,                 ,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar21,                 ,                  & noexcept ,   not,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar22,                 ,                 && noexcept ,   not,  not,  not,       ,    not,      ,      ,     ...     )

        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar23,            const,                             ,   not,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar24,            const,                       const ,      ,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar25,            const,                    volatile ,   not,     ,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar26,            const,                           & ,   not,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar27,            const,                          && ,   not,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar28,            const,                    noexcept ,   not,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar29,            const,                    const  & ,      ,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar30,            const,                    const && ,      ,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar31,            const,              const noexcept ,      ,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar32,            const,            const & noexcept ,      ,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar33,            const,           const && noexcept ,      ,  not,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar34,            const,                 volatile  & ,   not,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar35,            const,                 volatile && ,   not,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar36,            const,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar37,            const,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar38,            const,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar39,            const,           const volatile  & ,      ,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar40,            const,           const volatile && ,      ,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar41,            const,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar42,            const,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar43,            const,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar44,            const,                  & noexcept ,   not,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar45,            const,                 && noexcept ,   not,  not,  not,       ,    not,      ,      ,     ...     )

        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar46,         volatile,                             ,   not,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar47,         volatile,                       const ,      ,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar48,         volatile,                    volatile ,   not,     ,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar49,         volatile,                           & ,   not,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar50,         volatile,                          && ,   not,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar51,         volatile,                    noexcept ,   not,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar52,         volatile,                    const  & ,      ,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar53,         volatile,                    const && ,      ,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar54,         volatile,              const noexcept ,      ,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar55,         volatile,            const & noexcept ,      ,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar56,         volatile,           const && noexcept ,      ,  not,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar57,         volatile,                 volatile  & ,   not,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar58,         volatile,                 volatile && ,   not,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar59,         volatile,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar60,         volatile,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar61,         volatile,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar62,         volatile,           const volatile  & ,      ,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar63,         volatile,           const volatile && ,      ,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar64,         volatile,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar65,         volatile,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar66,         volatile,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar67,         volatile,                  & noexcept ,   not,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar68,         volatile,                 && noexcept ,   not,  not,  not,       ,    not,      ,      ,     ...     )

        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar69,   const volatile,                             ,   not,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar70,   const volatile,                       const ,      ,  not,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar71,   const volatile,                    volatile ,   not,     ,  not,    not,       ,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar72,   const volatile,                           & ,   not,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar73,   const volatile,                          && ,   not,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar74,   const volatile,                    noexcept ,   not,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar75,   const volatile,                    const  & ,      ,  not,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar76,   const volatile,                    const && ,      ,  not,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar77,   const volatile,              const noexcept ,      ,  not,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar78,   const volatile,            const & noexcept ,      ,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar79,   const volatile,           const && noexcept ,      ,  not,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar80,   const volatile,                 volatile  & ,   not,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar81,   const volatile,                 volatile && ,   not,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar82,   const volatile,        volatile    noexcept ,   not,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar83,   const volatile,        volatile  & noexcept ,   not,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar84,   const volatile,        volatile && noexcept ,   not,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar85,   const volatile,           const volatile  & ,      ,     ,     ,    not,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar86,   const volatile,           const volatile && ,      ,     ,  not,       ,    not,   not,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar87,   const volatile,     const volatile noexcept ,      ,     ,  not,    not,       ,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar88,   const volatile,   const volatile & noexcept ,      ,     ,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar89,   const volatile,  const volatile && noexcept ,      ,     ,  not,       ,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar90,   const volatile,                  & noexcept ,   not,  not,     ,    not,    not,      ,      ,     ...     )
        FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(   void,     bar91,   const volatile,                 && noexcept ,   not,  not,  not,       ,    not,      ,      ,     ...     )

#undef FAT_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR
    };
}

#endif
