module;

#include <_macros/Compiler.hxx>

export module FatPound.Traits.Callable;

import FatPound.Traits.Formation;

import std;

// NOLINTBEGIN(altera-struct-pack-align, fuchsia-virtual-inheritance)

export namespace fatpound::traits
{
    template <typename T>
    struct FATLIB_EBCO FunctionInfo;
    
    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(Args...)>
    {
        using Return_t       = R;
        using Callable_t     = R(Args...);
        using CallableDecl_t = R(Args...);
        using CallablePtr_t  = R(*)(Args...);
        using TupleOfArgs_t  = std::tuple<Args...>;

        template <std::size_t N>
        using Nth_Argument_t = std::tuple_element<N, TupleOfArgs_t>::type;

        static constexpr auto fixed_arity = sizeof...(Args);

        static constexpr bool is_noexcept_specified{};
        static constexpr bool is_variadic{};
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(Args..., ...)> : virtual FunctionInfo<R(Args...)>
    {
        using Callable_t     = R(Args..., ...);
        using CallableDecl_t = R(Args..., ...);
        using CallablePtr_t  = R(*)(Args..., ...);

        static constexpr bool is_variadic = true;
    };

    // (cv-qualified ptr bases)

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(*)(Args...)> : virtual FunctionInfo<R(Args...)>
    {
        using CallablePtr_no_ptr_cv_t = R(*)(Args...);
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using CallablePtr_t = R(* const)(Args...);
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* volatile)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using CallablePtr_t = R(* volatile)(Args...);
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const volatile)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using CallablePtr_t = R(* const volatile)(Args...);
    };

    // noexcept specializations

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(*)(Args...) noexcept> : virtual FunctionInfo<R(*)(Args...)>
    {
        using Callable_t              = R(Args...)    noexcept;
        using CallableDecl_t          = R(Args...)    noexcept;
        using CallablePtr_t           = R(*)(Args...) noexcept;
        using CallablePtr_no_ptr_cv_t = R(*)(Args...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const)(Args...) noexcept> : virtual FunctionInfo<R(*)(Args...) noexcept>
    {
        using Callable_t     = R(Args...) noexcept;
        using CallableDecl_t = R(Args...) noexcept;
        using CallablePtr_t  = R(* const)(Args...) noexcept;
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* volatile)(Args...) noexcept> : virtual FunctionInfo<R(*)(Args...) noexcept>
    {
        using Callable_t     = R(Args...) noexcept;
        using CallableDecl_t = R(Args...) noexcept;
        using CallablePtr_t  = R(* volatile)(Args...) noexcept;
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const volatile)(Args...) noexcept> : virtual FunctionInfo<R(*)(Args...) noexcept>
    {
        using Callable_t     = R(Args...) noexcept;
        using CallableDecl_t = R(Args...) noexcept;
        using CallablePtr_t  = R(* const volatile)(Args...) noexcept;
    };

    // cv-qualified ptr bases (variadic)

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(*)(Args..., ...)> : virtual FunctionInfo<R(Args..., ...)>
    {
        using CallablePtr_no_ptr_cv_t = R(*)(Args..., ...);
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const)(Args..., ...)> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using CallablePtr_t = R(* const)(Args..., ...);
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* volatile)(Args..., ...)> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using CallablePtr_t = R(* volatile)(Args..., ...);
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const volatile)(Args..., ...)> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using CallablePtr_t = R(* const volatile)(Args..., ...);
    };

    // noexcept specializations

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(*)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...)>
    {
        using Callable_t              = R(Args..., ...) noexcept;
        using CallableDecl_t          = R(Args..., ...) noexcept;
        using CallablePtr_t           = R(*)(Args..., ...) noexcept;
        using CallablePtr_no_ptr_cv_t = R(*)(Args..., ...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...) noexcept>
    {
        using Callable_t    = R(Args..., ...) noexcept;
        using CallablePtr_t = R(* const)(Args..., ...) noexcept;
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* volatile)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...) noexcept>
    {
        using Callable_t    = R(Args..., ...) noexcept;
        using CallablePtr_t = R(* volatile)(Args..., ...) noexcept;
    };

    template <typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(* const volatile)(Args..., ...) noexcept> : virtual FunctionInfo<R(*)(Args..., ...) noexcept>
    {
        using Callable_t    = R(Args..., ...) noexcept;
        using CallablePtr_t = R(* const volatile)(Args..., ...) noexcept;
    };

    //////////////////////////////////
    // member function specializations

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args...)> : virtual FunctionInfo<R(*)(Args...)>
    {
        using Class_t = std::conditional_t<std::is_class_v<C>, C, void>;
        using Union_t = std::conditional_t<std::is_union_v<C>, C, void>;

        using Callable_t                      = void;
        using CallableDecl_t                  = R(Args...);
        using CallablePtr_t                   = R(C::*)(Args...);
        using CallablePtr_no_ptr_cv_t         = R(C::*)(Args...); // removing pointer cv qualifiers
        using CallablePtr_no_cvrn_t           = R(C::*)(Args...); // removing all cvr-n but pointer cv qualifiers
        using CallablePtr_no_cvrn_no_ptr_cv_t = R(C::*)(Args...); // removing all cvr-n

        static constexpr bool is_const_qualified{};
        static constexpr bool is_volatile_qualified{};
        static constexpr bool is_lvalue_reference_qualified{};
        static constexpr bool is_rvalue_reference_qualified{};
        static constexpr bool is_not_reference_qualified{ true };
        static constexpr bool is_noexcept_specified{};
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args..., ...)>
        :
        virtual FunctionInfo<R(C::*)(Args...)>,
        virtual FunctionInfo<R(Args..., ...)>
    {
        using Callable_t                      = void;
        using CallableDecl_t                  = R(Args..., ...);
        using CallablePtr_t                   = R(C::*)(Args..., ...);
        using CallablePtr_no_ptr_cv_t         = R(C::*)(Args..., ...); // removing pointer cv qualifiers
        using CallablePtr_no_cvrn_t           = R(C::*)(Args..., ...); // removing all cvr-n but pointer cv qualifiers
        using CallablePtr_no_cvrn_no_ptr_cv_t = R(C::*)(Args..., ...); // removing all cvr-n
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::* const)(Args...)> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t         = R(C::* const)(Args...);
        using CallablePtr_no_cvrn_t = R(C::* const)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::* volatile)(Args...)> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallablePtr_t         = R(C::* volatile)(Args...);
        using CallablePtr_no_cvrn_t = R(C::* volatile)(Args...);
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::* const volatile)(Args...)>
        :
        virtual FunctionInfo<R(C::* const)(Args...)>,
        virtual FunctionInfo<R(C::* volatile)(Args...)>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args...);
        using CallablePtr_no_cvrn_t = R(C::* const volatile)(Args...);
    };

    ///////////////////////////
    // variadic specializations

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::* const)(Args..., ...)> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallablePtr_t         = R(C::* const)(Args..., ...);
        using CallablePtr_no_cvrn_t = R(C::* const)(Args..., ...);
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::* volatile)(Args..., ...)> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallablePtr_t         = R(C::* volatile)(Args..., ...);
        using CallablePtr_no_cvrn_t = R(C::* volatile)(Args..., ...);
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::* const volatile)(Args..., ...)>
        :
        virtual FunctionInfo<R(C::* const)(Args..., ...)>,
        virtual FunctionInfo<R(C::* volatile)(Args..., ...)>
    {
        using CallablePtr_t         = R(C::* const volatile)(Args..., ...);
        using CallablePtr_no_cvrn_t = R(C::* const volatile)(Args..., ...);
    };

    /////////////////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args...) const> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) const;
        using CallablePtr_t           = R(C::*)(Args...) const;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args...) const;

        static constexpr bool is_const_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args...) volatile> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) volatile;
        using CallablePtr_t           = R(C::*)(Args...) volatile;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args...) volatile;

        static constexpr bool is_volatile_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args...) &> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) &;
        using CallablePtr_t           = R(C::*)(Args...) &;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args...) &;

        static constexpr bool is_lvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args...) &&> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) &&;
        using CallablePtr_t           = R(C::*)(Args...) &&;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args...) &&;

        static constexpr bool is_rvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args...) noexcept> : virtual FunctionInfo<R(C::*)(Args...)>
    {
        using CallableDecl_t          = R(Args...) noexcept;
        using CallablePtr_t           = R(C::*)(Args...) noexcept;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };

    ///////////////////////////
    // variadic specializations

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args..., ...) const> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) const;
        using CallablePtr_t           = R(C::*)(Args..., ...) const;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args..., ...) const;

        static constexpr bool is_const_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args..., ...) volatile> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) volatile;
        using CallablePtr_t           = R(C::*)(Args..., ...) volatile;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args..., ...) volatile;

        static constexpr bool is_volatile_qualified = true;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args..., ...) &> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) &;
        using CallablePtr_t           = R(C::*)(Args..., ...) &;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args..., ...) &;

        static constexpr bool is_lvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args..., ...) &&> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) &&;
        using CallablePtr_t           = R(C::*)(Args..., ...) &&;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args..., ...) &&;

        static constexpr bool is_rvalue_reference_qualified = true;
        static constexpr bool is_not_reference_qualified    = false;
    };

    template <typename C, typename R, typename... Args>
    struct FATLIB_EBCO FunctionInfo<R(C::*)(Args..., ...) noexcept> : virtual FunctionInfo<R(C::*)(Args..., ...)>
    {
        using CallableDecl_t          = R(Args..., ...) noexcept;
        using CallablePtr_t           = R(C::*)(Args..., ...) noexcept;
        using CallablePtr_no_ptr_cv_t = R(C::*)(Args..., ...) noexcept;

        static constexpr bool is_noexcept_specified = true;
    };
    /////////////////////////////////////////////////////////////////////////////

#define MEM_FUNCDECL_TYPE R(Args...)
#define MEM_FUNCDECL_TYPE_VARIADIC R(Args..., ...)

// NOLINTBEGIN(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#define MEM_FUNCPTR_TYPE(PQUAL) R(C::* PQUAL )(Args...)
#define MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) R(C::* PQUAL )(Args..., ...)

#define V_INHERIT(PQUAL, FQS) virtual FunctionInfo< MEM_FUNCPTR_TYPE(PQUAL) FQS >
#define V_INHERIT_VARIADIC(PQUAL, FQS) virtual FunctionInfo< MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) FQS >

#define FATLIB_FUNC_INFO_GENERATOR1(PQUAL, ...)                                      \
template <typename C, typename R, typename... Args>                                  \
struct FATLIB_EBCO FunctionInfo< MEM_FUNCPTR_TYPE(PQUAL) __VA_ARGS__ >               
                                                                                     
#define FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, ...)                             \
template <typename C, typename R, typename... Args>                                  \
struct FATLIB_EBCO FunctionInfo< MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) __VA_ARGS__ >      
                                                                                     
#define FATLIB_FUNC_INFO_GENERATOR2(PQUAL, ...)                                      \
    :                                                                                \
    __VA_ARGS__                                                                      
                                                                                     
#define FATLIB_FUNC_INFO_GENERATOR3(PQUAL, ...)                                      \
{                                                                                    \
    using CallableDecl_t          = MEM_FUNCDECL_TYPE       __VA_ARGS__;             \
    using CallablePtr_t           = MEM_FUNCPTR_TYPE(PQUAL) __VA_ARGS__;             \
    using CallablePtr_no_ptr_cv_t = MEM_FUNCPTR_TYPE()      __VA_ARGS__;             \
    using CallablePtr_no_cvrn_t   = MEM_FUNCPTR_TYPE(PQUAL);                         \
};                                                                                   
                                                                                     
#define FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, ...)                             \
{                                                                                    \
    using CallableDecl_t          = MEM_FUNCDECL_TYPE_VARIADIC       __VA_ARGS__;    \
    using CallablePtr_t           = MEM_FUNCPTR_TYPE_VARIADIC(PQUAL) __VA_ARGS__;    \
    using CallablePtr_no_ptr_cv_t = MEM_FUNCPTR_TYPE_VARIADIC()      __VA_ARGS__;    \
    using CallablePtr_no_cvrn_t   = MEM_FUNCPTR_TYPE_VARIADIC(PQUAL);                \
};

#define FATLIB_FUNC_INFO_GENERATOR(PQUAL)                                                                                                        \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const &)                                                                                                  \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &))                                                             \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const &)                                                                                                  \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const &&)                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &&))                                                            \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const &&)                                                                                                 \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const noexcept)                                                                                           \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, noexcept))                                                      \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const noexcept)                                                                                           \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const & noexcept)                                                                                         \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                                 \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const & noexcept)                                                                                         \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const && noexcept)                                                                                        \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                                \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const && noexcept)                                                                                        \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, volatile &)                                                                                               \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &))                                                          \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, volatile &)                                                                                               \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, volatile &&)                                                                                              \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&))                                                         \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, volatile &&)                                                                                              \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, volatile noexcept)                                                                                        \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, noexcept))                                                   \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, volatile noexcept)                                                                                        \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, volatile & noexcept)                                                                                      \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                              \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, volatile & noexcept)                                                                                      \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, volatile && noexcept)                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                             \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, volatile && noexcept)                                                                                     \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const volatile)                                                                                           \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile))                                                      \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const volatile)                                                                                           \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const volatile &)                                                                                         \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &))                                 \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const volatile &)                                                                                         \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const volatile &&)                                                                                        \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&))                                \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const volatile &&)                                                                                        \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const volatile noexcept)                                                                                  \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, noexcept))                          \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const volatile noexcept)                                                                                  \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const volatile & noexcept)                                                                                \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))     \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const volatile & noexcept)                                                                                \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, const volatile && noexcept)                                                                               \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, const), V_INHERIT(PQUAL, volatile), V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))    \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, const volatile && noexcept)                                                                               \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, & noexcept)                                                                                               \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, &), V_INHERIT(PQUAL, noexcept))                                                          \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, & noexcept)                                                                                               \
                                                                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR1(PQUAL, && noexcept)                                                                                              \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT(PQUAL, &&), V_INHERIT(PQUAL, noexcept))                                                         \
    FATLIB_FUNC_INFO_GENERATOR3(PQUAL, && noexcept)                                                                                              \



#define FATLIB_FUNC_INFO_GENERATOR_VARIADIC(PQUAL)                                                                                               \
                                                                                                                                                  \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const &)                                                                                           \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &))                                              \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const &)                                                                                             \
                                                                                                                                                      \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const &&)                                                                                              \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &&))                                                 \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const &&)                                                                                                \
                                                                                                                                                          \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const noexcept)                                                                                            \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, noexcept))                                               \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const noexcept)                                                                                              \
                                                                                                                                                              \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const & noexcept)                                                                                              \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))                     \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const & noexcept)                                                                                                \
                                                                                                                                                                  \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const && noexcept)                                                                                                 \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept))                        \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const && noexcept)                                                                                                   \
                                                                                                                                                                      \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile &)                                                                                                            \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &))                                                               \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile &)                                                                                                              \
                                                                                                                                                                          \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile &&)                                                                                                               \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&))                                                                  \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile &&)                                                                                                                 \
                                                                                                                                                                              \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile noexcept)                                                                                                             \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, noexcept))                                                                \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile noexcept)                                                                                                               \
                                                                                                                                                                                  \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile & noexcept)                                                                                                               \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))                                      \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile & noexcept)                                                                                                                 \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, volatile && noexcept)                                                                                                                \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept))                                      \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, volatile && noexcept)                                                                                                                \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile)                                                                                                                      \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile))                                                                        \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile)                                                                                                                      \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile &)                                                                                                                    \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &))                                          \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile &)                                                                                                                    \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile &&)                                                                                                                   \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&))                                         \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile &&)                                                                                                                   \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile noexcept)                                                                                                             \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, noexcept))                                   \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile noexcept)                                                                                                             \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile & noexcept)                                                                                                           \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))     \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile & noexcept)                                                                                                           \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, const volatile && noexcept)                                                                                                          \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, const), V_INHERIT_VARIADIC(PQUAL, volatile), V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept))    \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, const volatile && noexcept)                                                                                                          \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, & noexcept)                                                                                                                          \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, &), V_INHERIT_VARIADIC(PQUAL, noexcept))                                                                            \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, & noexcept)                                                                                                                          \
                                                                                                                                                                                     \
    FATLIB_FUNC_INFO_GENERATOR1_VARIADIC(PQUAL, && noexcept)                                                                                                                         \
    FATLIB_FUNC_INFO_GENERATOR2(PQUAL, V_INHERIT_VARIADIC(PQUAL, &&), V_INHERIT_VARIADIC(PQUAL, noexcept))                                                                           \
    FATLIB_FUNC_INFO_GENERATOR3_VARIADIC(PQUAL, && noexcept)

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4003)
#endif
    FATLIB_FUNC_INFO_GENERATOR()
    FATLIB_FUNC_INFO_GENERATOR_VARIADIC()
#ifdef _MSC_VER
#pragma warning (pop)
#endif

    // with cv-qualified (member function) pointers

#define FATLIB_FUNC_INFO_GENERATOR4(PQUAL, FQS)                             \
    template <typename C, typename R, typename... Args>                     \
    struct FATLIB_EBCO FunctionInfo<R(C::* PQUAL)(Args...) FQS>             \
        :                                                                   \
        virtual FunctionInfo<R(C::* PQUAL)(Args...)>,                       \
        virtual FunctionInfo<R(C::*      )(Args...) FQS>                    \
    {                                                                       \
        using CallablePtr_t           = R(C::* PQUAL)(Args...) FQS;         \
        using CallablePtr_no_ptr_cv_t = R(C::*      )(Args...) FQS;         \
        using CallablePtr_no_cvrn_t   = R(C::* PQUAL)(Args...);             \
    };                                                                      
                                                                            
#define FATLIB_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, FQS)                    \
    template <typename C, typename R, typename... Args>                     \
    struct FATLIB_EBCO FunctionInfo<R(C::* PQUAL)(Args..., ...) FQS>        \
        :                                                                   \
        virtual FunctionInfo<R(C::* PQUAL)(Args..., ...)>,                  \
        virtual FunctionInfo<R(C::*      )(Args..., ...) FQS>               \
    {                                                                       \
        using CallablePtr_t           = R(C::* PQUAL)(Args..., ...) FQS;    \
        using CallablePtr_no_ptr_cv_t = R(C::*      )(Args..., ...) FQS;    \
        using CallablePtr_no_cvrn_t   = R(C::* PQUAL)(Args..., ...);        \
    };

#define FATLIB_FUNC_INFO_GENERATOR_BASE(PQUAL)               \
    FATLIB_FUNC_INFO_GENERATOR4(PQUAL, const)                \
    FATLIB_FUNC_INFO_GENERATOR4(PQUAL, volatile)             \
    FATLIB_FUNC_INFO_GENERATOR4(PQUAL, &)                    \
    FATLIB_FUNC_INFO_GENERATOR4(PQUAL, &&)                   \
    FATLIB_FUNC_INFO_GENERATOR4(PQUAL, noexcept)             
                                                             
#define FATLIB_FUNC_INFO_GENERATOR_BASE_VARIADIC(PQUAL)      \
    FATLIB_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, const)       \
    FATLIB_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, volatile)    \
    FATLIB_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, &)           \
    FATLIB_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, &&)          \
    FATLIB_FUNC_INFO_GENERATOR4_VARIADIC(PQUAL, noexcept)


    FATLIB_FUNC_INFO_GENERATOR_BASE(const)
    FATLIB_FUNC_INFO_GENERATOR(const)

    FATLIB_FUNC_INFO_GENERATOR_BASE(volatile)
    FATLIB_FUNC_INFO_GENERATOR(volatile)

    FATLIB_FUNC_INFO_GENERATOR_BASE(const volatile)
    FATLIB_FUNC_INFO_GENERATOR(const volatile)

    FATLIB_FUNC_INFO_GENERATOR_BASE_VARIADIC(const)
    FATLIB_FUNC_INFO_GENERATOR_VARIADIC(const)

    FATLIB_FUNC_INFO_GENERATOR_BASE_VARIADIC(volatile)
    FATLIB_FUNC_INFO_GENERATOR_VARIADIC(volatile)

    FATLIB_FUNC_INFO_GENERATOR_BASE_VARIADIC(const volatile)
    FATLIB_FUNC_INFO_GENERATOR_VARIADIC(const volatile)


#undef FATLIB_FUNC_INFO_GENERATOR_BASE_VARIADIC
#undef FATLIB_FUNC_INFO_GENERATOR_BASE
#undef FATLIB_FUNC_INFO_GENERATOR4_VARIADIC
#undef FATLIB_FUNC_INFO_GENERATOR4
#undef FATLIB_FUNC_INFO_GENERATOR_VARIADIC
#undef FATLIB_FUNC_INFO_GENERATOR
#undef FATLIB_FUNC_INFO_GENERATOR3_VARIADIC
#undef FATLIB_FUNC_INFO_GENERATOR3
#undef FATLIB_FUNC_INFO_GENERATOR2
#undef FATLIB_FUNC_INFO_GENERATOR1_VARIADIC
#undef FATLIB_FUNC_INFO_GENERATOR1
#undef V_INHERIT_VARIADIC
#undef V_INHERIT
#undef MEM_FUNCPTR_TYPE_VARIADIC
#undef MEM_FUNCPTR_TYPE
#undef MEM_FUNCDECL_TYPE_VARIADIC
#undef MEM_FUNCDECL_TYPE

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

    static_assert(    not Function<decltype([]{})>);
    static_assert(         Functor<decltype([]{})>);
    static_assert(HasFCallOperator<decltype([]{})>);
    static_assert(        Callable<decltype([]{})>);

    // NOLINTBEGIN(cert-dcl50-cpp)

#define FATLIB_FUNC_INFO_LAMBDA_STATIC_ASSERT_GENERATOR(arity, ...)                                                                                              \
                                                                                                                                                                 \
    static_assert(          FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::is_const_qualified           );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    ) mutable  {})::operator ())>::is_const_qualified           );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::is_volatile_qualified        );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::is_lvalue_reference_qualified);    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::is_rvalue_reference_qualified);    \
    static_assert(          FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::is_not_reference_qualified   );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::is_noexcept_specified        );    \
    static_assert(          FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    ) noexcept {})::operator ())>::is_noexcept_specified        );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::is_variadic                  );    \
                                                                                                                                                                 \
    static_assert(          FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::is_const_qualified           );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... ) mutable  {})::operator ())>::is_const_qualified           );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::is_volatile_qualified        );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::is_lvalue_reference_qualified);    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::is_rvalue_reference_qualified);    \
    static_assert(          FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::is_not_reference_qualified   );    \
    static_assert(      not FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::is_noexcept_specified        );    \
    static_assert(          FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... ) noexcept {})::operator ())>::is_noexcept_specified        );    \
    static_assert(          FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::is_variadic                  );    \
                                                                                                                                                                 \
    static_assert( arity == FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    )          {})::operator ())>::fixed_arity                  );    \
    static_assert( arity == FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    ) mutable  {})::operator ())>::fixed_arity                  );    \
    static_assert( arity == FunctionInfo<decltype(&decltype([]( __VA_ARGS__                    ) noexcept {})::operator ())>::fixed_arity                  );    \
    static_assert( arity == FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... )          {})::operator ())>::fixed_arity                  );    \
    static_assert( arity == FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... ) mutable  {})::operator ())>::fixed_arity                  );    \
    static_assert( arity == FunctionInfo<decltype(&decltype([]( __VA_ARGS__  __VA_OPT__(,) ... ) noexcept {})::operator ())>::fixed_arity                  );


    FATLIB_FUNC_INFO_LAMBDA_STATIC_ASSERT_GENERATOR(0, )
    FATLIB_FUNC_INFO_LAMBDA_STATIC_ASSERT_GENERATOR(1, int)
    FATLIB_FUNC_INFO_LAMBDA_STATIC_ASSERT_GENERATOR(2, int, float)


    // NOLINTEND(cert-dcl50-cpp)

    //////////////////////////////////

    struct FATLIB_EBCO _unused_ final
    {
        explicit _unused_()                    = delete;
        explicit _unused_(const _unused_&)     = delete;
        explicit _unused_(_unused_&&) noexcept = delete;

        auto operator = (const _unused_&)     -> _unused_& = delete;
        auto operator = (_unused_&&) noexcept -> _unused_& = delete;
        ~_unused_() noexcept                               = delete;
        
        //********************//

        auto operator () () -> int;

        static_assert(HasFCallOperator<               _unused_>);
        static_assert(HasFCallOperator<const          _unused_>);
        static_assert(HasFCallOperator<      volatile _unused_>);
        static_assert(HasFCallOperator<const volatile _unused_>);


#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wcompound-token-split-by-macro"
    #pragma clang diagnostic ignored "-Wcompound-token-split-by-space"
#endif


#define FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE1(klasscope, stat, ret_t, funcname, PQUAL, FQS, cons, vol, lref, rref, nonref, noexc, vary, arity, ...)                                                                                                                                                                                                                                                                                                                   \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        stat auto funcname ( __VA_ARGS__ ) FQS -> ret_t ;                                                                                                                                                                                                                                                                                                                                                                                                                            \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        static_assert( arity == FunctionInfo< PQUAL decltype(&_unused_::funcname)>::fixed_arity, "arity is not equal to the fixed arity!");                                                                                                                                                                                                                                                                                                                                          \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::CallablePtr_t                  , ret_t ( klasscope * PQUAL )(  __VA_ARGS__ ) FQS >, "CallablePtr_t"                   " check failed ==>"  #ret_t " (" #klasscope "* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::CallablePtr_no_ptr_cv_t        , ret_t ( klasscope *       )(  __VA_ARGS__ ) FQS >, "CallablePtr_no_ptr_cv_t"         " check failed ==>"  #ret_t " (" #klasscope "* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        static_assert(       noexc FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::is_noexcept_specified                                                             , "is_noexcept_specified"           " check failed ==> " #ret_t " (" #klasscope "* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(        vary FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::is_variadic                                                                       , "is_variadic"                     " check failed ==> " #ret_t " (" #klasscope "* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);



#define FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(ret_t, funcname, PQUAL, FQS, noexc, vary, arity, ...)                                                                                                                                                                                                                                                                                                                                                                   \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE1(, static, ret_t, funcname, PQUAL, FQS, N/A, N/A, N/A, N/A, N/A, noexc, vary, arity, __VA_ARGS__ )                                                                                                                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::Callable_t                     , ret_t ( __VA_ARGS__ ) FQS >                      , "Callable_t"                      " check failed ==> " #ret_t                " * " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS                                                                                                        ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::CallableDecl_t                 , ret_t ( __VA_ARGS__ ) FQS >                      , "CallableDecl_t"                  " check failed ==> " #ret_t                " * " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS                                                                                                        ", noexcept => " #noexc ", variadic => " #vary);



#define FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(ret_t, funcname, PQUAL, FQS, cons, vol, lref, rref, nonref, noexc, vary, arity, ...)                                                                                                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE1(_unused_:: , , ret_t, funcname, PQUAL, FQS, cons, vol, lref, rref, nonref, noexc, vary, arity, __VA_ARGS__ )                                                                                                                                                                                                                                                                                                            \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::Class_t                        , _unused_>                                        , "Class_t"                         " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::Callable_t                     , void>                                            , "Callable_t"                      " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::CallableDecl_t                 , ret_t ( __VA_ARGS__ ) FQS >                      , "CallableDecl_t"                  " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::CallablePtr_no_cvrn_t          , ret_t ( _unused_:: * PQUAL )(  __VA_ARGS__ )>    , "CallablePtr_no_cvrn_t"           " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(std::same_as<FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::CallablePtr_no_cvrn_no_ptr_cv_t, ret_t ( _unused_:: *       )(  __VA_ARGS__ )>    , "CallablePtr_no_cvrn_no_ptr_cv_t" " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
        static_assert(        cons FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::is_const_qualified                                                                , "is_const_qualified"              " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(         vol FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::is_volatile_qualified                                                             , "is_volatile_qualified"           " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(        lref FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::is_lvalue_reference_qualified                                                     , "is_lvalue_reference_qualified"   " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(        rref FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::is_rvalue_reference_qualified                                                     , "is_rvalue_reference_qualified"   " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);    \
        static_assert(      nonref FunctionInfo< PQUAL decltype(&_unused_:: funcname )>::is_not_reference_qualified                                                        , "is_not_reference_qualified"      " check failed ==> " #ret_t     " (_unused_::* " #PQUAL " ptr to: " #funcname ")(" # __VA_ARGS__ ") " #FQS ", const => " #cons ", volatile => " #vol ", lref => " #lref ", rref => " #rref ", nonref => " #nonref ", noexcept => " #noexc ", variadic => " #vary);



#define FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(ret_t, extra_funcname, arity, ...)                                                                                                                                                                            \
                                                                                                                                                                                                                                                                     \
        /* /////////////////////////////////////////////////    ret_t,                  funcname,             PQUAL,                            FQS,                                          noexc,  vary,      arity,                 parameters */                \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo00##extra_funcname,                  ,                               ,  /**************************************/  not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo01##extra_funcname,                  ,                       noexcept,  /**************************************/     ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo02##extra_funcname,    const         ,                               ,  /**************************************/  not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo03##extra_funcname,    const         ,                       noexcept,  /**************************************/     ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo04##extra_funcname,          volatile,                               ,  /**************************************/  not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo05##extra_funcname,          volatile,                       noexcept,  /**************************************/     ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo06##extra_funcname,    const volatile,                               ,  /**************************************/  not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_foo07##extra_funcname,    const volatile,                       noexcept,  /**************************************/     ,   not,      arity,   __VA_ARGS__                           )    \
                                                                                                                                                                                                                                                                     \
        /* variadic specializiation tests */                                                                                                                                                                                                                         \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar00##extra_funcname,                  ,                               ,  /**************************************/  not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar01##extra_funcname,                  ,                       noexcept,  /**************************************/     ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar02##extra_funcname,    const         ,                               ,  /**************************************/  not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar03##extra_funcname,    const         ,                       noexcept,  /**************************************/     ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar04##extra_funcname,          volatile,                               ,  /**************************************/  not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar05##extra_funcname,          volatile,                       noexcept,  /**************************************/     ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar06##extra_funcname,    const volatile,                               ,  /**************************************/  not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2(   ret_t,   S_bar07##extra_funcname,    const volatile,                       noexcept,  /**************************************/     ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
                                                                                                                                                                                                                                                                     \
                                                                                                                                                                                                                                                                     \
        /* /////////////////////////////////////////////////    ret_t,                  funcname,             PQUAL,                            FQS,   cons,    vol,   lref,   rref, nonref,  noexc,  vary,      arity,                 parameters */                \
                                                                                                                                                                                                                                                                     \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo00##extra_funcname,                  ,                               ,    not,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo01##extra_funcname,                  ,     const                     ,       ,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo02##extra_funcname,                  ,           volatile            ,    not,       ,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo03##extra_funcname,                  ,                    &          ,    not,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo04##extra_funcname,                  ,                    &&         ,    not,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo05##extra_funcname,                  ,                       noexcept,    not,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo06##extra_funcname,                  ,     const          &          ,       ,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo07##extra_funcname,                  ,     const          &&         ,       ,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo08##extra_funcname,                  ,     const             noexcept,       ,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo09##extra_funcname,                  ,     const          &  noexcept,       ,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo10##extra_funcname,                  ,     const          && noexcept,       ,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo11##extra_funcname,                  ,           volatile &          ,    not,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo12##extra_funcname,                  ,           volatile &&         ,    not,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo13##extra_funcname,                  ,           volatile    noexcept,    not,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo14##extra_funcname,                  ,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo15##extra_funcname,                  ,           volatile && noexcept,    not,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo16##extra_funcname,                  ,     const volatile &          ,       ,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo17##extra_funcname,                  ,     const volatile &&         ,       ,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo18##extra_funcname,                  ,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo19##extra_funcname,                  ,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo20##extra_funcname,                  ,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo21##extra_funcname,                  ,                    &  noexcept,    not,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo22##extra_funcname,                  ,                    && noexcept,    not,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo23##extra_funcname,    const         ,                               ,    not,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo24##extra_funcname,    const         ,     const                     ,       ,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo25##extra_funcname,    const         ,           volatile            ,    not,       ,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo26##extra_funcname,    const         ,                    &          ,    not,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo27##extra_funcname,    const         ,                    &&         ,    not,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo28##extra_funcname,    const         ,                       noexcept,    not,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo29##extra_funcname,    const         ,     const          &          ,       ,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo30##extra_funcname,    const         ,     const          &&         ,       ,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo31##extra_funcname,    const         ,     const             noexcept,       ,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo32##extra_funcname,    const         ,     const          &  noexcept,       ,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo33##extra_funcname,    const         ,     const          && noexcept,       ,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo34##extra_funcname,    const         ,           volatile &          ,    not,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo35##extra_funcname,    const         ,           volatile &&         ,    not,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo36##extra_funcname,    const         ,           volatile    noexcept,    not,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo37##extra_funcname,    const         ,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo38##extra_funcname,    const         ,           volatile && noexcept,    not,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo39##extra_funcname,    const         ,     const volatile &          ,       ,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo40##extra_funcname,    const         ,     const volatile &&         ,       ,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo41##extra_funcname,    const         ,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo42##extra_funcname,    const         ,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo43##extra_funcname,    const         ,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo44##extra_funcname,    const         ,                    &  noexcept,    not,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo45##extra_funcname,    const         ,                    && noexcept,    not,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo46##extra_funcname,          volatile,                               ,    not,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo47##extra_funcname,          volatile,     const                     ,       ,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo48##extra_funcname,          volatile,           volatile            ,    not,       ,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo49##extra_funcname,          volatile,                    &          ,    not,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo50##extra_funcname,          volatile,                    &&         ,    not,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo51##extra_funcname,          volatile,                       noexcept,    not,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo52##extra_funcname,          volatile,     const          &          ,       ,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo53##extra_funcname,          volatile,     const          &&         ,       ,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo54##extra_funcname,          volatile,     const             noexcept,       ,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo55##extra_funcname,          volatile,     const          &  noexcept,       ,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo56##extra_funcname,          volatile,     const          && noexcept,       ,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo57##extra_funcname,          volatile,           volatile &          ,    not,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo58##extra_funcname,          volatile,           volatile &&         ,    not,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo59##extra_funcname,          volatile,           volatile    noexcept,    not,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo60##extra_funcname,          volatile,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo61##extra_funcname,          volatile,           volatile && noexcept,    not,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo62##extra_funcname,          volatile,     const volatile &          ,       ,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo63##extra_funcname,          volatile,     const volatile &&         ,       ,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo64##extra_funcname,          volatile,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo65##extra_funcname,          volatile,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo66##extra_funcname,          volatile,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo67##extra_funcname,          volatile,                    &  noexcept,    not,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo68##extra_funcname,          volatile,                    && noexcept,    not,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo69##extra_funcname,    const volatile,                               ,    not,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo70##extra_funcname,    const volatile,     const                     ,       ,    not,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo71##extra_funcname,    const volatile,           volatile            ,    not,       ,    not,    not,       ,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo72##extra_funcname,    const volatile,                    &          ,    not,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo73##extra_funcname,    const volatile,                    &&         ,    not,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo74##extra_funcname,    const volatile,                       noexcept,    not,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo75##extra_funcname,    const volatile,     const          &          ,       ,    not,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo76##extra_funcname,    const volatile,     const          &&         ,       ,    not,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo77##extra_funcname,    const volatile,     const             noexcept,       ,    not,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo78##extra_funcname,    const volatile,     const          &  noexcept,       ,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo79##extra_funcname,    const volatile,     const          && noexcept,       ,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo80##extra_funcname,    const volatile,           volatile &          ,    not,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo81##extra_funcname,    const volatile,           volatile &&         ,    not,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo82##extra_funcname,    const volatile,           volatile    noexcept,    not,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo83##extra_funcname,    const volatile,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo84##extra_funcname,    const volatile,           volatile && noexcept,    not,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo85##extra_funcname,    const volatile,     const volatile &          ,       ,       ,       ,    not,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo86##extra_funcname,    const volatile,     const volatile &&         ,       ,       ,    not,       ,    not,    not,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo87##extra_funcname,    const volatile,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo88##extra_funcname,    const volatile,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo89##extra_funcname,    const volatile,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo90##extra_funcname,    const volatile,                    &  noexcept,    not,    not,       ,    not,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     foo91##extra_funcname,    const volatile,                    && noexcept,    not,    not,    not,       ,    not,       ,   not,      arity,   __VA_ARGS__                           )    \
                                                                                                                                                                                                                                                                     \
        /* variadic specializiation tests */                                                                                                                                                                                                                         \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar00##extra_funcname,                  ,                               ,    not,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar01##extra_funcname,                  ,     const                     ,       ,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar02##extra_funcname,                  ,           volatile            ,    not,       ,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar03##extra_funcname,                  ,                    &          ,    not,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar04##extra_funcname,                  ,                    &&         ,    not,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar05##extra_funcname,                  ,                       noexcept,    not,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar06##extra_funcname,                  ,     const          &          ,       ,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar07##extra_funcname,                  ,     const          &&         ,       ,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar08##extra_funcname,                  ,     const             noexcept,       ,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar09##extra_funcname,                  ,     const          &  noexcept,       ,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar10##extra_funcname,                  ,     const          && noexcept,       ,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar11##extra_funcname,                  ,           volatile &          ,    not,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar12##extra_funcname,                  ,           volatile &&         ,    not,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar13##extra_funcname,                  ,           volatile    noexcept,    not,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar14##extra_funcname,                  ,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar15##extra_funcname,                  ,           volatile && noexcept,    not,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar16##extra_funcname,                  ,     const volatile &          ,       ,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar17##extra_funcname,                  ,     const volatile &&         ,       ,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar18##extra_funcname,                  ,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar19##extra_funcname,                  ,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar20##extra_funcname,                  ,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar21##extra_funcname,                  ,                    &  noexcept,    not,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar22##extra_funcname,                  ,                    && noexcept,    not,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar23##extra_funcname,    const         ,                               ,    not,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar24##extra_funcname,    const         ,     const                     ,       ,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar25##extra_funcname,    const         ,           volatile            ,    not,       ,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar26##extra_funcname,    const         ,                    &          ,    not,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar27##extra_funcname,    const         ,                    &&         ,    not,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar28##extra_funcname,    const         ,                       noexcept,    not,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar29##extra_funcname,    const         ,     const          &          ,       ,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar30##extra_funcname,    const         ,     const          &&         ,       ,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar31##extra_funcname,    const         ,     const             noexcept,       ,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar32##extra_funcname,    const         ,     const          &  noexcept,       ,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar33##extra_funcname,    const         ,     const          && noexcept,       ,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar34##extra_funcname,    const         ,           volatile &          ,    not,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar35##extra_funcname,    const         ,           volatile &&         ,    not,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar36##extra_funcname,    const         ,           volatile    noexcept,    not,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar37##extra_funcname,    const         ,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar38##extra_funcname,    const         ,           volatile && noexcept,    not,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar39##extra_funcname,    const         ,     const volatile &          ,       ,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar40##extra_funcname,    const         ,     const volatile &&         ,       ,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar41##extra_funcname,    const         ,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar42##extra_funcname,    const         ,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar43##extra_funcname,    const         ,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar44##extra_funcname,    const         ,                    &  noexcept,    not,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar45##extra_funcname,    const         ,                    && noexcept,    not,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar46##extra_funcname,          volatile,                               ,    not,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar47##extra_funcname,          volatile,     const                     ,       ,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar48##extra_funcname,          volatile,           volatile            ,    not,       ,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar49##extra_funcname,          volatile,                    &          ,    not,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar50##extra_funcname,          volatile,                    &&         ,    not,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar51##extra_funcname,          volatile,                       noexcept,    not,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar52##extra_funcname,          volatile,     const          &          ,       ,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar53##extra_funcname,          volatile,     const          &&         ,       ,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar54##extra_funcname,          volatile,     const             noexcept,       ,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar55##extra_funcname,          volatile,     const          &  noexcept,       ,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar56##extra_funcname,          volatile,     const          && noexcept,       ,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar57##extra_funcname,          volatile,           volatile &          ,    not,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar58##extra_funcname,          volatile,           volatile &&         ,    not,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar59##extra_funcname,          volatile,           volatile    noexcept,    not,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar60##extra_funcname,          volatile,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar61##extra_funcname,          volatile,           volatile && noexcept,    not,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar62##extra_funcname,          volatile,     const volatile &          ,       ,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar63##extra_funcname,          volatile,     const volatile &&         ,       ,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar64##extra_funcname,          volatile,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar65##extra_funcname,          volatile,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar66##extra_funcname,          volatile,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar67##extra_funcname,          volatile,                    &  noexcept,    not,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar68##extra_funcname,          volatile,                    && noexcept,    not,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
                                                                                                                                                                                                                                                                     \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar69##extra_funcname,    const volatile,                               ,    not,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar70##extra_funcname,    const volatile,     const                     ,       ,    not,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar71##extra_funcname,    const volatile,           volatile            ,    not,       ,    not,    not,       ,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar72##extra_funcname,    const volatile,                    &          ,    not,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar73##extra_funcname,    const volatile,                    &&         ,    not,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar74##extra_funcname,    const volatile,                       noexcept,    not,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar75##extra_funcname,    const volatile,     const          &          ,       ,    not,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar76##extra_funcname,    const volatile,     const          &&         ,       ,    not,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar77##extra_funcname,    const volatile,     const             noexcept,       ,    not,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar78##extra_funcname,    const volatile,     const          &  noexcept,       ,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar79##extra_funcname,    const volatile,     const          && noexcept,       ,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar80##extra_funcname,    const volatile,           volatile &          ,    not,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar81##extra_funcname,    const volatile,           volatile &&         ,    not,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar82##extra_funcname,    const volatile,           volatile    noexcept,    not,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar83##extra_funcname,    const volatile,           volatile &  noexcept,    not,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar84##extra_funcname,    const volatile,           volatile && noexcept,    not,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar85##extra_funcname,    const volatile,     const volatile &          ,       ,       ,       ,    not,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar86##extra_funcname,    const volatile,     const volatile &&         ,       ,       ,    not,       ,    not,    not,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar87##extra_funcname,    const volatile,     const volatile    noexcept,       ,       ,    not,    not,       ,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar88##extra_funcname,    const volatile,     const volatile &  noexcept,       ,       ,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar89##extra_funcname,    const volatile,     const volatile && noexcept,       ,       ,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar90##extra_funcname,    const volatile,                    &  noexcept,    not,    not,       ,    not,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )    \
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3(   ret_t,     bar91##extra_funcname,    const volatile,                    && noexcept,    not,    not,    not,       ,    not,       ,      ,      arity,   __VA_ARGS__   __VA_OPT__(,)    ...    )

        ///
        /// fat::pound
        ///

        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(void, _a, 0, )
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(void, _b, 1, int)
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(void, _c, 2, int, double)
        FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR(float, _d, 0, )


// NOLINTEND(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif

#undef FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR
#undef FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE3
#undef FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE2
#undef FATLIB_FUNC_INFO_STATIC_ASSERT_TESTS_GENERATOR_BASE1
    };
}

#endif

// NOLINTEND(altera-struct-pack-align, fuchsia-virtual-inheritance)
